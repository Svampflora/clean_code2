#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#include "raymath.h"
#pragma warning(pop)

#include "State.h"
#include "Resources.h"
#include "Player.h"
#include "Alien.h"
#include "Projectile.h"
#include "Wall.h"
#include "Background.h"
#include <memory>
#include <vector>
#include <string>


struct HighScoreData
{
	std::string name{""};
	int score = 0;
};

class Game
{
	std::unique_ptr<State> currentState;
	Resources resources;
	Player player;
	std::vector<Projectile> playerProjectiles;
	std::vector<Projectile> enemyProjectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::vector<HighScoreData> Leaderboard;
	Background background;
	float shootTimer;
	int score;
	int formationWidth;
	int formationHeight;
	int alienSpacing;
	int formationX;
	int formationY;
	
	void SpawnAliens();
	void MakeWalls();
	bool CheckCollision(Vector2 circlePos, float circleRadius, std::pair<Vector2, Vector2> edges);
	void LoadLeaderboard() noexcept;

	template <typename Object>
	bool CheckProjectileCollision(const Projectile& projectile, const Object& object);
	template <typename ProjectileContainer, typename ObjectType>
	void HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object);
	template <typename ObjectType>
	void HandleProjectileCollisions(std::vector<Projectile>& projectiles, std::vector<ObjectType>& objects);
	
public:
	Game() noexcept;
	float CalculateOffset() const;
	int	GetScore() const noexcept;
	int GetLives() const noexcept;
	bool PlayerHasLives() const noexcept;
	bool IsNewHighScore() const noexcept;
	bool CheckAlienHasInvaded(const Alien& alien) const noexcept;
	void CheckPlayerShooting();
	void CheckAlienAmount();
	void SwitchStates(std::unique_ptr<State> newState) noexcept;
	void Update();
	void UpdatePlayer() noexcept;
	bool UpdateAliens() noexcept;
	void UpdateGameObjects();
	void HandleCollisions();
	void AlienShooting();
	void RemoveInactiveEntities() noexcept;
	void Render();
	void DrawTitle() const noexcept;
	void RenderStats() const noexcept;
	void RenderBackground() const noexcept;
	void RenderGameObjects() noexcept;
	void DrawTextBox() const noexcept;
	void DrawLeaderboard() const noexcept;
	void Reset();
	void Clear() noexcept;
	void EnterName();
	void InsertLetters();
	void InsertNewHighScore(std::string name);
	void SaveLeaderboard();

	//TODO: separate intertface object
	Rectangle textBox = { 600, 500, 225, 50 };
	int letterCount = 0;
	std::string name{};
	bool mouseOnText = false;
	int framesCounter = 0;

};