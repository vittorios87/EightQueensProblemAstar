#pragma once
class PathFinderAStar
{
public:
	PathFinderAStar();
	~PathFinderAStar();

	void PathFinderStep();
	std::wstring& PrintDisplay();
	int GetOpenNodeRecordsLength();
	int GetSolutionsLength();

	bool solutionViewingStarted = false;
	void ShiftSolutionIndex(char);

private:
	std::vector<NodeRecord*>* openNodeRecords;
	std::vector<NodeRecord*>* closedNodeRecords;

	NodeRecord* SelectNRWithLowestEstimatedCost(int& selectedNRindex);

	bool NRListContainsNode(std::vector<NodeRecord*>*, Node*);

	NodeRecord* currentNodeRecord;
	std::wstring nOfQueensCurrentNode = L"0";

	std::vector<Node> solutions;

	std::wstring buffer;

	bool solutionHasBeenFound = false;

	int solutionToViewIndex = 0;

};

