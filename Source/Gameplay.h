#pragma once
#include "State.h"

#include "Player.h"
#include "Alien.h"
#include "Projectile.h"
#include "Wall.h"
#include "Background.h"
#include "Resources.h"


class Gameplay : public State
{
	Player player;
	Background background;
	Resources resources;
	float shootTimer;
	float formationX;
	float formationY;
	int formationWidth;
	int formationHeight;
	int alienSpacing;
	int score;
	std::vector<Projectile> playerProjectiles;
	std::vector<Projectile> enemyProjectiles;
	std::vector<Alien> aliens;
	std::vector<Wall> walls;

	float CalculateOffset() const;
	bool CheckCollision(Vector2 circlePos, float circleRadius, std::pair<Vector2, Vector2> edges);
	template <typename Object>
	bool CheckProjectileCollision(const Projectile& projectile, const Object& object);
	template <typename ProjectileContainer, typename ObjectType>
	void HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object);
	template <typename ObjectType>
	void HandleProjectileCollisions(std::vector<Projectile>& projectiles, std::vector<ObjectType>& objects);

	int	GetScore() const noexcept;
	int GetLives() const noexcept;
	void SpawnAliens();
	void MakeWalls();
	bool PlayerHasLives() const noexcept; //TODO: dumb?

	bool CheckAlienHasInvaded(const Alien& alien) const noexcept;
	void CheckPlayerShooting(); //TODO: make bool
	void CheckAlienAmount(); //TODO: make bool
	void UpdatePlayer() noexcept;
	bool UpdateAliens() noexcept; //TODO: make void
	void UpdateGameObjects();
	void HandleCollisions();
	void AlienShooting();
	void RemoveInactiveEntities() noexcept;
	void RenderStats() const noexcept;
	void RenderBackground() const noexcept;
	void RenderGameObjects() const noexcept;
	void Clear() noexcept;
public:
	
	Gameplay();
	Switch_State Update() override;
	int Reset() override;
	void Render() const noexcept override;
};