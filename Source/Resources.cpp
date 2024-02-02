  #include "Resources.h"
#include <iostream>


void Resources::Load()
{
    alienTexture = LoadTexture("./Assets/Alien.png");
    if (alienTexture.id == 0) 
    {
        std::cerr << "Error loading Alien texture\n";
    }

    barrierTexture = LoadTexture("./Assets/Barrier.png");
    if (barrierTexture.id == 0) 
    {
        std::cerr << "Error loading Barrier texture\n";
    }

    laserTexture = LoadTexture("./Assets/Laser.png");
    if (laserTexture.id == 0) 
    {
        std::cerr << "Error loading Laser texture\n";
    }

    std::cout << "Loaded resources!\n";
}

Resources::Resources()
{
    Load();
}

//copy constructor
Resources::Resources(const Resources& other)
    : shipTextures(other.shipTextures.size())
{
    for (size_t i = 0; i < other.shipTextures.size(); ++i) 
    {
        shipTextures[i] = other.shipTextures[i];
    }

    alienTexture = other.alienTexture;
    barrierTexture = other.barrierTexture;
    laserTexture = other.laserTexture;

    Load();  //load resources for the current instance
}

//copy assignment operator
Resources& Resources::operator=(const Resources& other) 
{
    if (this != &other) 
    {
        shipTextures.clear();
        shipTextures.resize(other.shipTextures.size());
        for (size_t i = 0; i < other.shipTextures.size(); ++i) 
        {
            shipTextures[i] = other.shipTextures[i];
        }

        alienTexture = other.alienTexture;
        barrierTexture = other.barrierTexture;
        laserTexture = other.laserTexture;

        Load();
    }
    return *this;
}

//move constructor
Resources::Resources(Resources&& other) noexcept
    : shipTextures(std::move(other.shipTextures)),
    alienTexture(std::move(other.alienTexture)),
    barrierTexture(std::move(other.barrierTexture)),
    laserTexture(std::move(other.laserTexture)) 
{
}

//move assignment operator
Resources& Resources::operator=(Resources&& other) noexcept 
{
    if (this != &other) 
    {
        shipTextures = std::move(other.shipTextures);
        alienTexture = std::move(other.alienTexture);
        barrierTexture = std::move(other.barrierTexture);
        laserTexture = std::move(other.laserTexture);
    }
    return *this;
}

Resources::~Resources() 
{
    UnloadTexture(alienTexture);
    UnloadTexture(barrierTexture);
    UnloadTexture(laserTexture);
}

const Texture2D& Resources::GetAlienTexture() const 
{
    return alienTexture;
}

const Texture2D& Resources::GetBarrierTexture() const 
{
    return barrierTexture;
}

const Texture2D& Resources::GetLaserTexture() const 
{
    return laserTexture;
}





Animation::~Animation()
{
	for (const auto& texture : frames)
	{
		UnloadTexture(texture);
	}
}

//copy assignment operator
Animation& Animation::operator=(const Animation& other)
{
    if (this != &other) 
    {
        frames = other.frames;
        timer = other.timer;
        current_frame = other.current_frame;
    }
    return *this;
}

//move assignment operator
Animation& Animation::operator=(Animation&& other) noexcept 
{
    if (this != &other) 
    {
        frames = std::move(other.frames);
        timer = other.timer;
        current_frame = other.current_frame;
    }
    return *this;
}

const Texture2D& Animation::get() 
{
	timer += GetFrameTime();
	if (timer <= 0.4) {
		return frames[current_frame];
	}
	current_frame++;
	timer = 0;
	if (current_frame == frames.size()) {
		current_frame = 0;			
	}		
	return frames[current_frame];
}
