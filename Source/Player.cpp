#include "Player.h"
#include <iostream>

void Player::Update() noexcept
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

Player::Player() noexcept
{
	[[gsl::suppress(f.6)]]
	position.x = static_cast<float>(GetScreenWidth() * 0.5f);
}

void Player::Render(const Texture2D& texture) const noexcept
{
	const Rectangle source_coordinates { 0,0,352,352, };
	const Rectangle destination_coordinates { position.x, position.y,100,100, };
	const Vector2 origin { 50, 50 };
	DrawTexturePro(texture, source_coordinates, destination_coordinates, origin, 0, WHITE);
}

void Player::Hurt(int damage) noexcept
{
	lives -= damage;
}

void Player::Reset() noexcept
{
	lives = 3;
	position = { GetScreenWidth() * 0.5f, GetScreenHeight() - size.y }; 
}

Vector2 Player::GetSize() const noexcept
{
	return size;
}

Vector2 Player::GetPosition() const noexcept
{
	return position;
}

float Player::GetRadius() const noexcept
{
	return radius;
}

int Player::GetLives() const noexcept
{
	return lives;
}