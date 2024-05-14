#include "State.h"
#include "game.h"
#include "raymath.h"
#include <iostream>
#include <chrono>
#include <fstream>



template<typename T, typename Func>
void CheckConditionAndPerformAction(T value, Func action)
{
	if (value)
	{
		action();
	}
}

template <typename T> 
void RenderObjects(const std::vector<T>& objects, const Texture& texture) noexcept
{
	for (const T& obj : objects) 
	{
		obj.Render(texture);
	}
}

template <typename T> 
void UpdateObjects(std::vector<T>& objects)  noexcept
{
	for (T& obj : objects) 
	{
		obj.Update();
	}
}

template <typename Container, typename Predicate>
void remove_if(Container& container, Predicate predicate) 
{
	container.erase(
		std::remove_if(container.begin(), container.end(), predicate),
		container.end());
}

template <typename Object>
bool Game::CheckProjectileCollision(const Projectile& projectile, const Object& object) 
{
	return CheckCollision(object.GetPosition(), object.GetRadius(), projectile.GetEdges());
}

template <typename ProjectileContainer, typename ObjectType>
void Game::HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object) 
{
	for (Projectile& projectile : projectiles) 
	{
		if (CheckProjectileCollision(projectile, object)) 
		{
			if constexpr (std::is_same_v<ObjectType, Player>) 
			{
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
			if (CheckProjectileCollision(projectile, object)) 
			{
				projectile.Impact();

				if constexpr (std::is_same_v<ObjectType, Alien>) 
				{
					object.SetActive(false);
					score += 100;
				}
				else if constexpr (std::is_same_v<ObjectType, Wall>) 
				{
					object.Damage(1);
				}
			}
		}
	}
}

Game::Game() noexcept
	: currentState(std::make_unique<Startscreen>(*this)),
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
	formationY(50)
{
}

float Game::CalculateOffset() const
{
	const Vector2 playerPos = { player.GetPosition().x, player.GetSize().y };
	const Vector2 cornerPos = { 0, player.GetSize().y };

	return Vector2Distance(playerPos, cornerPos) * -1;
}

void Game::Reset() 
{

	MakeWalls();
	SpawnAliens();
	player.Reset();
	score = 0;

}

void Game::MakeWalls() 
{
	const float window_width = static_cast<float>(GetScreenWidth());
	const float window_height = static_cast<float>(GetScreenHeight());
	constexpr int wallAmount = 5;
	const float wall_distance = window_width / (wallAmount + 1);

	for (int i = 0; i < wallAmount; ++i) {
		const Wall _wall{ Vector2{wall_distance * (i + 1), window_height - 250} };
		Walls.push_back(_wall);
	}
}

void Game::Clear() noexcept
{
	playerProjectiles.clear();
	enemyProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	score = 0;
}

void Game::Update() 
{
	currentState->Update();
}


void Game::Render() 
{
	currentState->Render();
}

void Game::DrawTextBox() const noexcept
{
	const Color borderColor = mouseOnText ? RED : DARKGRAY;
	DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), borderColor);

	DrawText(name.c_str(), static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);

	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

	if (mouseOnText && letterCount < 9)
	{
		if ((framesCounter / 20) % 2 == 0)
		{
			DrawText("_", static_cast<int>(textBox.x + 8 + MeasureText(name.c_str(), 40)), static_cast<int>(textBox.y + 12), 40, MAROON);
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

void Game::DrawLeaderboard() const
{
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < Leaderboard.size(); ++i)
	{
		DrawText(Leaderboard.at(i).name.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", Leaderboard.at(i).score), 350, 140 + (i * 40), 40, YELLOW); //TODO: don't usw at()
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++) 
	{
		for (int col = 0; col < formationWidth; col++) 
		{
			Aliens.emplace_back(Alien{ {formationX + 450.0f + (col * alienSpacing), static_cast<float>(formationY) + (row * alienSpacing)} });
		}
	}
}

void Game::InsertNewHighScore(std::string _name)
{
	HighScoreData newData;
	newData.name = _name;
	newData.score = score;

	for (size_t i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard.at(i).score)
		{
			Leaderboard.insert(Leaderboard.begin() + i, newData);
			Leaderboard.pop_back();
			
			i = Leaderboard.size();
			score = 0;
		}
	}
}

void Game::LoadLeaderboard() noexcept//TODO: empty
{

}

void Game::SaveLeaderboard() //TODO: does not save to file 
{
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
}

void Game::RemoveInactiveEntities() noexcept
{

	remove_if(Walls, [](const auto& projectile) noexcept { return !projectile.Active(); });
	remove_if(enemyProjectiles, [](const auto& projectile) noexcept { return !projectile.Active(); });
	remove_if(playerProjectiles, [](const auto& projectile) noexcept { return !projectile.Active(); });
	remove_if(Aliens, [](const auto& alien) noexcept { return !alien.Active(); });
}

void Game::UpdatePlayer() noexcept
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
	const float offset = CalculateOffset();
	background.Update(offset);
	UpdateObjects(playerProjectiles);
	UpdateObjects(enemyProjectiles);
	UpdateObjects(Walls);
}

