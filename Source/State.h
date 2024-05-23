#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#include "raymath.h"
#pragma warning(pop)

#include <memory>
#include <string>
#include "Utilities.h"

enum class Switch_State { to_startscreen, to_gameplay, to_endgame, stay_at_same };

class State
{

public:

	virtual ~State() = default;
	virtual Switch_State Update() = 0;
	virtual int Reset() = 0;
	virtual void Render()  const noexcept = 0;
};






