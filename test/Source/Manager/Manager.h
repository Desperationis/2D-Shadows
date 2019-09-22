#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

struct Manager{
public:
	virtual void update() {};
	virtual void render() {};
	
	sf::RenderWindow* window = nullptr;
};