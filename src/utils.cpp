#include "utils.h"


template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

bool compareStrings(std::string s1, std::string s2, std::string to) {return (abs(s1.compare(to)) < abs(s2.compare(to)));}

std::vector<std::string> getFileLines(std::string path)
{
    std::ifstream file(path);
    std::vector<std::string> words;
    for(std::string word; getline(file, word);)
        words.push_back(word);
    return words;
}

std::vector<Kanji> random_kanji_set(std::vector<Kanji> list, int amount)
{
    std::vector<Kanji> result;
    for (int i = 0; i < amount; i++) {
        int index = rand()%list.size();
        result.push_back(list[index]);
        list.erase(list.begin() + index);
    }
    return result;
}

float success_rate(unsigned int answered, unsigned int correct) {
    if (answered > 0)
        return static_cast<float>(correct)/static_cast<float>(answered);
    return 1;
}
