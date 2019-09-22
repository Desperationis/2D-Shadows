#pragma once
#include "Manager.h"
#include "SegmentManager.h"

class MapManager : public Manager {
public:
	MapManager(sf::RenderWindow& window);
	void render() override;
	void loadMap(int* map, float tilesize, int width, int height);
	SegmentManager& getSegments();
private:
	sf::VertexArray quads;
	SegmentManager segments;
};
