#include <string>
#include <vector>
#include <iostream>

#include "utils.h"


std::vector<Kanji> read_kanji(std::string file)
{
	std::vector<Kanji> kanjis;
	std::vector<std::string> lines = getFileLines(file);
	for (int i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> words = split(lines[i], ' ');
		Kanji new_kanji;
		new_kanji.meaning = words[0];
		new_kanji.symbol = words[1];
		if (words.size() > 2)
			new_kanji.pronunciation = words[3];
		kanjis.push_back(new_kanji);
	}
	return kanjis;
}

void print_kanjis(std::vector<Kanji> kanjis) {
	for (auto kanji : kanjis)
		std::cout << kanji.symbol << " - " << kanji.meaning << std::endl;
}

void play_random()
{
	std::vector<Kanji> kanji = read_kanji("kanji.txt");
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
}

void play_testmode()
{
	// Load kanji
	std::vector<Kanji> kanji = read_kanji("kanji.txt");
	srand(time(NULL));

	while (1)
	{
		int index = rand()%kanji.size();

		// Remove the requested kanji
		Kanji asked = kanji[index];
		kanji.erase(kanji.begin() + index);

		// Generate the possible answers
		std::vector<Kanji> options = random_kanji_set(kanji);
		options.insert(options.begin()+(rand()%options.size()), asked);

		// Give the user the task
		std::cout << "What kanji represents '" << asked.meaning << "' ?" << std::endl;
		for (int i = 0; i < options.size(); i++)
			std::cout << i+1 << " - " << options[i].symbol << "    ";
		std::cout << "\n";

		while (1)
		{
			std::string input;
			std::cout << asked.meaning << " -> ";
			std::cin >> input;

			if (input == "/exit")
				return;

			int answered = std::stoi(input);

			if (answered > options.size() || answered < 1)
				std::cout << "Your answer must be between 1 and " << options.size() << "." << std::endl;
			else if (options[answered-1].meaning == asked.meaning) {
				std::cout << "\033[1;32mCorrect! :D\033[0m\n" << std::endl;
				break;
			} else {
				std::cout << "\033[1;31mIncorrect! D:\033[0m" << std::endl;
				std::cout << options[answered-1].symbol << " means " << options[answered-1].meaning << std::endl;
			}

			if (kanji.size() == 0) {
				std::cout << "You got all Kanji!!!" << std::endl;
				return;
			}
		}
	}
}

void play_practice()
{
	std::cout << "Game-mode not avalible yet." << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "Welcome to JapanTerminal!" << std::endl;
	std::cout << "  /\\____/\\" << std::endl;
	std::cout << " /        \\" << std::endl;
	std::cout << "|   U   U  |" << std::endl;
	std::cout << "|  .: Y :. |" << std::endl;
	std::cout << " \\________/" << std::endl;

	std::cout << "Choose your game mode: " << std::endl;
	std::cout << "1 - random kanji" << std::endl;
	std::cout << "2 - practice" << std::endl;
	std::cout << "3 - test mode" << std::endl;
	std::cout << "> ";

	std::string input;
	std::cin >> input;
	if (input == "1")
		play_random();
	else if (input == "2")
		play_practice();
	else if (input == "3")
		play_testmode();
	else
		std::cout << "Invalid Input." << std::endl;

	return 0;
}
