#include "Endscreen.h"
#include "Startscreen.h"
#include <fstream>
#include <iostream>

Endscreen::Endscreen() noexcept :
	Leaderboard({ {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} }),
	textBox{ 600, 500, 225, 50 },
	name{},
	letterCount(0),
	framesCounter(0),
	mouseOnText(false)
{
}

Switch_State Endscreen::Update()
{
	if (IsNewHighScore())
	{
		EnterName();
		return Switch_State::stay_at_same;
	}

	if (IsKeyReleased(KEY_ENTER))
	{
		SaveLeaderboard();
		return Switch_State::to_startscreen;
	}
	return Switch_State::stay_at_same;
}

void Endscreen::Render() const noexcept
{
	if (IsNewHighScore())
	{
		DrawTextBox();
	}
	else
	{
		DrawLeaderboard();
	}
}

int Endscreen::Reset() noexcept
{
	return 0;
}

bool Endscreen::IsNewHighScore() const noexcept
{
	return (currentScore.score > Leaderboard.back().score);
}

void Endscreen::EnterName() //TODO: make shorter
{
	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

	if (mouseOnText)
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		InsertLetters();
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

void Endscreen::InsertLetters()
{
	int key;
	while ((key = GetCharPressed()) > 0)
	{
		if ((key >= 32) && (key <= 125) && (letterCount < 9))
		{

			[[gsl::suppress(type.1)]]
			const char character_key = static_cast<char>(key); //TODO: find solution so we don't need to cast

			name.push_back(character_key);
			letterCount++;
		}
	}

	if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
	{
		name.pop_back();
		letterCount--;
	}
}
void Endscreen::InsertNewHighScore(std::string _name)
{
	for (auto it = Leaderboard.begin(); it != Leaderboard.end(); ++it)
	{
		if (currentScore.score > it->score)
		{
			ScoreData newData{ _name, currentScore.score };
			Leaderboard.insert(it, newData);
			Leaderboard.pop_back();

			currentScore.score = 0;
			break;
		}
	}
}

void Endscreen::LoadLeaderboard() noexcept //TODO: empty
{

}

void Endscreen::SaveLeaderboard() //TODO: does not save to file
{
	std::fstream file{ "Leaderboard" };

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}
}

void Endscreen::ProvideScore(ScoreData scoreData) noexcept
{
	currentScore.score = scoreData.score;
}

void Endscreen::DrawTextBox() const noexcept //TODO: magic values
{
	const Color borderColor = mouseOnText ? RED : DARKGRAY;
	constexpr float thickness = 2.0f;
	DrawRectangleLinesEx(textBox, thickness, borderColor);
	DrawTextF(name.c_str(), textBox.x + 5.0f, textBox.y + 8.0f, 40, MAROON);
	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

	constexpr int maxLetterCount = 9;
	if (mouseOnText && letterCount < maxLetterCount)
	{
		if ((framesCounter / 20) % 2 == 0)
		{
			DrawTextF("_", textBox.x + 8 + MeasureText(name.c_str(), 40), textBox.y + 12.0f, 40, MAROON);
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

void Endscreen::DrawLeaderboard() const noexcept //TODO: magic values
{
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);
	int yOffset = 140;
	for (const auto& entry : Leaderboard)
	{
		DrawText(entry.name.c_str(), 50, yOffset, 40, YELLOW);
		DrawText(TextFormat("%i", entry.score), 350, yOffset, 40, YELLOW);
		yOffset += 40;
	}
}