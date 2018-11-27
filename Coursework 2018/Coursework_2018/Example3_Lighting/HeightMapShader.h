#pragma once
#include "DXF.h"

using namespace std;
using namespace DirectX;

class HeightMapShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		float padding;
		XMFLOAT4 ambientColour;
	};

	struct HeightBufferType
	{
		float heightAmount;
		XMFLOAT3 padding;
	};

public:
	HeightMapShader(ID3D11Device* device, HWND hwnd);
	~HeightMapShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, Light* light, int heightAmount);

private:
	void initShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11Buffer * heightBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
};

