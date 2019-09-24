#pragma once
#include "SFML/Graphics.hpp"

class Segment {
public:
	Segment(sf::Vector2f first, sf::Vector2f second);
	bool intersect(Segment& target);
	sf::Vector2f intersection(Segment& target);

public:
	sf::Vector2f first, second;
	double angle = 0.0;

private:
	bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
		return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
			q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
	}

	int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
		int val = static_cast<int>((q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y));

		if (val == 0) return 0;  // colinear 

		return (val > 0) ? 1 : 2; // clock or counterclock wise 
	}
};
