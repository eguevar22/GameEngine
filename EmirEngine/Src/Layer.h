#pragma once
#include "Game.h"

class Layer
{
public:
	Layer(std::string id, int tSize, int sc, int r);
	~Layer();

	void LoadLayer(std::string path, int sizex, int sizey);
	void AddColliders(std::string path, int sizeX, int sizeY);
	void addTile(int srcX, int srcY, int posX, int posY);



private:
	std::string terrainID;
	int scale;
	int scaledSize;
	int tileSize;
	int ratio;


};