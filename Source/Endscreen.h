#pragma once
#include"State.h"
#include <vector>


struct ScoreData
{
	std::string name{ "" };
	unsigned int score{ 0 };
};

class Endscreen : public State
{
	std::vector<ScoreData> leaderboard{ {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	ScoreData current_score{};
	Rectangle text_box = { 600, 500, 225, 50 };
	std::string name{""};
	int letter_count = 0;
	int frame_counter = 0;
	bool mouse_on_text = false;

	void DrawTextBox() const noexcept;
	void DrawLeaderboard() const noexcept;
	void LoadLeaderboard() noexcept;
	void EnterName();
	void InsertLetters();
	void InsertNewHighScore(std::string name);
	void SaveLeaderboard();
	bool IsNewHighScore() const noexcept;
public:
	Switch_State Update() override;
	int Reset() noexcept override;
	void ProvideScore(ScoreData scoreData) noexcept;
	void Render() const noexcept override;
};