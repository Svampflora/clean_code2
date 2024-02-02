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
    Texture2D alienTexture;
    Texture2D barrierTexture;
    Texture2D laserTexture;

    void Load();

public:

    Resources();
    Resources(const Resources& other);
    Resources& operator=(const Resources& other);
    Resources(Resources&& other) noexcept;
    Resources& operator=(Resources&& other) noexcept;
    ~Resources();

    const Texture2D& GetAlienTexture() const;
    const Texture2D& GetBarrierTexture() const;
    const Texture2D& GetLaserTexture() const;
};