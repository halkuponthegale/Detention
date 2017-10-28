#ifndef END_VIEW_H
#define END_VIEW_H

#include "View.h"

class EndView : public MiniView{
	public:
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);

	private:
		sf::Font font;

		int intro_return;
		int cur_select;

		sf::Text tmp;
		sf::Text tmp2;
		sf::Text tmp3;


};


#endif
