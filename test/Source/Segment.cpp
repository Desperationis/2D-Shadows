#include "Segment.h"


Segment::Segment(sf::Vector2f first, sf::Vector2f second) : line(sf::Lines, 2) {
	this->first = first;
	this->second = second;

	line[0].position = first;
	line[1].position = second;

	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;
};

void Segment::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(line, states);
}

bool Segment::intersect(Segment& target) {
	// Find the four orientations needed for general and 
		// special cases 
	int o1 = orientation(first, second, target.getFirst());
	int o2 = orientation(first, second, target.getSecond());
	int o3 = orientation(target.getFirst(), target.getSecond(), first);
	int o4 = orientation(target.getFirst(), target.getSecond(), second);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// first, second and target.getFirst() are colinear and target.getFirst() lies on segment firstsecond 
	if (o1 == 0 && onSegment(first, target.getFirst(), second)) return true;

	// first, second and target.getSecond() are colinear and target.getSecond() lies on segment firstsecond 
	if (o2 == 0 && onSegment(first, target.getSecond(), second)) return true;

	// target.getFirst(), target.getSecond() and first are colinear and first lies on segment target.getFirst()target.getSecond() 
	if (o3 == 0 && onSegment(target.getFirst(), first, target.getSecond())) return true;

	// target.getFirst(), target.getSecond() and second are colinear and second lies on segment target.getFirst()target.getSecond() 
	if (o4 == 0 && onSegment(target.getFirst(), second, target.getSecond())) return true;

	return false; // Doesn't fall in any of the above cases 
}

inline double Det(double a, double b, double c, double d)
{
	return a * d - b * c;
}

sf::Vector2f Segment::intersection(Segment& target) {
	sf::Vector2f result;
	float x1 = first.x;
	float y1 = first.y;
	float x2 = second.x;
	float y2 = second.y;
	float x3 = target.first.x;
	float y3 = target.first.y;
	float x4 = target.second.x;
	float y4 = target.second.y;


	float detL1 = Det(x1, y1, x2, y2);
	float detL2 = Det(x3, y3, x4, y4);
	float x1mx2 = x1 - x2;
	float x3mx4 = x3 - x4;
	float y1my2 = y1 - y2;
	float y3my4 = y3 - y4;
	float xnom = Det(detL1, x1mx2, detL2, x3mx4);
	float ynom = Det(detL1, y1my2, detL2, y3my4);
	float denom = Det(x1mx2, y1my2, x3mx4, y3my4);
	if (denom == 0.0)//Lines don't seem to cross
	{
		result.x = NAN;
		result.y = NAN;
		return result;
	}

	result.x = xnom / denom;
	result.y = ynom / denom;
	return result;
}

void Segment::setFirst(float x, float y) {
	first.x = x;
	first.y = y;
	line[0].position = sf::Vector2f(x, y);
}

void Segment::setSecond(float x, float y) {
	second.x = x;
	second.y = y;
	line[1].position = sf::Vector2f(x, y);
}