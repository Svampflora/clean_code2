#include "game.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
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

Game::Game(): resources(), background(600)
{
	gameState = State::STARTSCREEN;
}


void Game::Start()
{

	MakeWalls();
	SpawnAliens();

	score = 0;
	gameState = State::GAMEPLAY;
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

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	playerProjectiles.clear();
	enemyProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	SaveLeaderboard();
	gameState = State::STARTSCREEN;
}


void Game::Update()
{
	int framesPerSecond = GetFPS();
	switch (gameState)
	{
	case State::STARTSCREEN:
	
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}

		break;
	case State::GAMEPLAY:
	
		if (IsKeyReleased(KEY_Q))
		{
			End();
		}

		player.Update();
		
		for (Alien& alien : Aliens)
		{
			alien.Update(); 

			if (alien.GetPosition().y > GetScreenHeight() - player.GetSize().y)
			{
				End();
			}
		}

		if (player.GetLives() < 1)
		{
			End();
		}

		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}

		background.Update(player);
		UpdateObjects(playerProjectiles);
		UpdateObjects(enemyProjectiles);
		UpdateObjects(Walls);

		HandleProjectileCollisions(enemyProjectiles, player);
		HandleProjectileCollisions(enemyProjectiles, Walls);
		HandleProjectileCollisions(playerProjectiles, Aliens);
		HandleProjectileCollisions(playerProjectiles, Walls);

		if (IsKeyPressed(KEY_SPACE)) //TODO: should be part of player Input?
		{
			float window_height = static_cast<float>(GetScreenHeight());
			playerProjectiles.push_back(Projectile({ player.GetPosition().x, window_height - 130}, 15));
		}
		
		if (++shootTimer > framesPerSecond) 
		{
			if (Aliens.size() > 1) 
			{
				int randomAlienIndex = rand() % Aliens.size();
				enemyProjectiles.push_back(Projectile({ Aliens[randomAlienIndex].position.x, Aliens[randomAlienIndex].position.y + 40 }, -15));

			}
			shootTimer = 0;
		}


		RemoveInactiveEntities();
		

	break;
	case State::ENDSCREEN:
		//Code
	
		//Exit endscreen
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

		if (newHighScore)
		{
			if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
			else mouseOnText = false;

			if (mouseOnText)
			{
				// Set the window's cursor to the I-Beam
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				// Get char pressed on the queue
				int key = GetCharPressed();

				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (letterCount < 9))
					{
						name[letterCount] = (char)key;
						name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
						letterCount++;
					}

					key = GetCharPressed();  // Check next character in the queue
				}

				//Remove chars 
				if (IsKeyPressed(KEY_BACKSPACE))
				{
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					name[letterCount] = '\0';
				}
			}
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
				framesCounter = 0;
			}

			// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
			// name + score to scoreboard
			if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
			{
				std::string nameEntry(name);

				InsertNewHighScore(nameEntry);

				newHighScore = false;
			}


		}
		
		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}


void Game::Render() //TODO: long function
{
	switch (gameState)
	{
	case State::STARTSCREEN:

		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);

		break;
	case State::GAMEPLAY:
		
		background.Render();
		DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.GetLives()), 50, 70, 40, YELLOW);

		player.Render();
		RenderObjects(enemyProjectiles, resources.GetLaserTexture());
		RenderObjects(playerProjectiles, resources.GetLaserTexture());
		RenderObjects(Walls, resources.GetBarrierTexture());
		RenderObjects(Aliens, resources.GetAlienTexture());

		break;
	case State::ENDSCREEN:

		if (newHighScore)
		{
			DrawTextBox();
		}
		else 
		{
			DrawLeaderboard();
		}

		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
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

void Player::Update() 
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

	if (position.x < 0 + radius)
	{
		position.x = 0 + radius;
	}
	else if (position.x > GetScreenWidth() - radius)
	{
		position.x = GetScreenWidth() - radius;
	}
}

Player::Player() : frames(std::vector{ LoadTexture("./Assets/Ship1.png"), LoadTexture("./Assets/Ship2.png"), LoadTexture("./Assets/Ship3.png") })
{
	position.x = (float)GetScreenWidth() * 0.5f;
	std::cout << "Find Player -X:" << GetScreenWidth() / 2 << "Find Player -Y" << GetScreenHeight() - size.y << std::endl;
}

void Player::Render()
{
	Rectangle source_coordinates = { 0,0,352,352, };
	Rectangle destination_coordinates = { position.x, position.y,100,100, };
	Vector2 origin = { 50, 50 };
	DrawTexturePro(frames.get(), source_coordinates, destination_coordinates, origin, 0, WHITE);
}

void Player::Hurt(int damage)
{
	lives -= damage;
}

Vector2 Player::GetSize() const
{
	return size;
}

Vector2 Player::GetPosition() const
{
	return position;
}

float Player::GetRadius() const
{
	return radius;
}

int Player::GetLives() const
{
	return lives;
}



Projectile::Projectile(Vector2 _position, int _speed)
{
	position = _position;
	speed = _speed;
}

void Projectile::Update()
{
	position.y -= speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;
	lineEnd.y   = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x   = position.x;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Impact()
{
	active = false;
}

void Projectile::Render(const Texture2D& texture) const
{
	//DrawCircle((int)position.x, (int)position.y, 10, RED);
	DrawTexturePro(texture,
		{
			0,
			0,
			176,
			176,
		},
		{
			position.x,
			position.y,
			50,
			50,
		}, { 25 , 25 },
		0,
		WHITE);
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

Vector2 Alien::GetPosition() const
{
	return position;
}

float Alien::GetRadius() const
{
	return radius;
}

void Alien::Update() 
{


	if (moveRight) {
		position.x += speed;

		if (position.x >= GetScreenWidth()) {
			ChangeDirection();
		}
	}
	else {
		position.x -= speed;

		if (position.x <= 0) {
			ChangeDirection();
		}
	}
}


void Alien::ChangeDirection() {
	moveRight = !moveRight;
	position.y += 50;
}

void Alien::Render(const Texture2D& texture) const
{
	//DrawRectangle((int)position.x - 25, (int)position.y, 30, 30, RED);
	//DrawCircle((int)position.x, (int)position.y, radius, GREEN);
	
	

	DrawTexturePro(texture,
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, {50 , 50},
		0,
		WHITE);
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


