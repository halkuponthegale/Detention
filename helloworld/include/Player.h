#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>

#include "Machine.h"

class Player {

public:

    Player(); // Constructor

    void Update(); // handles input

    int intersects(Machine *m);

    // Puts player back in original position
    void reset();

    // Accessor method
    sf::RectangleShape getShape();

    // return if player in machine or not
    int inMachine();

private:

    //Create a simple rectangle, stand in for the player
    sf::RectangleShape playerbody;
    Machine *my_machine;

    int in_machine;

    // Moves the player up
    void player_up();

    // Moves the player down
    void player_down();
    
    // Moves the player left
    void player_left();

    // Moves the player right
    void player_right();

};
#endif

