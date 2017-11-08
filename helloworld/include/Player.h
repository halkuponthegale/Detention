#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>
#include "Box2D.h"
class player {

public:

    //Create a simple rectangle, stand in for the player
    sf::RectangleShape playerbody;

    player(); // Constructor


    // Moves the player up
    void player_up();

    // Moves the player down
    void player_down();

    // Moves the player left
    void player_left();

    // Moves the player right
    void player_right();

    void launch(double velocity, double theta);
    // Puts player back in original position
    void reset();
    void setBody(b2Body& bod){
      body = &bod;
    }
private:
  b2Body* body;
  bool inMachine;
};
#endif
