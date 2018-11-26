// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "LightShader.h"


class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	void inputMan();

	bool frame();

protected:
	bool render();
	void gui();

private:
	XMFLOAT3 lightPos;
	XMFLOAT4 lightColour;
	LightShader* shader;
	PlaneMesh* mesh;
	Light* light;
};

#endif