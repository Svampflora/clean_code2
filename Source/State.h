#pragma once

class Game;

class State
{
protected:
	Game& game;
public:
	State(Game& _game);
	virtual ~State();
	virtual void Update() = 0;
	virtual void Render() = 0;
};


class Startscreen : public State
{
public:
	Startscreen(Game& _game);
	void Update() override;
	void Render() override;
};

class Gameplay : public State
{
public:
	Gameplay(Game& _game) : State(_game) {}
	void Update() override;
	void Render() override;
};

class Endscreen : public State
{
public:
	Endscreen(Game& _game) : State(_game) {}
	void Update() override;
	void Render() override;
};