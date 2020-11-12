#include "InspectorSystem.h"


InspectorSystem::InspectorSystem()
{
}

InspectorSystem::~InspectorSystem()
{
}

void InspectorSystem::InspectorThread()
{
	while (true) {
		TCHAR buff[1024];
		GetWindowText(textbox, buff, 1024);
		int pos =std::stoi(buff);

		//OutputDebugString(buff);
	}
}

void InspectorSystem::StartInspectorThread()
{
	inspectorThread = std::thread(&InspectorSystem::InspectorThread, this);
}

void InspectorSystem::SetTextBox(HWND tb) {
	textbox = tb;
	SetWindowText(textbox, L"0.00f");
}

void InspectorSystem::SetRenderSystem(RenderSystem* renderer) {
	rS = renderer;
	//rS = renderer;
}

