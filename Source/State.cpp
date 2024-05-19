#include "State.h"
#include "game.h"
#include <memory>

State::State(Game& _game) noexcept : game(_game) {}
State::~State() {} //TODO: rule of six?

Startscreen::Startscreen(Game& _game) noexcept : State(_game) {}

void Startscreen::Update()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		game.Reset();
		game.SwitchStates(std::make_unique<Gameplay>(game));
	}
}

void Startscreen::Render() noexcept
{
	game.DrawTitle();
}

void Gameplay::Update()
{
	if (IsKeyReleased(KEY_Q))
	{
		game.SwitchStates(std::make_unique<Endscreen>(game));
		return;
	}

	game.UpdatePlayer();
	
	const bool invaded = game.UpdateAliens();

	if (!game.PlayerHasLives() || invaded)
	{
		game.SwitchStates(std::make_unique<Endscreen>(game));
		return;
	}
	
	game.CheckAlienAmount();
	game.UpdateGameObjects();
	game.HandleCollisions();
	game.CheckPlayerShooting();
	game.AlienShooting();
	game.RemoveInactiveEntities();
}

void Gameplay::Render() //TODO: make noexcept
{
	game.RenderBackground();
	game.RenderStats();
	game.RenderGameObjects();
}

void Endscreen::Update()
{
	if (game.IsNewHighScore())
	{
		game.EnterName();
		return;
	}

	if (IsKeyReleased(KEY_ENTER))
	{
		game.SaveLeaderboard();
		game.Clear();
		game.SwitchStates(std::make_unique<Startscreen>(game));
		return;
	}
}

void Endscreen::Render() noexcept
{
	if (game.IsNewHighScore())
	{
		game.DrawTextBox();
	}
	else
	{
		game.DrawLeaderboard();
	}
}
