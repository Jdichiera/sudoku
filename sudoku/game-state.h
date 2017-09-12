#pragma once
#include "globals.h"
class GameState {
public:
	virtual void HandleEvents() = 0;
	virtual void Logic() = 0;
	virtual void Render() = 0;
	virtual ~GameState() {};
};