
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "iostream"

    // Constructor
    // Creates a simple rectanglein place of player sprite
    Player::Player() {
        playerbody.setSize(sf::Vector2f(10,30));
        playerbody.setOrigin(playerbody.getOrigin().x + 5, playerbody.getOrigin().y + 15);
        playerbody.setPosition(80,80);
        //inMachine = true;
        in_machine = 0;
        mType = -1;
        jumping = 0;
        facing = 1;
    }


    // Moves the player up, unless it's already at the top of the screen
    void Player::player_up() {
        if(playerbody.getPosition().y > 0 && body -> GetLinearVelocity().y == 0) {
            //playerbody.move(0, -.1);
  //        if(facing == 0){ // if facing left
            this->launch(1.8,M_PI/2);
//          }
          // else{ // if facing right
          //   this->launch(3.0,M_PI/2);
          // }
        }
    }


    // Moves the player down, unless it's already at the bottom of the screen
    void Player::player_down() {
        if(playerbody.getPosition().y < 570) {
            //playerbody.move(0, .1);

        }
    }


    // Moves the player left, unless it's already at the left of the screen
    void Player::player_left() {
        if(playerbody.getPosition().x > 0) {  // check
            //playerbody.move(-.1, 0);  // check
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = -5;
            body->SetLinearVelocity( vel );
        }
    }


    // Moves the player right, unless it's already at the right of the screen
    void Player::player_right() {
        if(playerbody.getPosition().x < 800) {  // check
            //playerbody.move(.1, 0);  // check
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );
        }
    }
    void Player::Update(){
    // if player in machine, call update on that machine object (handle appropriate moves)
    if(in_machine){
        my_machine -> Update();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

            my_machine->getBody()->SetLinearVelocity(b2Vec2(0,0));
            my_machine->getBody()->SetGravityScale(1);
            my_machine->Update();
            my_machine->getOut();

            in_machine = 0;

            // TEMPORARY
            if(mType==0)
              my_machine -> setColor(sf::Color::Red);
            else if(mType==1)
              my_machine -> setColor(sf::Color::Yellow);
            else if(mType==2)
              my_machine -> setColor(sf::Color::Magenta);

            // reset player position
            body->SetTransform(my_machine -> getBody()->GetPosition(),0);
            mType = -1;

        }
        if(mType == 1){

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
              in_machine = 0;
              mType=-1;
              my_machine -> setColor(sf::Color::Yellow);
              body->SetTransform(my_machine -> getBody()->GetPosition(),0);
              launch(5,my_machine->getTheta());
          }
        }
    }
    else{
        // If user presses WASD direction, move the player box
        // (if in machine, don't move)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
              if(!jumping){
                  jumping = 1;
                  player_up();
              }
        }
        else{
          jumping = 0;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
               facing = 0;
               player_left();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player_down();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                facing = 1;
                player_right();
        }
        //std::cout << mType;

    }

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    //     in_machine = 1;
    // }
}
    void Player::launch(double velocity, double theta){
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


    // Puts paddle back to original position
    void Player::reset() {
        playerbody.setPosition(700,300);
    }
    // Accessor method for rectangle shape
    sf::RectangleShape Player::getShape(){
        return playerbody;
  }

    // return if player in machine
    int Player::inMachine(){
        return in_machine;
    }
    int Player::intersects(std::vector<Machine *> marr, std::vector<int> types){
      for(unsigned i = 0; i < marr.size(); i++){
    if(playerbody.getGlobalBounds().intersects(marr[i] -> getShape().getGlobalBounds())){
        in_machine = 1;
        my_machine = marr[i];
        //std::cout << types[i];
        this->mType = types[i];
        if(mType==2){
          my_machine->getBody()->SetGravityScale(0);
          b2Vec2 pos = my_machine->getBody()->GetPosition();
          my_machine->getBody()->SetTransform(b2Vec2(pos.x,pos.y-2),my_machine->getBody()->GetAngle());
        }
        //std::cout << mType;
        body->SetLinearVelocity(b2Vec2(0,0));
        //->SetGravityScale(0);
        // TEMPORARY
        my_machine -> setColor(sf::Color::Green);
      //  std::cout << in_machine;
        break;
    }
    else{
        in_machine = 0;
      //  body->SetGravityScale(1);
    }
  }
}
