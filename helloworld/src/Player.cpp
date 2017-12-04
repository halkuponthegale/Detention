
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "iostream"

// Constructor
Player::Player(double xo, double yo) {

    // Load player spritesheet from png file (in include folder)
    if(!playerTexture.loadFromFile("../include/sprites/FinalCalSprite.png",sf::IntRect(0, 0, 100, 140)))
    {
    }

    playerImage.setTexture(playerTexture);

    playerbody.setSize(sf::Vector2f(25,35)); //used in getShape, gives a rect the same dimensions as the player sprite
    //playerImage.setPosition(xo,yo);
    playerImage.setOrigin(playerImage.getOrigin().x + 25, playerImage.getOrigin().y + 17.5);

    x = xo; y = yo;

    in_machine = 0;
    mType = -1;
    jumping = 0;
    facing = 1;
}


// makes player jump (< 1 block)
void Player::player_up() {
    if(playerImage.getPosition().y > 0 && body -> GetLinearVelocity().y == 0) {
        this->launch(1.8,M_PI/2);

    }
}


// Moves the player left
void Player::player_left() {
    if(playerImage.getPosition().x > 0) {  // check
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = -5;
        body->SetLinearVelocity( vel );

        source.y = Left;
        source.x++;
    }
}


// Moves the player right, unless it's already at the right of the screen
void Player::player_right() {
    if(playerImage.getPosition().x < 800) {  // check
        //playerbody.move(.1, 0);  // check
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = 5;
        body->SetLinearVelocity( vel );

        source.y = Right;
        source.x++;
    }
}
void Player::Update(){

    // if player in machine, call update on that machine object (handle appropriate moves)
    if(in_machine){
      // builder = 0, launcher = 1, mobile = 2
      my_machine->isActive(1);
      my_machine -> Update();

      // down (and box is not moving up or down) = get out of machine
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && my_machine -> getBody() -> GetLinearVelocity().y == 0){

          in_machine = 0;
          my_machine->isActive(0);


          // TEMPORARY
          if(mType==0)
            my_machine -> setColor(sf::Color::Red);
          else if(mType==1)
            my_machine -> setColor(sf::Color(40,40,40));
          else if(mType==2)
            my_machine -> setColor(sf::Color::Magenta);

          // reset player position
          body->SetTransform(my_machine -> getBody()->GetPosition(),0);
          body->SetLinearVelocity(b2Vec2(0,1));


          my_machine->getBody()->SetLinearVelocity(b2Vec2(0,0));
          my_machine->getBody()->SetGravityScale(1);
          my_machine->Update();
          my_machine->getOut();

          mType = -1;

      }

      // if in launcher, process launch power
      if(mType == 1){

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
          if(my_machine->launchVel <5){
            my_machine->launchVel += .05;
          }

        }else{
          if(my_machine->launchVel!=0){
            launch(my_machine->launchVel,my_machine->getTheta());
            my_machine->launchVel = 0;
            in_machine = 0;
            mType=-1;
            my_machine -> setColor(sf::Color(40,40,40));
            body->SetTransform(my_machine -> getBody()->GetPosition(),0);
            my_machine -> Update();
          }
        }
      }
    }
    // else if player not in machine, process input on player
    else{

        // If user presses WASD direction, move the player box
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                facing = 1;
                player_right();
        }

        if (source.x * 25 >= playerTexture.getSize().x)
            source.x = 0;
        playerImage.setTextureRect(sf::IntRect(source.x*25, source.y*35, 25, 35));

    }

}

void Player::launch(double velocity, double theta){
    b2Vec2 vel = body->GetLinearVelocity();

    double vx = cos(theta)* velocity;
    double vy = sin(theta)* velocity;
    double impx = (vel.x)*body->GetMass();
    double impy = (vel.y)*body->GetMass();

    body->ApplyLinearImpulse( b2Vec2(vx, -vy), body->GetWorldCenter(), true );

}


// Puts paddle back to original position
void Player::reset() {
    playerImage.setPosition(700,300);
}
// Accessor method for rectangle shape
sf::RectangleShape Player::getShape(){
    return playerbody;
}

// return if player in machine
int Player::inMachine(){
    return in_machine;
}

// check if player intersecting machine, if so, enter machine
int Player::intersects(std::vector<Machine *> marr, std::vector<int> types){

  int desired = -1;
  int type = -1;

  for(unsigned i = 0; i < marr.size(); i++){
    // account for dome shape on launcher
    int intersects_dome = 0;
    if(types[i] == 1){
      intersects_dome = playerImage.getGlobalBounds().intersects(marr[i] -> dome.getGlobalBounds());
    }

    // if player body intersects machine box
    if(playerImage.getGlobalBounds().intersects(marr[i] -> getShape().getGlobalBounds()) || intersects_dome){
      // if machine is not currently falling (for mobile bug)
      if(marr[i] -> getBody() -> GetLinearVelocity().y != 0) { break; }
        //builder = 0, launcher = 1, mobile = 2;
        // priority system for entering: mobile, builder, launcher
        if(types[i] == 2){
          desired = i;
          type = 2;
        }
        else if(types[i] == 0 && (type == -1 || type == 1)){
          desired = i;
          type = 0;
        }
        else if(types[i] == 1 && (type == -1)){
            desired = i;
            type = 1;
        }
      }
    }

  // set player to desired machine
  if(desired != -1){
    in_machine = 1;
    my_machine = marr[desired];


    this->mType = types[desired];

    // if in mobile machine, update initial height
    if(mType==2){
      my_machine->getBody()->SetGravityScale(0);
      b2Vec2 pos = my_machine->getBody()->GetPosition();
      my_machine->getBody()->SetTransform(b2Vec2(pos.x,pos.y-2),my_machine->getBody()->GetAngle());
      my_machine->isActive( 1 ); //used in Mobile.cpp for spritesheet animation
    }

    body->SetLinearVelocity(b2Vec2(0,0));

    // TEMPORARY
    my_machine -> setColor(sf::Color::Green);

  }
  else{
    in_machine = 0;
  }
}
