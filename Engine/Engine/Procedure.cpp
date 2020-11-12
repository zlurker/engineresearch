#include "Procedure.h"


LRESULT CALLBACK Win::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RenderSystem* rS;
	rS = (RenderSystem*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (message == WM_NCCREATE) {
		RenderSystem* rS = (RenderSystem*)((CREATESTRUCT*)lParam)->lpCreateParams;
		rS->SetHandle(hWnd);
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)rS);
		//::MessageBox(0, L"Set up RS.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}

	switch (message)
	{

	case WM_CREATE:
	{

		rS->BeginLoop();
		//::MessageBox(0, L"Loop begun.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		//return (LRESULT)0;
		//return DefWindowProc(hWnd, message, wParam, lParam);
	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK Win::MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT Win::InspectorSystemProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);

		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 184));
		RECT header;

		header.bottom = 200;
		header.top = 0;
		header.left = 0;
		header.right = 400;

		DrawTextW(hdc, L"Transform", 9, &header, DT_LEFT);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
