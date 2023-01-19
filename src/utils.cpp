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

void draw_graph(std::vector<float> nums, std::string title)
{
    int rows = 15;
    int columns = 20;
    int colums = nums.size();
    int dif = nums.size()-columns;
    if (nums.size() < columns) {
        columns = nums.size();
        dif = 0;
    }
    std::cout << "     "; // Space for numbers
    if (title.length() < columns) {
        int line_len = (columns-((title.length()+2)*0.5))*0.5;
        for (int i = 0; i < line_len; i++)
            std::cout << "--";
        std::cout << " " << title << " ";
        for (int i = 0; i < line_len; i++)
            std::cout << "--";
        std::cout << "\n";
    } else {
        std::cout << title << std::endl;
    }
    for (int j = 0; j < rows; j++) {
        float perc = static_cast<float>(rows-j)/static_cast<float>(rows);
        for (int i = 0; i < columns; i++)
        {
            { // Draw percetages on graph
                int tmp = perc*100;
                if (i == 0) { std::cout << tmp;
                if (tmp < 10) std::cout << "  % ";
                else if (tmp < 100) std::cout << " % ";
                else std::cout << "% "; }
            }
            if (nums[i+dif] > perc)
                std::cout << "\033[1;34m# \033[0m";
            else
                std::cout << "  ";
        }
        std::cout << "\n";
    }
}
