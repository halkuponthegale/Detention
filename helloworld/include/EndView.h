#ifndef END_VIEW_H
#define END_VIEW_H

#include "GameView.h"

/*
	EndView handles finish screen
	Can choose to continue to next level, return to main menu, or quit game
	Updates "unlocked levels" logic
*/

class EndView : public MiniView{
	public:
		EndView(int lvl){ finished_lvl = lvl; }
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);

	private:
		sf::Font font;

		int intro_return;
		int cur_select;
		int finished_lvl;

		sf::Text tmp;
		sf::Text tmp2;
		sf::Text tmp3;


};


#endif
