#include "pch.h"
#include "Connection.h"


Connection::Connection(Node* originNode_init , QueenPosition& nextQueen_init, int connectionCost_init): nextQueen(nextQueen_init)
{
	originNode = originNode_init;
	connectionCost = connectionCost_init;
}


Connection::~Connection()
{
}

const int& Connection::GetCost() {
	return connectionCost;
}
QueenPosition Connection::GetQueenPosition() {
	return nextQueen;
}

