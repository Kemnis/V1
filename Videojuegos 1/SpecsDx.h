#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: SpecsDx.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SpecsDx_H_
#define _SpecsDx_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <string>
using namespace std;
using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: SpecsDx
////////////////////////////////////////////////////////////////////////////////
class SpecsDx
{
public:
	SpecsDx();
	SpecsDx(const SpecsDx&);
	~SpecsDx();

	string Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	int GetScreenWidth();
	int GetScreenHeight();

	void TurnZBufferOn();
	void TurnZBufferOff();
	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();
	//ParaSkyDome
	void TurnOnCulling();
	void TurnOffCulling();

	void GetVideoCardInfo(char*, int&);
	void EnableSecondBlendState();

private:
	int m_screenWidth;
	int m_screenHeight;
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;

	//Nuevas variables
	ID3D11DepthStencilState* m_depthDisabledStencilState;
	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;
	//Para SkyDome
	ID3D11RasterizerState * m_rasterStateNoCulling;
	ID3D11BlendState* m_alphaBlendState2;

};

#endif