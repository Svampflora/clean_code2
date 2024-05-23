#include "Gameplay.h"
#include "Endscreen.h"

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
bool Gameplay::CheckProjectileCollision(const Projectile& projectile, const Object& object)
{
	return CheckCollision(object.GetPosition(), object.GetRadius(), projectile.GetEdges());
}

template <typename ProjectileContainer, typename ObjectType>
void Gameplay::HandleProjectileCollisions(ProjectileContainer& projectiles, ObjectType& object)
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
void Gameplay::HandleProjectileCollisions(std::vector<Projectile>& projectiles, std::vector<ObjectType>& objects) 
{
	for (Projectile& projectile : projectiles) 
	{
		for (ObjectType& object : objects) 
		{
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

Switch_State Gameplay::Update()
{
	if (IsKeyReleased(KEY_Q))
	{

		return Switch_State::to_endgame;
	}

	UpdatePlayer();

	const bool invaded = UpdateAliens();

	if (!PlayerHasLives() || invaded)
	{
		return Switch_State::to_endgame;
	}

	CheckAlienAmount();
	UpdateGameObjects();
	HandleCollisions();
	CheckPlayerShooting();
	AlienShooting();
	RemoveInactiveEntities();
	return Switch_State::stay_at_same;
}

Gameplay::Gameplay() :
	player(),
	background(600),
	resources(),
	shootTimer(0),
	formationX(100.0f),
	formationY(50.0f),
	formationWidth(8),
	formationHeight(5),
	alienSpacing(80),
	score(0)
{
	
	playerProjectiles;
	enemyProjectiles;
	SpawnAliens();
	MakeWalls();
}

void Gameplay::Render() const noexcept
{
	RenderBackground();
	RenderStats();
	RenderGameObjects();
}

int Gameplay::Reset() 
{
	const int _score = score;
	Clear();
	MakeWalls();
	SpawnAliens(); //TODO: put spawn stupp in a function and use similar naming
	player.Reset();
	return _score;
}

void Gameplay::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++)
	{
		for (int column = 0; column < formationWidth; column++)
		{
			aliens.emplace_back(Alien{ {formationX + 450.0f + (column * alienSpacing), formationY + (row * alienSpacing)} });
		}
	}
}

void Gameplay::MakeWalls() //TODO: old loop
{
	const float window_width = GetScreenWidthF();
	const float window_height = GetScreenHeightF();
	constexpr int wallAmount = 5;
	const float wall_distance = window_width / (wallAmount + 1);

	for (int i = 0; i < wallAmount; ++i)
	{
		walls.emplace_back(Vector2{ wall_distance * (i + 1), window_height - 250 });
	}
}



void Gameplay::Clear() noexcept
{
	playerProjectiles.clear();
	enemyProjectiles.clear();
	walls.clear();
	aliens.clear();
	score = 0;
}



void Gameplay::RemoveInactiveEntities() noexcept
{

	remove_if(walls, [](const auto& projectile) noexcept { return !projectile.Active(); });
	remove_if(enemyProjectiles, [](const auto& projectile) noexcept { return !projectile.Active(); });
	remove_if(playerProjectiles, [](const auto& projectile) noexcept { return !projectile.Active(); });
	remove_if(aliens, [](const auto& alien) noexcept { return !alien.Active(); });
}

void Gameplay::UpdatePlayer() noexcept
{
	player.Update();
}

void Gameplay::HandleCollisions()
{
	HandleProjectileCollisions(enemyProjectiles, player);
	HandleProjectileCollisions(enemyProjectiles, walls);
	HandleProjectileCollisions(playerProjectiles, aliens);
	HandleProjectileCollisions(playerProjectiles, walls);
}

void Gameplay::UpdateGameObjects()
{
	const float offset = CalculateOffset();
	background.Update(offset);
	UpdateObjects(playerProjectiles);
	UpdateObjects(enemyProjectiles);
	UpdateObjects(walls);
}

int Gameplay::GetScore() const noexcept
{
	return score;
}

int Gameplay::GetLives() const noexcept
{
	return player.GetLives();
}

bool Gameplay::PlayerHasLives() const noexcept
{
	return (player.GetLives() > 0);
}


bool Gameplay::CheckAlienHasInvaded(const Alien& alien) const noexcept
{
	if (alien.GetPosition().y > GetScreenHeight() - player.GetSize().y)
	{
		return true;
	}
	return false;
}

void Gameplay::CheckAlienAmount()
{
	if (aliens.size() < 1)
	{
		SpawnAliens();
	}
}

void Gameplay::AlienShooting() //TODO: get around at()
{
	const int framesPerSecond = GetFPS();
	if (++shootTimer > framesPerSecond)
	{
		if (aliens.size() > 1)
		{
			const int randomAlienIndex = rand() % aliens.size();
			enemyProjectiles.push_back(Projectile({ aliens.at(randomAlienIndex).GetPosition().x, aliens.at(randomAlienIndex).GetPosition().y + 40 }, -15));

		}
		shootTimer = 0;
	}
}

void Gameplay::CheckPlayerShooting()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		const float window_height = GetScreenHeightF();
		playerProjectiles.push_back(Projectile({ player.GetPosition().x, window_height - 130 }, 15));
	}
}

float Gameplay::CalculateOffset() const
{
	const Vector2 playerPos = { player.GetPosition().x, player.GetSize().y };
	const Vector2 cornerPos = { 0, player.GetSize().y };

	return Vector2Distance(playerPos, cornerPos) * -1;
}

bool Gameplay::CheckCollision(Vector2 circlePos, float circleRadius, std::pair<Vector2, Vector2> edges)
{
	const float length = Vector2Distance(edges.first, edges.second);
	if (CheckCollisionPointCircle(edges.first, circlePos, circleRadius) || CheckCollisionPointCircle(edges.second, circlePos, circleRadius))
	{
		return true;
	}
	else if (CheckCollisionCircleRec(circlePos, circleRadius, Rectangle{ edges.first.x, edges.first.y, 0.5f, length }))
	{
		return true;
	}
	return false;
}

bool Gameplay::UpdateAliens() noexcept
{
	for (Alien& alien : aliens)
	{
		alien.Update();

		if (CheckAlienHasInvaded(alien))
		{
			return true;
		}
	}
	return false;
}

void Gameplay::RenderStats() const noexcept
{
	DrawText(TextFormat("Score: %i", GetScore()), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", GetLives()), 50, 70, 40, YELLOW);
}

void Gameplay::RenderBackground() const noexcept
{
	background.Render();
}

void Gameplay::RenderGameObjects() const noexcept
{
	//const size_t frame = resources.animator.Get(shipTextures.size());
	//player.Render(resources.GetShipTexture(3)); //TODO:Hardcoded bullshit
	player.Render();
	RenderObjects(enemyProjectiles, resources.GetLaserTexture());
	RenderObjects(playerProjectiles, resources.GetLaserTexture());
	RenderObjects(walls, resources.GetBarrierTexture());
	RenderObjects(aliens, resources.GetAlienTexture());
}