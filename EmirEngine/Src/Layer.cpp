#include "Layer.h"
#include <fstream>
#include <string>
#include "Game.h"
#include "../ECS/Components.h"
#include "../ECS/ECS.h"
extern Manager manager;


Layer::Layer(std::string id, int tSize, int sc, int r)
{
	terrainID = id;
	tileSize = tSize;
	scale = sc;
	scaledSize = sc * tSize;
	ratio = r;

}

Layer::~Layer()
{


}

void Layer::LoadLayer(std::string path, int sizex, int sizey)
//size x = 25;
{
	if (path == "")
	{
		return;
	}


	std::fstream mapFile;
	std::string str;//+

	mapFile.open(path);
	//int srcX ,  srcY;
	for (int y = 0; y < sizey; y++)
	{
		for (int x = 0; x < sizex; x++)
		{

			std::getline(mapFile, str, ',');
			//std::cout << "the value in the pos :" << x << "," << y << " is " << str << std::endl;
			//std::cout << "the pos is :" << x << "," << y << std::endl;

			//std::cout << str << std::endl;

			int src = std::stoi(str);
			int srcY = (src / 10) * tileSize;



			int srcX = (src % 10) * tileSize;



			addTile(srcX, srcY, x * scaledSize, y * scaledSize);
			//mapFile.ignore();
		}
		mapFile.ignore();

	}



	mapFile.close();
}



void Layer::addTile(int srcX, int srcY, int posX, int posY)
{
	auto& tile(manager.addEntity());

	tile.addComponent<TileComponent>(terrainID, srcX, srcY, posX, posY, tileSize, scale, ratio);
	tile.addGroup(Game::groupMap);
}


void Layer::AddColliders(std::string path, int sizeX, int sizeY)
{
	std::fstream mapFile;
	char c;

	mapFile.open(path);

	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& col(manager.addEntity());
				col.addComponent<TileCollider>("terrain", scaledSize*x, scaledSize*y, scaledSize);
				col.addGroup(Game::groupColliders);
			}

			mapFile.ignore();
		}
	}

	mapFile.close();

}
