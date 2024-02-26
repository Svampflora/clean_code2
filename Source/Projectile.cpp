#include "Projectile.h"



Projectile::Projectile(Vector2 _position, int _speed)
{
	position = _position;
	speed = _speed;
}

std::pair<Vector2, Vector2> Projectile::GetEdges() const
{
	std::pair<Vector2, Vector2> edges = { {position.x, position.y - 15}, {position.x, position.y + 15} };
	return edges;
}

bool Projectile::Active() const
{
	return active;
}

void Projectile::Update()
{
	position.y -= speed;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Impact()
{
	active = false;
}

void Projectile::Render(const Texture2D& texture) const
{
	DrawTexturePro(texture,{0,0,176,176,},{position.x,position.y,50,50,}, { 25 , 25 },0, WHITE);
}