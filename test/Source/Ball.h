#pragma once
#include "Object.h"
#include "SFML/Window/Mouse.hpp"

class Segment;
class Ball : public Object {
public:
	Ball(sf::RenderWindow& window, int count);
	void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::CircleShape circle;
	sf::Vector2f velocity;
	sf::RenderWindow* window;
private:
	sf::VertexArray linesRender;
	std::vector<Segment> lines;


	std::vector<Segment> segments;
};