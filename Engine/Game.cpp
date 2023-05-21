/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/

/*
TODO:
Random obstacles

*/

#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 5,10 }),
	goal(rng, brd, snek)
{
	brd.CheckValidBoardLocation();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	if (!isStarted) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) isStarted = true;
	}
	else {
		if (!gameIsOver) {
			Location up_delta = { 0, -1 };
			Location down_delta = { 0, 1 };
			Location left_delta = { -1, 0 };
			Location right_delta = { 1, 0 };

			if (wnd.kbd.KeyIsPressed('W') && !(blacklistLoc == up_delta)) {
				delta_loc = up_delta;
			}
			else if (wnd.kbd.KeyIsPressed('S') && !(blacklistLoc == down_delta)) {
				delta_loc = down_delta;
			}
			else if (wnd.kbd.KeyIsPressed('A') && !(blacklistLoc == left_delta)) {
				delta_loc = left_delta;
			}
			else if (wnd.kbd.KeyIsPressed('D') && !(blacklistLoc == right_delta)) {
				delta_loc = right_delta;
			}

			goal.UpdateColor();

			snekMoveCounter += dt;
			if (snekMoveCounter >= snek.getMovePeriod()) {
				snekMoveCounter = 0.0f;

				blacklistLoc = delta_loc.Invert();

				const Location next = snek.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(next) || snek.IsInTileExceptEnd(next)) {
					gameIsOver = true;
				}
				else {
					bool eating = next == goal.GetLocation();
					if (eating) {
						snek.Grow();
					}
					snek.MoveBy(delta_loc);
					if (eating) {
						goal.Respawn(rng, brd, snek);
					}
				}
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (!isStarted) {
		SpriteCodex::DrawTitle(300, 200, gfx);
	}
	else {
		brd.DrawBG();
		brd.DrawBorder();
		snek.Draw(brd);
		goal.Draw(brd);
		if (gameIsOver) {
			SpriteCodex::DrawGameOver(225, 25, gfx);
		}
	}
}
