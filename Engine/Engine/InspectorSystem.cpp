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
			TCHAR test[1024];
			swprintf(test, 1024, L"%s %d %s end",L"This is", i,buff);

			OutputDebugString(test);
			//OutputDebugString(buff);
			

			try {
				int pos = std::stoi(buff);
				rS->SetPos(pos, i);
			}
			catch (const std::invalid_argument& e) {
				TCHAR s[256];

				swprintf(s, 256, L"There is %d invalid args", i);
				OutputDebugString(s);
			}
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

