#ifndef BUILDER_H
#define BUILDER_H

#include "Machine.h"

class Builder : public Machine{
	public:


		Builder(){
			machine_body.setSize(sf::Vector2f(50,50));
			machine_body.setPosition(100,100);
			machine_body.setFillColor(sf::Color::Red);
		}



	private:

};


#endif
