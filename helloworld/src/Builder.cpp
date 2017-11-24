#include "Builder.h"

// constructor
Builder::Builder(double xo, double yo){

    machine_body.setSize(sf::Vector2f(50,50));
    machine_body.setPosition(0,0);
    machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
    machine_body.setFillColor(sf::Color::Red);

    x = xo; y = yo;

    machine_body.setPosition(xo, yo);

    cur_box_idx = 0;
    carrybox = 0;
}

// define how this machine can move (can set limitations)
void Builder::Update(){
    // move up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && body->GetLinearVelocity().y == 0) {
        if(machine_body.getPosition().y > 0) {
            machine_body.move(0, -1);
            this->launch(180,M_PI/2);

            // if you have a box, move it as well
            if(carrybox){
              // mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 60)/30.0),0);
              //  mybox -> move(0,-1);
            }
        }
    }
    // move left
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(machine_body.getPosition().x > 0) {
          //  machine_body.move(-1, 0);
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = -5;
          body->SetLinearVelocity( vel );

          facing = 0;

            // if you have a box, move it as well
            if(carrybox){
              // mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 60)/30.0),0);
              // mybox -> move(-1,0);
            }
        }
    }
    // move down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if(machine_body.getPosition().y < 550) {  // check
            machine_body.move(0, 1);

             // if you have a box, move it as well
           if(carrybox){

                // mybox -> move(0,1);
                // mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 60)/30.0),0);

            }
        }
    }
    // move right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(machine_body.getPosition().x < 750) {  // check
            // machine_body.move(1, 0);
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );
            facing = 1;

             // if you have a box, move it as well
           if(carrybox){
                // mybox -> move(1,0);
                // mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 60)/30.0),0);
            }
        }
    }

    if(carrybox){
      mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 60)/30.0),0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        int intersect = 0;
        int i;

        for(i = 0; i < cur_box_idx; i++){
          //std:: cout << touching(boxlist[i]) << " ";
          // std::cout << boxlist[i] -> getShape().getPosition().y << "\n";
          // std::cout << machine_body.getPosition().y << "\n\n";
            if(intersects(boxlist[i]) &&  (boxlist[i] -> getBody()->GetPosition().y < (body ->GetPosition().y + 1))){
                intersect = 1;
                break;
            }
        }
        //std:: cout << "|";
        // if you're carrying a box and it's not the initial space press, set it down the way you're facing
        if(carrybox && !space){
            if(facing == 0){ // if facing left
                mybox->getBody()->SetTransform(b2Vec2((machine_body.getPosition().x - 60)/30.0, machine_body.getPosition().y/30.0),0);
            }
            else{
                mybox->getBody()->SetTransform(b2Vec2((machine_body.getPosition().x + 60)/30.0, machine_body.getPosition().y/30.0),0);
            }
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


void Builder::launch(double velocity, double theta){
    b2Vec2 vel = body->GetLinearVelocity();
    //if(inMachine == true){
      double vx = cos(theta)* velocity;
      double vy = sin(theta)* velocity;
      double impx = (vel.x)*body->GetMass();
      double impy = (vel.y)*body->GetMass();
      //std::cout << vx <<"," << vy;
      body->ApplyLinearImpulse( b2Vec2(vx, -vy), body->GetWorldCenter(), true );
      //inMachine = false;
    //}
}

void Machine::setWorld(b2World& World){
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
  body->CreateFixture(&FixtureDef2);
  body->SetFixedRotation(true);
  //builderBody->SetGravityScale(0);

  //builder.setBody(*builderBody);
}
