#pragma once

#include "Graphics.h"
#include "Location.h"

class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	void DrawBG();
	bool IsInsideBoard(const Location& loc) const;

	void CheckValidBoardLocation() const;

	int GetGridWidth() const;
	int GetGridHeight() const;
private:
	static constexpr int gridDimension = 20;
	static constexpr int width = 20;
	static constexpr int height = 20;

	static constexpr Location BoardLoc = { 
		(Graphics::ScreenWidth - gridDimension * width) / 2,
		(Graphics::ScreenHeight - gridDimension * height) / 2
	};

	static constexpr int borderThickness = 3;
	static constexpr Color borderColor = Colors::MakeRGB(255, 255, 255);
	static constexpr Color bgColor1 = Colors::MakeRGB(30, 30, 30);
	static constexpr Color bgColor2 = Colors::MakeRGB(25, 25, 25);

	Graphics& gfx;
};