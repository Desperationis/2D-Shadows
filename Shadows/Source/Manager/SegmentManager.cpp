#include "SegmentManager.h"

SegmentManager::SegmentManager() {
	segmentsRender.setPrimitiveType(sf::Lines);
}

void SegmentManager::update() {
	for (int i = 0; i < segments.size(); i++) {
		int index = i * 2;
		segmentsRender[index].position = segments[i].first;
		segmentsRender[index + 1].position = segments[i].second;
	}
}

void SegmentManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(segmentsRender, states);
}

void SegmentManager::insertLine(sf::Vector2f first, sf::Vector2f second) {
	segments.push_back(Segment(first, second));

	int index = (segments.size() - 1) * 2;

	segmentsRender[index].position = first;
	segmentsRender[index + 1].position = second;

	segmentsRender[index].color = sf::Color::Red;
	segmentsRender[index + 1].color = sf::Color::Red;
}

void SegmentManager::setPosition(int index, sf::Vector2f first, sf::Vector2f second) {
	segments[index].first = first;
	segments[index].second = second;
}

void SegmentManager::resize(size_t size) {
	segmentsRender.resize(size * 2);
}
