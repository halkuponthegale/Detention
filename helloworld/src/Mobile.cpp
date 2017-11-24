// Mobile.cpp
#include <SFML/Graphics.hpp>
#include "Mobile.h"

  // Constructor
    // Creates a simple rectangle in place of mobile sprite
    // TODO: file parser will call constructor and pass in position
    // TODO: instance variable that is 1 or 0, if 1 then you can't move left/right yet


    //TODO: energy level - set a level amount, deplete with movement, return variable
    //TODO: algorithm to float one "unit" above ground (incuding hovering over holes and ascending stairs)
    // the distance between Mobile and any "wall" that is below it (any wall with the same X coord, higher Y coord int) is ___ (1 unit)
    // inc or dec
    // BUT you can fall and glide down things
    //TODO: inherit from Machine?
    //TODO: ensure mobile doesn't fly off the edge

     // Blast off: moves the mobile up
     //TODO: Implement clock/delta time
     //TODO: Don't move if energy is empty
     //TODO: if you walk right "into" a block, you actually adjust height and THEN go right (over it)

    //TODO: player.cpp will call "activeate/deactivate". if adjusting is 0, deactivate will stop hover


void Mobile::setWorld(b2World& World){
  static const float SCALE = 30.f;

  b2BodyDef BodyDef4;
  BodyDef4.position = b2Vec2(x/SCALE, y/SCALE);
  BodyDef4.type = b2_dynamicBody;
  body = World.CreateBody(&BodyDef4);

  b2PolygonShape Shape4;
  Shape4.SetAsBox((50.f/2)/SCALE, (50.f/2)/SCALE);
  b2FixtureDef FixtureDef4;
  FixtureDef4.density = 100.f;
  FixtureDef4.friction = 1;
  FixtureDef4.shape = &Shape4;
  FixtureDef4.filter.maskBits = ~0x0002;
  body->CreateFixture(&FixtureDef4);
  body->SetFixedRotation(true);
  //builderBody->SetGravityScale(0);

  // mobile.setBody(*mobileBody);
}
