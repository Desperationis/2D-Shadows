#include "ObjectManager.h"
#include "Object.h"
#include "Ball.h"
#include "MapManager.h"

ObjectManager::ObjectManager(sf::RenderWindow& window) {
	this->window = &window;
	objects.push_back(new Ball(window, 10));
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