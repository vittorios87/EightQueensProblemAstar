#include "pch.h"
#include "Node.h"


Node::Node(): placedQueens(0)
{
	queens = new std::array<QueenPosition, CHESSTABLEDIM>();
	
	GenerateConnections();
}
Node::Node(std::array<QueenPosition, CHESSTABLEDIM>* queens_init) : queens(queens_init){
	SortQueensArray();
	int placedQueensCntr = 0;
	for (int i = 0; i < CHESSTABLEDIM; i++) {
		if (queens->at(i) != QueenPosition(8, 8)) {
			placedQueensCntr++;
		}
	}
	placedQueens=placedQueensCntr;
	GenerateConnections();
}



Node::~Node()
{
}

void Node::SwapQueens(int i_a, int i_b)
{
	QueenPosition temp = queens->at(i_a);
	queens->at(i_a) = queens->at(i_b);
	queens->at(i_b) = temp;
}
void Node::SortQueensArray() {
	int a;
	int b;
	for (int i = 0; i < CHESSTABLEDIM-1; i++) {
		for (int j = 0; j < CHESSTABLEDIM-i-1; j++) {
			a = queens->at(j).r * CHESSTABLEDIM + queens->at(j).c;
			b = queens->at(j+1).r * CHESSTABLEDIM + queens->at(j + 1).c;
			if (a > b) {
				SwapQueens(j, j + 1);
			}
		}
	}	
}
bool Node::operator==(const Node& other) {
	if (placedQueens == other.placedQueens) {
		for (int i = 0; i < CHESSTABLEDIM - 1; i++) {
			if (queens->at(i) != other.queens->at(i)) {
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
void Node::FillAllowedCellsTable(int* tablePtr, int r_q, int c_q) {
	if (r_q != CHESSTABLEDIM && c_q != CHESSTABLEDIM) {
		//mark the row
		for (int c_i = 0; c_i < CHESSTABLEDIM; c_i++) {
			*(tablePtr + CHESSTABLEDIM *r_q+c_i) = 1;
		}
		//mark the column
		for (int r_i = 0; r_i < CHESSTABLEDIM; r_i++) {
			*(tablePtr + CHESSTABLEDIM * r_i + c_q) = 1;
		}
		// mark TL - BR diagonal 

	
		if (r_q + 1 < CHESSTABLEDIM && c_q + 1 < CHESSTABLEDIM) {
			for (int r_i = r_q + 1, c_i = c_q + 1; r_i < CHESSTABLEDIM && c_i < CHESSTABLEDIM; r_i++, c_i++) {
				*(tablePtr + CHESSTABLEDIM * r_i + c_i) = 1;
			}
		}
		

		if (r_q - 1 >= 0 && c_q - 1 >= 0) {
			for (int r_i = r_q - 1, c_i = c_q - 1; r_i >= 0 && c_i >= 0; r_i--, c_i--) {
				*(tablePtr + CHESSTABLEDIM * r_i + c_i) = 1;
			}
		}
		//mark TR - BL diagonal
		for (int r_i = r_q, c_i = c_q; r_i >= 0 && c_i < CHESSTABLEDIM; r_i--, c_i++) {
			*(tablePtr + CHESSTABLEDIM * r_i + c_i) = 1;
		}
		for (int r_i = r_q, c_i = c_q; r_i < CHESSTABLEDIM && c_i >= 0; r_i++, c_i--) {
			*(tablePtr + CHESSTABLEDIM * r_i + c_i) = 1;
		}

	}
}
int Node::CountNotAllowedPositsOfTable(int* tablePtr) {
	int notAllowedPositsCounter = 0;
	for (int r = 0; r < CHESSTABLEDIM; r++) {
		for (int c = 0; c < CHESSTABLEDIM; c++) {
			if (*(tablePtr + CHESSTABLEDIM * r + c) == 1) {
				notAllowedPositsCounter++;
			}
		}
	}
	return notAllowedPositsCounter;
}



void Node::GenerateConnections() {
	// (0,0) coordinates on the top left corner
	int allowedCellsTable[CHESSTABLEDIM][CHESSTABLEDIM]  = { 0 };
	//{ { 0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0} };
	

	for (int i = 0; i < CHESSTABLEDIM; i++) {
		
		FillAllowedCellsTable((int*)&allowedCellsTable, queens->at(i).r, queens->at(i).c);

	}
	int notAllowedPositions = CountNotAllowedPositsOfTable((int*)&allowedCellsTable);
	
	for (int r = 0; r < CHESSTABLEDIM; r++) {
		//for (int c = 0; c < CHESSTABLEDIM; c++) {}
		int c = GetPlacedQueens();
		if (allowedCellsTable[r][c] == 0) {
			int nextAllowedCellsTable[CHESSTABLEDIM][CHESSTABLEDIM] = { 0 };
			for (int i = 0; i < CHESSTABLEDIM; i++) {
				for (int j = 0; j < CHESSTABLEDIM; j++) {
					nextAllowedCellsTable[i][j] = allowedCellsTable[i][j];
				}
			}
			FillAllowedCellsTable((int*)&nextAllowedCellsTable, r, c);
			int nextNotAllowedPositions = CountNotAllowedPositsOfTable((int*)&nextAllowedCellsTable);
			QueenPosition newPlacedQueenPos = QueenPosition(r, c);
			Connection connectToEmptyCell(this, newPlacedQueenPos, nextNotAllowedPositions - notAllowedPositions);
			connections.push_back(connectToEmptyCell);
		}
			
		
	}

}
const int&  Node::GetPlacedQueens() {
	return placedQueens;
}

QueenPosition Node::GetQueenPositionAtIndex(int index) {
	return queens->at(index);
}
