#include <SFML/Graphics.hpp>
#include "Player.h"

sf::RectangleShape playerbody;

    // Constructor
    // Creates a simple rectanglein place of player sprite
    player::player() {
        player_paddle.setSize(sf::Vector2f(10,30));
        player_paddle.setPosition(0,0);
    }


    // Moves the player up, unless it's already at the top of the screen
    void player::player_up() {
        if(player_paddle.getPosition().y > 0) {
            player_paddle.move(0, -1);
        }
    }


    // Moves the player down, unless it's already at the bottom of the screen
    void player::player_down() {
        if(player_paddle.getPosition().y < 570) {
            player_paddle.move(0, 1);
        }
    }


    // Moves the player left, unless it's already at the left of the screen
    void player::player_left() {
        if(player_paddle.getPosition().x < 0) {  // check
            player_paddle.move(-1, 0);  // check
        }
    }


    // Moves the player right, unless it's already at the right of the screen
    void player::player_right() {
        if(player_paddle.getPosition().x < 750) {  // check
            player_paddle.move(1, 0);  // check
        }
    }


    // Puts paddle back to original position
    void player::reset() {
        player_paddle.setPosition(700,300);
    }

