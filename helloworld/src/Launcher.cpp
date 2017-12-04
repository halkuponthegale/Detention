#include "Launcher.h"

Launcher::Launcher(double xo, double yo){

    // make machine body
    machine_body.setSize(sf::Vector2f(50,25));
    machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y);
    machine_body.setPosition(xo, yo);

    machine_body.setFillColor(sf::Color(40,40,40));
    theta = M_PI/2;

    // make dome
    dome.setRadius(25);
    dome.setOrigin(dome.getOrigin().x + 25, dome.getOrigin().y + 25);
    dome.setPosition(xo,yo);
    dome.setFillColor(sf::Color(40,40,40));

    // make barrel and power bar
    barrel = sf::RectangleShape(sf::Vector2f(20,55));
    barrel.setPosition(350,200);
    barrel.setOrigin(10,55);
    barrel.setFillColor(sf::Color::Black);
    powerBG= sf::RectangleShape(sf::Vector2f(5,45));
    powerBG.setPosition(350,200);
    powerBG.setOrigin(2.5,45);
    powerBG.setFillColor(sf::Color::White);
    powerBG.rotate(180);
    power= sf::RectangleShape(sf::Vector2f(5,0));
    power.setPosition(350,200);
    power.setOrigin(2.5,45);
    power.setFillColor(sf::Color::Red);
    power.rotate(180);

    // initial x y pos
    x = xo; y = yo;

    launchVel = 0;
}


// define how this machine can move (can set limitations)
void Launcher::Update(){
  power.setSize(sf::Vector2f(5,9.0*launchVel));

    // A = rotate barrel left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(theta <= 5*(M_PI/6) ) {
          theta += M_PI/50;


        }
    }
    // D = rotate barrel right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      if(theta >=(M_PI/6) ) {
        theta -= M_PI/50;


      }
    }
  }

 void Launcher::setWorld(b2World& World){
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
    FixtureDef3.filter.groupIndex = -2;

    body->CreateFixture(&FixtureDef3);
    body->SetFixedRotation(true);
 }
