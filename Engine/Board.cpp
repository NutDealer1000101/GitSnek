#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c) {
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	gfx.DrawRectDim(BoardLoc.x + loc.x * gridDimension + 1, 
					BoardLoc.y + loc.y * gridDimension + 1, 
					gridDimension - 2, gridDimension - 2,
					c);
}

void Board::DrawBorder() {
	int xleft = BoardLoc.x;
	int xright = BoardLoc.x + gridDimension * width;
	int ytop = BoardLoc.y;
	int ybottom = BoardLoc.y + gridDimension * height;

	int size = borderThickness;
	Color c = borderColor;

	assert(xleft - size >= 0);
	assert(ytop - size >= 0);
	assert(xright + size < Graphics::ScreenWidth);
	assert(ybottom + size < Graphics::ScreenHeight);

	gfx.DrawRect(xleft, ytop, xright + size, ytop - size, c);		//Top line

	gfx.DrawRect(xright, ytop, xright + size, ybottom + size, c);	//Right line

	gfx.DrawRect(xright, ybottom, xleft - size, ybottom + size, c);	//Bottom line
	
	gfx.DrawRect(xleft, ybottom, xleft - size, ytop - size, c);		//Left line
}

void Board::DrawBG() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Location loc = { x, y };
			if ((x + y) % 2) {
				DrawCell(loc, bgColor1);
			}
			else {
				DrawCell(loc, bgColor2);
			}
		}
	}
}

bool Board::IsInsideBoard(const Location& loc) const {
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

void Board::CheckValidBoardLocation() const {
	assert(BoardLoc.x >= 0);
	assert(BoardLoc.x + gridDimension * width < Graphics::ScreenWidth);
	assert(BoardLoc.y >= 0);
	assert(BoardLoc.y + gridDimension * height < Graphics::ScreenHeight);
}

int Board::GetGridWidth() const {
	return width;
}

int Board::GetGridHeight() const {
	return height;
}
