#ifndef MACHINE_H
#define MACHINE_H

// #include "Actor.h"
#include <SFML/Graphics.hpp>

class Machine{
	public:
		void Update();
		void setPosition(int x, int y);
		sf::RectangleShape getShape() {return machine_body;}

		void setColor(sf::Color c){	machine_body.setFillColor(c); } // TEMPORARY

	protected:
		sf::RectangleShape machine_body;


};


#endif
