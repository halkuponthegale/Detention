#ifndef MINI_VIEW_H
#define MINI_VIEW_H

#include <SFML/Graphics.hpp>


class MiniView{
	public:
		virtual void Init(sf::RenderWindow *window){ }
		virtual void Update(sf::RenderWindow *window){ }
		virtual void Render(sf::RenderWindow *window){ }
};






#endif