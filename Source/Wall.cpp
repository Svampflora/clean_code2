#include "Wall.h"
#include "Utilities.h"

float Wall::GetRadius() const noexcept
{
	return radius;
}

Wall::Wall(Vector2 _position) noexcept:
 position(_position),
 rectangle{},
 color{},
 radius(60),
 health(50),
 active(true)
{
}

Vector2 Wall::GetPosition() const noexcept
{
	return position;
}

void Wall::Render(const Texture2D& texture) const noexcept
{
	DrawTexturePro(texture,{0,0,704,704,},{position.x,position.y,200,200,}, { 100 , 100 },0,WHITE);
	DrawTextF(TextFormat("%i", health), position.x - 21.0f, position.y + 10.0f, 40, RED);
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