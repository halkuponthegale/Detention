#include "PlayView.h"
#include "EndView.h"

void PlayView::Init(sf::RenderWindow *window){
	// load font
	font.loadFromFile("../include/Fonts/Beyblade Metal Fight Font.ttf");

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


	// Construct a world object, which will hold and simulate the rigid bodies.
	window->setFramerateLimit(60);

	// load background sprite
	if(!Bkg.loadFromFile("../include/Textures/brick.jpg"));
	Bkg.setRepeated(true);
	bgSprite.setTexture(Bkg);
	bgSprite.setTextureRect(sf::IntRect(0,0,800,600));

	// push builders onto launcher
	if(!builders_list.empty()){
		int z;
		for(z = 0; z < builders_list.size(); z++){
			vec.push_back(&(*builders_list[z]));
			ty.push_back(0);
		}
	}

	// push launchers onto vector
	if(!launchers_list.empty()){
		int z;
		for(z = 0; z < launchers_list.size(); z++){
			vec.push_back(&(*launchers_list[z]));
			ty.push_back(1);
		}
	}

	// push mobiles onto vector
	if(!mobiles_list.empty()){
		int z;
		for(z = 0; z < mobiles_list.size(); z++){
			vec.push_back(&(*mobiles_list[z]));
			ty.push_back(2);
		}
	}


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

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					//builder = 0, launcher = 1, mobile = 2;
					if(!PlayerInstance.inMachine())
						PlayerInstance.intersects(vec,ty);
  }

	PlayerInstance.Update();
	world.Step(1/60.f, 8, 3);


}

void PlayView::Render(sf::RenderWindow *window){
	window -> draw(bgSprite);
	window -> draw(tmp);
	window -> draw(tmp2);
	window -> draw(tmp3);

	// for( auto&& pointer : objs) {
	// 	wall.setPosition(pointer->getX(), pointer->getY());
	// 	wall.setSize(sf::Vector2f(pointer->getW(),pointer->getH()));
	// 	window->draw(wall);
	// }

	// draw boxes
	if(!boxes_list.empty()){
		int j;
		for(j = 0; j < boxes_list.size(); j++){
			(*boxes_list[j]).setPos(SCALE* (*boxes_list[j]).getBody()->GetPosition().x,SCALE*(*boxes_list[j]).getBody()->GetPosition().y);
			window->draw((*boxes_list[j]).getShape());
		}
	}

	// draw mobiles
	if(!mobiles_list.empty()){
		int z;
		for(z = 0; z < mobiles_list.size(); z++){
			(*mobiles_list[z]).machine_body.setPosition(SCALE * (*mobiles_list[z]).getBody()->GetPosition().x, SCALE * (*mobiles_list[z]).getBody()->GetPosition().y);
			(*mobiles_list[z]).machine_body.setRotation((*mobiles_list[z]).getBody()->GetAngle() * 180/b2_pi);
			window->draw((*mobiles_list[z]).machine_body);
		}
	}

  // draw launchers
	if(!launchers_list.empty()){
		int z;
		for(z = 0; z < launchers_list.size(); z++){
			(*launchers_list[z]).machine_body.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).machine_body.setRotation((*launchers_list[z]).getBody()->GetAngle() * 180/b2_pi);
			(*launchers_list[z]).line.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).line.setRotation(90+(-1*( 180.0/3.141592653589793 )*(*launchers_list[z]).getTheta()));
			window->draw((*launchers_list[z]).machine_body);
			if(PlayerInstance.inMachine() && PlayerInstance.mType == 1)
				window->draw((*launchers_list[z]).line);
		}
	}

	// draw builders
	if(!builders_list.empty()){
		int z;
		for(z = 0; z < builders_list.size(); z++){
			(*builders_list[z]).machine_body.setPosition(SCALE * (*builders_list[z]).getBody()->GetPosition().x, SCALE *  (*builders_list[z]).getBody()->GetPosition().y);
			(*builders_list[z]).machine_body.setRotation( (*builders_list[z]).getBody()->GetAngle() * 180/b2_pi);
			window->draw((*builders_list[z]).machine_body);
		}
	}

	// draw player
	PlayerInstance.playerbody.setPosition(SCALE * PlayerInstance.getBody()->GetPosition().x, SCALE * PlayerInstance.getBody()->GetPosition().y);
	PlayerInstance.playerbody.setRotation(PlayerInstance.getBody()->GetAngle() * 180/b2_pi);
	if(!PlayerInstance.inMachine())
		window->draw(PlayerInstance.playerbody);


}
