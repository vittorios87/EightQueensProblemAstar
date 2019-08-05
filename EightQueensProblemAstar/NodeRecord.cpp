#include "pch.h"
#include "NodeRecord.h"


NodeRecord::NodeRecord()
{
	node = new Node();
	costSoFar = 0;
	estimatedTotalCost = CHESSTABLEDIM;
}
NodeRecord::NodeRecord(std::array<QueenPosition, CHESSTABLEDIM>* queens_init, int costSoFar_init) {
	node = new Node(queens_init);
	costSoFar = costSoFar_init;
	estimatedTotalCost = costSoFar + (CHESSTABLEDIM - node->GetPlacedQueens());
}

NodeRecord::~NodeRecord()
{
}

void NodeRecord::GenerateNodeRecords() {
	for (int i=0; i < node->connections.size(); i++) {
		//create array of queen positions
		std::array<QueenPosition, CHESSTABLEDIM>* queens_new_node_init = new std::array<QueenPosition, CHESSTABLEDIM>();
		for (int j=0; j < node->GetPlacedQueens(); j++) {
			queens_new_node_init->at(j) = node->GetQueenPositionAtIndex(j);
		}
		queens_new_node_init->at(node->GetPlacedQueens()) = node->connections.at(i).GetQueenPosition();
		//calculate a new value for cost so far
		int costSoFar_new_nodeRecord_init = costSoFar + node->connections.at(i).GetCost();
		//calculate a new value for estimated total cost: not necessary

		childNodeRecords->push_back(new NodeRecord(queens_new_node_init,costSoFar_new_nodeRecord_init));
	}
}

int NodeRecord::GetEstimatedTotalCost() {
	return estimatedTotalCost;
}
int NodeRecord::GetCostSoFar() {
	return costSoFar;
}

Node* NodeRecord::GetOwnedNodePtr() {
	return node;
}



