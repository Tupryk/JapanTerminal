#ifndef GRAPHICS
#define GRAPHICS

#include <string>
#include <vector>
#include <iostream>


class Screen
{
	const static unsigned int width = 100;
	const static unsigned int height = 30;
	char pixels[width][height];

public:
	void fill(char c);
	void clear(bool border = false);
	void paste_element(unsigned int x, unsigned int y, std::vector<std::vector<char> > image);
	void print();
};

std::vector<std::vector<char> > level_block_visual(int lvl, short int succes_rate = -1);


#endif
