#pragma once

#include "Board.h"
#include "Location.h"
#include "Colors.h"

class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location& in_loc);
		void InitBody(int nSegments);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileExceptEnd(const Location& target) const;
	int getSpeed() const;
private:
	static constexpr Color headColor = Colors::MakeRGB(255, 191, 0);	//Amber
	static constexpr Color bodyColor1 = Colors::MakeRGB(124, 252, 0);
	static constexpr Color bodyColor2 = Colors::MakeRGB(0, 255, 0);
	static constexpr Color bodyColor3 = Colors::MakeRGB(50, 205, 50);
	
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;

};