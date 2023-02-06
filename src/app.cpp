#include "app.h"

std::vector<std::string> App::getFileWords(std::string file_path)
{
    std::ifstream file(file_path);
    std::vector<std::string> words;
    for(std::string word; file >> word; )
        words.push_back(word);
    return words;
}

std::vector<Kanji> App::read_kanji(std::string file)
{
	std::vector<Kanji> kanjis;
	std::vector<std::string> lines = getFileLines("../data/" + file);
	for (int i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> words = split(lines[i], ' ');
		if (words.size() > 1) {
			Kanji new_kanji;
			new_kanji.symbol = words[0];
			new_kanji.meaning = words[1];
			if (words.size() > 2)
				new_kanji.pronunciation = words[3];
			kanjis.push_back(new_kanji);
		}
	}
	return kanjis;
}

void App::print_kanjis(std::vector<Kanji> kanjis) {
	for (auto kanji : kanjis)
		std::cout << kanji.symbol << " - " << kanji.meaning << std::endl;
};

void App::play_testmode(int level, bool inverted)
{
	// Load kanji
	std::vector<Kanji> all_kanji = read_kanji("../data/kanji1-500.txt");
	if (all_kanji.size() < 6) {
		std::cout << "not enough Kanji!" << std::endl;
		return;
	}
	std::vector<std::string> success_rates = getFileWords("../data/success_rate1-500.txt");

	srand(time(NULL));

	unsigned int answered_count = 0;
	unsigned int correct = 0;

	std::vector<Kanji>::const_iterator first = all_kanji.begin()+(level*level_size);
	std::vector<Kanji>::const_iterator last  = all_kanji.begin()+((level+1)*level_size);
	std::vector<Kanji> kanji(first, last);

	while (1)
	{
		int index = rand()%kanji.size();

		// Remove the requested kanji
		Kanji asked = kanji[index];
		kanji.erase(kanji.begin() + index);

		// Generate the possible answers
		std::vector<Kanji> options = random_kanji_set(kanji);
		options.insert(options.begin()+(rand()%options.size()), asked);

		if (kanji.size() <= options.size()-1) {
			std::cout << "You got all Kanji!!!" << std::endl;
			int tmp = std::stoi(success_rates[level]);
			if (answered_count >= level_size*0.5 && tmp < success_rate(answered_count, correct)*100)
				success_rates[level] = std::to_string(static_cast<int>(success_rate(answered_count, correct)*100));
			std::ofstream mistakes_file("../data/success_rate1-500.txt");
			std::ostream_iterator<std::string> output_iterator(mistakes_file, "\n");
			std::copy(success_rates.begin(), success_rates.end(), output_iterator);
			return;
		}
		std::cout << "_______________________" << std::endl;
		std::cout << "                       " << std::endl;
		std::cout << "Level: " << level+1 << std::endl;
		std::cout << "Success rate: " << success_rate(answered_count, correct)*100 << "%" << std::endl;
		std::cout << "answered_count: " << answered_count << std::endl;
		std::cout << "correct: " << correct << std::endl;
		std::cout << "_______________________" << std::endl;

		// Give the user the task
		if (inverted) {
			std::vector<std::string> meanings = split(asked.meaning, '/');
			std::cout << "What kanji represents the following meanings?" << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
			for (auto mean : meanings)
				std::cout << mean << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
			for (int i = 0; i < options.size(); i++)
				std::cout << i+1 << " - " << options[i].symbol << "    ";
			std::cout << "\n";
		} else {
			std::cout << "What is the meaning of '" << asked.symbol << "' ?\n" << std::endl;
			for (int i = 0; i < options.size(); i++)
			{
				std::vector<std::string> meanings = split(options[i].meaning, '/');
				std::cout << i+1 << " - ";
				for (auto mean : meanings)
					std::cout << mean << std::endl;
				std::cout << std::endl;
			}
		}

		bool first_guess = true;

		while (1)
		{
			std::string input;
			std::cout << "> ";
			std::cin >> input;

			if (input == "/exit") {
				int tmp = std::stoi(success_rates[level]);
				if (answered_count >= level_size*0.5 && tmp < success_rate(answered_count, correct)*100)
					success_rates[level] = std::to_string(static_cast<int>(success_rate(answered_count, correct)*100));
				std::ofstream mistakes_file("../data/success_rate1-500.txt");
				std::ostream_iterator<std::string> output_iterator(mistakes_file, "\n");
				std::copy(success_rates.begin(), success_rates.end(), output_iterator);
				return;
			} // Should store the succes rate and question count in a file

			int answered = std::stoi(input);

			if (answered > options.size() || answered < 1)
				std::cout << "Your answer must be between 1 and " << options.size() << "." << std::endl;
			else if (options[answered-1].meaning == asked.meaning) {
				std::cout << "\033[1;32mCorrect! :D\033[0m\n" << std::endl;
				if (first_guess) correct++;
				answered_count++;
				break;
			} else {
				std::cout << "\033[1;31mIncorrect! D:\033[0m" << std::endl;
				if (inverted)
					std::cout << options[answered-1].symbol << " means " << options[answered-1].meaning << "\n" << std::endl;
				else
					std::cout << options[answered-1].meaning << " is written " << options[answered-1].symbol << "\n" << std::endl;
				first_guess = false;
			}
		}
	}
};

void App::run()
{
	std::cout << "   ____" << std::endl;
	std::cout << "  / ___ \\" << std::endl;
	std::cout << " / /   \\|                                /\\____/\\" << std::endl;
	std::cout << " | |                                    /        \\" << std::endl;
	std::cout << " | |                                   |   U   U  |" << std::endl;
	std::cout << " \\ \\-----------------------------------|  .: Y :. |" << std::endl;
	std::cout << "  |              Japan Terminal         \\________/" << std::endl;
	std::cout << "  |                   :D                      |" << std::endl;
	std::cout << "  | |-| |-------------------------------| |-| |" << std::endl;
	std::cout << "  | | | |                               | | | |" << std::endl;
	std::cout << "  | | | |                               | | | |" << std::endl;
	std::cout << "   ''' '''                               ''' '''" << std::endl;

	std::cout << "What do you want to practice?" << std::endl;
	std::cout << "1 - Katakana" << std::endl;
	std::cout << "2 - Hiragana" << std::endl;
	std::cout << "3 - Kanji" << std::endl;
	std::cout << "> ";

	std::string input;
	std::cin >> input;

	if (input == "1")
		std::cout << "Not implemented." << std::endl;
	else if (input == "2")
		std::cout << "Not implemented." << std::endl;
	else if (input == "3")
	{
		std::cout << "Choose your game mode: " << std::endl;
		std::cout << "1 - test mode (find symbol)" << std::endl;
		std::cout << "2 - test mode (find meaning)" << std::endl;
		std::cout << "> ";
		std::cin >> input;

		bool find_meaning = false;
		if (input == "1")
			find_meaning = true;

		std::vector<std::string> success_rates = getFileWords("../data/success_rate1-500.txt");
		Screen s;
		s.clear(true);
		for (int i = 0; i < 7; i++) {
			std::vector<std::vector<char> > image = level_block_visual(i+1, std::stoi(success_rates[i]));
			int x = (i+1)*10;
			s.paste_element(x, 10, image);
		}
		s.print();

		std::cout << "Choose a level: ";
		std::cin >> input;
		play_testmode(std::stoi(input)-1, find_meaning);

	} else
		std::cout << "Invalid Input." << std::endl;

};
