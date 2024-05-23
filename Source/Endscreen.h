#pragma once
#include"State.h"
#include <vector>


struct ScoreData
{
	std::string name{ "" };
	unsigned int score = 0;
};

class Endscreen : public State
{
	ScoreData currentScore{};
	std::vector<ScoreData> Leaderboard;
	Rectangle textBox = { 600, 500, 225, 50 };
	std::string name{};
	int letterCount = 0;
	int framesCounter = 0;
	bool mouseOnText = false;

	void DrawTextBox() const noexcept;
	void DrawLeaderboard() const noexcept;
	void LoadLeaderboard() noexcept;
	void EnterName();
	void InsertLetters();
	void InsertNewHighScore(std::string name);
	void SaveLeaderboard();
	bool IsNewHighScore() const noexcept;
public:
	Endscreen() noexcept;
	Switch_State Update() override;
	void ProvideScore(ScoreData scoreData) noexcept;
	void Render() const noexcept override;
	int Reset() noexcept override;
};