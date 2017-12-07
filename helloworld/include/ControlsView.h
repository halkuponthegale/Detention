#ifndef CONTROLS_VIEW_H
#define CONTROLS_VIEW_H

#include "GameView.h"

/*
	ControlsView handles showing the user the basic controls
  Navigated to/from MenuView
*/

class ControlsView : public MiniView{
	public:
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);
		~ControlsView(){
			header.setString("");
			wasd.setString("");
			updown.setString("");
			space.setString("");
			goback.setString("");
		}
	private:
		sf::Font font;

		sf::Text header;
		sf::Text wasd;
		sf::Text updown;
    sf::Text space;
    sf::Text goback;

		int intro_return;

};

#endif
