// Mobile.cpp
#include <SFML/Graphics.hpp>
#include "Mobile.h"

Mobile::Mobile(double xo, double yo){

    // Load mobile spritesheet from png file (in include folder)
    if(!mobileTexture.loadFromFile("../include/sprites/mobile3.png",sf::IntRect(0, 0, 200, 100)))
    {
    }

    machine_body.setSize(sf::Vector2f(50,50));
    machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
    machine_body.setPosition(xo, yo);

    mobileImage.setTexture(mobileTexture);

    //mobileImage.setPosition(xo, yo);

    // set initial x and y
    x = xo; y = yo;
    source.x = 0;
    source.y = 1;

    mobileImage.setTextureRect(sf::IntRect(source.x*50, source.y*50, 50, 50));
    mobileImage.setOrigin(mobileImage.getOrigin().x + 25, mobileImage.getOrigin().y + 25);
    printf("here\n");

    active = 0;
}

// define how this machine can move (can set limitations)
void Mobile::Update(){
    // A = LEFT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      if(mobileImage.getPosition().x < 750) {
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = -5;
          body->SetLinearVelocity( vel );
          source.x++;
      }
    }

    // D = RIGHT
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      if(mobileImage.getPosition().x < 750) {
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = 5;
          body->SetLinearVelocity( vel );
          source.x++;
    }
  }

  // set velocity to 0 if neither direction is pressed
  if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    body->SetLinearVelocity(b2Vec2(0,0));
    source.x++;
  }

  // sprite assignment
  if (active){
    source.y = 0;
  }
  else { //active == false
    source.y = 1;
  }

  cout << "Mobile active? " << active <<"\n";

  if (source.x * 50 >= mobileTexture.getSize().x){
    source.x = 0;
  }

  mobileImage.setTextureRect(sf::IntRect(source.x*50, source.y*50, 50, 50));

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
