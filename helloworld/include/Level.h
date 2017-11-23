#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <fstream>
#include "Object.h"
#include "Box.h"

using namespace std;

class Level{
public:
  // Level(std::vector<std::unique_ptr<Actor>> walls, std::vector<std::unique_ptr<Actor>> machines, std::vector<std::unique_ptr<Actor>> objects){
  //   this->walls = walls;
  //   this->machines = machines;
  //   this->objects = objects;
  // }
  Level(std::string file){
    //parse level from txt file
    // std::cout << file << "\n";

    ifstream inFile;
    inFile.open(file);

    if(!inFile){
      cerr << "File " << file << " does not exist" << "\n";
      exit(1);
    }

    // placeholder box, never used
    boxes.push_back(unique_ptr<Box>(new Box(0,0)));

    // read in x coord, y coord, object
    double x,y;
    string type;

    while (inFile >> x >> y >> type){
      cout << x << " " << y << " " << type << "\n";
      if(type == "box"){
        boxes.push_back(unique_ptr<Box>(new Box(x, y)));
      }
    }

    inFile.close();


  }

  std::vector<std::unique_ptr<Box>> const& getBoxes(){
    return boxes;
  }


private:
  std::vector<std::unique_ptr<Box>> boxes;
  std::vector<std::unique_ptr<Actor>> walls;
  std::vector<std::unique_ptr<Actor>> machines;
  std::vector<std::unique_ptr<Actor>> objects;
};



#endif
