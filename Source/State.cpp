#include "State.h"
#include "game.h"
#include <memory>

State::State(Game& _game) : game(_game) {}
State::~State() {}

Startscreen::Startscreen(Game& _game) : State(_game) {}

void Startscreen::Update()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		game.Reset();
		game.SwitchStates(std::make_unique<Gameplay>(game));
	}
}

void Startscreen::Render()
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void Gameplay::Update()
{
	if (IsKeyReleased(KEY_Q))
	{
		game.Clear();
		game.SwitchStates(std::make_unique<Endscreen>(game));
		return;
	}

	game.UpdatePlayer();
	game.UpdateAliens(); //TODO: need to be fixed. aliens reachin ground fucks shit up

	if (game.PlayerHasLives())
	{
		game.Clear();
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

void Gameplay::Render()// TODO: tampering with reference, breaking demeter
{
	game.RenderBackground();

	DrawText(TextFormat("Score: %i", game.GetScore()), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", game.GetLives()), 50, 70, 40, YELLOW);

	game.RenderGameObjects();
}

void Endscreen::Update() // TODO: alot of tampering with reference, Demeter it better when UI has been improved
{
	if (IsKeyReleased(KEY_ENTER) && !game.IsNewHighScore())
	{
		game.SaveLeaderboard();
		game.SwitchStates(std::make_unique<Startscreen>(game));
		return;
	}

	if (game.IsNewHighScore())
	{
		game.EnterName();
	}
}

void Endscreen::Render()// TODO: should try and keep drawcalls in the Renderfunction
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
