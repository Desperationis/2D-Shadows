#pragma once
#include "SegmentManager.h"


class RadialManager : public SegmentManager {
public:
	RadialManager();
	void insertLine(sf::Vector2f first, sf::Vector2f second) override;
	void resize(size_t size) override;
};