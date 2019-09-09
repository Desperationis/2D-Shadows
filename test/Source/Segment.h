#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Segment : public sf::Drawable {
public:
	Segment(sf::Vector2f first, sf::Vector2f second);

	bool intersect(Segment& target);
	sf::Vector2f intersection(Segment& target);
	sf::Vector2f getFirst() { return first; }
	sf::Vector2f getSecond() { return second; }
	void setFirst(float x, float y);
	void setSecond(float x, float y);
private:
	sf::VertexArray line;
	sf::Vector2f first, second;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// thanks to https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/  and https://rosettacode.org/wiki/Find_the_intersection_of_two_lines
	// for the formulas and math! I tried to understand this for hours, but my puny high school brain needs to learn more math. Instead, I copied them
	// and changed it a bit, sorry.

	bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
		// Given three colinear points p, q, r, the function checks if 
		// point q lies on line segment 'pr' 
		return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
			q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
	}


	int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
	{
		// To find orientation of ordered triplet (p, q, r). 
		// The function returns following values 
		// 0 --> p, q and r are colinear 
		// 1 --> Clockwise 
		// 2 --> Counterclockwise 
		// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
		// for details of below formula. 
		int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

		if (val == 0) return 0;  // colinear 

		return (val > 0) ? 1 : 2; // clock or counterclock wise 
	}
};
