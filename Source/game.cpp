#include "State.h"
#include "game.h"
#include "raymath.h"
#include <iostream>
#include <chrono>
#include <fstream>


template <typename T>
void RenderObjects(const std::vector<T>& objects, const Texture& texture) {
	for (const T& obj : objects) {
		obj.Render(texture);
	}
}

template <typename T>
void UpdateObjects(std::vector<T>& objects) {
	for (T& obj : objects) {
		obj.Update();
	}
}

template <typename Container, typename Predicate>
void remove_if(Container& container, Predicate predicate) {
	container.erase(
		std::remove_if(container.begin(), container.end(), predicate),
		container.end());
}

template <typename Object>
bool Game::CheckProjectileCollision(const Projectile& projectile, const Object& object) {
	return CheckCollision(object.GetPosition(), object.GetRadius(), projectile.lineStart, projectile.lineEnd);
}

template <typename ProjectileContainer, typename ObjectType>
void Game::HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object) {
	for (Projectile& projectile : projectiles) {
		if (CheckProjectileCollision(projectile, object)) {
			if constexpr (std::is_same_v<ObjectType, Player>) {
				projectile.Impact();
				object.Hurt(1);
			}
		}
	}
}

template <typename ObjectType>
void Game::HandleProjectileCollisions(std::vector<Projectile>& projectiles, std::vector<ObjectType>& objects) {
	for (Projectile& projectile : projectiles) {
		for (ObjectType& object : objects) {
			if (CheckProjectileCollision(projectile, object)) {
				projectile.Impact();

				if constexpr (std::is_same_v<ObjectType, Alien>) {
					object.active = false;
					score += 100;
				}
				else if constexpr (std::is_same_v<ObjectType, Wall>) {
					object.health -= 1;
				}
			}
		}
	}
}

//Game::Game(): resources(), background(600), currentState(std::make_unique<Startscreen>(this))
//{
//}

Game::Game()
	: currentState(std::make_unique<Startscreen>(this)),
	rec({ 0, 0, 0, 0 }),
	resources(),
	player(),
	playerProjectiles(),
	enemyProjectiles(),
	Walls(),
	Aliens(),
	Leaderboard({ {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} }),
	background(600),
	shootTimer(0),
	score(0),
	formationWidth(8),
	formationHeight(5),
	alienSpacing(80),
	formationX(100),
	formationY(50),
	newHighScore(false)
{
}



void Game::Reset()
{

	MakeWalls();
	SpawnAliens();
	score = 0;

}

void Game::MakeWalls()
{
	const float window_width = static_cast<float>(GetScreenWidth());
	const float window_height = static_cast<float>(GetScreenHeight());
	const int wallAmount = 5;
	const float wall_distance = window_width / (wallAmount + 1);

	for (int i = 0; i < wallAmount; ++i) {
		Wall newWall;
		newWall.position.y = window_height - 250;
		newWall.position.x = wall_distance * (i + 1);
		Walls.push_back(newWall);
	}
}

void Game::Clear()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	playerProjectiles.clear();
	enemyProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();

}

void Game::Update()
{
	currentState->Update();
}


void Game::Render()
{
	currentState->Render();
}

void Game::DrawTextBox()
{
	Color borderColor = mouseOnText ? RED : DARKGRAY;
	DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, borderColor);

	DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

	if (mouseOnText && letterCount < 9)
	{
		if ((framesCounter / 20) % 2 == 0)
		{
			DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
		}
	}
	else if (mouseOnText)
	{
		DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
	}

	if (letterCount > 0 && letterCount < 9)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}
}

void Game::DrawLeaderboard()
{
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < Leaderboard.size(); ++i)
	{
		DrawText(Leaderboard[i].name.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Alien newAlien = Alien();
			newAlien.active = true;
			newAlien.position.x = formationX + 450.0f + (col * alienSpacing);
			newAlien.position.y = static_cast<float>(formationY) + (row * alienSpacing);
			Aliens.push_back(newAlien);
			std::cout << "Find Alien -X:" << newAlien.position.x << std::endl;
			std::cout << "Find Alien -Y:" << newAlien.position.y << std::endl;
		}
	}
}
      

bool Game::CheckNewHighScore() const
{
	return (score > Leaderboard[4].score);
}



void Game::InsertNewHighScore(std::string _name)
{
	HighScoreData newData;
	newData.name = _name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			i = static_cast<int>(Leaderboard.size());

		}
	}
}

void Game::LoadLeaderboard() //TODO: empty
{
	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}

void Game::SaveLeaderboard() //TODO: does not save to file 
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
	std::fstream file;

	file.open("Leaderboard");

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
}

