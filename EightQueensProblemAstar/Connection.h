#pragma once

class Node;

class Connection
{
public:
	Connection(Node*, QueenPosition&, int);
	~Connection();
	const int& GetCost();
	QueenPosition GetQueenPosition();
private:
	Node* originNode;
	QueenPosition nextQueen;
	int connectionCost;
};

