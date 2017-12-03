#include "ControlsView.h"
#include "MenuView.h"

void ControlsView::Init(sf::RenderWindow *window){
  font.loadFromFile("../include/Fonts/Beyblade Metal Fight Font.ttf");

	// create texts
	header.setFont(font);
  wasd.setFont(font);
  updown.setFont(font);
  space.setFont(font);
  goback.setFont(font);

	header.setCharacterSize(80);
  wasd.setCharacterSize(30);
  updown.setCharacterSize(30);
  space.setCharacterSize(30);
  goback.setCharacterSize(25);


	header.setString("Controls");
  wasd.setString("WASD = Move Player/Machine");
  updown.setString("Up/Down = Get in/out of Machine");
  space.setString("Space = Use Machine's ability (if exists)");
  goback.setString("Backspace = Return to Menu");

	sf::FloatRect header_bounds = header.getLocalBounds();
  sf::FloatRect wasd_bounds = wasd.getLocalBounds();
  sf::FloatRect updown_bounds = updown.getLocalBounds();
  sf::FloatRect space_bounds = space.getLocalBounds();
  sf::FloatRect goback_bounds = goback.getLocalBounds();

	header.setOrigin(header_bounds.width / 2, header_bounds.height / 2);
  wasd.setOrigin(wasd_bounds.width / 2, wasd_bounds.height / 2);
  updown.setOrigin(updown_bounds.width / 2, updown_bounds.height / 2);
  space.setOrigin(space_bounds.width / 2, space_bounds.height / 2);
  goback.setOrigin(goback_bounds.width / 2, goback_bounds.height / 2);

	header.setPosition(window -> getSize().x / 2, window -> getSize().y / 5);
  wasd.setPosition(window -> getSize().x / 2, window -> getSize().y / 3 + wasd_bounds.height);
  updown.setPosition(window -> getSize().x / 2, window -> getSize().y / 3 + wasd_bounds.height * 2.5);
  space.setPosition(window -> getSize().x / 2, window -> getSize().y / 3 + wasd_bounds.height * 4);
  goback.setPosition(window -> getSize().x / 2, window -> getSize().y / 3 + wasd_bounds.height * 16);

}

void ControlsView::Update(sf::RenderWindow *window){

  	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
  		window -> close();
  	}

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace)){
      game_view.setView(new MenuView());
    }

}

void ControlsView::Render(sf::RenderWindow *window){

  	window -> draw(header);
    window -> draw(wasd);
    window -> draw(updown);
    window -> draw(space);
    window -> draw(goback);
}
