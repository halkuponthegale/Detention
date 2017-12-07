#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include "Box2D.h"


// Box class sets box texture, sets it to the world, and updates its position/location


class Box : public Object{
public:
	
	sf::Texture boxtexture;
	
	// Constructor
	Box(double xo, double yo) : Object(0, 0, 50, 50, true){
		
		// Load box texture from jpg file (from include folder)
		if(!boxtexture.loadFromFile("../include/Textures/box.jpg",sf::IntRect(0, 0, 512, 512)))
		{
		}

		// Assign coordinate variables
		x = xo; y = yo;
		
		// Set the size, position, origin, and texture to the box body
		box_body.setSize(sf::Vector2f(50,50));
		box_body.setOrigin(box_body.getOrigin().x + 25, box_body.getOrigin().y+25 );
		box_body.setTexture(&boxtexture);
		box_body.setPosition(xo,yo);

	}

	~Box(){
			bod->GetWorld()->DestroyBody( bod );
	}
  
	void setWorld(b2World& World){
		static const double SCALE = 30.f;

		b2BodyDef BodyDef2;
		BodyDef2.position = b2Vec2(x/SCALE, y/SCALE);
	    	BodyDef2.type = b2_dynamicBody;
		bod = World.CreateBody(&BodyDef2);
		b2PolygonShape Shape2;
		Shape2.SetAsBox((50.0/2)/SCALE, (50.0/2)/SCALE);
		b2FixtureDef FixtureDef2;
		FixtureDef2.density = 1000000.f;
		FixtureDef2.friction = 1;
		FixtureDef2.shape = &Shape2;
		bod->CreateFixture(&FixtureDef2);
		bod->SetFixedRotation(true);
		bod->SetUserData( (void*)(int)201 );
	}

	
	void setPos(float x, float y){ box_body.setPosition(x, y); }

	
	void move(int x, int y){ box_body.move(x,y);}

	
	sf::RectangleShape getShape(){ return box_body;}

	
	b2Body *getBody(){ return bod; }


	
private:
	sf::RectangleShape box_body;
	b2Body *bod;
	double x, y;
};


#endif
