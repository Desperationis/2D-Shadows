#pragma once
#include "Manager.h"
#include <unordered_map>
#include "../Objects/Segment.h"

/*

	This is a special manager, as it is used in objects to organize their
	segments, and not hold a global segment database. 

*/
class Segment;
class RadialManager;
class SegmentManager : public Manager, public sf::Drawable {
public:
	SegmentManager();
	virtual void update() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void insertLine(sf::Vector2f first, sf::Vector2f second);
	virtual void setPosition(int index, sf::Vector2f first, sf::Vector2f second);
	virtual void resize(size_t size); // resizes by number of segments, not points

public:
	std::vector<Segment> segments;
	sf::VertexArray segmentsRender;
};