// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "LightShader.h"
#include "TextureShader.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void firstPass();
	void finalPass();
	void secondPass();
	void gui();

private:
	CubeMesh* cubeMesh;
	OrthoMesh* orthoMesh;
	OrthoMesh* playerOrthoMesh;
	LightShader* lightShader;
	TextureShader* textureShader;
	TextureShader* playerDotShader;

	RenderTexture* renderTexture;
	RenderTexture* playerRenderTexture;

	Camera* birdsEyeCamera;
	Light* light;
};

#endif