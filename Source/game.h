#pragma once
#include "Startscreen.h"
#include "Gameplay.h"
#include "Endscreen.h"


class Game
{
	std::shared_ptr<Startscreen> startscreen{ std::make_shared<Startscreen>() };
	std::shared_ptr<Gameplay> gameplay{ std::make_shared<Gameplay>() };
	std::shared_ptr<Endscreen> endscreen{ std::make_shared<Endscreen>() };
	std::shared_ptr<State> current_state = startscreen;
	ScoreData scoreData{};

	void SwitchState(Switch_State);
	void ResetState();
public:
	void Update();
	void Render() const noexcept;
};