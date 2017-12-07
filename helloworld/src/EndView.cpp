#include "EndView.h"
#include "MenuView.h"
#include "PlayView.h"
#include "AudioManager.h"

// EndView draws a relevant message, plays an affirming noise, and draws an interactive menu

void EndView::Init(sf::RenderWindow *window){
	
	// load font
	font.loadFromFile("../include/Fonts/Beyblade Metal Fight Font.ttf");

	// if the completed level is the final level, play a special cheers noise and load the character image
	intro_return = 1;
	cur_select = 1;
	if(finished_lvl == MAX_LVL){
		cur_select = 2;
		AudioManager::play_cheers();
		pals.setSize(sf::Vector2f(326,255));
		pals.setOrigin(pals.getOrigin().x + 326/2, pals.getOrigin().y + 255/2);
		img.loadFromFile("../include/Textures/calandkevin.png");
		pals.setTexture(&img);
		pals.setPosition(sf::Vector2f(400, 480));

	}else{ //if the completed level is 1-9, play regular end nosie
		AudioManager::play_end();
	}

	up_press = 0; down_press = 0;




	// create tmp text for end messages
	tmp.setFont(font);
	tmp2.setFont(font);
	tmp3.setFont(font);
	tmp4.setFont(font);

	tmp.setCharacterSize(50);
	tmp2.setCharacterSize(30);
	tmp3.setCharacterSize(30);
	tmp4.setCharacterSize(30);

	// if not the final level, set relevant message
	if(finished_lvl != MAX_LVL){
		char tmptext[24];
		sprintf(tmptext, "You completed level %d", finished_lvl);

		tmp.setString(tmptext);
	}
	else{ // if final level, set relevant message
		tmp.setString("Success! Kevin is free!");
	}
	
	// Set menu strings
	tmp2.setString("Continue");
	tmp3.setString("Replay");
	tmp4.setString("Main Menu");

	// Set bounds
	sf::FloatRect tmp_bounds = tmp.getLocalBounds();
	sf::FloatRect tmp2_bounds = tmp2.getLocalBounds();
	sf::FloatRect tmp3_bounds = tmp3.getLocalBounds();
	sf::FloatRect tmp4_bounds = tmp4.getLocalBounds();

	// Set origins of text
	tmp.setOrigin(tmp_bounds.width / 2, tmp_bounds.height / 2);
	tmp2.setOrigin(tmp2_bounds.width / 2, tmp2_bounds.height / 2);
	tmp3.setOrigin(tmp3_bounds.width / 2, tmp3_bounds.height / 2);
	tmp4.setOrigin(tmp4_bounds.width / 2, tmp4_bounds.height / 2);

	// Set positions of text
	tmp.setPosition(window -> getSize().x / 2, window -> getSize().y / 3);
	tmp2.setPosition(window -> getSize().x / 2, window -> getSize().y / 2);
	if(finished_lvl != MAX_LVL){
		tmp3.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + tmp2_bounds.height * 2);
		tmp4.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + tmp2_bounds.height * 4);
	}
	else{
		tmp3.setPosition(window -> getSize().x / 2, window -> getSize().y / 2);
		tmp4.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + tmp2_bounds.height * 2);
	}


}


// take input from keyboard for interactive menu
void EndView::Update(sf::RenderWindow *window){

	// Down and Up navigate the menu
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
		if(down_press){return;}

		if(cur_select < 3)
			cur_select++;
		down_press = 1;
	}
	else{
		down_press = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
		if(up_press){return;}

		if(finished_lvl == MAX_LVL && cur_select > 2)
			cur_select--;
		else if(!(finished_lvl == MAX_LVL) && cur_select > 1)
			cur_select--;
		up_press = 1;
	}
	else{
		up_press = 0;
	}

	// Return/enter steps into the selected menu option
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if(intro_return){ return; }

		if(cur_select == 1){
			// progress to next level (or final level again if finished final)
		  if(finished_lvl < MAX_LVL)
				game_view.setView(new PlayView(finished_lvl + 1));
			else if(finished_lvl == MAX_LVL)
				game_view.setView(new PlayView(finished_lvl));
		}
		else if(cur_select == 2){
			// replay level
			game_view.setView(new PlayView(finished_lvl));
		}
		else if(cur_select == 3){
			// menu screen
			game_view.setView(new MenuView());
		}
	}
	else{
		intro_return = 0;
	}

}


// Draws all text and images
void EndView::Render(sf::RenderWindow *window){

	// Set color of all texts white, then set color of the "selected" text blue to indicate selection
	tmp2.setFillColor(sf::Color::White);
	tmp3.setFillColor(sf::Color::White);
	tmp4.setFillColor(sf::Color::White);

	if(cur_select == 1){
		tmp2.setFillColor(sf::Color::Blue);
	}
	else if(cur_select == 2){
		tmp3.setFillColor(sf::Color::Blue);
	}
	else if(cur_select == 3){
		tmp4.setFillColor(sf::Color::Blue);
	}

	// Draw the text to the screen
	window -> draw(tmp);
	
	// If the completed level is the final level, draw the final message and image
	// Otherwise draw the regular text
	if(finished_lvl != MAX_LVL)
		window -> draw(tmp2);
	else
		window -> draw(pals);
	window -> draw(tmp3);
	window -> draw(tmp4);

}
