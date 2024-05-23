#include "Player.h"
#include <iostream>

void Player::Update() noexcept //TODO: too long function?
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

	if (position.x < 0.0f + radius)
	{
		position.x = 0 + radius;
	}
	else if (position.x > GetScreenWidthF() - radius)
	{
		position.x = GetScreenWidthF() - radius;
	}
	animator.Update(GetFrameTime());
}

Player::Player() : animator( std::vector{	"./Assets/Ship1.png"sv,
											"./Assets/Ship2.png"sv,
											"./Assets/Ship3.png"sv })
{
	position.x = GetScreenWidthF() * 0.5f;
}

//void Player::Render(const Texture2D& texture) const noexcept //TODO: magic values
//{
//
//	const Rectangle source_coordinates { 0,0,352,352, };
//	const Rectangle destination_coordinates { position.x, position.y,100,100, };
//	const Vector2 origin { 50, 50 };
//	DrawTexturePro(texture, source_coordinates, destination_coordinates, origin, 0, WHITE);
//}

void Player::Render() const noexcept //TODO: magic values
{

	const Rectangle source_coordinates{ 0,0,352,352, };
	const Rectangle destination_coordinates{ position.x, position.y,100,100, };
	const Vector2 origin{ 50, 50 };
	const Texture2D& texture = animator.GetFrame();
	DrawTexturePro(texture, source_coordinates, destination_coordinates, origin, 0, WHITE);
}

void Player::Hurt(int damage) noexcept
{
	lives -= damage;
}

void Player::Reset() noexcept
{
	lives = 3;
	position = { GetScreenWidthF() * 0.5f, GetScreenHeightF() - size.y };
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