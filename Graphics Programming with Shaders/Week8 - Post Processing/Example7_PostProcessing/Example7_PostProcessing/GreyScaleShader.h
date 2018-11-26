#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;

class GreyScaleShader : public BaseShader
{
private:


public:
	GreyScaleShader(ID3D11Device* device, HWND hwnd);
	~GreyScaleShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture);

private:
	void initShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
};
