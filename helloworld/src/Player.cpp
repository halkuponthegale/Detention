
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "iostream"

    // Constructor
    // Creates a simple rectanglein place of player sprite
    Player::Player() {
        playerbody.setSize(sf::Vector2f(10,30));
        playerbody.setPosition(0,0);
        //inMachine = true;
        in_machine = 0;
    }


    // Moves the player up, unless it's already at the top of the screen
    void Player::player_up() {
        if(playerbody.getPosition().y > 0) {
            //playerbody.move(0, -.1);
          //  this->launch(12.0,M_PI/4);
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

            in_machine = 0;

            // TEMPORARY
            my_machine -> setColor(sf::Color::Red);
        }
    }

    // If user presses WASD direction, move the player box
    // (if in machine, move in background)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player_up();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
           player_left();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player_down();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player_right();
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
          std::cout << vx <<"," << vy;
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
    int Player::intersects(Machine *m){
    if(playerbody.getGlobalBounds().intersects(m -> getShape().getGlobalBounds())){
        in_machine = 1;
        my_machine = m;

        // TEMPORARY
        my_machine -> setColor(sf::Color::Green);
    }
    else{
        in_machine = 0;
    }
}
