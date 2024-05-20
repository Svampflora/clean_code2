#include "Alien.h"

Alien::Alien(Vector2 _position) noexcept
{
	color = WHITE;
	position = _position;
	radius = 30;
	x = 0;					
	y = 0;
	speed = 2;
	active = true;
}

Vector2 Alien::GetPosition() const noexcept
{
	return position;
}

float Alien::GetRadius() const noexcept
{
	return radius;
}

bool Alien::Active() const noexcept
{
	return active;
}

void Alien::SetActive(bool _status) noexcept
{
	active = _status;
}

void Alien::Update() noexcept
{
	position.x += speed;
	
	if (position.x >= GetScreenWidth() || position.x <= 0)
	{
		ChangeDirection();
	}
}

void Alien::ChangeDirection() noexcept //TODO: magic values
{
	speed *= -1;
	position.y += 50;
}

void Alien::Render(const Texture2D& texture) const noexcept //TODO: magic values
{
	DrawTexturePro(texture,{0,0,352,352,},{position.x,position.y,100,100,}, { 50 , 50 },0,WHITE);
}