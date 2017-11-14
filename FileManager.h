//FileManager.h
#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "Object.h"
class File {
public:
	static std::vector<std::unique_ptr<Actor>> loadLevel(std::string fileName){
		std::vector<std::unique_ptr<Actor>> out;
		std::ifstream in(fileName.c_str());
		std::string line;
		double x,y;
		int w,h;
		bool solid;
		std::string objType;
		while(std::getline(in, line))
		{
	    std::stringstream   linestream(line);
	    linestream >> x >> y >> w >> h >> solid >> objType;
			std::cout << h;
			if(objType.compare("Object")==0){
				std:: cout << "ahhhh";
				out.emplace_back(std::unique_ptr<Actor>(new Object(x,y,w,h,solid)));
				//out.push_back(Object(x,y,w,h,solid));
			}
			//out.push_back(Object(x,y,w,h,solid));
		}
		return out;
	}

};

#endif
