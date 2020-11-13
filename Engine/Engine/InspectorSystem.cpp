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
				int pos = std::stoi(buff);
				rS->SetPosX(pos);
			}
			catch (const std::invalid_argument& e) {}
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

	for (int i = 0; i < 3; i++) 
		SetWindowText(tb[i], L"0");
}

void InspectorSystem::SetRenderSystem(RenderSystem* renderer) {
	rS = renderer;
	//rS = renderer;
}

