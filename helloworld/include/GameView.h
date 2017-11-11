#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "MiniView.h"

/*
	GameView handles what is displayed on the screen, handles transitions between
	different screens, each represented by a "MiniView". Serves as a wrapper
	and handler between different screens, as well as calls to Update() and
	Render() in the MiniView objects
*/

class GameView{
	public:
		GameView(){
			game_view = NULL;
		}

		void setWindow(sf::RenderWindow *window){
			// sets window of application
			this -> window = window;
		}

		void setView(MiniView *view){

			// set view variable to new view
			game_view = view; 

			// initialize new view
			if(game_view != NULL){
				game_view -> Init(window);
			}
		}

		void Update(){
			// call update on respective internal view object
			if(game_view != NULL){
				game_view -> Update(window);
			}
		}

		void Render(){
			// render view
			if(game_view != NULL){
				game_view -> Render(window);
			}
		}

		~GameView(){ }


	private:
		sf::RenderWindow *window;
		MiniView *game_view;
};

extern GameView game_view;
extern int top_lvl;
#define MAX_LVL 6




#endif