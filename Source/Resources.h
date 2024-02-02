#pragma once
#include "raylib.h"
#include "vector"

class Animator 
{
    float timer = 0;
    int current_frame = 0;

public:
    const int get(int _number_of_frames);
};


class Resources 
{
    std::vector<Texture2D> shipTextures;
    Texture2D alienTexture;
    Texture2D barrierTexture;
    Texture2D laserTexture;
    Animator animator;

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
    const Texture2D& GetShipTexture();
};