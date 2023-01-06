#include <string>
#include <vector>
#include <iostream>

#include "utils.h"

struct Kanji
{
	std::string symbol;
	std::string meaning;
	std::string pronunciation = "";
};

std::vector<Kanji> read_kanji (std::string file)
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

int main(int argc, char** argv)
{
	std::cout << "Welcome to JapanTerminal!" << std::endl;

	std::vector<Kanji> kanji = read_kanji("kanji.txt");
	srand(time(NULL));
	int index = rand()%kanji.size();

	std::cout << "What kanji is this?" << std::endl;

	while (1)
	{
		std::cout << kanji[index].symbol << " - ";
		std::string input;
		std::cin >> input;
		if (input == "/giveup")
			std::cout << "The correct answer is: " << kanji[index].meaning << std::endl;
		else if (input == "/printlist")
			print_kanjis(kanji);
		else if (input == "/exit")
			break;
		else if (input == kanji[index].meaning) {
			std::cout << "Correct! :D" << std::endl;
			kanji.erase(kanji.begin() + index);
			index = rand()%kanji.size();
		} else
			std::cout << "Incorrect! D:" << std::endl;

		if (kanji.size() == 0) {
			std::cout << "You got all Kanji!!!" << std::endl;
			break;
		}
	}

	return 0;
}
