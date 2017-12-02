#include "Machine.h"

class Launcher: public Machine{
public:
  Launcher(double xo, double yo){

      machine_body.setSize(sf::Vector2f(50,50));
      machine_body.setPosition(0,0);
      machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
      machine_body.setFillColor(sf::Color::Yellow);
      theta = M_PI/2;

      barrel = sf::RectangleShape(sf::Vector2f(5,45));
			barrel.setPosition(350,200);
			barrel.setOrigin(2.5,45);
      barrel.setFillColor(sf::Color::Black);

      x = xo; y = yo;

      machine_body.setPosition(xo, yo);

  }

  void rotate(double dTheta){
    theta += dTheta;
  }
  double getTheta(){
    return theta;
  }
  void setBody(b2Body& bod){
    body = &bod;
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

   void setWorld(b2World& World){
     static const float SCALE = 30.f;


      b2BodyDef BodyDef3;
   		BodyDef3.position = b2Vec2(x/SCALE, y/SCALE);
   		BodyDef3.type = b2_dynamicBody;
   		body = World.CreateBody(&BodyDef3);

   		b2PolygonShape Shape3;
   		Shape3.SetAsBox((50.f/2)/SCALE, (50.f/2)/SCALE);
   		b2FixtureDef FixtureDef3;
   		FixtureDef3.density = 100.f;
   		FixtureDef3.friction = 1;
   		FixtureDef3.shape = &Shape3;
      FixtureDef3.filter.maskBits = ~0x0002;
      FixtureDef3.filter.categoryBits = ~0x0006;
   		body->CreateFixture(&FixtureDef3);
   		body->SetFixedRotation(true);
   		//builderBody->SetGravityScale(0);

   	// 	launcher.setBody(*launcherBody);
   }

   sf::RectangleShape barrel;

private:
  double theta;
};
