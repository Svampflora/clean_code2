  #include "Resources.h"
#include <iostream>


Resources::Resources() noexcept
{
    shipTextures.reserve(3);
    shipTextures.emplace_back("./Assets/Ship1.png"sv);
    shipTextures.emplace_back("./Assets/Ship2.png"sv);
    shipTextures.emplace_back("./Assets/Ship3.png"sv);
}


const Texture2D& Resources::GetAlienTexture() const noexcept
{
    return alienTexture.texture;
}

const Texture2D& Resources::GetBarrierTexture() const noexcept
{
    return barrierTexture.texture;
}

const Texture2D& Resources::GetLaserTexture() const noexcept
{
    return laserTexture.texture;
}

const Texture2D& Resources::GetShipTexture()
{
    const size_t frame = animator.get(shipTextures.size());
    return shipTextures.at(frame).texture;
}

const size_t Animator::get(size_t _number_of_frames) noexcept
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
