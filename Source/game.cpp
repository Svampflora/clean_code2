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
    BeginDrawing();
    ClearBackground(BLACK);
	current_state->Render();
    EndDrawing();
}