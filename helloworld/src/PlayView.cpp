#include "PlayView.h"
#include "EndView.h"

void PlayView::Init(sf::RenderWindow *window){
	// load font
	font.loadFromFile("../include/Fonts/ComicSans.ttf");

	intro_return = 1;

	// create tmp text
	tmp.setFont(font);
	tmp2.setFont(font);
	tmp3.setFont(font);

	tmp.setCharacterSize(50);
	tmp2.setCharacterSize(30);
	tmp3.setCharacterSize(30);

	char tmptext[16];
	sprintf(tmptext, "Playing Level %d", play_lvl);

	tmp.setString(tmptext);
	tmp2.setString("Press Return to go to finish (win level)");
	tmp3.setString("Press Escape to quit game");

	sf::FloatRect tmp_bounds = tmp.getLocalBounds();
	sf::FloatRect tmp2_bounds = tmp2.getLocalBounds();
	sf::FloatRect tmp3_bounds = tmp3.getLocalBounds();

	tmp.setOrigin(tmp_bounds.width / 2, tmp_bounds.height / 2);
	tmp2.setOrigin(tmp2_bounds.width / 2, tmp2_bounds.height / 2);
	tmp3.setOrigin(tmp3_bounds.width / 2, tmp3_bounds.height / 2);

	tmp.setPosition(window -> getSize().x / 2, window -> getSize().y / 3);
	tmp2.setPosition(window -> getSize().x / 2, window -> getSize().y / 2);
	tmp3.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + 30);
	Object w1(0.0,0.0,50,50,true);
	Object w2(150.0,150.0,25,2,true);
	objs.push_back(w1);
	objs.push_back(w2);

}

void PlayView::Update(sf::RenderWindow *window){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if(intro_return){ return; }

		// increase top level if completed level is top level
		if(play_lvl == top_lvl && top_lvl < MAX_LVL){
			top_lvl++;
		}

		game_view.setView(new EndView(play_lvl));
	}
	else{
		intro_return = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
		window -> close();
	}


}

void PlayView::Render(sf::RenderWindow *window){
	window -> draw(tmp);
	window -> draw(tmp2);
	window -> draw(tmp3);
	for(int i = 0; i < objs.size(); i++){
		wall.setPosition(objs[i].getX(), objs[i].getY());
		wall.setSize(sf::Vector2f(objs[i].getW(),objs[i].getH()));
		window->draw(wall);
	}
}
