#ifndef PLAY_VIEW_H
#define PLAY_VIEW_H

#include "GameView.h"
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

/*
	PlayView handles level loading, drawing, and gameplay
	As of right now, also handles physics and logic
*/

static const float SCALE = 30.f;
class PlayView : public MiniView, public b2ContactListener{
	public:
		PlayView(int lvl) : gravity(0.0f, 10.0f), world(gravity),
							level("../include/Levels/level"+std::to_string(lvl)+".txt"),
							boxes_list(level.getBoxes()),builders_list(level.getBuilders()),
							mobiles_list(level.getMobiles()), launchers_list(level.getLaunchers()),
							walls_list(level.getWalls()),players_list(level.getPlayers()),
							exits_list(level.getExits()), textures_list(level.getTextures())
		{

			play_lvl = lvl;

			AudioManager::play_level(lvl);

			int i;
			if(play_lvl==3)
			printf("lol\n\n\n\n");
			// set box objects to world
			if(!boxes_list.empty()){
					for(i = 0; i < boxes_list.size(); i++){
						(*boxes_list[i]).setWorld(world);
					}
			}
			if(play_lvl==3)
			printf("lol2\n\n\n\n");
			// set builder machines to world
			if(!builders_list.empty()){
				for(i = 0; i < builders_list.size(); i++){
					(*builders_list[i]).setWorld(world);
				}
			}

			if(play_lvl==3)
			printf("lol3\n\n\n\n");
			// set launcher machines to world
			if(!launchers_list.empty()){
				for(i = 0; i < launchers_list.size(); i++){
					(*launchers_list[i]).setWorld(world);
				}
			}

			if(play_lvl==3)
			printf("lol4\n\n\n\n");
		// set mobile machines to world
		if(!mobiles_list.empty()){

			for(i = 0; i < mobiles_list.size(); i++){
				(*mobiles_list[i]).setWorld(world);
				if(play_lvl==3)
				printf("mob1\n\n\n\n");
				for( int z = 0; z < walls_list.size(); z++){
					(*mobiles_list[i]).add_wall(&(*walls_list[z]));
					if(play_lvl==3)
					printf("mob2\n\n\n\n");
				}
			}

		}
		if(play_lvl==3)
		printf("lol5\n\n\n\n");

		// set player(s) to world
		if(!players_list.empty()){
			for(i = 0; i < players_list.size(); i++){
				(*players_list[i]).setWorld(world);
			}
		}
		if(play_lvl==3)
		printf("lol6\n\n\n\n");
		// set walls to world
		if(!walls_list.empty()){
			for(i = 0; i < walls_list.size(); i++){
				(*walls_list[i]).setWorld(world);
			}

			int b,z;
			if(!builders_list.empty()){
				for(b = 0; b < builders_list.size(); b++){
					for(z = 0; z < walls_list.size(); z++){
						(*builders_list[b]).add_wall(&(*walls_list[z]));
					}
				}
			}
		}

		if(play_lvl==3)
		printf("lol7\n\n\n\n");
		// set exit to world
		if(!exits_list.empty()){
			for(i = 0; i < exits_list.size(); i++){
				(*exits_list[i]).setWorld(world);
			}
		}
		if(play_lvl==3)
		printf("lol8\n\n\n\n");
		// add boxes to builder machines if necessary
		if(!boxes_list.empty()){
			int b,z;
			if(!builders_list.empty()){
				for(b = 0; b < builders_list.size(); b++){
					for(z = 0; z < boxes_list.size(); z++){
						(*builders_list[b]).add_box(&(*boxes_list[z]));
					}
				}
			}
			if(play_lvl==3)
			printf("lol9\n\n\n\n");
			if(!mobiles_list.empty()){
				for(b = 0; b < mobiles_list.size(); b++){
					for(z = 0; z < boxes_list.size(); z++){
						(*mobiles_list[b]).add_box(&(*boxes_list[z]));
					}
				}
			}
		}
		if(play_lvl==3)
		printf("lol10\n\n\n\n");

		}
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);
		void BeginContact(b2Contact* contact) {
	       void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				 void* otherUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	       if (bodyUserData && otherUserData){
	         if(*(int*)( bodyUserData ) == 200 && *(int*)( otherUserData )==201){
						 	if(contact->GetFixtureA()->GetBody()->GetLinearVelocity().y >=10)
								game_view.setView(new PlayView(play_lvl));
					 }
					 else if(*(int*)( bodyUserData ) == 201 && *(int*)( otherUserData )==200){
						 if(contact->GetFixtureB()->GetBody()->GetLinearVelocity().y >=10)
							 game_view.setView(new PlayView(play_lvl));
					 }
				 }
	     }
	private:
		sf::Font font;

		int intro_return;
		int play_lvl;

		sf::Text tmp;
		sf::Text tmp2;
		sf::Text tmp3;

		b2Vec2 gravity;
		b2World world;
		b2Body* pBody;

		sf::Texture Bkg;
		sf::Sprite bgSprite;
		std::vector<int> ty;
		std::vector<Machine*> vec;

		Level level;
		std::vector<std::unique_ptr<Box>> const& boxes_list;
		std::vector<std::unique_ptr<Builder>> const& builders_list;
		std::vector<std::unique_ptr<Mobile>> const& mobiles_list;
		std::vector<std::unique_ptr<Launcher>> const& launchers_list;
		std::vector<std::unique_ptr<Wall>> const& walls_list;
		std::vector<std::unique_ptr<Player>> const& players_list;
		std::vector<std::unique_ptr<Exit>> const& exits_list;
		std::vector<std::unique_ptr<Texture>> const& textures_list;
};


#endif
