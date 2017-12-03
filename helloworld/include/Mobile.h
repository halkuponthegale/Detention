#include "Machine.h"

class Mobile: public Machine{
public:
  // constructor
  Mobile(double xo, double yo);

  // process input
  void Update();

  // reinstate gravity and reset velocity to 0, but falling
  void getOut(){
    body->SetGravityScale(1);
    body->SetLinearVelocity(b2Vec2(0,1));
  }

  // update theta
  void rotate(double dTheta){ theta += dTheta; }
  // accessor
  double getTheta(){ return theta; }

  // set physics body
  void setBody(b2Body& bod){ body = &bod; }

  // set body to physics world
  void setWorld(b2World& World);

private:
  double theta;
};
