#pragma once
#include <Windows.h>
#include <thread>
#include "RenderSystem.h"
#include <sstream>

class InspectorSystem
{

public:
	InspectorSystem();
	~InspectorSystem();

	void InspectorThread();
	void StartInspectorThread();
	void SetTextBox(HWND tb);
	void SetRenderSystem(RenderSystem* renderer);

	HWND textbox;
	std::thread inspectorThread;
	RenderSystem* rS;
	//RenderSystem rS;

};

