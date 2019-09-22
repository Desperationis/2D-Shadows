#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

/*
	Handles the window, objects, and events.
*/

struct Manager;
class Game {
public:
	Game(sf::VideoMode mode, std::string title);

	void update();
	void events();
	void render() const;
	bool isRunning() { return running; };
	sf::RenderWindow& getWindow() const;

private:
	std::unique_ptr<sf::RenderWindow> window;
	std::vector<Manager*> managers;
	sf::ContextSettings settings;
	sf::Event event;
	bool running = false;
};
