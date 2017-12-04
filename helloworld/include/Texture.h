#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>

class Texture{
public:
  Texture(double xo, double yo, double hw, double hh, std::string filename){

    // Load box texture from jpg file (in include folder)
    if(!image.loadFromFile(filename))
    {
    }

    body.setSize(sf::Vector2f(hw * 2, hh * 2));
    body.setOrigin(body.getOrigin().x + hw, body.getOrigin().y + hh);
    body.setPosition(sf::Vector2f(xo, yo));

    body.setTexture(&image);


  }

  sf::RectangleShape getShape(){
    return body;
  }

private:
  sf::RectangleShape body;
  sf::Texture image;
};


#endif
