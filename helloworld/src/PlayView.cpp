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

	// Object w1(0.0,0.0,50,50,true);
	// Object w2(150.0,150.0,25,2,true);
	// objs.push_back(w1);
	// objs.push_back(w2);

	player PlayerInstance;
	//gravity = b2Vec2(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	//world = b2World(gravity);
window->setFramerateLimit(60);
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
            PlayerInstance.player_up();
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            PlayerInstance.player_down();
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
           PlayerInstance.player_left();
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            PlayerInstance.player_right();
    }
world.Step(1/60.f, 8, 3);


}

void PlayView::Render(sf::RenderWindow *window){
	window -> draw(tmp);
	window -> draw(tmp2);
	window -> draw(tmp3);
	//window -> draw(PlayerInstance.playerbody);
	for( auto&& pointer : objs) {
		wall.setPosition(pointer->getX(), pointer->getY());
		wall.setSize(sf::Vector2f(pointer->getW(),pointer->getH()));
		window->draw(wall);
	}
	for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
{
		if (BodyIterator->GetType() == b2_dynamicBody)
		{

				PlayerInstance.playerbody.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				PlayerInstance.playerbody.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
				window->draw(PlayerInstance.playerbody);
				//++BodyCount;
		}
		else
		{
				/*sf::Sprite GroundSprite;
				GroundSprite.SetTexture(GroundTexture);
				GroundSprite.SetOrigin(400.f, 8.f);
				GroundSprite.SetPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
				GroundSprite.SetRotation(180/b2_pi * BodyIterator->GetAngle());
				Window.Draw(GroundSprite);*/
		}
}
}
