
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "iostream"
    // Constructor
    // Creates a simple rectanglein place of player sprite
    player::player() {
        playerbody.setSize(sf::Vector2f(10,30));
        playerbody.setPosition(0,0);
        inMachine = true;
    }


    // Moves the player up, unless it's already at the top of the screen
    void player::player_up() {
        if(playerbody.getPosition().y > 0) {
            //playerbody.move(0, -.1);
            this->launch(12.0,M_PI/4);
        }
    }


    // Moves the player down, unless it's already at the bottom of the screen
    void player::player_down() {
        if(playerbody.getPosition().y < 570) {
            //playerbody.move(0, .1);

        }
    }


    // Moves the player left, unless it's already at the left of the screen
    void player::player_left() {
        if(playerbody.getPosition().x > 0) {  // check
            //playerbody.move(-.1, 0);  // check
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = -5;
            body->SetLinearVelocity( vel );
        }
    }


    // Moves the player right, unless it's already at the right of the screen
    void player::player_right() {
        if(playerbody.getPosition().x < 800) {  // check
            //playerbody.move(.1, 0);  // check
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );
        }
    }
    void player::launch(double velocity, double theta){
        b2Vec2 vel = body->GetLinearVelocity();
        if(inMachine == true){
          double vx = cos(theta)* velocity;
          double vy = sin(theta)* velocity;
          double impx = (vel.x)*body->GetMass();
          double impy = (vel.y)*body->GetMass();
          std::cout << vx <<"," << vy;
          body->ApplyLinearImpulse( b2Vec2(vx, -vy), body->GetWorldCenter(), true );
          inMachine = false;
        }
    }


    // Puts paddle back to original position
    void player::reset() {
        playerbody.setPosition(700,300);
    }
