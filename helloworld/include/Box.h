#ifndef BOX_H
#define BOX_H

#include "Object.h"

class Box : public Object{
	public:
		Box() : Object(0, 0, 50, 50, true){
			box_body.setSize(sf::Vector2f(50,50));
			box_body.setPosition(0,0);
			box_body.setFillColor(sf::Color::Blue);
		}

		void setPos(double x, double y){
			box_body.setPosition(x, y);
		}

		void move(int x, int y){ box_body.move(x,y); }

		sf::RectangleShape getShape(){ return box_body;}

	private:
		sf::RectangleShape box_body;
};


#endif