void Game::RemoveInactiveEntities()
{
	remove_if(enemyProjectiles, [](const auto& projectile) { return !projectile.active; });
	remove_if(playerProjectiles, [](const auto& projectile) { return !projectile.active; });
	remove_if(Walls, [](const auto& projectile) { return !projectile.active; });
	remove_if(Aliens, [](const auto& projectile) { return !projectile.active; });
}

void Game::UpdatePlayer()
{
	player.Update();
}

void Game::HandleCollisions()
{
	HandleProjectileCollisions(enemyProjectiles, player);
	HandleProjectileCollisions(enemyProjectiles, Walls);
	HandleProjectileCollisions(playerProjectiles, Aliens);
	HandleProjectileCollisions(playerProjectiles, Walls);
}

void Game::UpdateGameObjects()
{
	background.Update(player);
	UpdateObjects(playerProjectiles);
	UpdateObjects(enemyProjectiles);
	UpdateObjects(Walls);
}

void Game::CheckPlayerHealth()
{
	if (player.GetLives() < 1)
	{
		Clear();
	}
}

void Game::CheckAlienAmount()
{
	if (Aliens.size() < 1)
	{
		SpawnAliens();
	}
}

void Game::AlienShooting()
{
	int framesPerSecond = GetFPS();
	if (++shootTimer > framesPerSecond)
	{
		if (Aliens.size() > 1)
		{
			int randomAlienIndex = rand() % Aliens.size();
			enemyProjectiles.push_back(Projectile({ Aliens[randomAlienIndex].position.x, Aliens[randomAlienIndex].position.y + 40 }, -15));

		}
		shootTimer = 0;
	}
}

void Game::CheckPlayerShooting()
{
	if (IsKeyPressed(KEY_SPACE)) //TODO: should be part of player Input?
	{
		float window_height = static_cast<float>(GetScreenHeight());
		playerProjectiles.push_back(Projectile({ player.GetPosition().x, window_height - 130 }, 15));
	}
}

void Game::UpdateAliens()
{
	for (Alien& alien : Aliens)
	{
		alien.Update();

		if (alien.GetPosition().y > GetScreenHeight() - player.GetSize().y)
		{
			Clear();
		}
	}
}

void Game::SwitchStates(std::unique_ptr<State> newState)
{
	currentState = std::move(newState);
}

void Game::RenderGameObjects()
{
	player.Render(resources.GetShipTexture());
	RenderObjects(enemyProjectiles, resources.GetLaserTexture());
	RenderObjects(playerProjectiles, resources.GetLaserTexture());
	RenderObjects(Walls, resources.GetBarrierTexture());
	RenderObjects(Aliens, resources.GetAlienTexture());
}

void Game::RenderBackground()
{
	background.Render();
}

bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
{
	if (CheckCollisionPointCircle(lineStart, circlePos, circleRadius) || CheckCollisionPointCircle(lineEnd, circlePos, circleRadius))
	{
		return true;
	}

	Vector2 A = lineStart;
	Vector2 B = lineEnd;
	Vector2 C = circlePos;

	float length = Vector2Distance(A, B);
	float dotP = ((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y)) / static_cast<float>(pow(length, 2));

	float closestX = A.x + (dotP * (B.x - A.x));
	float closestY = A.y + (dotP * (B.y - A.y));

	float buffer = 0.1f;

	float closeToStart = Vector2Distance(A, { closestX, closestY });
	float closeToEnd = Vector2Distance(B, { closestX, closestY });

	float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		float closeToCentre = Vector2Distance(A, { closestX, closestY });

		if (closeToCentre < circleRadius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

float Wall::GetRadius() const
{
	return static_cast<float>(radius);
}

Vector2 Wall::GetPosition() const
{
	return position;
}

void Wall::Render(const Texture2D& texture) const
{
	DrawTexturePro(texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), static_cast<int>(position.x-21), static_cast<int>(position.y+10), 40, RED);
	
}

void Wall::Update() 
{

	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}


}




//BACKGROUND
void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


Background::Background(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		Star newStar;

		newStar.initPosition.x = static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150));
		newStar.initPosition.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
		newStar.color = SKYBLUE;
		newStar.size = static_cast<float>(GetRandomValue(1, 4) / 2);

		Stars.emplace_back(newStar);

	}
}

void Background::Update(const Player& player)
{
	playerPos = { player.GetPosition().x, (float)player.GetSize().y};
	cornerPos = { 0, (float)player.GetSize().y};
	offset = Vector2Distance(playerPos, cornerPos) * -1;
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Update(offset / 15);
	}
}

void Background::Render()
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Render();
	}
}


