#ifndef PLAY_VIEW_H
#define PLAY_VIEW_H

#include "View.h"

class PlayView : public MiniView{
	public:
		PlayView(int lvl){ play_lvl = lvl; }
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);

	private:
		sf::Font font;

		int intro_return;
		int play_lvl;

		sf::Text tmp;
		sf::Text tmp2;
		sf::Text tmp3;


};


#endif