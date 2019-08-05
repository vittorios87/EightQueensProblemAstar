#include "pch.h"
#include "EightQueensLoop.h"

EightQueensLoop* EightQueensLoop::loopInstance;


EightQueensLoop::EightQueensLoop()
{
}
EightQueensLoop * EightQueensLoop::GetInstance()
{
	if (loopInstance == nullptr)
		loopInstance = new EightQueensLoop();

	return loopInstance;
}

void EightQueensLoop::Start() {
	myDisplay = new Display();
	myInputManager = InputManager::GetInstance();
	myPathFinderEightQs = new PathFinderAStar();
	myDisplay->cls();
	myDisplay->printBuffer(myPathFinderEightQs->PrintDisplay());
	Loop();
}
void EightQueensLoop::Input() {
	myInputManager->Input();

}

void EightQueensLoop::Update() {

	pressedKey = Key::None;

	if (myInputManager->ButtonPressed())
	{
		pressedKey = myInputManager->GetButtonPressed();
	}
	/*
	if (pressedKey != Key::None)
	{
		if (myPathFinderEightQs->GetOpenNodeRecordsLength() > 0) {
			myPathFinderEightQs->PathFinderStep();
			myDisplay->cls();
			myDisplay->printBuffer(myPathFinderEightQs->PrintDisplay());
		}
		//displayBuffer.clear();
		//displayBuffer.append(L"ciao");
	}
	*/
	if (myPathFinderEightQs->GetOpenNodeRecordsLength() > 0) {
		myPathFinderEightQs->PathFinderStep();
		displayToRefresh = true;
		
	}
	if (myPathFinderEightQs->GetSolutionsLength() != 0 && myPathFinderEightQs->GetOpenNodeRecordsLength() == 0) {
		if (pressedKey != Key::None && myPathFinderEightQs->solutionViewingStarted == false)
		{
			myPathFinderEightQs->solutionViewingStarted = true;
			displayToRefresh = true;

		}
		if (myPathFinderEightQs->solutionViewingStarted == true) {
			if (pressedKey == Key::Right || pressedKey == Key::Up) {
				myPathFinderEightQs->ShiftSolutionIndex('R');
				displayToRefresh = true;

			}
			if (pressedKey == Key::Left || pressedKey == Key::Down) {
				myPathFinderEightQs->ShiftSolutionIndex('L');
				displayToRefresh = true;


			}
		}
	}
	
	
}
void EightQueensLoop::Render() {
	if (displayToRefresh) {
		myDisplay->cls();
		myDisplay->printBuffer(myPathFinderEightQs->PrintDisplay());
		displayToRefresh = false;
	}
}

void EightQueensLoop::Loop() {
	while (true) {
		Input();
		Update();
		Render();
	}
}


EightQueensLoop::~EightQueensLoop()
{
}


