#pragma once

#include <windows.h>
#include "RenderSystem.h"
#include "GameObjectData.h"

namespace Win {
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT InspectorSystemProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	GameObjectData gObjD;
}