int Game::GetScore() const noexcept
{
	return score;
}

int Game::GetLives() const noexcept
{
	return player.GetLives();
}

bool Game::PlayerHasLives() const noexcept
{
	return (player.GetLives() > 0);
}

bool Game::IsNewHighScore() const noexcept
{
	return (score > Leaderboard.at(4).score); //TODO: hardcoded
}

bool Game::CheckAlienHasInvaded(const Alien& alien) const noexcept
{
	if (alien.GetPosition().y > GetScreenHeight() - player.GetSize().y)
	{
		return true;
	}
	return false;
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
	const int framesPerSecond = GetFPS();
	if (++shootTimer > framesPerSecond)
	{
		if (Aliens.size() > 1)
		{
			const int randomAlienIndex = rand() % Aliens.size();
			enemyProjectiles.push_back(Projectile({ Aliens.at(randomAlienIndex).GetPosition().x, Aliens.at(randomAlienIndex).GetPosition().y + 40}, -15));

		}
		shootTimer = 0;
	}
}

void Game::CheckPlayerShooting() 
{
	if (IsKeyPressed(KEY_SPACE))
	{
		const float window_height = static_cast<float>(GetScreenHeight());
		playerProjectiles.push_back(Projectile({ player.GetPosition().x, window_height - 130 }, 15));
	}
}

bool Game::UpdateAliens() noexcept
{
	for (Alien& alien : Aliens)
	{
		alien.Update();

		if (CheckAlienHasInvaded(alien))
		{
			return true;
		}
	}
	return false;
}

void Game::EnterName() //TODO: make shorter 
{
	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

	if (mouseOnText)
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		int key;
		while ((key = GetCharPressed()) > 0)
		{
			if ((key >= 32) && (key <= 125) && (letterCount < 9))
			{

				const char character_key = static_cast<char>( key ); //TODO: find solution so we don't need to cast
				name.push_back( character_key );
				letterCount++;
			}
		}

		if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
		{
			name.pop_back();
			letterCount--;
		}
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}

	framesCounter = mouseOnText ? framesCounter + 1 : 0;

	if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
	{
		InsertNewHighScore(name);
	}
}

//void Game::EnterName() 
//{
//	if (CheckCollisionPointRec(GetMousePosition(), textBox))
//	{
//		mouseOnText = true;
//	}
//	else
//	{
//		mouseOnText = false;
//	}
//
//	if (mouseOnText)
//	{
//		SetMouseCursor(MOUSE_CURSOR_IBEAM);
//		int key =  GetCharPressed();
//
//		while (key > 0)
//		{
//			if ((key >= 32) && (key <= 125) && (letterCount < 9))
//			{
//			
//				name.append({ static_cast<char>(key) });
//				letterCount++;
//			}
//
//			key = GetCharPressed();
//		}
//
//		if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
//		{
//			name.pop_back();
//			letterCount--;
//		}
//	}
//	else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
//
//	if (mouseOnText)
//	{
//		framesCounter++;
//	}
//	else
//	{
//		framesCounter = 0;
//	}
//
//	if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
//	{
//		//std::string nameEntry(name);
//		InsertNewHighScore(name);
//	}
//}

void Game::SwitchStates(std::unique_ptr<State> newState) noexcept
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

void Game::DrawTitle() const noexcept
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void Game::RenderStats() const noexcept
{
	DrawText(TextFormat("Score: %i", GetScore()), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", GetLives()), 50, 70, 40, YELLOW);
}

void Game::RenderBackground() const noexcept
{
	background.Render();
}

bool Game::CheckCollision(Vector2 circlePos, float circleRadius, std::pair<Vector2, Vector2> edges) //TODO: casting and too long function
{
	if (CheckCollisionPointCircle(edges.first, circlePos, circleRadius) || CheckCollisionPointCircle(edges.second, circlePos, circleRadius))
	{
		return true;
	}

	const Vector2 A = edges.first;
	const Vector2 B = edges.second ;
	const Vector2 C = circlePos;

	const float length = Vector2Distance(A, B);
	const float dotP = ((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y)) / static_cast<float>(pow(length, 2));

	const float closestX = A.x + (dotP * (B.x - A.x));
	const float closestY = A.y + (dotP * (B.y - A.y));

	constexpr float buffer = 0.1f;

	const float closeToStart = Vector2Distance(A, { closestX, closestY });
	const float closeToEnd = Vector2Distance(B, { closestX, closestY });

	const float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		const float closeToCentre = Vector2Distance(A, { closestX, closestY });

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
