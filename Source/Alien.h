#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)



class Alien
{
	Color color;
	Vector2 position;
	float radius;
	int x;
	int y;
	int speed;
	bool active; 

	void ChangeDirection() noexcept;
public:

	Alien(Vector2 _position) noexcept;
	Vector2 GetPosition() const noexcept;
	float GetXPosition() const noexcept;
	float GetYPosition() const noexcept;
	float GetRadius() const noexcept;
	bool Active() const noexcept;
	void SetActive(bool _status) noexcept;
	void Update() noexcept;
	void Render(const Texture2D& _texture) const noexcept;
};