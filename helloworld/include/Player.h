#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>
#include "Box2D.h"
#include "Machine.h"
#include "Mobile.h"
#include "Box.h"
#include "Wall.h"
#include "AudioManager.h"

class Player {

public:

    //Create a simple rectangle, stand in for the player
    sf::RectangleShape playerbody;

    // used for spritesheet
    // playerTexture will be the full 100x140p sprite sheet, playerImage will be the current 25x35p sprite
    sf::Texture playerTexture;
    sf::Sprite playerImage;
    enum Directions { Down, Left, Right, Up }; // Enumerates direction, used to determine where from sprite sheet to begin dawing
    sf::Vector2i source; // Keeps track of coordincates in sprite sheet --> draw the proper 25x35p sprite


    Player(double xo, double yo, std::string name); // Constructor

    // Makes the player jump (limited to < 1 block)
    void player_up();

    // Moves the player left
    void player_left();

    // Moves the player right
    void player_right();

    // Handles keyboard input
    void Update();

    void launch(double velocity, double theta);
    
    // Accessor method
    sf::RectangleShape getShape();
    
    // returns whether player is in machine
    int inMachine();
    Machine *my_machine;
    int mType;
    int in_machine;
    
    int intersects(std::vector<Machine *> marr, std::vector<int> types);

    
//////////////////////////////////////////////////////
   
    void setBody(b2Body& bod){
      body = &bod;
    }

    b2Body* getBody(){
      return body;
    }

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
      body->SetUserData( (void*)(int)200 );

    }


    double lastVelocity;
private:
  b2Body* body;
  int jumping;
  int facing; // 0 = left, 1 = right
  double x, y;


};
#endif
