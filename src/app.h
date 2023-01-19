#include <string>
#include <vector>
#include <iostream>

#include "utils.h"


class App
{
	std::vector<Kanji> read_kanji(std::string file);
	std::vector<Character> read_alphabet(std::string file);

	void print_kanjis(std::vector<Kanji> kanjis);
	void play_hardmode();
	void set_learning(unsigned int set_size = 6);
	void play_testmode(std::string file, bool find_symbol = true);
	void play_practice();

public:
	void run();
};
