#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "vector"
#include <string>
#include <string_view>
#include <stdexcept>
#include <format>

using namespace std::literals::string_view_literals;

class Texture_Container
{
    Texture2D texture;
public:
    Texture_Container(std::string_view path);
    Texture_Container(const Texture_Container& other) = delete;
    Texture_Container& operator=(const Texture_Container& other) = delete;
    Texture_Container(Texture_Container&& other) noexcept;
    Texture_Container& operator=(Texture_Container&& other) noexcept;
    ~Texture_Container();
    const Texture2D& Get() const noexcept;
};

class Animator
{
    std::vector<Texture_Container> frames;
    size_t current_frame = 0;
    float frames_per_second = 3.0f;
    float timer = 0;

public:
    Animator(std::vector<std::string_view> file_paths);

    void Update(float deltaTime) noexcept;
    const Texture2D& GetFrame() const noexcept;
};

class Resources 
{
    Texture_Container alienTexture = Texture_Container( "./Assets/Alien.png"sv );
    Texture_Container barrierTexture = Texture_Container( "./Assets/Barrier.png"sv);
    Texture_Container laserTexture = Texture_Container( "./Assets/Laser.png"sv );
public:

    const Texture2D& GetAlienTexture() const noexcept;
    const Texture2D& GetBarrierTexture() const noexcept;
    const Texture2D& GetLaserTexture() const noexcept;

};