#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc) {
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc) {
	for (int i = nSegments - 1; i > 0; --i) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const {
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);

	return l;
}

void Snake::Grow() {
	if (nSegments < nSegmentsMax) {
		segments[nSegments].InitBody(nSegments);
		++nSegments;
	}
}

void Snake::Draw(Board& brd) const {
	for (int i = 0; i < nSegments; ++i) {
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTile(const Location& target) const {
	for (int i = 0; i < nSegments; ++i) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

bool Snake::IsInTileExceptEnd(const Location& target) const {
	for (int i = 0; i < nSegments - 1; ++i) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

float Snake::getMovePeriod() const {
	if (nSegments < nSegmentToMaxSpeed) {
		const float p = 1.0f - nSegments / nSegmentToMaxSpeed;

		return snekMovePeriodMax * p + snekMovePeriodMin * (1.0f - p);
	}
	else {
		return snekMovePeriodMin;
	}
}

void Snake::Segment::InitHead(const Location& in_loc) {
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(int nSegments) {
	int mod = nSegments % 3;
	if (mod == 0) {
		c = Snake::bodyColor1;
	}
	else if (mod == 1) {
		c = Snake::bodyColor2;
	}
	else {
		c = Snake::bodyColor3;
	}

}

void Snake::Segment::Follow(const Segment& next) {
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc) {
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const {
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const {
	return loc;
}
