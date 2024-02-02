#pragma once
#include "raylib.h"
#include "vector"

class Animation 
{
    std::vector<Texture2D> frames;
    float timer;
    int current_frame;

public:


    Animation(std::vector<Texture2D> _frames) : frames(std::move(_frames)), timer(0.0f), current_frame(0){}
    Animation(const Animation& other) : frames(other.frames), timer(other.timer), current_frame(other.current_frame) {}
    Animation& operator=(const Animation& other);
    Animation(Animation&& other) noexcept : frames(std::move(other.frames)), timer(other.timer), current_frame(other.current_frame) {}
    Animation& operator=(Animation&& other) noexcept;
    ~Animation();

    const Texture2D& get();
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