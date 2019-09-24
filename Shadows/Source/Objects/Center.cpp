#include "Center.h"
#define M_PI 3.14159265359

#include <iostream>
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
	for (int i = 0; i < segmentManager.segments.size(); i++) {
		segmentManager.segments[i].angle = atan2(mouse.y - segmentManager.segments[i].second.y,  mouse.x - segmentManager.segments[i].second.x) * (180.0 / M_PI);
	}

	std::sort(segmentManager.segments.begin(), segmentManager.segments.end(),
		[](const Segment& p1, const Segment& p2) {
		return p1.angle > p2.angle;
	});

	for (int i = 0; i < segmentManager.segments.size(); i++) {
		int index = i * 3;
		if (i != 0) {
			segmentManager.triangles[index].position = segmentManager.segments[i - 1].second;
		}
		segmentManager.triangles[index + 1].position = mouse;
		segmentManager.triangles[index + 2].position = segmentManager.segments[i].second;

		if (i == segmentManager.segments.size() - 1) {
			segmentManager.triangles[0].position = segmentManager.segments[segmentManager.segments.size() - 1].second;
		}
	}

	// Updates GPU rays
	segmentManager.update();
};

void Center::updateSegments(sf::Vector2f& mouse) {
	for (int i = 0; i < map->segments.size(); i++) {
		int index = i * 3;
		segmentManager.segments[index].first = mouse;
		segmentManager.segments[index].second = map->segments[i].first;

		float radian = atan2(map->segments[i].second.y - mouse.y, map->segments[i].second.x - mouse.x);
		sf::Vector2f offset_l(cos(radian - 0.0001f) * 10000 + mouse.x, sin(radian - 0.0001f) * 10000 + mouse.y);
		segmentManager.segments[index + 1].first = mouse;
		segmentManager.segments[index + 1].second = offset_l;
	
		sf::Vector2f offset_r(cos(radian + 0.0001f) * 10000 + mouse.x, sin(radian + 0.0001f) * 10000 + mouse.y);
		segmentManager.segments[index + 2].first = mouse;
		segmentManager.segments[index + 2].second = offset_r;
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
	target.draw(segmentManager, states);
	target.draw(center, states);
}

void Center::setCenterSize(float size) {
	center.setRadius(size);
}