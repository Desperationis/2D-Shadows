#include "RadialManager.h"

#include <iostream>
RadialManager::RadialManager() : SegmentManager() {

}

void RadialManager::insertLine(sf::Vector2f first, sf::Vector2f second) {
	int index = segments.size() * 2;
	std::cout << index << std::endl;
	segmentsRender[index].color = sf::Color::Red;
	segmentsRender[index + 1].color = sf::Color::Red;
	segmentsRender[index + 2].color = sf::Color::Red;
	segmentsRender[index + 3].color = sf::Color::Red;
	segmentsRender[index + 4].color = sf::Color::Red;
	segmentsRender[index + 5].color = sf::Color::Red;

	segments.push_back(Segment(first, second));
	segments.push_back(Segment(first, second));
	segments.push_back(Segment(first, second));

	// 0 & 1 Original Line
	// 2 & 3 Left support
	// 4 & 5 Right support
}

void RadialManager::resize(size_t size) {
	segmentsRender.resize(size * 6);
}