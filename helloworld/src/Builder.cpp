#include "Builder.h"

// constructor
Builder::Builder(){

    machine_body.setSize(sf::Vector2f(50,50));
    machine_body.setPosition(150,150);
    machine_body.setFillColor(sf::Color::Red);

    cur_box_idx = 0;
    carrybox = 0;
}

// define how this machine can move (can set limitations)
void Machine::Update(){
    // move up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if(machine_body.getPosition().y > 0) {
            machine_body.move(0, -1);

            // if you have a box, move it as well
            if(carrybox){
                mybox -> move(0,-1);
            }
        }
    }
    // move left
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(machine_body.getPosition().x > 0) {
          //  machine_body.move(-1, 0);
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = -5;
          body->SetLinearVelocity( vel );

          facing = 0;

            // if you have a box, move it as well
            if(carrybox){
                mybox -> move(-1,0);
            }
        }
    }
    // move down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if(machine_body.getPosition().y < 550) {  // check
            machine_body.move(0, 1);

             // if you have a box, move it as well
           if(carrybox){
                mybox -> move(0,1);
            }
        }
    }
    // move right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(machine_body.getPosition().x < 750) {  // check
            // machine_body.move(1, 0);
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );
            facing = 1;

             // if you have a box, move it as well
           if(carrybox){
                mybox -> move(1,0);
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        int intersect = 0;
        int i;

        for(i = 0; i < cur_box_idx; i++){
            if(intersects(boxlist[i])){
                intersect = 1;
                break;
            }
        }

        // if you're carrying a box and it's not the initial space press, set it down the way you're facing
        if(carrybox && !space){
            if(facing == 0){ // if facing left
                mybox -> setPos(machine_body.getPosition().x - 60, machine_body.getPosition().y);
            }
            else{
                mybox -> setPos(machine_body.getPosition().x + 60, machine_body.getPosition().y);
            }
            carrybox = 0;
        }
        // if you aren't carrying a box and you're intersecting one, pick it up
        else if(intersect){
            mybox = boxlist[i];
            mybox -> setPos(machine_body.getPosition().x, machine_body.getPosition().y - 60);
            carrybox = 1;
        }
        space = 1;

    }
    else{
        space = 0;
    }
}
