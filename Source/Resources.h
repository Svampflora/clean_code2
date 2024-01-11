#pragma once
#include "raylib.h"
#include "vector"

class Animation
{
	std::vector<Texture2D> frames;
	float timer;
	int current_frame;
public:
	Animation(std::vector<Texture2D> _frames);
	~Animation();

	Texture2D get(); 
};


class Resources 
{
	std::vector<Texture2D> shipTextures;

	void Load();
	void Unload();
public:									
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;

	Resources();
	Resources(const Resources& other)
		: shipTextures(other.shipTextures),
		alienTexture(other.alienTexture),
		barrierTexture(other.barrierTexture),
		laserTexture(other.laserTexture)
	{
		Load();
	}
	Resources& operator=(const Resources& other)
	{
		if (this != &other) {

			shipTextures = other.shipTextures;
			alienTexture = other.alienTexture;
			barrierTexture = other.barrierTexture;
			laserTexture = other.laserTexture;

		}
		return *this;
	}
	~Resources();

};