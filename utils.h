#ifndef UTILS
#define UTILS

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <random>

struct Kanji
{
	std::string symbol;
	std::string meaning;
	std::string pronunciation = "";
};


template <typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

bool compareStrings(std::string s1, std::string s2, std::string to);

std::vector<std::string> getFileLines(std::string path);

std::vector<Kanji> random_kanji_set(std::vector<Kanji> list, int amount = 5);


#endif
