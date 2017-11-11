#include "Builder.h"

// constructor

// define how this machine can move (can set limitations)
#include "Builder.h"

// constructor
Builder::Builder(){
	machine_body.setSize(sf::Vector2f(50,50));
	machine_body.setPosition(100,100);
	machine_body.setFillColor(sf::Color::Red);
}

// define how this machine can move (can set limitations)
void Machine::Update(){
	// move up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    	if(machine_body.getPosition().y > 0) {
            machine_body.move(0, -1);
        }
    }
    // move left
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    	if(machine_body.getPosition().x > 0) {
           machine_body.move(-1, 0);
    	}
    }
    // move down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    	if(machine_body.getPosition().y < 550) {  // check
            machine_body.move(0, 1);
        }
    }
    // move right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    	if(machine_body.getPosition().x < 750) {  // check
            machine_body.move(1, 0);
        }
    }
}
