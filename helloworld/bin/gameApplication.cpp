#include <SFML/Graphics.hpp>

#include "View.h"
#include "MenuView.h"

// push game display onto play_state, keep main loop clean
View game_view;


int main(int argc, char** argv)
{
    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Detention", sf::Style::Close);

    // set "gameplay" window to main window to draw
    game_view.setWindow(&App);
    game_view.setView(new MenuView());

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

        // clear screen and fill with black
        App.clear(sf::Color::Black);

        game_view.Update();
        game_view.Render();


        // display
        App.display();


    }

    // Done.
    return 0;
}
