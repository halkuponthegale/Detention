// Mobile.cpp
#include <SFML/Graphics.hpp>
#include "Mobile.h"

Mobile::Mobile(double xo, double yo){

    // create machine body
    machine_body.setSize(sf::Vector2f(50,50));
    machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
    machine_body.setPosition(xo, yo);

    machine_body.setFillColor(sf::Color::Magenta);

    // set initial x and y
    x = xo; y = yo;
}


// define how this machine can move (can set limitations)
void Mobile::Update(){
    // A = move left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      if(machine_body.getPosition().x < 750) {
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = -5;
          body->SetLinearVelocity( vel );
      }
    }

    // D = move right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      if(machine_body.getPosition().x < 750) {
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = 5;
          body->SetLinearVelocity( vel );
    }
  }

  // set velocity to 0 if neither direction is pressed
  if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    body->SetLinearVelocity(b2Vec2(0,0));
  }
}

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
  FixtureDef4.filter.categoryBits = ~0x0008;
  FixtureDef4.filter.groupIndex = -2;

  body->CreateFixture(&FixtureDef4);
  body->SetFixedRotation(true);

}
