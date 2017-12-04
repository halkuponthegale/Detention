#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <fstream>
#include "Object.h"
#include "Box.h"
#include "Player.h"
#include "Wall.h"
#include "Exit.h"
#include "Texture.h"

using namespace std;

class Level{
public:
  Level(std::string file){
    //parse level from txt file
    ifstream inFile;
    inFile.open(file);

    if(!inFile){
      cerr << "File " << file << " does not exist" << "\n";
      exit(1);
    }

    cout << "\n" << file << "\n";

    // read in x coord, y coord, object
    double x,y;
    string type;

    string player_name = "Cal";

    while (inFile >> x >> y >> type){

      cout << x << " " << y << " " << type << "\n";

      if(type == "box"){
        boxes.push_back(unique_ptr<Box>(new Box(x, y)));
      }

      else if(type == "builder"){
        builders.push_back(unique_ptr<Builder>(new Builder(x, y)));
      }

      else if(type == "mobile"){
        mobiles.push_back(unique_ptr<Mobile>(new Mobile(x, y)));
      }

      else if(type == "launcher"){
        launchers.push_back(unique_ptr<Launcher>(new Launcher(x, y)));
      }

      else if(type == "player"){
        players.push_back(unique_ptr<Player>(new Player(x,y, player_name)));
        player_name = "Kevin";
      }

      else if(type == "wall"){
        double half_w, half_h;
        inFile >> half_w >> half_h;
        walls.push_back(unique_ptr<Wall>(new Wall(x, y, half_w, half_h)));

      }

      else if(type == "exit"){
        exits.push_back(unique_ptr<Exit>(new Exit(x, y)));
      }

      else if(type == "texture"){
        double half_w, half_h;
        string file;

        inFile >> half_w >> half_h >> file;
        textures.push_back(unique_ptr<Texture>(new Texture(x, y, half_w, half_h, file)));
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

  std::vector<std::unique_ptr<Wall>> const& getWalls(){
    return walls;
  }

  std::vector<std::unique_ptr<Player>> const& getPlayers(){
    return players;
  }

  std::vector<std::unique_ptr<Exit>> const& getExits(){
    return exits;
  }

  std::vector<std::unique_ptr<Texture>> const& getTextures(){
    return textures;
  }

private:
  std::vector<std::unique_ptr<Box>> boxes;
  std::vector<std::unique_ptr<Builder>> builders;
  std::vector<std::unique_ptr<Mobile>> mobiles;
  std::vector<std::unique_ptr<Launcher>> launchers;
  std::vector<std::unique_ptr<Wall>> walls;
  std::vector<std::unique_ptr<Player>> players;
  std::vector<std::unique_ptr<Exit>> exits;
  std::vector<std::unique_ptr<Texture>> textures;


};



#endif
