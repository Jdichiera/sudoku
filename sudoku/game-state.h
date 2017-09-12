#pragma once
class GameState {
public:
	virtual void HandleEvents() = 0;
	virtual void Logic() = 0;
	virtual void Render() = 0;
	virtual ~GameState() {};
};