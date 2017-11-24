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

    ifstream inFile;
    inFile.open(file);

    if(!inFile){
      cerr << "File " << file << " does not exist" << "\n";
      exit(1);
    }

    // placeholder box, never used
    //boxes.push_back(unique_ptr<Box>(new Box(0,0)));

    // read in x coord, y coord, object
    double x,y;
    string type;

    while (inFile >> x >> y >> type){

      cout << x << " " << y << " " << type << "\n";

      if(type == "box"){
        boxes.push_back(unique_ptr<Box>(new Box(x, y)));
      }

      if(type == "builder"){
        builders.push_back(unique_ptr<Builder>(new Builder(x, y)));
      }

      if(type == "mobile"){
        mobiles.push_back(unique_ptr<Mobile>(new Mobile(x, y)));
      }

      if(type == "launcher"){
        launchers.push_back(unique_ptr<Launcher>(new Launcher(x, y)));
      }
    }

    inFile.close();


  }

  std::vector<std::unique_ptr<Box>> const& getBoxes(){
    return boxes;
  }

  std::vector<std::unique_ptr<Builder>> const& getBuilders(){
    return builders;
  }

  std::vector<std::unique_ptr<Mobile>> const& getMobiles(){
    return mobiles;
  }

  std::vector<std::unique_ptr<Launcher>> const& getLaunchers(){
    return launchers;
  }

private:
  std::vector<std::unique_ptr<Box>> boxes;
  std::vector<std::unique_ptr<Builder>> builders;
  std::vector<std::unique_ptr<Mobile>> mobiles;
  std::vector<std::unique_ptr<Launcher>> launchers;

  std::vector<std::unique_ptr<Actor>> walls;
  std::vector<std::unique_ptr<Actor>> machines;
  std::vector<std::unique_ptr<Actor>> objects;
};



#endif
