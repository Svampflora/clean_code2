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
	game.UpdateAliens();

	if (game.PlayerHasHealth())
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

	DrawText(TextFormat("Score: %i", game.score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", game.player.GetLives()), 50, 70, 40, YELLOW);

	game.RenderGameObjects();
}

void Endscreen::Update() // TODO: alot of tampering with reference, Demeter it better when UI has been improved
{
	if (IsKeyReleased(KEY_ENTER) && !game.newHighScore)
	{
		game.SaveLeaderboard();
		game.SwitchStates(std::make_unique<Startscreen>(game));
		return;

	}

	if (game.newHighScore)
	{
		if (CheckCollisionPointRec(GetMousePosition(), game.textBox)) game.mouseOnText = true;
		else game.mouseOnText = false;

		if (game.mouseOnText)
		{
			// Set the window's cursor to the I-Beam
			SetMouseCursor(MOUSE_CURSOR_IBEAM);

			// Get char pressed on the queue
			int key = GetCharPressed();

			// Check if more characters have been pressed on the same frame
			while (key > 0)
			{
				// NOTE: Only allow keys in range [32..125]
				if ((key >= 32) && (key <= 125) && (game.letterCount < 9))
				{
					game.name[game.letterCount] = (char)key;
					game.name[game.letterCount + 1] = '\0'; // Add null terminator at the end of the string.
					game.letterCount++;
				}

				key = GetCharPressed();  // Check next character in the queue
			}

			//Remove chars 
			if (IsKeyPressed(KEY_BACKSPACE))
			{
				game.letterCount--;
				if (game.letterCount < 0) game.letterCount = 0;
				game.name[game.letterCount] = '\0';
			}
		}
		else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

		if (game.mouseOnText)
		{
			game.framesCounter++;
		}
		else
		{
			game.framesCounter = 0;
		}

		// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
		// name + score to scoreboard
		if (game.letterCount > 0 && game.letterCount < 9 && IsKeyReleased(KEY_ENTER))
		{
			std::string nameEntry(game.name);

			game.InsertNewHighScore(nameEntry);

			game.newHighScore = false;
		}
	}
}

void Endscreen::Render()// TODO: tampering with reference
{

	if (game.newHighScore)
	{
		game.DrawTextBox();
	}
	else
	{
		game.DrawLeaderboard();
	}
}
