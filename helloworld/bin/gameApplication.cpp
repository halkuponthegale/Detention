#include <SFML/Graphics.hpp>

#include "View.h"
#include "MenuView.h"
#include "Player.h"

// push game display onto play_state, keep main loop clean
View game_view;
int top_lvl;
player PlayerInstance;


int main(int argc, char** argv)
{
    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Detention", sf::Style::Close);

    // set "gameplay" window to main window to draw
    game_view.setWindow(&App);
    game_view.setView(new MenuView());
    top_lvl = 1;

    // start main loop
    while(App.isOpen())
    {
        // process events
        sf::Event Event;
        while(App.pollEvent(Event))
        {
            // Exit
            if(Event.type == sf::Event::Closed)
            App.close();
        }
        
         // If user presses up or down, move the player paddle
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    PlayerInstance.player_up();
            }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    PlayerInstance.player_down();
            }
        
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                   PlayerInstance.player_left();
            }
        
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    PlayerInstance.player_right();
            }

            else { // If they press something other than up or down, don't do anything
            }


        // clear screen and fill with black
        App.clear(sf::Color::Black);
        
        // Draw player
        App.draw(playerInstance.playerbody);

        game_view.Update();
        game_view.Render();


        // display
        App.display();

    
    }

    // Done.
    return 0;
}
