#pragma once
#include <Windows.h>
#include <thread>

class InspectorSystem
{

public:
	InspectorSystem();
	~InspectorSystem();

	void InspectorThread();
	void StartInspectorThread();
	void SetTextBox(HWND tb);

	HWND textbox;
	std::thread inspectorThread;

};

