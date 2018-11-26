// Light shader.h
// Basic single light shader setup
#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;


class TessellationShader : public BaseShader
{
private:
	struct TessellationBufferType
	{
		int tessellationFactor;
		XMFLOAT3 padding;
		XMFLOAT4 cameraPos;
	};

	struct TimeBufferType
	{
		XMFLOAT4 timeBufferData;
	};

public:

	TessellationShader(ID3D11Device* device, HWND hwnd);
	~TessellationShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, int tessellationAmount, XMFLOAT4 timeVars, XMFLOAT4 cameraPos);

private:
	void initShader(WCHAR* vsFilename, WCHAR* psFilename);
	void initShader(WCHAR* vsFilename, WCHAR* hsFilename, WCHAR* dsFilename, WCHAR* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* tessellationBuffer;
	ID3D11Buffer* timeBuffer;
};
