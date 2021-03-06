#include "Game.h"
#include "Manager/Manager.h"
#include "Manager/ObjectManager.h"
#include "Manager/MapManager.h"

int map[144] = { 0,0,0,0,0,0,0,0,0,0,0,0,
				 0,0,0,0,0,0,1,0,1,0,0,0,
				 0,0,0,1,0,0,0,0,0,1,0,0,
				 0,0,0,0,0,0,1,0,1,0,0,0,
				 0,0,0,0,0,1,0,0,0,0,0,0,
				 0,0,0,0,0,0,0,1,0,0,0,0,
				 0,1,0,0,0,0,0,0,0,0,1,0,
				 0,0,0,0,0,1,0,0,0,0,0,0,
				 0,0,0,0,0,0,0,0,0,0,0,0,
				 0,0,0,0,0,0,0,1,0,0,0,0,
				 0,1,0,0,0,0,1,0,0,1,0,0,
				 0,0,0,1,0,0,0,0,0,0,0,0 };

Game::Game(sf::VideoMode mode, std::string title) {
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(mode, title, sf::Style::Default, settings));

	running = window->isOpen();
	window->setFramerateLimit(120);

	managers.push_back(new MapManager(*window));
	static_cast<MapManager*>(managers[0])->loadMap(map, 66.6f, 12, 12);
	managers.push_back(new ObjectManager(*window, managers));

}

void Game::render() const{
	window->clear(sf::Color(0, 0, 0, 255));

	for (unsigned int i = 0; i < managers.size(); i++) {
		managers[i]->render();
	}

	window->display();
}

void Game::update() {
	for (unsigned int i = 0; i < managers.size(); i++) {
		managers[i]->update();
	}
}

void Game::events() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
			running = false;
		}
	}
}

sf::RenderWindow& Game::getWindow() const {
	return *window;
}