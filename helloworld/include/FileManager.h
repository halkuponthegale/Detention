#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Object.h"
class File {
public:
	static std::vector<Object> loadLevel(std::string fileName){
		std::vector<Object> out;
		std::ifstream in(fileName.c_str());
		std::string line;
		double x,y;
		int w,h;
		bool solid;
		while(std::getline(in, line))
		{
	    std::stringstream   linestream(line);
	    linestream >> x >> y >> w >> h >> solid;
			out.push_back(Object(x,y,w,h,solid));
		}
		return out;
	}

};
