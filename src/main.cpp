// g++ main.cpp -o p -std=c++11 utils.cpp app.cpp graphics.cpp
#include "graphics.h"
#include "app.h"


int main(int argc, char** argv)
{
	App app;
	app.run();
	/*Screen s;
	s.clear(true);
	std::vector<std::vector<char> > image = level_block_visual(10, 888);
	s.paste_element(10, 10, image);
	s.print();*/
	return 0;
}
