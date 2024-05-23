#pragma once
#include "Startscreen.h"
#include "Gameplay.h"
#include "Endscreen.h"


class Game
{
	std::shared_ptr<Startscreen> startscreen;
	std::shared_ptr<Gameplay> gameplay;
	std::shared_ptr<Endscreen> endscreen;
	std::shared_ptr<State> current_state;
	ScoreData scoreData;

	void SwitchState(Switch_State);
	void ResetState();
public:
	Game();
	void Update();
	void Render() const noexcept;
};