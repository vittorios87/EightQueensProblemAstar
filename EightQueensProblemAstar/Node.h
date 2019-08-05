#pragma once



class Node
{
public:
	Node();
	Node(std::array<QueenPosition, CHESSTABLEDIM>*);
	~Node();

	void SortQueensArray();
	bool operator==(const Node& other);
	void GenerateConnections();
	const int&  GetPlacedQueens();
	QueenPosition GetQueenPositionAtIndex(int index);

private:
	void SwapQueens(int i_a, int i_b);
	void FillAllowedCellsTable( int* tablePtr , int r_q, int c_q);
	int  CountNotAllowedPositsOfTable(int* tablePtr);

public:
	std::vector<Connection> connections;
private:
	std::array<QueenPosition, CHESSTABLEDIM>* queens;
	int placedQueens;

};

