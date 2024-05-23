#include "Startscreen.h"
#include "Gameplay.h"

Startscreen::Startscreen() noexcept{}


Switch_State Startscreen::Update() noexcept
{
	if (IsKeyReleased(KEY_SPACE))
	{
		//game.Reset();//TODO: new place to reset in between games
		return Switch_State::to_gameplay;
	}
	return Switch_State::stay_at_same;
}

void Startscreen::Render() const noexcept
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

int Startscreen::Reset() noexcept
{
	return 0;
}

void Startscreen::DrawTitle() const noexcept
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}