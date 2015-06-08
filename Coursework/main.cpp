/*
===========================================================================
This project distributed under GNU GPLv3
Copyright (C) 2015 Chabanenko Dmitry
This file is part of the Tanks GPL Source Code.
Tanks Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Tanks Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Tanks Source Code.  If not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

#include "Game.h"
#include <fstream>
#include <string>
#include "gamedef.h"
#include <iostream>


si width = 1920;
si height = 1080;


int main()
{
	srand(time(0));

	std::ofstream *fout = new std::ofstream;
	std::ifstream *fin = new std::ifstream;

	char lineOne[15];
	char lineTwo[15];

	std::string widthStr;
	std::string heightStr;

	fin->open("config.cfg");
	if (!*fin) {
		fout->open("config.cfg");
		*fout << "WIDTH=1920;" << std::endl;
		*fout << "HEIGHT=1080;";
		fout->close();
	}
	fin->close();

	fin->open("config.cfg");
	*fin >> lineOne >> lineTwo;
	fin->close();

	for (int i = 6; ; ++i) {
		if (lineOne[i] != ';') {
			widthStr = widthStr + lineOne[i];
		}
		else break;
	}

	for (int i = 7; ; ++i) {
		if (lineOne[i] != '\0') {
			heightStr = heightStr + lineTwo[i];
		}
		else break;
	}

	width = stoi(widthStr);
	height = stoi(heightStr);

	delete fout;
	delete fin;

	Game game;
	game.run();

	return 0;
}