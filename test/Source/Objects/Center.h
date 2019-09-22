#pragma once
#include "Object.h"
#include "../Manager/SegmentManager.h"

struct Center : public Object {
public:
	Center(sf::RenderWindow& window, SegmentManager& map);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setCenterSize(float size);

private:
	void updateSegments(sf::Vector2f& mouse); // Updates position of each segment
	void collideSegments(sf::Vector2f& mouse); // collides rays with walls
	void moveCenter(sf::Vector2f& mouse); // Centers circle to the cursor
private:
	sf::RenderWindow* window;
	sf::CircleShape center;
	SegmentManager segmentManager;
	SegmentManager* map;

};