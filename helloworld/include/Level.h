#include <vector>
#include <string>
#include "Object.h"
class Level{
public:
  Level(std::vector<std::unique_ptr<Actor>> walls, std::vector<std::unique_ptr<Actor>> machines, std::vector<std::unique_ptr<Actor>> objects){
    this->walls = walls;
    this->machines = machines;
    this->objects = objects;
  }
  Level(std::string file){
    //parse level from json file
  }
  std::vector<std::unique_ptr<Actor>> walls;
  std::vector<std::unique_ptr<Actor>> machines;
  std::vector<std::unique_ptr<Actor>> objects;
};
