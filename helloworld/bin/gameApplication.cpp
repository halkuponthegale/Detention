#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameView.h"
#include "MenuView.h"

// push game display onto play_state, keep main loop clean
GameView game_view;
int top_lvl;

// global sound vars
sf::SoundBuffer buffer;
sf::SoundBuffer buffer2;
sf::Sound sound;
sf::Sound sound2;
sf::Music music;


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



        // clear screen and fill with black
        App.clear(sf::Color::Black);

        // call Update and Render() on game_view
        if(App.hasFocus())
          game_view.Update();
        game_view.Render();


        // display
        App.display();


    }

    // Done.
    return 0;
}
