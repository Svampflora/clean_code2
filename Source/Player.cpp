#include "Player.h"
#include <iostream>

void Player::Update()
{

	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	position.x += speed * direction;

	if (position.x < 0 + radius)
	{
		position.x = 0 + radius;
	}
	else if (position.x > GetScreenWidth() - radius)
	{
		position.x = GetScreenWidth() - radius;
	}
}

Player::Player()
{
	position.x = (float)GetScreenWidth() * 0.5f;
	std::cout << "Find Player -X:" << GetScreenWidth() / 2 << "Find Player -Y" << GetScreenHeight() - size.y << std::endl;
}

void Player::Render(const Texture2D& texture) const
{
	Rectangle source_coordinates = { 0,0,352,352, };
	Rectangle destination_coordinates = { position.x, position.y,100,100, };
	Vector2 origin = { 50, 50 };
	DrawTexturePro(texture, source_coordinates, destination_coordinates, origin, 0, WHITE);
}

void Player::Hurt(int damage)
{
	lives -= damage;
}

void Player::Reset()
{
	lives = 3;
	position = { GetScreenWidth() * 0.5f, GetScreenHeight() - size.y }; 
}

Vector2 Player::GetSize() const
{
	return size;
}

Vector2 Player::GetPosition() const
{
	return position;
}

float Player::GetRadius() const
{
	return radius;
}

int Player::GetLives() const
{
	return lives;
}