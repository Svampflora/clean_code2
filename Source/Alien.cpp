#include "Alien.h"

Alien::Alien(Vector2 _position)
{
	color = WHITE;
	position = _position;
	radius = 30;
	x = 0;					 //TODO: x, y?
	y = 0;
	speed = 2;
	active = true;
	moveRight = true;
}

Vector2 Alien::GetPosition() const
{
	return position;
}

float Alien::GetRadius() const
{
	return radius;
}

bool Alien::Active() const
{
	return active;
}

void Alien::SetActive(bool _status)
{
	active = _status;
}

void Alien::Update()
{
	if (moveRight) {
		position.x += speed;

		if (position.x >= GetScreenWidth()) {
			ChangeDirection();
		}
	}
	else {
		position.x -= speed;

		if (position.x <= 0) {
			ChangeDirection();
		}
	}
}


void Alien::ChangeDirection() {
	moveRight = !moveRight;
	position.y += 50;
}

void Alien::Render(const Texture2D& texture) const
{
	//DrawRectangle((int)position.x - 25, (int)position.y, 30, 30, RED);
	//DrawCircle((int)position.x, (int)position.y, radius, GREEN);



	DrawTexturePro(texture,
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, { 50 , 50 },
		0,
		WHITE);
}