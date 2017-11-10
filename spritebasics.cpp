#include<SFML/Graphics.hpp>
#include<SFML/Clock.hpp>
#include<string>
#include<iostream>
//should be in the game engine class?
//modeled after https://www.youtube.com/watch?v=ma5QWDYsmBg&index=11&list=PLHJE4y54mpC5j_x90UkuoMZOdmmL9-_rg
//and Graphics lecture page 39

int main(){
	//45 animations across, 12 down)
	enum Direction { Down, Left, Right, Up};
	
	sf::Vector2i source(133, Down);
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Mario Sprites by Halk Upon the Gale");
	Window.setKeyRepeatEnabled(false);
	sf::Texture pTexture;
	std::vector<sf::IntRect> sequence;
	sf::Sprite playerImage;
	sf::Clock deltaClock;
	sf::Time lastTime;
	float timePerFrame;
	
	if(!pTexture.loadFromFile("Mario.png")){
		std::cout << "Error could not load player image" << std::endl;
		return 0;
	}
	playerImage.setTexture(pTexture);
	sinceLastUpdate = sf::Time::Zero;
	timePerFrame = (1.f/60.f); //can change this
	
	
	while(Window.isOpen()){
		sf::Event Event;
		deltaClock = deltaClock.restart();
		lastTime += deltaClock;
		
		
			
			
		while(Window.pollEvent(Event)){
			
			
			switch(Event.type){
				
				case sf::Event::Closed:
				   Window.close();
				   break;
				   
				case sf::Event::KeyPressed:
				
				   if(Event.key.code == sf::Keyboard::Up)
					   source.y = Up;
					   
				   else if(Event.key.code == sf::Keyboard::Down)
					   source.y = Down;
					   
				   else if(Event.key.code == sf::Keyboard::Right)
					   source.y = Right;
				   else if(Event.key.code == sf::Keyboard::Left)
					   source.y = Left;
				   break;
					   
					   
			   }
		   }
		   while(sinceLastUpdate > timePerFrame){   //could be >=
			sinceLastUpdate -= timePerFrame;
			
			//this is where time per frame should pass to an update function for our game objects / actors (update events, update objects, draw objects)
		   }
		   playerImage.setTextureRect(sf::IntRect(source.x * 133, source.y * 200, 133, 200));
		   Window.draw(playerImage);
		   Window.display();
		   //Window.clear();
	   }
   }
