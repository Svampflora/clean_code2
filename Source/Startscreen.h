#pragma once
#include"State.h"

class Startscreen : public State
{
	void DrawTitle() const noexcept;
public:
	Startscreen() noexcept;
	Switch_State Update() noexcept override;
	void Render() const noexcept override;
	int Reset() noexcept override;
};
