  #include "Resources.h"
#include <iostream>;


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

void Resources::Unload()
{
    UnloadTexture(alienTexture);
    UnloadTexture(barrierTexture);
    UnloadTexture(laserTexture);
}

Resources::Resources()
{
    Load();
}

Resources::~Resources()
{
    Unload();
}





Animation::Animation(std::vector<Texture2D> _frames)
{
	frames = _frames;
	current_frame = 0;
	timer = 0;
}

Animation::~Animation()
{
	for (const auto& texture : frames)
	{
		UnloadTexture(texture);
	}
}

Texture2D Animation::get()
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
