// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "TessellationShader.h"
#include "MyQuadMesh.h"
class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
	TessellationMesh * mesh;
	MyQuadMesh* quadMesh;
	TessellationShader* shader;


	int tessellationAmount; 
	XMFLOAT4 timeVars;
	XMFLOAT4 cameraPos;
};

#endif