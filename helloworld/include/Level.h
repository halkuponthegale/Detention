#include <vector>
#include <string>
#include "Object.h"
class Level{
public:
  Level(std::vector<Object> objs){
    levelObjects = objs;
  }
  Level(std::string file){
    //parse level from json file
  }
  std::vector<Object> levelObjects;
};
