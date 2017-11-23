#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include "Box2D.h"
static const double SCALEd = 30.f;
class Box : public Object{
	public:
		Box(double xo, double yo) : Object(0, 0, 50, 50, true){
			box_body.setSize(sf::Vector2f(50,50));
			box_body.setOrigin(box_body.getOrigin().x + 25, box_body.getOrigin().y+25 );
			box_body.setPosition(0,0);
			box_body.setFillColor(sf::Color::Blue);

			x = xo; y = yo;

			box_body.setPosition(xo,yo);


		}

		void setWorld(b2World& World){
			b2BodyDef BodyDef2;
	    BodyDef2.position = b2Vec2(x/SCALEd, y/SCALEd);
	    BodyDef2.type = b2_dynamicBody;
			bod = World.CreateBody(&BodyDef2);
			b2PolygonShape Shape2;
			 Shape2.SetAsBox((50.0/2)/SCALEd, (50.0/2)/SCALEd);
			 b2FixtureDef FixtureDef2;
			 FixtureDef2.density = 100.f;
			 FixtureDef2.friction = 1;
			 FixtureDef2.shape = &Shape2;
			 //FixtureDef2.filter.maskBits = ~0x0002;
			 bod->CreateFixture(&FixtureDef2);
			 bod->SetFixedRotation(true);
		}

		void setPos(double x, double y){
			box_body.setPosition(x, y);
			//bod->SetTransform(b2Vec2(x,y),0);
		}

		void move(int x, int y){
				//bod->SetTransform(b2Vec2(box_body.getPosition().x+x,box_body.getPosition().y+y),0);
				box_body.move(x,y); }

		sf::RectangleShape getShape(){ return box_body;}

		b2Body *getBody(){
			return bod;
		}
	private:
		sf::RectangleShape box_body;
		b2Body *bod;
		double x, y;
};


#endif
