#ifndef MACHINE_H
#define MACHINE_H

// #include "Actor.h"
#include <SFML/Graphics.hpp>
#include "Box.h"
#include <iostream>
class Machine{
	public:
		virtual void Update();
		virtual double getTheta(){return 0;}
		void setPosition(int x, int y);
		sf::RectangleShape getShape() {return machine_body;}
		bool intersects(Box* o){//return machine_body.getGlobalBounds().intersects(o -> getShape().getGlobalBounds());
				return touching(o) < 52;//&& machine_body.getGlobalBounds().top == o -> getShape().getGlobalBounds().top;
		}
		float touching(Box* o){
			return abs(machine_body.getGlobalBounds().left - o -> getShape().getGlobalBounds().left);
		}
		b2Body* getBody(){ return body; }
		void setColor(sf::Color c){	machine_body.setFillColor(c); } // TEMPORARY

		sf::RectangleShape machine_body;

		void getOut(){return;}

		//void setWorld(b2World& World);

	protected:
		b2Body* body;


		// tmp builder vars - later will be stored in Level
		Box* boxlist[10];
		int carrybox;
		Box* mybox;
		int facing; // 0 = left, 1 = right
		int space;
		int cur_box_idx;

		double x, y;




};


#endif
