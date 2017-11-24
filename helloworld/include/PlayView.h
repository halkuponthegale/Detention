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

/*
	PlayView handles level loading, drawing, and gameplay
	As of right now, also handles physics and logic
*/

static const float SCALE = 30.f;
class PlayView : public MiniView{
	public:
		PlayView(int lvl) : gravity(0.0f, 10.0f), world(gravity),
							level("../include/Levels/level"+std::to_string(lvl)+".txt"),
							boxes_list(level.getBoxes()),builders_list(level.getBuilders()),
							mobiles_list(level.getMobiles()), launchers_list(level.getLaunchers()){

			play_lvl = lvl;
			// objs = File::loadLevel("./level"+std::to_string(play_lvl)+".json");

			int i;


			CreateGround(world, 400.f, 500.f);
			// for( auto&& pointer : objs) {
			// 	CreateWall(world,pointer->getX(), pointer->getY(),pointer->getW(),pointer->getH());
			// }

			// set box objects to world
			if(!boxes_list.empty()){
					for(i = 0; i < boxes_list.size(); i++){
						(*boxes_list[i]).setWorld(world);
					}
			}

			// set builder machines to world
			if(!builders_list.empty()){
				for(i = 0; i < builders_list.size(); i++){
					(*builders_list[i]).setWorld(world);
				}
			}


			// set launcher machines to world
			if(!launchers_list.empty()){
				for(i = 0; i < launchers_list.size(); i++){
					(*launchers_list[i]).setWorld(world);
				}
			}


		// set mobile machines to world
		if(!mobiles_list.empty()){
			for(i = 0; i < mobiles_list.size(); i++){
				(*mobiles_list[i]).setWorld(world);
			}
		}



		// create player physics body
		b2BodyDef BodyDef;
		BodyDef.position = b2Vec2(80.f/SCALE, 90.f/SCALE);
		BodyDef.type = b2_dynamicBody;
		pBody = world.CreateBody(&BodyDef);

		b2PolygonShape Shape;
		Shape.SetAsBox((10.f/2)/SCALE, (30.f/2)/SCALE);
		b2FixtureDef FixtureDef;
		FixtureDef.density = 1.f;
		FixtureDef.friction = 1;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = 0x0002;
		pBody->CreateFixture(&FixtureDef);
		pBody->SetFixedRotation(true);

		PlayerInstance.setBody(*pBody);


			// add boxes to builder machines if necessary
			int z,b;
			if(!boxes_list.empty()){
				if(!builders_list.empty()){
					for(b = 0; b < builders_list.size(); b++){
						for(z = 0; z < boxes_list.size(); z++){
							(*builders_list[b]).add_box(&(*boxes_list[z]));
						}
					}
				}
			}
		}
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);
		void CreateGround(b2World& World, float X, float Y)
		{
		    b2BodyDef BodyDef;
		    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
		    BodyDef.type = b2_staticBody;
		    b2Body* Body = World.CreateBody(&BodyDef);

		    b2PolygonShape Shape;
		    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
		    b2FixtureDef FixtureDef;
		    FixtureDef.density = 0.f;
		    FixtureDef.shape = &Shape;
		    Body->CreateFixture(&FixtureDef);
				groundBody = Body;
		}
		void CreateWall(b2World &World, double x, double y, int w, int h){
			b2BodyDef BodyDef;
			BodyDef.position = b2Vec2(x/SCALE, y/SCALE);
			BodyDef.type = b2_staticBody;
			b2Body* Body = World.CreateBody(&BodyDef);

			b2PolygonShape Shape;
			Shape.SetAsBox((w/2.0)/SCALE, (h/2.0)/SCALE);
			b2FixtureDef FixtureDef;
			FixtureDef.density = 0.f;
			FixtureDef.shape = &Shape;
			Body->CreateFixture(&FixtureDef);
		}
	private:
		sf::Font font;

		int intro_return;
		int play_lvl;

		sf::Text tmp;
		sf::Text tmp2;
		sf::Text tmp3;

		//std::vector<std::unique_ptr<Actor>> objs;
		sf::RectangleShape wall;
		Player PlayerInstance;
		b2Vec2 gravity;
		b2World world;
		b2Body* pBody;

		sf::Texture Bkg;
		sf::Sprite bgSprite;
		b2Body* groundBody;
		std::vector<int> ty;
		std::vector<Machine*> vec;

		Level level;
		std::vector<std::unique_ptr<Box>> const& boxes_list;
		std::vector<std::unique_ptr<Builder>> const& builders_list;
		std::vector<std::unique_ptr<Mobile>> const& mobiles_list;
		std::vector<std::unique_ptr<Launcher>> const& launchers_list;
};


#endif
