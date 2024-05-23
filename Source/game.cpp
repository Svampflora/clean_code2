#include "State.h"
#include "game.h"
#include "raymath.h"
#include <iostream>
#include <chrono>

void Game::SwitchState(Switch_State to)
{
    switch (to)
    {
    case Switch_State::to_startscreen:
        current_state = startscreen;
        return;

    case Switch_State::to_gameplay:
        current_state = gameplay;
        return;

    case Switch_State::to_endgame:
        endscreen->ProvideScore(scoreData);
        current_state = endscreen;
        return;


    default:
        throw std::runtime_error("Invalid game state");

    }
}

void Game::ResetState()
{
    scoreData.score = current_state->Reset();
}

Game::Game() //TODO: default constructor insists in noexcept
{
    startscreen = std::make_shared<Startscreen>();
    gameplay = std::make_shared<Gameplay>();
    endscreen = std::make_shared<Endscreen>();
    current_state = startscreen;
    scoreData = ScoreData{};
}

void Game::Update()
{
    const Switch_State new_state = current_state->Update();
    if (new_state == Switch_State::stay_at_same)
    {
        return;
    }
    ResetState();
	SwitchState(new_state);
}

void Game::Render() const noexcept 
{
	current_state->Render();
}