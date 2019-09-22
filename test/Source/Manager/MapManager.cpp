#include "MapManager.h"
#include "Segment.h"

MapManager::MapManager(sf::RenderWindow& window) : segments(){
	this->window = &window;
	quads.setPrimitiveType(sf::Quads);
}

void MapManager::render() {
	window->draw(quads);
	window->draw(segments);
}

void MapManager::loadMap(int* map, float tilesize, int width, int height) {
	quads.resize(width * height * 4);
	segments.resize(width * height * 8);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int tileNumber = map[i * width + j];
			sf::Vertex* quad = &quads[(i * width + j) * 4];

			quad[0].position = sf::Vector2f(j * tilesize, i * tilesize);
			quad[1].position = sf::Vector2f((j + 1) * tilesize, i * tilesize);
			quad[2].position = sf::Vector2f((j + 1) * tilesize, (i + 1) * tilesize);
			quad[3].position = sf::Vector2f(j * tilesize, (i + 1) * tilesize);

			switch (tileNumber) {
			case 0:
				quad[0].color = sf::Color(255, 255, 255, 0);
				quad[1].color = sf::Color(255, 255, 255, 0);
				quad[2].color = sf::Color(255, 255, 255, 0);
				quad[3].color = sf::Color(255, 255, 255, 0);
				break;
			case 1:
				quad[0].color = sf::Color::Black;
				quad[1].color = sf::Color::Black;
				quad[2].color = sf::Color::Black;
				quad[3].color = sf::Color::Black;

				segments.insertLine(quad[0].position, quad[1].position);
				segments.insertLine(quad[1].position, quad[2].position);
				segments.insertLine(quad[2].position, quad[3].position);
				segments.insertLine(quad[3].position, quad[0].position);

				break;
			}

		}
	}

	segments.insertLine(sf::Vector2f(0.0f,0.0f), sf::Vector2f(800.0f,0.0f));
	segments.insertLine(sf::Vector2f(800.0f,0.0f), sf::Vector2f(800.0f,800.0f));
	segments.insertLine(sf::Vector2f(800.0f,800.0f), sf::Vector2f(0.0f,800.0f));
	segments.insertLine(sf::Vector2f(0.0f, 800.0f), sf::Vector2f(0.0f, 0.0f));
}

SegmentManager& MapManager::getSegments() {
	return segments;
}