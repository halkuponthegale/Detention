#include "Builder.h"

// constructor
Builder::Builder(double xo, double yo){

    // create machine body rectangle
    machine_body.setSize(sf::Vector2f(50,50));
    machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
    machine_body.setPosition(xo, yo);
    machine_body.setFillColor(sf::Color::Red);

    // initial x, y pos
    x = xo; y = yo;

    cur_box_idx = 0;
    carrybox = 0;
}

// define how this machine can move (can set limitations)
void Builder::Update(){
    // W = jump
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && body->GetLinearVelocity().y == 0) {
        if(machine_body.getPosition().y > 0) {
            jump();
        }
    }
    // A = move left
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(machine_body.getPosition().x > 0) {
          // update velocity
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = -5;
          body->SetLinearVelocity( vel );

          // facing left
          facing = 0;
        }
    }
    // D = move right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(machine_body.getPosition().x < 750) {
            // update velocity
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );

            // facing right
            facing = 1;
        }
    }

    // if you're carrying a box, move it too
    if(carrybox){
      mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 60)/30.0),0);
    }

    // Space = pick up/set down Box
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        int intersect = 0;
        int i;

        // loop through boxes until find one that is touching and on same y level
        for(i = 0; i < cur_box_idx; i++){
            if(intersects(boxlist[i]) &&  (boxlist[i] -> getBody()->GetPosition().y < (body ->GetPosition().y + 1))
                                      &&  (boxlist[i] -> getBody()->GetPosition().y > (body ->GetPosition().y - 1))){
                intersect = 1;
                break;
            }
        }

        // if you're carrying a box, not jumping, and it's not the initial space press, set it down the way you're facing
        if(carrybox && body->GetLinearVelocity().y == 0 && !space){
            // if facing left, place left
            if(facing == 0){
                mybox->getBody()->SetTransform(b2Vec2((machine_body.getPosition().x - 60)/30.0, machine_body.getPosition().y/30.0),0);
                mybox->getBody()->SetGravityScale(1);
            }
            // if facing right, place right
            else{
                mybox->getBody()->SetTransform(b2Vec2((machine_body.getPosition().x + 60)/30.0, machine_body.getPosition().y/30.0),0);
                mybox->getBody()->SetGravityScale(1);

            }

            // no longer carrying a box
            carrybox = 0;
        }
        // if you aren't carrying a box and you're intersecting one, pick it up
        else if(intersect && !space){
            mybox = boxlist[i];
            mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 60)/30.0),0);
            mybox->getBody()->SetGravityScale(0);
            carrybox = 1;
        }
        space = 1;

    }
    else{
        space = 0;
    }
}

void Builder::jump(){
  machine_body.move(0, -1);

  double velocity = 180;
  double theta = M_PI/2;

  b2Vec2 vel = body->GetLinearVelocity();
  double vx = cos(theta)* velocity;
  double vy = sin(theta)* velocity;
  double impx = (vel.x)*body->GetMass();
  double impy = (vel.y)*body->GetMass();

  body->ApplyLinearImpulse( b2Vec2(vx, -vy), body->GetWorldCenter(), true );
}


void Builder::setWorld(b2World& World){
  static const float SCALE = 30.f;

  b2BodyDef BodyDef2;
  BodyDef2.position = b2Vec2(x/SCALE, y/SCALE);
  BodyDef2.type = b2_dynamicBody;
  body = World.CreateBody(&BodyDef2);

  b2PolygonShape Shape2;
  Shape2.SetAsBox((50.f/2)/SCALE, (50.f/2)/SCALE);
  b2FixtureDef FixtureDef2;
  FixtureDef2.density = 10.f;
  FixtureDef2.friction = 1;
  FixtureDef2.shape = &Shape2;
  FixtureDef2.filter.maskBits = ~0x0002;
  FixtureDef2.filter.categoryBits = ~0x0007;
  FixtureDef2.filter.groupIndex = -2;

  body->CreateFixture(&FixtureDef2);
  body->SetFixedRotation(true);

}
