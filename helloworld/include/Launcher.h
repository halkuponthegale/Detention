#include "Machine.h"

class Launcher: public Machine{
public:
  void rotate(double dTheta){
    theta += dTheta;
  }
  double getTheta(){
    return theta;
  }
  void setBody(b2Body& bod){
    body = &bod;
  }
  Launcher(){

      machine_body.setSize(sf::Vector2f(50,50));
      machine_body.setPosition(150,150);
      machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
      machine_body.setFillColor(sf::Color::Yellow);
      theta = M_PI/2;

  }

  // define how this machine can move (can set limitations)
  void Update(){
      // move up
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
          if(machine_body.getPosition().y > 0) {
              machine_body.move(0, -1);

              // if you have a box, move it as well

          }
      }
      // move left
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
          if(theta <= 5*(M_PI/6) ) {
            //  machine_body.move(-1, 0);
            theta += M_PI/50;


          }
      }
      // move down
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
          if(machine_body.getPosition().y < 550) {  // check
              machine_body.move(0, 1);


          }
      }
      // move right
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(theta >=(M_PI/6) ) {
          //  machine_body.move(-1, 0);
          theta -= M_PI/50;


        }
      }
    }

private:
  double theta;
};
