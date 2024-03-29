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

class Animator 
{
    float timer = 0;
    int current_frame = 0;
    
public:
    const int get(int _number_of_frames) noexcept;
};

class Texture_Container
{
public:
    Texture2D texture;
    Texture_Container(std::string_view path);
    Texture_Container(const Texture_Container& other) = delete;
    Texture_Container& operator=(const Texture_Container& other) = delete;
    Texture_Container(Texture_Container&& other) noexcept;
    Texture_Container& operator=(Texture_Container&& other) noexcept;
    ~Texture_Container();
};

class Resources 
{
public:
    std::vector<Texture_Container> shipTextures;
    Texture_Container alienTexture;
    Texture_Container barrierTexture;
    Texture_Container laserTexture;
    Animator animator;

     Resources();

    const Texture2D& GetAlienTexture() const noexcept;
    const Texture2D& GetBarrierTexture() const noexcept;
    const Texture2D& GetLaserTexture() const noexcept;
    const Texture2D& GetShipTexture() noexcept;
};