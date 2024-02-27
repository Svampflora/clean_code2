#include "Wall.h"


float Wall::GetRadius() const noexcept
{
	return static_cast<float>(radius);
}

Wall::Wall(Vector2 _position) noexcept
{
	position = _position;
	rec = Rectangle{};
	color = Color{};
	health = 50;
	radius = 60;
	active = true;
}

Vector2 Wall::GetPosition() const noexcept
{
	return position;
}

void Wall::Render(const Texture2D& texture) const noexcept
{
	DrawTexturePro(texture,{0,0,704,704,},{position.x,position.y,200,200,}, { 100 , 100 },0,WHITE);
	DrawText(TextFormat("%i", health), static_cast<int>(position.x - 21), static_cast<int>(position.y + 10), 40, RED);
}

void Wall::Damage(int _damage) noexcept
{
	health -= _damage;
}

bool Wall::Active() const noexcept
{
	return active;
}

void Wall::Update() noexcept
{
	if (health < 1)
	{
		active = false;
	}
}