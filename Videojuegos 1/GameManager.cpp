#include "stdafx.h"
//using namespace libZPlay;//Se declara que se usara la libreria de libZPlay para reproductor de musica

GameManager::GameManager(){
	Dx11 = 0;
	hwnd = 0;
	Entity = 0;
}

GameManager::~GameManager(){}

string GameManager::StartEngine(int screenWidth, int screenHeight, HWND hWnd, char Mode){
	hwnd = hWnd;
	Dx11 = new SpecsDx;				 //Descripción:Se inicializa toda la configuracion del entorno grafico
	RS = Dx11->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hWnd, Mode, SCREEN_DEPTH, SCREEN_NEAR);
	if (RS != "S_OK")
		return Error("No se pudo inicializar DirectX11");
	else
	{
		RS = InitEntity();
		if (RS != "S_OK")
			return Error("No se pudo inicializar la Escena");
		else
			_RPT0(0, "Scene Started!\n");

		_RPT0(0, "Directx Device & Context Started!\n");
	}
	return "S_OK";
}

string GameManager::InitEntity()
{
	Entity = new EntityManager(Dx11, hwnd);
	Entity->Start();
	return "S_OK";
}

string GameManager::FrameProcess()
{
	RS = Entity->Calculate();
	if (RS != "S_OK")
		return Error("No se pudo procesar la entidad");
	return "S_OK";
}

string GameManager::FrameRender()
{
	RS = Entity->Run();
	if (RS != "S_OK")
		return Error("No se pudo Renderear la entidad");
	return "S_OK";
}

//Every object call  it's shutdown process
void GameManager::Shutdown()
{
}
