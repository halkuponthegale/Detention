#ifndef EXIT_H
#define EXIT_H

#include <SFML/Graphics.hpp>
#include "Box2D.h"

class Exit{
public:
  Exit(double cx, double cy){
    bounds.setSize(sf::Vector2f(40, 80));
    bounds.setOrigin(bounds.getOrigin().x + 20, bounds.getOrigin().y + 40);
    bounds.setPosition(cx, cy);
    bounds.setFillColor(sf::Color(130,255,0));

    x = cx; y = cy;
  }

  sf::RectangleShape getShape(){
    return bounds;
  }

  void setWorld(b2World& World){

    static const double SCALE = 30.f;

    b2BodyDef BodyDef2;
    BodyDef2.position = b2Vec2(x/SCALE, y/SCALE);
    BodyDef2.type = b2_dynamicBody;
    bod = World.CreateBody(&BodyDef2);

    b2PolygonShape Shape2;
    Shape2.SetAsBox((40/2)/SCALE, (80/2)/SCALE);
    b2FixtureDef FixtureDef2;
    FixtureDef2.density = 0.f;
    FixtureDef2.friction = 1;
    FixtureDef2.filter.maskBits = ~0x0002;
    FixtureDef2.filter.categoryBits = ~0x0005;

    FixtureDef2.shape = &Shape2;

    bod->CreateFixture(&FixtureDef2);
    bod->SetFixedRotation(true);
    bod->SetGravityScale(1);
  }

  b2Body* getBody(){
    return bod;
  }

  sf::RectangleShape bounds;

private:
  b2Body *bod;
  double x, y;
};

#endif
