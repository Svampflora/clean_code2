#pragma once
#include "State.h"
#include "Resources.h"
#include "Player.h"
#include "Alien.h"
#include "Projectile.h"
#include <memory>
#include <vector>
#include <string>


struct HighScoreData
{
	std::string name{};
	int score = 0;
};

struct Wall  //TODO: class
{
	Vector2 position{0.0f,0.0f};
	Rectangle rec{};
	Color color{};
	int health = 50;
	int radius = 60;
	bool active = true; 

public: 
	Vector2 GetPosition() const;
	float GetRadius() const;
	void Render(const Texture2D& texture) const; //TODO: should pass in a const ref texture
	void Update(); 
};

struct Star  //TODO:make proper background class
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = GRAY;
	float size = 0;
	float radius = size;
	void Update(float starOffset);
	void Render() const;
};

class Background  //TODO: make into class  C.8: Use class rather than struct if any member is non-public
{
	std::vector<Star> Stars;
	Vector2 playerPos{0.0f, 0.0f};
	Vector2 cornerPos{0.0f,0.0f};
	float offset = 0.0f;

public:

	Background(int starAmount);
	void Update(const Player& player);
	void Render();  //TODO: const ref

};

class Game //TODO: make members non-public
{
	std::unique_ptr<State> currentState;
	Rectangle rec; 
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
	
public:

	Game();
	void SpawnAliens();
	void MakeWalls();
	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);
	bool CheckNewHighScore() const;
	void LoadLeaderboard();
	void SaveLeaderboard();
	void RemoveInactiveEntities();
	template <typename Object>
	bool CheckProjectileCollision(const Projectile& projectile, const Object& object);
	template <typename ProjectileContainer, typename ObjectType>
	void HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object);
	template <typename ObjectType>
	void HandleProjectileCollisions(std::vector<Projectile>& projectiles, std::vector<ObjectType>& objects);
	
	int	GetScore() const;
	int GetLives() const;
	bool PlayerHasLives() const;
	bool IsNewHighScore() const;
	bool CheckAlienHasInvaded(const Alien& alien);
	bool UpdateAliens();
	void InsertNewHighScore(std::string name);                      
	void Update();
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

	//TODO: delegate rendering properly
	void RenderBackground();
	void RenderGameObjects();
	void DrawTextBox();
	void DrawLeaderboard();

	void SwitchStates(std::unique_ptr<State> newState);

	//TODO: separate intertface object

	//TEXTBOX ENTER
	Rectangle textBox = { 600, 500, 225, 50 };
	int letterCount = 0;
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	bool mouseOnText = false;

	int framesCounter = 0;

};