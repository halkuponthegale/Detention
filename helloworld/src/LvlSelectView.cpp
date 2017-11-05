#include "LvlSelectView.h"
#include "PlayView.h"

void LvlSelectView::Init(sf::RenderWindow *window){
	// selected option
	cur_select = 1;
	intro_return = 1;
	right_press = 0;
	left_press = 0;

	// load font
	font.loadFromFile("../include/Fonts/ComicSans.ttf");

	// create texts
	header.setFont(font);
	header.setCharacterSize(80);
	header.setString("Level Select");
	sf::FloatRect title_bounds = header.getLocalBounds();
	header.setOrigin(title_bounds.width / 2, title_bounds.height / 2);
	header.setPosition(window -> getSize().x / 2, window -> getSize().y / 5);

	int i;
	for(i = 0; i < MAX_LVL; i++){
		LEVEL_T tmp;
		tmp.text.setFont(font);
		tmp.text.setCharacterSize(60);
		char level[1];
		sprintf(level, "%d", i+1);
		tmp.text.setString(level);
		sf::FloatRect tmp_bounds = tmp.text.getLocalBounds();
		tmp.text.setOrigin(tmp_bounds.width / 2, tmp_bounds.height / 2);
		tmp.text.setPosition(window -> getSize().x / 8 - 10 + 120 * i,
						window -> getSize().y / 2);

		tmp.lvl = i + 1;

		lvls[i] = tmp;
	}

}

void LvlSelectView::Update(sf::RenderWindow *window){

	// handle left/right operations between level options
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
		if(right_press){ return; }
		if(cur_select < top_lvl)
			cur_select++;
		right_press = 1;
	}
	else{
		right_press = 0;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
		if(left_press){ return; }

		if(cur_select > 1)
			cur_select--;
		left_press = 1;
	}
	else{
		left_press = 0;
	}

	// handle selected option
	// pass level to PlayView
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if(intro_return){ return; }

		game_view.setView(new PlayView(cur_select));

	}
	else{
		intro_return = 0;
	}

}

void LvlSelectView::Render(sf::RenderWindow *window){
	// draw everything to screen
	// locked levels = Grey
	// unlocked levels = White
	// selected level = Blue

	window -> draw(header);

	int i;
	for(i = 0; i < MAX_LVL; i++){
		if(lvls[i].lvl > top_lvl){
			lvls[i].text.setFillColor(sf::Color(120,120,120));
		}
		else{
			lvls[i].text.setFillColor(sf::Color::White);
		}

		if(lvls[i].lvl == cur_select){
			lvls[i].text.setFillColor(sf::Color::Blue);
		}

		window -> draw(lvls[i].text);
	}

}