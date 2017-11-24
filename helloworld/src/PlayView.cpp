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

	// Object w1(0.0,0.0,50,50,true);
	// Object w2(150.0,150.0,25,2,true);
	// objs.push_back(w1);
	// objs.push_back(w2);

	//player PlayerInstance;
	//gravity = b2Vec2(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	//world = b2World(gravity);
	window->setFramerateLimit(60);

	if(!Bkg.loadFromFile("../include/Textures/brick.jpg"));

	Bkg.setRepeated(true);

	bgSprite.setTexture(Bkg);
	bgSprite.setTextureRect(sf::IntRect(0,0,800,600));
	if(!builders_list.empty()){
		int z;
		for(z = 0; z < builders_list.size(); z++){
			vec.push_back(&(*builders_list[z]));
			ty.push_back(0);
		}
	}
	//vec.push_back(&(*builders_list[0]));
	vec.push_back(&launcher);
	vec.push_back(&mobile);
	// ty.push_back(0);
	// ty.push_back(0);
	ty.push_back(1);
	ty.push_back(2);


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

     // If user presses direction, move the player paddle
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            //PlayerInstance.player_up();
						//builder = 0, launcher = 1, mobile = 2;

						if(!PlayerInstance.inMachine())
							PlayerInstance.intersects(vec,ty);
						//PlayerInstance.intersects(&builder);
						//PlayerInstance.intersects(&launcher);
    }

PlayerInstance.Update();
world.Step(1/60.f, 8, 3);


}

void PlayView::Render(sf::RenderWindow *window){
	window -> draw(bgSprite);
	window -> draw(tmp);
	window -> draw(tmp2);
	window -> draw(tmp3);
	//window -> draw(builder.getShape());
//window->draw(line);
	// draw boxes

	//window -> draw(box2.getShape());

	//window -> draw(PlayerInstance.playerbody);
	// for( auto&& pointer : objs) {
	// 	wall.setPosition(pointer->getX(), pointer->getY());
	// 	wall.setSize(sf::Vector2f(pointer->getW(),pointer->getH()));
	// 	window->draw(wall);
	// }


	int j;
	if(!boxes_list.empty()){
			for(j = 0; j < boxes_list.size(); j++){
				(*boxes_list[j]).setPos(SCALE* (*boxes_list[j]).getBody()->GetPosition().x,SCALE*(*boxes_list[j]).getBody()->GetPosition().y);
				window->draw((*boxes_list[j]).getShape());
			}
	}
	// *boxes_list.front() -> setPos(SCALE* boxes_list.front() -> getBody()->GetPosition().x,SCALE*boxes_list.front() -> getBody()->GetPosition().y);
	// window->draw(*boxes_list.front()->getShape());

	//sf::Sprite GroundSprite;
	//GroundSprite.SetTexture(GroundTexture);
	//GroundSprite.SetOrigin(400.f, 8.f);
	//GroundSprite.SetPosition(groundBody->GetPosition().x * SCALE, groundBody->GetPosition().y * SCALE);
	//GroundSprite.SetRotation(180/b2_pi * BodyIterator->GetAngle());
	//Window.Draw(GroundSprite);
	int i = 0;
	for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()){
		if (BodyIterator->GetType() == b2_dynamicBody ){
				if( i == 0 ){
				PlayerInstance.playerbody.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				PlayerInstance.playerbody.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
				//++BodyCount;
				i++;
			}
			else if(i==1){
				mobile.machine_body.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				mobile.machine_body.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
				window->draw(mobile.machine_body);
				i++;
			}
			else if (i==2){
				launcher.machine_body.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				launcher.machine_body.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
				line.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				line.setRotation(90+(-1*( 180.0/3.141592653589793 )*launcher.getTheta()));
				window->draw(launcher.machine_body);
				if(PlayerInstance.inMachine() && PlayerInstance.mType == 1)
					window->draw(line);
				i++;
			}
			else if(i == 3 || i == 4){
				if(!builders_list.empty()){
					int z;
					for(z = 0; z < builders_list.size(); z++){
						(*builders_list[z]).machine_body.setPosition(SCALE * (*builders_list[z]).getBody()->GetPosition().x, SCALE *  (*builders_list[z]).getBody()->GetPosition().y);
						(*builders_list[z]).machine_body.setRotation( (*builders_list[z]).getBody()->GetAngle() * 180/b2_pi);
						window->draw((*builders_list[z]).machine_body);
						//++BodyCount;
					}
				}
				i++;
			}

		}
		// else if (i==4){
			//box1.setPos(SCALE * BodyIterator->GetPosition().x,SCALE * BodyIterator->GetPosition().y);
			//window -> draw(box1.getShape());
			//i++;
		//}
		else if(i==5)
		{
			//box2.setPos(SCALE * box2.getBody()->GetPosition().x,SCALE * box2.getBody()->GetPosition().y);
			//window -> draw(box2.getShape());

				//window -> draw(box2.getShape());

				/*sf::Sprite GroundSprite;
				GroundSprite.SetTexture(GroundTexture);
				GroundSprite.SetOrigin(400.f, 8.f);
				GroundSprite.SetPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
				GroundSprite.SetRotation(180/b2_pi * BodyIterator->GetAngle());
				Window.Draw(GroundSprite);*/
		}

		if(!PlayerInstance.inMachine())
			window->draw(PlayerInstance.playerbody);

}
//std::cout << i;
}
