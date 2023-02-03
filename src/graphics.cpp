#include "graphics.h"


void Screen::fill(char c) {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			pixels[i][j] = c;
}

void Screen::clear(bool border) {
	fill(' ');
	if (border) {
		for (int i = 0; i < width; i++) {
			pixels[i][0] = '-';
			pixels[i][height-1] = '-';
		}
		for (int i = 0; i < height; i++) {
			pixels[0][i] = '|';
			pixels[width-1][i] = '|';
		}
		pixels[0][0] = '+';
		pixels[width-1][0] = '+';
		pixels[0][height-1] = '+';
		pixels[width-1][height-1] = '+';
	}
}

void Screen::paste_element(unsigned int x, unsigned int y, std::vector<std::vector<char> > image)
{
	if (image.size() <= 0 || x+image.size() > width || y+image[0].size() > height) return;
	for (int i = 0; i < image.size(); i++)
		for (int j = 0; j < image[0].size(); j++)
			pixels[x+i][y+j] = image[i][j];
}

void Screen::print() {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++)
			std::cout << pixels[i][j];
		std::cout << std::endl;
	}
}

std::vector<std::vector<char> > level_block_visual(int lvl, short int succes_rate)
{
	unsigned int h = 5;
	unsigned int w = h*2;

	// Fill square
	std::vector<std::vector<char> > final;
	for (int i = 0; i < w; i++) {
		std::vector<char> y;
		for (int j = 0; j < h; j++) {
			y.push_back(' ');
		}
		final.push_back(y);
	}

	// Create borders
	for (int i = 0; i < w; i++) {
			final[i][0] = '-';
			final[i][h-1] = '-';
	}
	for (int i = 0; i < h; i++) {
		final[0][i] = '|';
		final[w-1][i] = '|';
	}
	final[0][0] = '+';
	final[w-1][0] = '+';
	final[0][h-1] = '+';
	final[w-1][h-1] = '+';

	// Write info
	unsigned int y = h*0.2;
	unsigned int x = (w-5)*0.5;
	if (lvl >= 10) x = (w-6)*0.5;

	final[x][y] = 'l';
	final[x+1][y] = 'v';
	final[x+2][y] = 'l';
	final[x+3][y] = '-';
	std::string s = std::to_string(lvl);
	for (int i = 0; i < s.size(); i++)
		final[x+4+i][y] = s[i];

	y = h*0.6;
	if (succes_rate > -1) {
		std::string s = std::to_string(succes_rate);
		x = (w-s.size()-1)*0.5;
		for (int i = 0; i < s.size(); i++)
			final[x+i][y] = s[i];
		final[x+s.size()][y] = '%';
	} else {
		x = (w-4)*0.5;
		final[x][y] = 'n';
		final[x+1][y] = 'e';
		final[x+2][y] = 'w';
		final[x+3][y] = '!';
	}

	return final;
}
