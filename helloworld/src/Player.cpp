#include <SFML/Graphics.hpp>
#include "Player.h"
#include "iostream"

// Player class 
// Player movements (left, right)
// When the player is in a machine, calls the update method of that machine
// Sets the sprite used for the player, which gets drawn in PlayView


// Constructor - takes parameters for x, y, and character name
Player::Player(double xo, double yo, std::string name) {

////////////////////// SPRITE INIT ///////////////////////
    // Choose the character based on name parameter - Cal appears in evey level, Kevin appears only in final level
    // playerTexture is the full 100x140p sprite sheet
    // playerTexture - load the appropriate player spritesheet from png file (from include folder)
    if(name == "Cal"){
      if(!playerTexture.loadFromFile("../include/sprites/FinalCalSprite.png",sf::IntRect(0, 0, 100, 140)))
      {}
    }
    else{
      if(!playerTexture.loadFromFile("../include/sprites/kevin.png",sf::IntRect(0, 0, 100, 140)))
      {}
    }

    // Set playerImage to the current 25x35p sprite
    playerImage.setTexture(playerTexture);
    playerImage.setTextureRect(sf::IntRect(source.x*25, source.y*35, 25, 35));
    
/////////////////////////////////////////////////////////
    
    // Set the center of the player
    playerImage.setOrigin(playerImage.getOrigin().x + 12, playerImage.getOrigin().y + 17.5);
    
    x = xo; y = yo;

    // Set variables
    in_machine = 0;
    mType = -1;
    jumping = 0;
    facing = 1;
    lastVelocity=0;

}


// Makes player jump (limited to < 1 block)
void Player::player_up() {
    if(playerImage.getPosition().y > 0 && body -> GetLinearVelocity().y == 0) {
        this->launch(1.8,M_PI/2);
    }
}


// Moves the player left
void Player::player_left() {
    if(playerImage.getPosition().x > 0) {
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = -5;
        body->SetLinearVelocity( vel );

        source.y = Left;
        source.x++;
    }
}


// Moves the player right
void Player::player_right() {
    if(playerImage.getPosition().x < 800) {
        //playerbody.move(.1, 0);  // check
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = 5;
        body->SetLinearVelocity( vel );

        source.y = Right;
        source.x++;
    }
}


// Update method - Handles input
// Calls movement methods on player (if alone) or on machine (if player in machine)
// Machine codes: builder = 0, launcher = 1, mobile = 2
void Player::Update(){

    // IF PLAYER IN MACHINE, call update on that machine object (handle appropriate moves)
    if(in_machine){
      my_machine->isActive(1); // Used in machine classes for sprite handling
      my_machine -> Update();

      // If user presses down (and box is not moving up or down) = get out of machine
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && my_machine -> getBody() -> GetLinearVelocity().y == 0){
          in_machine = 0;
          my_machine->isActive(0);

          // reset player position
          body->SetTransform(my_machine -> getBody()->GetPosition(),0);
          body->SetLinearVelocity(b2Vec2(0,1));
          
          // set machine in accordance w/player exiting machine
          my_machine->getBody()->SetLinearVelocity(b2Vec2(0,0));
          my_machine->getBody()->SetGravityScale(1);
          my_machine->Update();
          my_machine->getOut();

          mType = -1;

      }

      // If player in launcher, and user presses/holds space bar,
      // process launch power (limited at velocity of 5) and catapult player
      if(mType == 1){
       
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
          if(my_machine->launchVel <5){
            my_machine->launchVel += .05;
          }
        }
          else {
          if(my_machine->launchVel!=0){
            launch(my_machine->launchVel,my_machine->getTheta());

            AudioManager::play_launch(); // play launch noise

            // Set machine in acordance with player exiting machine
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
    
    
    // else IF PLAYER NOT IN MACHINE, process input on player
    else{

        // If user presses WASD direction, move the player's position
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

        // Update the player sprite
        if (source.x * 25 >= playerTexture.getSize().x)
            source.x = 0;
        playerImage.setTextureRect(sf::IntRect(source.x*25, source.y*35, 25, 35));

    }

}


// Launch the player (when in launcher machine)
void Player::launch(double velocity, double theta){
    b2Vec2 vel = body->GetLinearVelocity();

    double vx = cos(theta)* velocity;
    double vy = sin(theta)* velocity;
    double impx = (vel.x)*body->GetMass();
    double impy = (vel.y)*body->GetMass();

    body->ApplyLinearImpulse( b2Vec2(vx, -vy), body->GetWorldCenter(), true );

}


// Accessor method for rectangle shape
// Gives rect of player's dimensions
sf::RectangleShape Player::getShape(){
    playerbody.setSize(sf::Vector2f(25,35));
    return playerbody;
}


// Return whether player is in machine
int Player::inMachine(){
    return in_machine;
}


// Check if player intersecting machine, if so, enter machine
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
      // if machine is not currently falling (fixes previous mobile bug)
      if(abs(marr[i] -> getBody() -> GetLinearVelocity().y) > 0.0001) { break; }
        // Machine types: builder = 0, launcher = 1, mobile = 2
        // If player intersects multiple machines, use priority system for entering: mobile, builder, launcher
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

    }
    my_machine->isActive( 1 ); //used in Mobile.cpp for spritesheet animation

    body->SetLinearVelocity(b2Vec2(0,0));

      

  }
  else{
    in_machine = 0;
  }

  return 0;
}
