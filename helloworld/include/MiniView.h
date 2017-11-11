#ifndef MINI_VIEW_H
#define MINI_VIEW_H

#include <SFML/Graphics.hpp>

/*
	Abstract class that will be implemented in subclasses to hold each View State
	Init is used to set instance variables
	Update is used to handle keyInput
	Render is used to draw onto the window
*/


class MiniView{
	public:
		virtual void Init(sf::RenderWindow *window){ }
		virtual void Update(sf::RenderWindow *window){ }
		virtual void Render(sf::RenderWindow *window){ }
};






#endif