#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snek) {
	Respawn(rng, brd, snek);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snek) {
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do {
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc));

	loc = newLoc;
}

void Goal::Draw(Board& brd) const {
	brd.DrawCell(loc, GetColor());
}

void Goal::UpdateColor() {
	int speed = 2;
	int min = 0;
	int max = 50;

	if (blinkStatus) {
		colorStrength += speed;
		if (colorStrength > max) {
			colorStrength = max;
			blinkStatus = false;
		}
	}
	else {
		colorStrength -= speed;
		if (colorStrength < min) {
			colorStrength = min;
			blinkStatus = true;
		}
	}
}

Color Goal::GetColor() const {
	Color resultc = c;

	//There has to be a better looking solution to this, but it works for now.
	resultc.SetR((resultc.GetR() * (100 - colorStrength) + 255 * colorStrength) / 100);
	resultc.SetG((resultc.GetG() * (100 - colorStrength) + 255 * colorStrength) / 100);
	resultc.SetB((resultc.GetB() * (100 - colorStrength) + 255 * colorStrength) / 100);

	return resultc;
}

const Location& Goal::GetLocation() const {
	return loc;
}
