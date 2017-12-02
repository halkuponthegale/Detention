#include "Machine.h"

class Mobile: public Machine{
public:
  Mobile(double xo, double yo){

      machine_body.setSize(sf::Vector2f(50,50));
      machine_body.setPosition(0,0);
      machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
      machine_body.setFillColor(sf::Color::Magenta);

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

      // if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      //     if(machine_body.getPosition().y > 0) {
      //         machine_body.move(0, -1);
      //
      //         // if you have a box, move it as well
      //
      //     }
      // }

      // move left
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(machine_body.getPosition().x < 750) {  // check
            // machine_body.move(1, 0);
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = -5;
            body->SetLinearVelocity( vel );
        }
      }
      // // move down
      // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      //     if(machine_body.getPosition().y < 550) {  // check
      //         machine_body.move(0, 1);
      //
      //
      //     }
      // }
      // move right
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(machine_body.getPosition().x < 750) {  // check
            // machine_body.move(1, 0);
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );
      }
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      body->SetLinearVelocity(b2Vec2(0,0));
    }
  }

  void getOut(){
    // b2Vec2 vel = body->GetLinearVelocity();
    // vel.x = 0;
    // vel.y = -1;
    // body->SetLinearVelocity(vel);
    body->SetGravityScale(1);
    body->SetLinearVelocity(b2Vec2(0,1));
  }

  void setWorld(b2World& World){
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
    body->CreateFixture(&FixtureDef4);
    body->SetFixedRotation(true);
    //builderBody->SetGravityScale(0);

    // mobile.setBody(*mobileBody);
  }

private:
  double theta;
};
