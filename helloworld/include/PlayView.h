#ifndef PLAY_VIEW_H
#define PLAY_VIEW_H

#include "GameView.h"
#include "Object.h"
#include "FileManager.h"
#include "Player.h"
#include "Builder.h"

/*
	PlayView handles level loading, drawing, and gameplay
	As of right now, also handles physics and logic
*/

static const float SCALE = 30.f;
class PlayView : public MiniView{
	public:
		PlayView(int lvl) : gravity(0.0f, 10.0f), world(gravity){
			play_lvl = lvl;
			objs = File::loadLevel("./level"+std::to_string(play_lvl)+".json");
			CreateGround(world, 400.f, 500.f);
			for( auto&& pointer : objs) {
				CreateWall(world,pointer->getX(), pointer->getY(),pointer->getW(),pointer->getH());
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
	    pBody->CreateFixture(&FixtureDef);
			pBody->SetFixedRotation(true);
			PlayerInstance.setBody(*pBody);

			// create builder physics body
			b2BodyDef BodyDef2;
	    BodyDef2.position = b2Vec2(200.f/SCALE, 200.f/SCALE);
	    BodyDef2.type = b2_dynamicBody;
	    builderBody = world.CreateBody(&BodyDef2);

	    b2PolygonShape Shape2;
	    Shape2.SetAsBox((50.f/2)/SCALE, (50.f/2)/SCALE);
	    b2FixtureDef FixtureDef2;
	    FixtureDef2.density = 100.f;
	    FixtureDef2.friction = 1;
	    FixtureDef2.shape = &Shape2;
	    builderBody->CreateFixture(&FixtureDef2);
			builderBody->SetFixedRotation(true);
			builder.setBody(*builderBody);

			// temporary hard code boxes
			box1.setPos(250,250);
			builder.add_box(&box1);

			box2.setPos(40, 300);
			builder.add_box(&box2);
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
		std::vector<std::unique_ptr<Actor>> objs;
		sf::RectangleShape wall;
		Player PlayerInstance;
		b2Vec2 gravity;
		b2World world;
		b2Body* pBody;
		b2Body* builderBody;

		Builder builder;
		Box box1, box2;

};


#endif
