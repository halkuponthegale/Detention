#pragma once
#include "Machine.h"
#include <string>
#include <fstream>

using namespace std;

class Mobile: public Machine{
public:

  // used for spritesheet
  sf::Texture mobileTexture;
  sf::Sprite mobileImage;
  sf::Vector2i source;
//  bool active = false;


  // constructor
  Mobile(double xo, double yo);

  // process input
  void Update();
  void adjustHeight();
  // reinstate gravity and reset velocity to 0, but falling
  void getOut(){
    body->SetGravityScale(1);
    body->SetLinearVelocity(b2Vec2(0,1));
  }

  void isActive(int status){
    active = status;
    // cout << "set active in mobile.h\n";
  }

  // update theta
  void rotate(double dTheta){ theta += dTheta; }
  // accessor
  double getTheta(){ return theta; }

  // set physics body
  void setBody(b2Body& bod){ body = &bod; }
  void add_box(Box *b){ boxlist[cur_box_idx] = b; cur_box_idx++; }
  void add_wall(Wall *w){walllist[cur_wall_idx] = w; cur_wall_idx++; }
  // set body to physics world
  void setWorld(b2World& World);

private:
  double theta;
};
