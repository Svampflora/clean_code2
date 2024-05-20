#pragma once

class Game;

class State
{
protected:
	Game& game; //TODO: avoid using reference member
public:
	State(Game& _game) noexcept;
	virtual ~State() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;
};


class Startscreen : public State
{
public:
	Startscreen(Game& _game) noexcept;
	void Update() override;
	void Render() noexcept override;
};

class Gameplay : public State
{
public:
	Gameplay(Game& _game) noexcept : State(_game) {}
	void Update() override;
	void Render() noexcept override;
};

class Endscreen : public State
{
public:
	Endscreen(Game& _game) noexcept : State(_game) {}
	void Update() override;
	void Render() noexcept override;
};