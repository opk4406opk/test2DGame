#include "stdafx.h"
#include "main.h"
#include <boost/format.hpp>
//
// Globals
//
IDirect3DDevice9* Device = 0;
bool isGameSetupEnd = false;
// camera
Simple2DCamera* mainCamera;
//
// Framework Functions Prototype
//
bool Setup();
void Cleanup();
bool Display(float timeDelta);
//
void DebugInfos(float timeDelta);
FPSManager fpsManager;

// window procedure prototype func.
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	if (!d3d::InitD3D(hinstance,
		1024, 768, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, L"InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, L"Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();
	Device->Release();

	return 0;
}


bool Setup()
{	
	//
	// Set projection matrix.
	//
	D3DXMATRIX proj;
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, 1024.0f, 768.0f, 0.0f, 0.0f, 1.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	//
	// test for 2d game class
	
	mainCamera = Simple2DCamera::GetInstance();
	mainCamera->SetDevice(Device);
	mainCamera->Init(1024.0f, 768.0);

	//
	KojeomD3DUtil::GetInstance()->SetD3DDevice(Device);
	//
	GameStateManager::GetInstance()->InsertState(GAME_STATE::MAIN_MENU);
	//
	ColliderManager::GetInstance();
	//
	isGameSetupEnd = true;
	return true;
}

// 프로그램 종료 시 호출되는 클린업.
void Cleanup()
{
	//gui shutdown..
	KojeomGameUI::Release();
}

bool Display(float timeDelta)
{
	if (Device) // Only use Device methods if we have a valid device.
	{
		fpsManager.CalcFPS();
		// Instruct the device to set each pixel on the back buffer black -
		// D3DCLEAR_TARGET: 0x00000000 (black) - and to set each pixel on
		// the depth buffer to a value of 1.0 - D3DCLEAR_ZBUFFER: 1.0f.
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();
		//ImGui
		KojeomGameUI::NewFrame();
		//
		DebugInfos(timeDelta);
		GameState* const curState = GameStateManager::GetInstance()->GetCurrentState();
		if (curState != nullptr) curState->Update();
		//
		KojeomGameUI::EndFrame();
		KojeomGameUI::Render();
		//
		Device->EndScene();
		// Swap the back and front buffers.
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

void DebugInfos(float timeDelta) {
	KojeomGameUI::UIBegin("[DEBUG]::timeDelta", 0, ImVec2(0, 0), 0.65f, 0);
	KojeomGameUI::UIText(boost::str(boost::format("timeDelta : %f") % timeDelta));
	KojeomGameUI::UIText(boost::str(boost::format("FPS : %d") % fpsManager.GetFPS()));
	KojeomGameUI::UIEnd();
}

//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (isGameSetupEnd)
	{
		// gui input process..
		KojeomGameUI::InputProcess(hwnd, msg, wParam, lParam);
		// 현재 game state에 대한 입력처리.
		GameState* curState = GameStateManager::GetInstance()->GetCurrentState();
		if (curState != nullptr) curState->InputUpdate(msg, wParam);
	}
	
	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) ::DestroyWindow(hwnd);
		break;
	case WM_LBUTTONDOWN:
		//POINT mousePoint;
		//GetCursorPos(&mousePoint);
		//ScreenToClient(hwnd, &mousePoint);
		//// ray test.
		//ray = KojeomGameUI::CalcPickingRay(mousePoint.x, mousePoint.y, Device);
		//kojeomDebugLogger::MessageBoxLog(L"마우스 왼쪽 버튼 클릭.");
		break;
	case WM_SIZE:
		KojeomGameUI::ResetRendering();
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}
