  #include "Resources.h"
#include <iostream>


void Resources::Load()
{
    shipTextures = std::vector{ LoadTexture("./Assets/Ship1.png"), LoadTexture("./Assets/Ship2.png"), LoadTexture("./Assets/Ship3.png") };
    for (auto &texture : shipTextures)
    {
        if (texture.id == 0) 
        {
            std::cerr << "Error loading Ship texture\n";
        }
    }

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
    animator = {};
    Load();
}

//copy constructor
Resources::Resources(const Resources& other)
    : shipTextures(other.shipTextures.size()),
    animator(other.animator)
{
    for (size_t i = 0; i < other.shipTextures.size(); ++i) 
    {
        shipTextures[i] = other.shipTextures[i];
    }

    alienTexture = other.alienTexture;
    barrierTexture = other.barrierTexture;
    laserTexture = other.laserTexture;

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
        animator = other.animator;
    }
    return *this;
}

//move constructor
Resources::Resources(Resources&& other) noexcept
    : shipTextures(std::move(other.shipTextures)),
    alienTexture(std::move(other.alienTexture)),
    barrierTexture(std::move(other.barrierTexture)),
    laserTexture(std::move(other.laserTexture)),
    animator(std::move(other.animator))
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
        animator = std::move(other.animator);
    }
    return *this;
}

Resources::~Resources() 
{
    for (auto &texture : shipTextures)
    {
        UnloadTexture(texture);
    }
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

const Texture2D& Resources::GetShipTexture()
{
    int frame = animator.get(static_cast<int>(shipTextures.size()));
    return shipTextures[frame];
}

const int Animator::get(int _number_of_frames) 
{
	timer += GetFrameTime();
	if (timer <= 0.4) 
    {
		return current_frame;
	}
	current_frame++;
	timer = 0;
	if (current_frame == _number_of_frames) 
    {
		current_frame = 0;			
	}		
	return current_frame;
}
