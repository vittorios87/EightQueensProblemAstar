#include "pch.h"
#include "PathFinderAStar.h"


PathFinderAStar::PathFinderAStar(): openNodeRecords(new std::vector<NodeRecord*>()), closedNodeRecords(new std::vector<NodeRecord*>())
{
	openNodeRecords->push_back(new NodeRecord());
}


PathFinderAStar::~PathFinderAStar()
{
}

NodeRecord* PathFinderAStar::SelectNRWithLowestEstimatedCost(int& selectedNRindex) {
	NodeRecord* selectedNR = openNodeRecords->at(0);
	for (int i = 1; i < openNodeRecords->size(); i++) {
		if (selectedNR->GetEstimatedTotalCost() > openNodeRecords->at(i)->GetEstimatedTotalCost()) {
			selectedNR = openNodeRecords->at(i);
			selectedNRindex = i;
		}
	}
	return selectedNR;
}

bool PathFinderAStar::NRListContainsNode(std::vector<NodeRecord*>* nodeRecordsListToScan, Node* nodeToFind) {
	for (std::vector<NodeRecord*>::iterator it = nodeRecordsListToScan->begin(); it != nodeRecordsListToScan->begin(); it++) {
		if (*(*it)->GetOwnedNodePtr() == (*nodeToFind)) {
			return true;
		};
	}
	return false;
}

void PathFinderAStar::PathFinderStep() {
	//scegli il node record con il valore di estimated total cost più basso
	//solutionHasBeenFound = false;

	int currentNRindex = 0;
	currentNodeRecord = SelectNRWithLowestEstimatedCost(currentNRindex);
	nOfQueensCurrentNode.assign(std::to_wstring(currentNodeRecord->GetOwnedNodePtr()->GetPlacedQueens()));

	if (currentNodeRecord->GetOwnedNodePtr()->GetPlacedQueens() == CHESSTABLEDIM) {
		solutions.push_back(*currentNodeRecord->GetOwnedNodePtr());
		
		//solutionHasBeenFound = true;
	}
	else {
		currentNodeRecord->GenerateNodeRecords();
		for (std::vector<NodeRecord*>::iterator it = currentNodeRecord->childNodeRecords->begin(); it != currentNodeRecord->childNodeRecords->end(); it++) {
			if (NRListContainsNode(closedNodeRecords, (*it)->GetOwnedNodePtr())) {
				continue;
			}
			else if (NRListContainsNode(openNodeRecords, (*it)->GetOwnedNodePtr())) {
				continue;
			}
			else {
				openNodeRecords->push_back((*it));
			}
		}
	}
	closedNodeRecords->push_back((*(openNodeRecords->begin() + currentNRindex)));
	openNodeRecords->erase(openNodeRecords->begin() + currentNRindex);
	return;

}

std::wstring& PathFinderAStar::PrintDisplay() {
	buffer.clear();
	buffer.append(L"   OPEN NODES "+ std::to_wstring(openNodeRecords->size())+L"  \n\n");
	/*
	buffer.append(L" QUEENS   \t COST   \t ESTIMATED COST   \n\n");
	for (std::vector<NodeRecord*>::iterator it = openNodeRecords->begin(); it != openNodeRecords->end(); it++) {
		buffer.append(std::to_wstring((*it)->GetOwnedNodePtr()->GetPlacedQueens()) + L"  \t " + std::to_wstring((*it)->GetCostSoFar()) + L"  \t " + std::to_wstring((*it)->GetEstimatedTotalCost()) + L"\n");
	}
	*/

	buffer.append(L"   CLOSED NODES " + std::to_wstring(closedNodeRecords->size()) + L"  \n\n");
	/*
	buffer.append(L" QUEENS   \t COST   \t ESTIMATED COST   \n\n");
	for (std::vector<NodeRecord*>::iterator it = closedNodeRecords->begin(); it != closedNodeRecords->end(); it++) {
		buffer.append(std::to_wstring((*it)->GetOwnedNodePtr()->GetPlacedQueens()) +L"  \t " + std::to_wstring((*it)->GetCostSoFar()) + L"  \t " + std::to_wstring((*it)->GetEstimatedTotalCost()) + L"\n");
	}
	*/
	buffer.append(L" number of queens last node record: " + nOfQueensCurrentNode + L"  \n\n");
	buffer.append(L"number of solutions: " + std::to_wstring(solutions.size()) + L"  \n\n");

	if (solutions.size()!=0 && openNodeRecords->size()== 0) {
		buffer.append(L"\n press a key to start seeing solutions, then the left and right arrows to slide in between\n\n\n" );
	}
	if (solutionViewingStarted) {
		Node nodeToDisplay=solutions.at(solutionToViewIndex);
		int queenIndex=0;
		bool queenHasBeenPlaced = false;
		buffer.append(L"solution index: "+std::to_wstring(solutionToViewIndex+1)+L"\n\n\n");

		QueenPosition queen=nodeToDisplay.GetQueenPositionAtIndex(queenIndex);
		buffer.append(L"+---+---+---+---+---+---+---+---+\n");
		for (int r = 0; r < CHESSTABLEDIM; r++) {
			buffer.append(L"|");
			for (int c = 0; c < CHESSTABLEDIM; c++) {
				if (r == queen.r && c == queen.c) {
					buffer.append(L" o |");
					queenHasBeenPlaced = true;

				}
				else {
					buffer.append(L"   |");
				}
				if (queenIndex < CHESSTABLEDIM - 1 && queenHasBeenPlaced)
				{
					queenIndex++;
					queen = nodeToDisplay.GetQueenPositionAtIndex(queenIndex);
					queenHasBeenPlaced = false;
				}
			}
			buffer.append(L"\n+---+---+---+---+---+---+---+---+\n");

		}
	}
	
	return buffer;
}
int PathFinderAStar::GetOpenNodeRecordsLength() {
	return openNodeRecords->size();
}

int PathFinderAStar::GetSolutionsLength() {
	return solutions.size();
}

void PathFinderAStar::ShiftSolutionIndex(char direction) {
	
	switch (direction) {
	case 'R':
	{
		if (solutionToViewIndex == solutions.size() - 1) {
			solutionToViewIndex = 0;
		}
		else {
			solutionToViewIndex++;
		}
		break;
	}
	case'L':
	{
		if (solutionToViewIndex == 0) {
			solutionToViewIndex = solutions.size() - 1;
		}
		else {
			solutionToViewIndex--;
		}
		break;
	}
	default:
		break;
	}
}


