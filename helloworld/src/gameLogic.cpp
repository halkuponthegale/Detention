#include "gameLogic.h"
int GameLogic::update(std::vector<std::unique_ptr<Box>> const& boxes_list,
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
int &intro_return){

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
  return -1;
}

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
  game_view->setView(new PlayView(play_lvl));
  return 0;
}

// if last level, check if two player bodies are touching
// if so, end level
if(players_list.size() > 1){
  if(!(players_list[0] -> inMachine()) && !(players_list[1] -> inMachine()) &&
     (*players_list[0]).isAtExit((*exits_list[0]).getShape()) && (*players_list[1]).isAtExit((*exits_list[0]).getShape()) &&
     (*players_list[0]).getBody() -> GetLinearVelocity().y == 0 && (*players_list[1]).getBody() -> GetLinearVelocity().y == 0) {
    if(play_lvl == top_lvl && top_lvl < MAX_LVL){
      top_lvl++;
    }

    game_view->setView(new EndView(play_lvl));
    return 0;
  }
}
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			//builder = 0, launcher = 1, mobile = 2;
			if(!players_list.empty()){
				int z;
				for(z = 0; z < players_list.size(); z++){
					if(!(*players_list[z]).inMachine() && (*players_list[z]).getBody()->GetLinearVelocity().y ==0){
						// if player is at exit, leave
						if(players_list.size() == 1 && !exits_list.empty() && (*players_list[z]).isAtExit((*exits_list[0]).getShape())){
							if(play_lvl == top_lvl && top_lvl < MAX_LVL){
								top_lvl++;
							}

							game_view->setView(new EndView(play_lvl));
              return 0;
						}
						// otherwise, check if in machine
						else if((*players_list[z]).getBody()->GetLinearVelocity().y ==0){
							 (*players_list[z]).intersects(*vec,*ty);
						 }
					}
				}



			}
  }
	if(!players_list.empty()){
		int z;
		for(z = 0; z < players_list.size(); z++){
			if((*players_list[z]).inMachine() && (*players_list[z]).mType == 0){
				//in a builder
				Builder* mach = (Builder*)((*players_list[z]).my_machine);
				if((mach->lastVelocity>0 && mach->lastVelocity-mach->getBody()->GetLinearVelocity().y >=10) || mach->getBody()->GetPosition().y>(625/30.0)){
					game_view->setView(new PlayView(play_lvl));
					AudioManager::play_buzz();
          return 0;
				}
				mach->lastVelocity = mach->getBody()->GetLinearVelocity().y;
			}else if((*players_list[z]).inMachine() && (*players_list[z]).mType == 2){
				//in a builder
				Mobile* mach = (Mobile*)((*players_list[z]).my_machine);
				if(mach->getBody()->GetPosition().y>(625/30.0)){
					game_view->setView(new PlayView(play_lvl));
					AudioManager::play_buzz();
          return 0;
				}
			}

		}
	}

	if(!players_list.empty()){
		int z;
		for(z = 0; z < players_list.size(); z++){
			(*players_list[z]).Update();

			if(((*players_list[z]).lastVelocity>0 &&(*players_list[z]).lastVelocity-(*players_list[z]).getBody()->GetLinearVelocity().y >=10)||(*players_list[z]).getBody()->GetPosition().y > (625/30.0)){
				game_view->setView(new PlayView(play_lvl));
				AudioManager::play_buzz();
        return 0;
			}
			(*players_list[z]).lastVelocity = (*players_list[z]).getBody()->GetLinearVelocity().y;
		}
	}

return 1;
}
