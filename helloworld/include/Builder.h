#ifndef BUILDER_H
#define BUILDER_H

#include "Machine.h"
#include "Box.h"
#include "Box2D.h"

class Builder : public Machine{
	public:

		// used for spritesheet
		sf::Texture builderTexture;
		sf::Sprite builderImage;
		sf::Vector2i source;

		// constructor
		Builder(double xo, double yo);

		// process input
		void Update();

		// add box to box list
		void add_box(Box *b){ boxlist[cur_box_idx] = b; cur_box_idx++; }
		// reset velocity to 0 when getting out
		void getOut(){ body -> SetLinearVelocity(b2Vec2(0,0)); }

		void add_wall(Wall *w){walllist[cur_wall_idx] = w; cur_wall_idx++; }

		// set physics body
		void setBody(b2Body& bod){ body = &bod; }
		// set physics world
		void setWorld(b2World& World);

		void isActive(int status){
			active = status; }
double lastVelocity;
	private:
		// jump ~1 block
		void jump();
};


#endif
