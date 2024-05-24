  #include "Resources.h"
#include <iostream>


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
        UnloadTexture(texture);
        texture = std::move(other.texture);
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

Animator::Animator(std::vector<std::string_view> file_paths)
{
    frames.reserve(file_paths.size());
    for (const auto path : file_paths)
    {
        frames.emplace_back(path);
    } 
    if (frames.empty())
    {
        throw std::runtime_error("the animator did not recieve any frames");
    }
}

void Animator::Update(float deltaTime) noexcept
{
    if (frames.empty()) 
    {
        return;
    }

    timer += deltaTime;
    const float frame_duration = 1.0f / frames_per_second;
    while (timer >= frame_duration) 
    {

        timer -= frame_duration;
        current_frame = (current_frame + 1) % frames.size();
    }
}


const Texture2D& Animator::GetFrame() const noexcept
{
    [[gsl::suppress(bounds.4)]]
    return frames[current_frame].Get();
}

