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
							level("../include/Levels/level"+std::to_string(lvl)+".txt"),boxes_list(level.getBoxes()){
			play_lvl = lvl;
			// objs = File::loadLevel("./level"+std::to_string(play_lvl)+".json");

			int i;
			if(!boxes_list.empty()){
					for(i = 0; i < boxes_list.size(); i++){
						(*boxes_list[i]).setWorld(world);
					}
			}
			CreateGround(world, 400.f, 500.f);
			// for( auto&& pointer : objs) {
			// 	CreateWall(world,pointer->getX(), pointer->getY(),pointer->getW(),pointer->getH());
			// }
			line = sf::RectangleShape(sf::Vector2f(5,25));
			line.setPosition(350,200);
			line.setOrigin(2.5,25);


			// create builder physics body
			b2BodyDef BodyDef2;
	    BodyDef2.position = b2Vec2(200.f/SCALE, 200.f/SCALE);
	    BodyDef2.type = b2_dynamicBody;
	    builderBody = world.CreateBody(&BodyDef2);

	    b2PolygonShape Shape2;
	    Shape2.SetAsBox((50.f/2)/SCALE, (50.f/2)/SCALE);
	    b2FixtureDef FixtureDef2;
	    FixtureDef2.density = 10.f;
	    FixtureDef2.friction = 1;
	    FixtureDef2.shape = &Shape2;
			FixtureDef2.filter.maskBits = ~0x0002;
	    builderBody->CreateFixture(&FixtureDef2);
			builderBody->SetFixedRotation(true);
			//builderBody->SetGravityScale(0);

			builder.setBody(*builderBody);


		///build Launcher
		b2BodyDef BodyDef3;
		BodyDef3.position = b2Vec2(350.f/SCALE, 200.f/SCALE);
		BodyDef3.type = b2_dynamicBody;
		launcherBody = world.CreateBody(&BodyDef3);

		b2PolygonShape Shape3;
		Shape3.SetAsBox((50.f/2)/SCALE, (50.f/2)/SCALE);
		b2FixtureDef FixtureDef3;
		FixtureDef3.density = 100.f;
		FixtureDef3.friction = 1;
		FixtureDef3.shape = &Shape3;
		FixtureDef3.filter.maskBits = ~0x0002;
		launcherBody->CreateFixture(&FixtureDef3);
		launcherBody->SetFixedRotation(true);
		//builderBody->SetGravityScale(0);

		launcher.setBody(*launcherBody);

		//build mobile
		b2BodyDef BodyDef4;
		BodyDef4.position = b2Vec2(450.f/SCALE, 200.f/SCALE);
		BodyDef4.type = b2_dynamicBody;
		mobileBody = world.CreateBody(&BodyDef4);

		b2PolygonShape Shape4;
		Shape4.SetAsBox((50.f/2)/SCALE, (50.f/2)/SCALE);
		b2FixtureDef FixtureDef4;
		FixtureDef4.density = 100.f;
		FixtureDef4.friction = 1;
		FixtureDef4.shape = &Shape4;
		FixtureDef4.filter.maskBits = ~0x0002;
		mobileBody->CreateFixture(&FixtureDef4);
		mobileBody->SetFixedRotation(true);
		//builderBody->SetGravityScale(0);

		mobile.setBody(*mobileBody);



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

			// temporary hard code boxes
			// box1.setPos(250,250);
			// builder.add_box(&box1);
			//
			// // box2.setPos(40, 300);
			// builder.add_box(&box2);
			//
			// builder.add_box(&(*boxes_list.front()));

			int z;
			if(!boxes_list.empty()){
					for(z = 0; z < boxes_list.size(); z++){
						builder.add_box(&(*boxes_list[z]));
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
		sf::RectangleShape line;
		//std::vector<std::unique_ptr<Actor>> objs;
		sf::RectangleShape wall;
		Player PlayerInstance;
		b2Vec2 gravity;
		b2World world;
		b2Body* pBody;
		b2Body* builderBody;
		b2Body* launcherBody;
		b2Body* mobileBody;
		Mobile mobile;
		Builder builder;
		Launcher launcher;
		//Box box1, box2;
		sf::Texture Bkg;
		sf::Sprite bgSprite;
		b2Body* groundBody;
		std::vector<int> ty;
		std::vector<Machine*> vec;

		Level level;
		std::vector<std::unique_ptr<Box>> const& boxes_list;
};


#endif
