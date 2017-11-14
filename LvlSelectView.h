//LvlSelectView.h
#ifndef LVL_SELECT_VIEW_H
#define LVL_SELECT_VIEW_H

#include "GameView.h"

typedef struct{
	sf::Text text;
	int lvl;
}LEVEL_T;

class LvlSelectView : public MiniView{
	public:
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);

	private:
		sf::Font font;

		sf::Text header;
		LEVEL_T lvls[6];

		int cur_select;
		int intro_return;
		int right_press;
		int left_press;

};

#endif
