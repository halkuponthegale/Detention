#ifndef MACHINE_H
#define MACHINE_H

// #include "Actor.h"
#include <SFML/Graphics.hpp>
#include "Box.h"

class Machine{
	public:
		void Update();
		void setPosition(int x, int y);
		sf::RectangleShape getShape() {return machine_body;}
		bool intersects(Box* o){return machine_body.getGlobalBounds().intersects(o -> getShape().getGlobalBounds());}

		void setColor(sf::Color c){	machine_body.setFillColor(c); } // TEMPORARY

	protected:

		sf::RectangleShape machine_body;

		// tmp builder vars - later will be stored in Level
		Box* boxlist[10];
		int carrybox;
		Box* mybox;
		int facing; // 0 = left, 1 = right
		int space;
		int cur_box_idx;




};


#endif
