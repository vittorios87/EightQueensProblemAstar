#pragma once
class EightQueensLoop
{

private:
	static EightQueensLoop* loopInstance;
	EightQueensLoop();

public:
	~EightQueensLoop();



	static EightQueensLoop *GetInstance();
	void Start();
	void Render();
	void Update();
	void Input();
	void Loop();

private:
	Display* myDisplay; // = new Display();
	InputManager* myInputManager; // = InputManager::GetInstance();
	PathFinderAStar* myPathFinderEightQs; // = new PathFinderAStar();
	Key pressedKey;
	std::wstring displayBuffer;

	bool displayToRefresh=false;
};

