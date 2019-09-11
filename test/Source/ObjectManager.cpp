#include "ObjectManager.h"
#include "Object.h"
#include "Ball.h"
#include "MapManager.h"

ObjectManager::ObjectManager(sf::RenderWindow& window, std::vector<Manager*>& managers) {
	this->window = &window;
	objects.push_back(new Ball(window, 360, static_cast<MapManager*>(managers[0])->segments));
}

void ObjectManager::update() {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update();
	}
}

void ObjectManager::render() {
	for (int i = 0; i < objects.size(); i++) {
		window->draw(*objects[i]);
	}
}