#pragma once


//#include <math.h>
//struct Vector2i
//{
//	int x;
//	int y;
//};

//float Vector2iDistance(Vector2i v1, Vector2i v2) noexcept
//{
//	
//	const float result = sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
//
//	return result;
//}

static inline float GetScreenWidthF() noexcept
{
	return static_cast<float>(GetScreenWidth());
}

static inline float GetScreenHeightF() noexcept
{
	return static_cast<float>(GetScreenHeight());
}

static inline float GetRandomValueF(int min, int max) noexcept
{
	return static_cast<float>(GetRandomValue(min, max));
}