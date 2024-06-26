#include "Projectile.h"
#include "Utilities.h"



Projectile::Projectile(Vector2 _position, int _speed) noexcept
{
	position = _position;
	speed = _speed;
}

std::pair<Vector2, Vector2> Projectile::GetEdges() const noexcept //TODO: magic values
{
	std::pair<Vector2, Vector2> edges = { {position.x, position.y - 15}, {position.x, position.y + 15} };
	return edges;
}

bool Projectile::Active() const noexcept
{
	return active;
}

void Projectile::Update() noexcept //TODO: magic values
{
	position.y -= speed;

	if (position.y < 0 || position.y > GetScreenHeightF() + projectile_height)
	{
		active = false;
	}
}

void Projectile::Impact() noexcept
{
	active = false;
}

void Projectile::Render(const Texture2D& texture) const noexcept
{
	DrawTexturePro(texture,{0,0,176,176,},{position.x,position.y,50,50,}, { 25 , 25 },0, WHITE);
}