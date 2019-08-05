#pragma once

#define CHESSTABLEDIM 8

enum class Key { None, Up, Down, Left, Right,Any, Error };

struct QueenPosition
{
public:
	QueenPosition() {
		r = CHESSTABLEDIM; c = CHESSTABLEDIM;
	};
	QueenPosition(int r_init, int c_init) : r(r_init), c(c_init) {};
	~QueenPosition() {};

	bool operator==(const QueenPosition& other) {
		if (r == other.r && c == other.c) {
			return true;
		}
		return false;

	}
	bool operator!=(const QueenPosition& other) {
		if (r != other.r || c != other.c) {
			return true;
		}
		return false;
	}


	int r;
	int c;
};