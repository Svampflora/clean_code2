  #include "Resources.h"
#include <iostream>


const size_t Animator::Get(size_t _number_of_frames) noexcept
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

Texture_Container::Texture_Container(std::string_view path)
{
    texture = LoadTexture(path.data());
    if (texture.id == 0)
    {
        throw(std::runtime_error(std::format("Unable to load texture: {} "sv, path)));
        
    }
}

Texture_Container::Texture_Container(Texture_Container&& other) noexcept
{
    texture = std::move(other.texture);
}

Texture_Container& Texture_Container::operator=(Texture_Container&& other) noexcept
{
    if (this != &other)
    {
        std::swap(texture, other.texture);
    }
    return *this;
}

Texture_Container::~Texture_Container()
{
    UnloadTexture(texture);
}

const Texture2D& Texture_Container::Get() const noexcept
{
    return texture;
}

[[gsl::suppress(f.6)]]
Resources::Resources() //TODO: default constructor insists on noexcept
{
    shipTextures.reserve(3);
    shipTextures.emplace_back("./Assets/Ship1.png"sv);
    shipTextures.emplace_back("./Assets/Ship2.png"sv);
    shipTextures.emplace_back("./Assets/Ship3.png"sv);
}


const Texture2D& Resources::GetAlienTexture() const noexcept
{
    return alienTexture.Get();
}

const Texture2D& Resources::GetBarrierTexture() const noexcept
{
    return barrierTexture.Get();
}

const Texture2D& Resources::GetLaserTexture() const noexcept
{
    return laserTexture.Get();
}

const Texture2D& Resources::GetShipTexture() noexcept
{
    const size_t frame = animator.Get(shipTextures.size()-1);

    [[gsl::suppress(bounds.4)]]
    return shipTextures[frame].Get();
 
}

