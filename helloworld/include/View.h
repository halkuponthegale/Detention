#ifndef VIEW_H
#define VIEW_H

#include "MiniView.h"

class View{
	public:
		View(){
			game_view = NULL;
		}

		void setWindow(sf::RenderWindow *window){
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
			if(game_view != NULL){
				game_view -> Update(window);
			}
		}

		void Render(){
			if(game_view != NULL){
				game_view -> Render(window);
			}
		}

		~View(){ }


	private:
		sf::RenderWindow *window;
		MiniView *game_view;
};

extern View game_view;
extern int top_lvl;
#define MAX_LVL 6




#endif