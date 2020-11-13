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
		for (int i = 0; i < 3; i++) {
			TCHAR buff[1024];
			GetWindowText(transformPosUi[i], buff, 1024);

			try {
				//int pos = std::stoi(buff);
				//rS->SetPos(pos, i);
			}
			catch (const std::invalid_argument& e) { OutputDebugString(L"Invalid arg from " + i); }
			catch (const std::out_of_range& e) {}
		}
	}
}

void InspectorSystem::StartInspectorThread()
{
	inspectorThread = std::thread(&InspectorSystem::InspectorThread, this);
}

void InspectorSystem::SetTextBox(HWND* tb) {
	transformPosUi = tb;

	for (int i = 0; i < 2; i++)
		SetWindowText(tb[i], L"0");

	SetWindowText(tb[2], L"-7");
}

void InspectorSystem::SetRenderSystem(RenderSystem* renderer) {
	rS = renderer;
	//rS = renderer;
}

