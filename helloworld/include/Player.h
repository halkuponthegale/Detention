#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>
#include "Box2D.h"
#include "Machine.h"
#include "Mobile.h"
class Player {

public:

    //Create a simple rectangle, stand in for the player
    sf::RectangleShape playerbody;

    // used for spritesheet
    sf::Texture playerTexture;
    sf::Sprite playerImage;
    enum Directions { Down, Left, Right, Up };
    sf::Vector2i source;


    Player(double xo, double yo); // Constructor


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

    int isAtExit(sf::RectangleShape door){
      return playerImage.getGlobalBounds().intersects(door.getGlobalBounds());
    }

    void setWorld(b2World &World){
      static const float SCALE = 30.f;

      b2BodyDef BodyDef;
      BodyDef.position = b2Vec2(x/SCALE, y/SCALE);
      BodyDef.type = b2_dynamicBody;
      body = World.CreateBody(&BodyDef);

      b2PolygonShape Shape;
      Shape.SetAsBox((10.f/2)/SCALE, (30.f/2)/SCALE);
      b2FixtureDef FixtureDef;
      FixtureDef.density = 1.f;
      FixtureDef.friction = 1;
      FixtureDef.shape = &Shape;
      FixtureDef.filter.categoryBits = 0x0002;
      FixtureDef.filter.groupIndex = -2;

      body->CreateFixture(&FixtureDef);
      body->SetFixedRotation(true);

    }

private:
  b2Body* body;
  int jumping;
  int facing; // 0 = left, 1 = right
  double x, y;

};
#endif
