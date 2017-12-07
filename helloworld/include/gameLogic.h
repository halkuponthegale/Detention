#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "Object.h"
#include "FileManager.h"
#include "Player.h"
#include "Builder.h"
#include "Launcher.h"
#include "Mobile.h"
#include "Level.h"
#include "Wall.h"
#include "Exit.h"
#include "Texture.h"
#include "AudioManager.h"
#include "PlayView.h"
#include "EndView.h"
class GameLogic{
public:
  static int update(std::vector<std::unique_ptr<Box>> const& boxes_list,
  std::vector<std::unique_ptr<Builder>> const& builders_list,
  std::vector<std::unique_ptr<Mobile>> const& mobiles_list,
  std::vector<std::unique_ptr<Launcher>> const& launchers_list,
  std::vector<std::unique_ptr<Wall>> const& walls_list,
  std::vector<std::unique_ptr<Player>> const& players_list,
  std::vector<std::unique_ptr<Exit>> const& exits_list,
  int &play_lvl,
  int &top_lvl,
  GameView * game_view,
  std::vector<int> *ty,
  std::vector<Machine*> *vec,
  int &intro_return);


};

#endif /* end of include guard: DETENTION_H */
