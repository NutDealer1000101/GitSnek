#pragma once

class Location {
public:
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}

	Location Invert() 
	{
		Location result = { x * -1, y * -1 };
		return result;
	}

	bool operator==(const Location& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	int x;
	int y;
};