#include "RadialManager.h"

#include <iostream>
RadialManager::RadialManager() : SegmentManager() {
	triangles.setPrimitiveType(sf::Triangles);
}

void RadialManager::insertLine(sf::Vector2f first, sf::Vector2f second) {
	int index = segments.size() * 2;

	segments.push_back(Segment(first, second));
	segments.push_back(Segment(first, second));
	segments.push_back(Segment(first, second));

	// 0 & 1 Original Line
	// 2 & 3 Left support
	// 4 & 5 Right support
}

void RadialManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(segmentsRender, states);
	target.draw(triangles, states);
}

void RadialManager::resize(size_t size) {
	int lines = size * 3; // Inludes extra lines to hit behind a corner
	segmentsRender.resize(lines * 2);
	triangles.resize(lines * 3);

	for (int i = 0; i < lines * 2; i++) {
		segmentsRender[i].color = sf::Color::Red;
	}
	for (int i = 0; i < lines * 3; i++) {
		triangles[i].color = sf::Color::White;
	}
}