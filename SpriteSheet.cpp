#include<SFM/Graphics.hpp>
#include<string>
#include<iostream>
//modeled after https://www.youtube.com/watch?v=ma5QWDYsmBg&index=11&list=PLHJE4y54mpC5j_x90UkuoMZOdmmL9-_rg
//and Graphics lecture page 39


const float duration = 10; //should be based on pixel delta!!
float elapsedDuration = duration;
unsigned in currentFrame;
std::vector<sf::IntRect> sequence;
sf::Sprite playerImage;

void update(float deltaTime){ //delta time is milliseconds since the last time it was called
	elapsedDuration += deltaTime;
	while(elapsedDuration > duration){
		elapsedDuration -+ duration;
		currentFrame = (currentFrame+1) % sequence.size();
	}
	playerImage.setTextureRect(sequence[currentFrame]);
}

void setTexture{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Mario Sprites by Halk Upon the Gale");
	Window.setKeyRepeatEnabled(false);
	sf::Texture pTexture;
	
	
	if(!pTexture.loadFromFile("SNES - Super Mario World - Mario.png")){
		std::cout << "Error could not load player image" << std::endl;
	}
	playerImage.setTexture(pTexture);
}
int runWindow{
	
	while(window.isOpen()){
		sf::Event Event;
		while(Window.pollEvent(Event)){
			switch(Event.type){
				case sf::Event::Closed:
				   Window.close();
				   break;
			   }
		   }
		   Window.draw(playerImage);
		   Window.display();
	   }
}
setTexture();
runWindow();
update();
runWindow();


			   
				
			
