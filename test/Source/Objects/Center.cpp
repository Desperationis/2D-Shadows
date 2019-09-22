#include "Center.h"
#define M_PI 3.14159265359


Center::Center(sf::RenderWindow & window, SegmentManager& map) : segmentManager() {
	center.setRadius(10.0f);
	center.setFillColor(sf::Color(255, 0, 0, 255));

	this->window = &window;
	this->map = &map;

	segmentManager.resize(map.segments.size() * 2);
	for (int i = 0; i < map.segments.size() * 2; i++) {
		segmentManager.insertLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));
	}
}

void Center::update() {
	sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window));
	
	moveCenter(mouse);
	updateSegments(mouse);
	collideSegments(mouse);


	// Updates GPU rays
	segmentManager.update();
};

void Center::updateSegments(sf::Vector2f& mouse) {
	for (int i = 0; i < map->segments.size(); i++) {
		int index = i * 2;
		segmentManager.segments[index].first = mouse;
		segmentManager.segments[index].second = map->segments[i].first;

		segmentManager.segments[index + 1].first = mouse;
		segmentManager.segments[index + 1].second = map->segments[i].second;
	}
}

void Center::collideSegments(sf::Vector2f& mouse) {
	for (int i = 0; i < segmentManager.segments.size(); i++) {
		sf::Vector2f outwardRay = segmentManager.segments[i].second;
		for (int j = 0; j < map->segments.size(); j++) {
			if (segmentManager.segments[i].intersect(map->segments[j])) {
				outwardRay = segmentManager.segments[i].intersection(map->segments[j]);
			}
			segmentManager.setPosition(i, mouse, outwardRay);
		}
	}
}

void Center::moveCenter(sf::Vector2f& mouse) {
	sf::Vector2f centerPos(mouse.x - center.getRadius(), mouse.y - center.getRadius());
	center.setPosition(centerPos);
}

void Center::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform(); // Applies all current transforms
	target.draw(center, states);
	target.draw(segmentManager, states);
}

void Center::setCenterSize(float size) {
	center.setRadius(size);
}