#include "LvlSelectView.h"
#include "PlayView.h"

void LvlSelectView::Init(sf::RenderWindow *window){

	// selected option
	intro_return = 1;
	right_press = 0;
	left_press = 0;
	up_press = 0;
	down_press = 0;

	cur_col = 1; cur_row = 1;
	cur_select = 1;

	// load font
	font.loadFromFile("../include/Fonts/Beyblade Metal Fight Font.ttf");

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
		char level[2];
		sprintf(level, "%d", i+1);
		tmp.text.setString(level);

		sf::FloatRect tmp_bounds = tmp.text.getLocalBounds();
		tmp.text.setOrigin(tmp_bounds.width / 2, tmp_bounds.height / 2);

		if(i < 5){
				tmp.text.setPosition(window -> getSize().x / 8 - 10 + 150 * i,
								window -> getSize().y / 2);
		}
		else{
			tmp.text.setPosition(window -> getSize().x / 8 - 10 + 150 * (i-5),
							3 * (window -> getSize().y) / 4);
		}
		tmp.lvl = i + 1;
		lvls[i] = tmp;
	}
}


// Take keyboard input
void LvlSelectView::Update(sf::RenderWindow *window){

	// Left, Right, Up, and Down navigate the menu
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
		if(right_press){ return; }

		if(cur_col < 5 && cur_select < top_lvl){
			cur_col++;
			cur_select = cur_col + 5 * (cur_row-1);

		}

		right_press = 1;
	}
	else{
		right_press = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
		if(left_press){ return; }

		if(cur_col > 1){
			cur_col--;
			cur_select = cur_col + 5 * (cur_row-1);

		}

		left_press = 1;
	}
	else{
		left_press = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
		if(down_press){ return; }

		if(cur_row == 1 && cur_select < top_lvl - 4){
			cur_row = 2;
			cur_select = cur_col + 5 * (cur_row-1);

		}
		down_press = 1;
	}
	else{
		down_press = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
		if(up_press){ return; }

		if(cur_row == 2){
			cur_row = 1;
			cur_select = cur_col + 5 * (cur_row-1);

		}
		up_press = 1;
	}
	else{
		up_press = 0;
	}


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if(intro_return){ return; }

		game_view.setView(new PlayView(cur_select));

	}
	else{
		intro_return = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
		window -> close();
	}


}


// Set the text color to white, then set selected option to blue. Draw the menu to the screen
void LvlSelectView::Render(sf::RenderWindow *window){
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
