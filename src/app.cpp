#include "app.h"


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

std::vector<Character> App::read_alphabet(std::string file)
{
	std::vector<Character> characters;
	std::vector<std::string> lines = getFileLines("../data/" + file);
	for (int i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> words = split(lines[i], ' ');
		Character new_char;
		new_char.symbol = words[0];
		new_char.pronunciation = words[1];
		characters.push_back(new_char);
	}
	return characters;
};

void App::print_kanjis(std::vector<Kanji> kanjis) {
	for (auto kanji : kanjis)
		std::cout << kanji.symbol << " - " << kanji.meaning << std::endl;
};

void App::play_hardmode()
{
	std::vector<Kanji> kanji = read_kanji("../data/kanji.txt");
	srand(time(NULL));
	int index = rand()%kanji.size();

	std::cout << "What kanji is this?" << std::endl;

	while (1)
	{
		std::cout << kanji[index].symbol << " - ";
		std::string input;
		std::cin >> input;
		if (input == "/idk")
			std::cout << "The correct answer is: " << kanji[index].meaning << std::endl;
		else if (input == "/printlist")
			print_kanjis(kanji);
		else if (input == "/exit")
			break;
		else if (input == kanji[index].meaning) {
			std::cout << "\033[1;32mCorrect! :D\033[0m\n" << std::endl;
			kanji.erase(kanji.begin() + index);
			index = rand()%kanji.size();
		} else
			std::cout << "\033[1;31mIncorrect! D:\033[0m\n" << std::endl;

		if (kanji.size() == 0) {
			std::cout << "You got all Kanji!!!" << std::endl;
			break;
		}
	}
};

void App::set_learning(unsigned int set_size)
{
	std::vector<Kanji> kanji = read_kanji("../data/kanji.txt");
	if (kanji.size() < set_size) {
		std::cout << "not enough Kanji!" << std::endl;
		return;
	}
	unsigned int set_count = kanji.size()/set_size;
	std::vector< std::vector<Kanji> > sets;
	for (int i = 0; i < set_count; i++) {
		std::vector<Kanji> new_set;
		for (int j = 0; j < set_size; j++) {
			new_set.push_back(kanji[(i*set_size)+j]);
		}
		sets.push_back(new_set);
	}
	unsigned int set_index = 0;
	print_kanjis(sets[set_index]);
	while(1)
	{
		std::string input;
		std::cout << "> ";
		std::cin >> input;

		if (input == "/exit") break;
		if (input == "/next")
		{
			set_index++;
			print_kanjis(sets[set_index]);
		}
	}
};

void App::play_testmode(std::string file, bool find_symbol)
{
	// Load kanji
	std::vector<Kanji> kanji = read_kanji("../data/" + file);
	if (kanji.size() < 6) {
		std::cout << "not enough Kanji!" << std::endl;
		return;
	}
	std::vector<std::string> mistakes;

	srand(time(NULL));

	unsigned int answered_count = 0;
	unsigned int correct = 0;

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
			return;
		}
		std::cout << "_______________________" << std::endl;
		std::cout << "                       " << std::endl;
		std::cout << "Success rate: " << success_rate(answered_count, correct)*100 << "%" << std::endl;
		std::cout << "answered_count: " << answered_count << std::endl;
		std::cout << "correct: " << correct << std::endl;
		std::cout << "_______________________" << std::endl;

		// Give the user the task
		if (find_symbol) {
			std::vector<std::string> meanings = split(asked.meaning, '/');
			std::cout << "What kanji represents the following meanings?" << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
			for (auto mean : meanings)
				std::cout << mean << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
			for (int i = 0; i < options.size(); i++)
				std::cout << i+1 << " - " << options[i].symbol << "    ";
		} else {
			std::cout << "What is the meaning of '" << asked.symbol << "' ?" << std::endl;
			for (int i = 0; i < options.size(); i++)
				std::cout << i+1 << " - " << options[i].meaning << "    ";
		}
		std::cout << "\n";

		bool first_guess = true;

		while (1)
		{
			std::string input;
			std::cout << "> ";
			std::cin >> input;

			if (input == "/exit") {
				if (file.rfind("mistakes", 0) != 0) {
					std::ofstream mistakes_file("../data/mistakes_in_" + file);
    				std::ostream_iterator<std::string> output_iterator(mistakes_file, "\n");
    				std::copy(mistakes.begin(), mistakes.end(), output_iterator);
				}
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
				if (find_symbol)
					std::cout << options[answered-1].symbol << " means " << options[answered-1].meaning << "\n" << std::endl;
				else
					std::cout << options[answered-1].meaning << " is written " << options[answered-1].symbol << "\n" << std::endl;
				if (first_guess)
					mistakes.push_back(asked.meaning + " " + asked.symbol + " " + asked.pronunciation);
				first_guess = false;
			}
		}
	}
};

void App::play_practice()
{
	std::cout << "Game-mode not avalible yet." << std::endl;
};

void App::run()
{
	std::cout << "Welcome to JapanTerminal!" << std::endl;
	std::cout << "  /\\____/\\" << std::endl;
	std::cout << " /        \\" << std::endl;
	std::cout << "|   U   U  |" << std::endl;
	std::cout << "|  .: Y :. |" << std::endl;
	std::cout << " \\________/" << std::endl;

	std::cout << "What do you want to practice?" << std::endl;
	std::cout << "1 - Katakana" << std::endl;
	std::cout << "2 - Hiragana" << std::endl;
	std::cout << "3 - Kanji" << std::endl;
	std::cout << "> ";

	std::string input;
	std::cin >> input;

	if (input == "1")
	{
		std::cout << "Choose your game mode: " << std::endl;
		std::cout << "1 - test mode (find symbol)" << std::endl;
		std::cout << "2 - test mode (find meaning)" << std::endl;
		std::cout << "> ";

		std::cin >> input;
		if (input == "1")
			play_testmode("katakana.txt");
		else if (input == "2")
			play_testmode("katakana.txt", false);
		else
			std::cout << "Invalid Input." << std::endl;
	}
	else if (input == "2")
	{
		std::cout << "Choose your game mode: " << std::endl;
		std::cout << "1 - test mode (find symbol)" << std::endl;
		std::cout << "2 - test mode (find meaning)" << std::endl;
		std::cout << "> ";

		std::cin >> input;
		if (input == "1")
			play_testmode("hiragana.txt");
		else if (input == "2")
			play_testmode("hiragana.txt", false);
		else
			std::cout << "Invalid Input." << std::endl;
	}
	else if (input == "3")
	{
		std::cout << "Choose your game mode: " << std::endl;
		std::cout << "1 - practice mistakes" << std::endl;
		std::cout << "2 - test mode (find symbol)" << std::endl;
		std::cout << "3 - test mode (find meaning)" << std::endl;
		std::cout << "4 - hard mode" << std::endl;
		std::cout << "5 - set learning" << std::endl;
		std::cout << "> ";

		std::cin >> input;
		if (input == "1")
			play_testmode("mistakes_in_kanji.txt");
		else if (input == "2")
			play_testmode("kanji1-500.txt");
		else if (input == "3")
			play_testmode("kanji1-500.txt", false);
		else if (input == "4")
			play_hardmode();
		else if (input == "5")
			set_learning();
		else
			std::cout << "Invalid Input." << std::endl;
	} else
		std::cout << "Invalid Input." << std::endl;

};
