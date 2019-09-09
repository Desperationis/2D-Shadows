#pragma once
#include "Manager.h"
#include <vector>

class Segment;
class MapManager : public Manager {
public:
	MapManager(sf::RenderWindow& window);
	void update() override;
	void render() override;
	void loadMap(int* map, float tilesize, int width, int height);
	
	std::vector<Segment> segments;
private:
	sf::VertexArray quads;
};
