#pragma once
class NodeRecord
{
public:
	NodeRecord();
	NodeRecord(std::array<QueenPosition, CHESSTABLEDIM>* queens_init, int costSoFar_init);
	~NodeRecord();
	void GenerateNodeRecords();
	int GetEstimatedTotalCost();
	int GetCostSoFar();
	Node* GetOwnedNodePtr();

	std::vector<NodeRecord*>* childNodeRecords = new std::vector<NodeRecord*>();

private:
	Node* node;
	int costSoFar;
	int estimatedTotalCost;
};

