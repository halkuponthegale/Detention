#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>
#include "Box2D.h"
#include "Machine.h"
class Player {

public:

    //Create a simple rectangle, stand in for the player
    sf::RectangleShape playerbody;

    Player(); // Constructor


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
    //oid reset();
    void setBody(b2Body& bod){
      body = &bod;
    }
    void Update(); // handles input

    b2Body* getBody(){
      return body;
    }

    int intersects(std::vector<Machine *> marr, std::vector<int> types);

    // Puts player back in original position
    void reset();

    // Accessor method
    sf::RectangleShape getShape();

    // return if player in machine or not
    int inMachine();
    Machine *my_machine;
    int mType;
    int in_machine;

private:
  b2Body* body;
  int jumping;
  int facing; // 0 = left, 1 = right

};
#endif
