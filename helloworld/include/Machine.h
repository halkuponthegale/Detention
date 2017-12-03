#ifndef MACHINE_H
#define MACHINE_H

// #include "Actor.h"
#include <SFML/Graphics.hpp>
#include "Box.h"
#include <iostream>
class Machine{
	public:
		double launchVel;
		sf::RectangleShape machine_body;

		virtual void Update(){}

		bool intersects(Box* o){ return touching(o) < 52; }
		float touching(Box* o){ return abs(machine_body.getGlobalBounds().left - o -> getShape().getGlobalBounds().left); }

		virtual void getOut(){};

		virtual double getTheta(){return 0;}
		sf::RectangleShape getShape() {return machine_body;}
		b2Body* getBody(){ return body; }

		void setPosition(int x, int y);
		void setColor(sf::Color c){	machine_body.setFillColor(c); } // TEMPORARY



	protected:
		b2Body* body;

		int facing; // 0 = left, 1 = right
		int space;
		int cur_box_idx;

		// builder vars
		Box* boxlist[10];
		int carrybox;
		Box* mybox;


		double x, y;




};


#endif
