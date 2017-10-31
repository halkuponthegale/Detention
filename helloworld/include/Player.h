#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>

class player {

public:

    //Create a simple rectangle, stand in for the player
    sf::RectangleShape player_paddle;

    player(); // Constructor


    // Moves the player up
    void player_up();

    // Moves the player down
    void player_down();

    // Puts player back in original position
    void reset();

};
#endif

