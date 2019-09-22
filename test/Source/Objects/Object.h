#pragma once
#include <SFML/Graphics.hpp>

struct Object : public sf::Drawable, sf::Transformable {
public:
	virtual void update() {};
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
};