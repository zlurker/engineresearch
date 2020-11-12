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

		int pos;
		bool is_ok = false;
		try {
			pos = std::stoi(buff);
			is_ok = true;
		}
		catch (int e) {

		}

		if (is_ok)
			rS->SetPosX(pos);
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

