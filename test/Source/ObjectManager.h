#pragma once
#include <SFML/Graphics.hpp>
#include "Manager.h"

/*
	Updates and renders objects.
*/

struct Object;
class ObjectManager : public Manager {
public:
	ObjectManager(sf::RenderWindow& window);

	void update() override;
	void render() override;

	std::vector<Object*> objects;
};