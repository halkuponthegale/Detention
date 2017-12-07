#ifndef LVL_SELECT_VIEW_H
#define LVL_SELECT_VIEW_H

#include "GameView.h"

/*
	LvlSelectView handles all possible level options that the user could choose
	Handles logic for what levels are accessible based on completion
	Passes selected level to PlayView
*/

typedef struct{
	sf::Text text;
	int lvl;
}LEVEL_T;

class LvlSelectView : public MiniView{
	public:
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);
~LvlSelectView(){
	header.setString("");
	for(int i = 0; i < 10; i++){
		lvls[i].text.setString("");
	}
}
	private:
		sf::Font font;

		sf::Text header;
		LEVEL_T lvls[10];

		int intro_return;
		int right_press;
		int left_press;
		int up_press;
		int down_press;

		int cur_col;
		int cur_row;
		int cur_select;

};

#endif
