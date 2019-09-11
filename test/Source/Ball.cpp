#include "Ball.h"
#include "Segment.h"
#include <cmath>

#define M_PI 3.14159265359

Ball::Ball(sf::RenderWindow& window, int count, std::vector<Segment>& segments) : velocity(2.0f, 1.0f), linesRender(sf::Lines, (count + 1) * 2), triangles(sf::Triangles, (count + 1) * 3) {
	int newCount = count + 1;
	this->window = &window;
	circle.setRadius(3.0f);
	circle.setFillColor(sf::Color(255, 0, 0, 255));

	double degrees = 360.0 / (newCount - 1);
	for (int i = 0; i < newCount* 2; i++) {
		if (i % 2 == 0) {
			linesRender[i].position.x = cos((degrees * (i / 2)) * (M_PI / 180.0)) * 10000.0;
			linesRender[i].position.y = sin((degrees * (i / 2)) * (M_PI / 180.0)) * 10000.0;
		}
		else {
			linesRender[i].position = circle.getPosition();
		}
		linesRender[i].color = sf::Color::Red;
	}

	for (int i = 0; i < newCount; i++) {
		lines.push_back(Segment(circle.getPosition(), sf::Vector2f(cos((degrees * i) * (M_PI / 180.0)) * 10000.0, cos((degrees * i) * (M_PI / 180.0)) * 10000.0)));
	}
	for (int i = 0; i < newCount * 3; i++) {
		triangles[i].color = sf::Color::Blue;
	}
	
	this->segments = &segments;
}

void Ball::update() {
	circle.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x - circle.getRadius(), sf::Mouse::getPosition(*window).y - circle.getRadius()));
	
	double degrees = 360.0 / (lines.size() - 1);

	for (int i = 0; i < lines.size(); i++) {
		lines[i].setFirst(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());
		float sx = (cos((degrees * i) * (M_PI / 180.0)) * 10000.0) + circle.getPosition().x + circle.getRadius();
		float sy = (sin((degrees * i) * (M_PI / 180.0)) * 10000.0) + circle.getPosition().y + circle.getRadius();
		lines[i].setSecond(sx, sy);
		
		for (int j = 0; j < segments->size(); j++) {
			if (lines[i].intersect((*segments)[j])) {
				sf::Vector2f intersection = lines[i].intersection((*segments)[j]);
				lines[i].setSecond(intersection.x, intersection.y);
			}
		}
	}
	for (int i = 1; i < lines.size(); i++) {
		int number = (i * 2);
		linesRender[number].position = lines[i].getSecond();

		linesRender[number + 1].position = circle.getPosition();
		linesRender[number + 1].position.x += circle.getRadius();
		linesRender[number + 1].position.y += circle.getRadius();
	}

	for (int i = 0; i < lines.size(); i++) {
		int triangleIndex = i * 3;

		triangles[triangleIndex].position = lines[i].getSecond();
		triangles[triangleIndex + 1].position = lines[i].getFirst();
		if (i == lines.size() - 1) {
			triangles[triangleIndex + 2].position = lines[0].getSecond();
		}
		else {
			triangles[triangleIndex + 2].position = lines[i + 1].getSecond();
		}

	}
};

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//states.transform *= getTransform(); // Applies all current transforms
	target.draw(circle, states);
	target.draw(triangles, states);
	//target.draw(linesRender, states);
}