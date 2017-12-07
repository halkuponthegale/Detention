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
		~EndView(){
			tmp.setString("");
			tmp2.setString("");
			tmp3.setString("");
			tmp4.setString("");
		};
	private:
		sf::Font font;

		int intro_return;
		int cur_select;
		int finished_lvl;

		int up_press, down_press;

		sf::Text tmp;
		sf::Text tmp2;
		sf::Text tmp3;
		sf::Text tmp4;

		sf::RectangleShape pals;
		sf::Texture img;


};


#endif
