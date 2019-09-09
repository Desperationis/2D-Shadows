#include "Ball.h"
#include "Segment.h"
#include <cmath>

#define M_PI 3.14159265359

Ball::Ball(sf::RenderWindow& window, int count) : velocity(2.0f, 1.0f), linesRender(sf::Lines, count * 2) {
	this->window = &window;
	circle.setRadius(5.0f);
	circle.setFillColor(sf::Color(255, 0, 0, 255));

	double degrees = 360.0 / count;
	for (int i = 0; i < count * 2; i++) {
		if (i % 2 == 0) {
			linesRender[i].position.x = cos((degrees * (i / 2)) * (M_PI / 180.0)) * 10000.0;
			linesRender[i].position.y = sin((degrees * (i / 2)) * (M_PI / 180.0)) * 10000.0;
		}
		else {
			linesRender[i].position = circle.getPosition();
		}
		linesRender[i].color = sf::Color::Red;
	}

	for (int i = 0; i < count; i++) {
		lines.push_back(Segment(circle.getPosition(), sf::Vector2f(cos((degrees * i) * (M_PI / 180.0)) * 10000.0, cos((degrees * i) * (M_PI / 180.0)) * 10000.0)));
	}
}

void Ball::update() {
	circle.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x - circle.getRadius(), sf::Mouse::getPosition(*window).y - circle.getRadius()));
	
	double degrees = 360.0 / lines.size();

	for (int i = 0; i < lines.size() * 2; i++) {
		if (i % 2 == 0) {
			linesRender[i].position.x = cos((degrees * (i / 2)) * (M_PI / 180.0)) * 10000.0 + (circle.getPosition().x + circle.getRadius());
			linesRender[i].position.y = sin((degrees * (i / 2)) * (M_PI / 180.0)) * 10000.0 + (circle.getPosition().y + circle.getRadius());
		}
		else {
			linesRender[i].position = circle.getPosition();
			linesRender[i].position.x += circle.getRadius();
			linesRender[i].position.y += circle.getRadius();
		}
	}

};

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//states.transform *= getTransform(); // Applies all current transforms
	target.draw(circle, states);
	target.draw(linesRender, states);
}