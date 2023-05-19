#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Goal {
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snek);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snek);
	void Draw(Board& brd) const;
	void UpdateColor();
	Color GetColor() const;
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Red;
	Location loc;

	bool blinkStatus = true;
	int colorStrength = 0;
};