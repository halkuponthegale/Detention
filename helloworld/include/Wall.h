#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include "Box2D.h"

class Wall{
public:
  Wall(double cx, double cy, double hw, double hh, double fric){
    x = cx; y = cy; w = 2*hw; h = 2*hh;

    wall.setSize(sf::Vector2f(w, h));
    wall.setOrigin(wall.getOrigin().x + hw, wall.getOrigin().y + hh);
    wall.setPosition(cx, cy);
    wall.setFillColor(sf::Color::Black);

    friction = fric;

  }

  sf::RectangleShape getShape(){
    return wall;
  }

  void setWorld(b2World& World){

    static const double SCALE = 30.f;

    b2BodyDef BodyDef2;
    BodyDef2.position = b2Vec2(x/SCALE, y/SCALE);
    BodyDef2.type = b2_staticBody;
    bod = World.CreateBody(&BodyDef2);

    b2PolygonShape Shape2;
    Shape2.SetAsBox((w/2)/SCALE, (h/2)/SCALE);
    b2FixtureDef FixtureDef2;
    FixtureDef2.density = 0.f;
    if(friction == 0)
      FixtureDef2.friction = 0.f;
    FixtureDef2.shape = &Shape2;

    bod->CreateFixture(&FixtureDef2);
    bod->SetFixedRotation(true);
    bod->SetUserData( (void*)(int)201 );
  }

private:
  sf::RectangleShape wall;
  b2Body *bod;
  double x, y, w, h, friction;
};



#endif
