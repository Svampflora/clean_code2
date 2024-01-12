#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct HighScoreData
{
	std::string name{};
	int score = 0;
};

class Player 
{
	Animation frames;
	Vector2 size = { 70.0f, 70.0f };
	Vector2 position = { 0, GetScreenHeight() - size.y };
	float speed = 7;
	float radius = 50;
	int lives = 3;
	int direction = 0;

public:
	Player();
	void Update();
	void Render();
	void Hurt(int damage);
	Vector2 GetSize() const;
	Vector2 GetPosition() const;
	float GetRadius() const;
	int GetLives() const;
	
};


struct Projectile  //TODO: make class  C.8: Use class rather than struct if any member is non-public
{
	Vector2 position = {0,0};
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };
	int speed = 15; 
	bool active = true;  

public:

	Projectile(Vector2 _position, int _speed);
	void Update();
	void Impact();
	void Render(const Texture2D& texture) const;//TODO: should pass in a const ref for texture
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

struct Alien  //TODO:class  C.8: Use class rather than struct if any member is non-public
{
	
	Color color = WHITE; 
	Vector2 position = {0, 0};
	float radius = 30;
	int x = 0;					 //TODO: x, y?
	int y = 0; 
	int speed = 2; 
	bool active = true;  
	bool moveRight = true; 
	
public:
	Vector2 GetPosition() const;
	float GetRadius() const;
	void ChangeDirection();
	void Update(); 
	void Render(const Texture2D& texture) const; //TODO: should pass in a const ref texture
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

struct Game //TODO: make into class   C.8: Use class rather than struct if any member is non-public
{

	State gameState = {};
	Rectangle rec = { 0, 0 ,0 ,0 }; 
	Resources resources;
	Player player;
	std::vector<Projectile> playerProjectiles;
	std::vector<Projectile> enemyProjectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::vector<HighScoreData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	Background background;
	float shootTimer = 0;
	int score;
	int wallCount = 5;
	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;
	bool newHighScore = false;
	

	Game();
	void Start();
	void End();
	void Continue(); //TODO: continue?
	void Update();
	void Render();  //TODO: sends textures as copies. use references
	void DrawTextBox();
	void DrawLeaderboard();
	void SpawnAliens();
	void MakeWalls();
	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);
	bool CheckNewHighScore() const;
	void InsertNewHighScore(std::string name);                       
	void LoadLeaderboard();
	void SaveLeaderboard();
	void RemoveInactiveEntities();
	template <typename Object>
	bool CheckProjectileCollision(const Projectile& projectile, const Object& object);
	template <typename ProjectileContainer, typename ObjectType>
	void HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object);
	template <typename ObjectType>
	void HandleProjectileCollisions(std::vector<Projectile>& projectiles, std::vector<ObjectType>& objects);
	


	//TODO: separate intertface object

	//TEXTBOX ENTER
	Rectangle textBox = { 600, 500, 225, 50 };
	int letterCount = 0;
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	bool mouseOnText = false;

	int framesCounter = 0;

};