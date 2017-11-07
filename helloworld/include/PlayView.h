#ifndef PLAY_VIEW_H
#define PLAY_VIEW_H

#include "GameView.h"
#include "Object.h"
#include "FileManager.h"
#include "Player.h"
#include "Builder.h"

/*
	PlayView handles level loading, drawing, and gameplay

*/

class PlayView : public MiniView{
	public:
		PlayView(int lvl){
			play_lvl = lvl;
			// load level from file
			objs = File::loadLevel("./level"+std::to_string(play_lvl)+".json");
		}
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
		std::vector<Object> objs;
		sf::RectangleShape wall;

		Player PlayerInstance;
		Builder builder;
};


#endif
