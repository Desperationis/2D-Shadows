#pragma once
#include <SFML/Graphics.hpp>
#include "Manager.h"

/*
	Updates and renders objects.
*/

struct Object;
class ObjectManager : public Manager {
public:
	ObjectManager(sf::RenderWindow& window, std::vector<Manager*> managers);
	void update() override;
	void render() override;

private:
	std::vector<Object*> objects;
};