#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "utils.h"
#include "graphics.h"


class App
{
	const unsigned int level_size = 20;
	std::vector<Kanji> read_kanji(std::string file);
	std::vector<Character> read_alphabet(std::string file);
	std::vector<std::string> getFileWords(std::string file);

	void print_kanjis(std::vector<Kanji> kanjis);
	void play_hardmode();
	void set_learning(unsigned int set_size = 6);
	void play_testmode(int level, bool inverted = true);
	void play_practice();

public:
	void run();
};
