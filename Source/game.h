#pragma once
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
	std::string name{};
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
	void LoadLeaderboard();

	template <typename Object>
	bool CheckProjectileCollision(const Projectile& projectile, const Object& object);
	template <typename ProjectileContainer, typename ObjectType>
	void HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object);
	template <typename ObjectType>
	void HandleProjectileCollisions(std::vector<Projectile>& projectiles, std::vector<ObjectType>& objects);
	
public:
	Game();
	int	GetScore() const;
	int GetLives() const;
	bool PlayerHasLives() const;
	bool IsNewHighScore() const;
	bool CheckAlienHasInvaded(const Alien& alien);
	bool UpdateAliens();
	void SwitchStates(std::unique_ptr<State> newState);
	void InsertNewHighScore(std::string name);                      
	void RemoveInactiveEntities();
	void Update();
	void SaveLeaderboard();
	void Render();
	void UpdatePlayer();
	void HandleCollisions();
	void UpdateGameObjects();
	void CheckAlienAmount();
	void AlienShooting();
	void CheckPlayerShooting();
	void EnterName();
	void Reset();
	void Clear();

	//TODO: delegate rendering more clearly
	void DrawTitle();
	void RenderStats();
	void RenderBackground();
	void RenderGameObjects();
	void DrawTextBox();
	void DrawLeaderboard();

	//TODO: separate intertface object
	Rectangle textBox = { 600, 500, 225, 50 };
	int letterCount = 0;
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0' //TODO: why not add it in the InsertNewHighscore?
	bool mouseOnText = false;

	int framesCounter = 0;

};