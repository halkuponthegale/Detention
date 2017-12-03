#include "Machine.h"

class Launcher: public Machine{
public:
  // constructor
  Launcher(double xo, double yo);

  // process input
  void Update();

  // update theta
  void rotate(double dTheta){ theta += dTheta; }
  // accessor
  double getTheta(){ return theta; }

  // set physics body
  void setBody(b2Body& bod){ body = &bod; }
  // set body to physics world
  void setWorld(b2World& World);

  sf::RectangleShape barrel,powerBG,power;

private:
  double theta;

};
