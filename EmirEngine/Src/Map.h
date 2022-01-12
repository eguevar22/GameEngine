#pragma once
#include "Layer.h"
#include <fstream>
#include <string>
#include <map>
//#include "Game.h"




class Map
{
private:
	Layer* sky;
	Layer* clouds;
	Layer* ground;
	Layer* objects;
	int tileSize = Game::tileSize;
	int tilesX;
	int tilesY;


	//Manager* manager;
	//std::map<std::string, Layer*> layers;

public:

	Map(int tilesx, int tilesy)
	{
		tilesX = tilesx;
		tilesY = tilesy;
		sky = new Layer("terrain", tileSize, 3, 2);
		clouds = new Layer("terrain", tileSize, 3, 3);
		ground = new Layer("terrain", tileSize, 3, 1);
		objects = new Layer("terrain", tileSize, 3, 1);

		

	}
	~Map()
	{

		delete sky;
		sky = nullptr;
		delete clouds;
		clouds = nullptr;
		delete ground;
		ground = nullptr;
	}


	void LoadMap(int level)
	{

		//call this function and set a big texture as a rendering target
		//Load the layers below
		if (level == 1)
		{
			sky->LoadLayer("assets/sky_level1.map", tilesX, tilesY);

			clouds->LoadLayer("assets/clouds_level1.map", tilesX, tilesY);

			ground->LoadLayer("assets/ground_level1.map", tilesX, tilesY);
			objects->LoadLayer("", tilesX, tilesY);
			ground->AddColliders("assets/colliders_level1.map", tilesX, tilesY);


		}
		else
		{
			sky->LoadLayer("assets/sky_level2.map", tilesX, tilesY);

			clouds->LoadLayer("assets/clouds_level2.map", tilesX, tilesY);

			ground->LoadLayer("assets/ground_level2.map", tilesX, tilesY);
			objects->LoadLayer("assets/objects_level2.map", tilesX, tilesY);
			ground->AddColliders("assets/colliders_accurate.map", tilesX, tilesY);

		}
		

	}

	void ReloadLayers()
	{

	}






};
