#include "Wall.h"


float Wall::GetRadius() const
{
	return static_cast<float>(radius);
}

Wall::Wall(Vector2 _position)
{
	position = _position;
	rec = Rectangle{};
	color = Color{};
	health = 50;
	radius = 60;
	active = true;
}

Vector2 Wall::GetPosition() const
{
	return position;
}

void Wall::Render(const Texture2D& texture) const
{
	DrawTexturePro(texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);

	DrawText(TextFormat("%i", health), static_cast<int>(position.x - 21), static_cast<int>(position.y + 10), 40, RED);
}

void Wall::Damage(int _damage)
{
	health -= _damage;
}

bool Wall::Active() const
{
	return active;
}

void Wall::Update()
{
	if (health < 1)
	{
		active = false;
	}
}