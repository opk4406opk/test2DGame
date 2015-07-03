// test2DGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "test2DGame.h"

//
// Globals
//
IDirect3DDevice9* Device = 0;
//
//tests
//
GameMap* testGameMap;
TMXParser* testTmxparser;

Game2DSprite* playerSprite;
GameObjectFactory* playerFactory;
GameObject* playerObject;
Camera TheCamera(Camera::LANDOBJECT);
//
// Framework Functions Prototype
//
bool Setup();
void Cleanup();
bool Display(float timeDelta);
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
		800, 680, true, D3DDEVTYPE_HAL, &Device))
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
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, 800, 600.0f, 0.0f, 0.0f, 1.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	//
	// test
	//
	RECT rt2 = { 32, 0, 64, 32 };
	testGameMap = new GameMap("GameResources/test5.tmx", Device, "GameResources/tileb.png", rt2);
	
	playerFactory = new PlayerFactory();
	playerObject = playerFactory->ProduceGameObject(GAMEOBJECT_TYPE::PLAYER);
	playerSprite = new Game2DSprite(Device, "GameResources/ch01.png", RECT{ 0, 0, 42, 32 });
	playerObject->SetSpriteObject(playerSprite);

	return true;
}

void Cleanup()
{
	// Nothing to cleanup in this sample.
}

bool Display(float timeDelta)
{
	if (Device) // Only use Device methods if we have a valid device.
	{
		// Instruct the device to set each pixel on the back buffer black -
		// D3DCLEAR_TARGET: 0x00000000 (black) - and to set each pixel on
		// the depth buffer to a value of 1.0 - D3DCLEAR_ZBUFFER: 1.0f.
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();
		
		testGameMap->DrawMap(); // order : 0
		playerObject->Draw(); // order : 1

		Device->EndScene();
		// Swap the back and front buffers.
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);
		if (wParam == VK_LEFT)
		{
			playerObject->Move(-1, 0);	
		}
		if (wParam == VK_RIGHT)
		{
			playerObject->Move(1, 0);
			D3DXMATRIX mat;
			D3DXMatrixTranslation(&mat, -50.0f, 0.0f, 0.0f);
			Device->SetTransform(D3DTS_VIEW, &mat);
		}
		if (wParam == VK_UP)
		{
			playerObject->Move(0, -1);
		
		}
		if (wParam == VK_DOWN)
		{
			playerObject->Move(0, 1);
		
		}
		
		break;
	}
	

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}
