#include "Machine.h"
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
