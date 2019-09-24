#include "ObjectManager.h"
#include "MapManager.h"
#include "../Objects/Object.h"
#include "../Objects/Center.h"

ObjectManager::ObjectManager(sf::RenderWindow& window, std::vector<Manager*> managers) {
	this->window = &window;
	objects.push_back(new Center(window, static_cast<MapManager*>(managers[0])->getSegments()));
}

void ObjectManager::update() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i]->update();
	}
}

void ObjectManager::render() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		window->draw(*objects[i]);
	}
}