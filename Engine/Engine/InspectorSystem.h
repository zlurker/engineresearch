#pragma once
#include <Windows.h>
class InspectorSystem
{

public:
	InspectorSystem();
	~InspectorSystem();

	void InspectorThread();
	void StartInspectorThread();

	LRESULT CALLBACK InspectorSystemProc(HWND, UINT, WPARAM, LPARAM);
};

