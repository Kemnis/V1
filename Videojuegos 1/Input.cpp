#include "stdafx.h"

Input::Input()
{
	scroll = 0;
}

Input::~Input() {}

bool Input::Initialize(int screenWidth, int screenHeight)
{
	HRESULT result;
	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;
	m_mouseXOld = 0;
	m_mouseYOld = 0;

	return true;
}

bool Input::Update()
{
	BOOL result;
	//Este arreglo tiene que tecla se presiono
	char keystate[256];
	//Instanciar el mouse con esta funcion
	result = GetKeyboardState((PBYTE)keystate);

	//Si manda 0 hay un error en el teclado
	if (result = 0)
		return false;

	//Pasar el buffer del teclado a un arreglo boleano
	for (int i = 0; i<256; i++) {
		KEYS[i] = keystate[i] & 0x8000;
	}
}