#include "MyQuadMesh.h"



MyQuadMesh::MyQuadMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	initBuffers(device);
}


MyQuadMesh::~MyQuadMesh()
{
	// Run parent deconstructor
	BaseMesh::~BaseMesh();
}

void MyQuadMesh::initBuffers(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexCount = 6;
	indexCount = 8;

	VertexType_Colour* vertices = new VertexType_Colour[vertexCount];
	unsigned long* indices = new unsigned long[indexCount];

	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top right.
	vertices[0].colour = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // top left.
	vertices[1].colour = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(-1.0f, 0.0f, 0.0f);  // bottom left.
	vertices[2].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[3].position = XMFLOAT3(0.0f, 0.0f, 0.0f);  // bottom right.
	vertices[3].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[4].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // top right2.
	vertices[4].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[5].position = XMFLOAT3(1.0f, 0.0f, 0.0f);  // bottom right2.
	vertices[5].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Top right/
	indices[1] = 1;  // top left.
	indices[2] = 2;  // bottom left.
	indices[3] = 3;  // bottom right

	indices[4] = 4;  // top right 2
	indices[5] = 0;  // top left 2;
	indices[6] = 3;  // bottom left
	indices[7] = 5;  //bottom right
	

	//CreatePlane(vertices, indices);


	D3D11_BUFFER_DESC vertexBufferDesc = { sizeof(VertexType_Colour) * vertexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	vertexData = { vertices, 0 , 0 };
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc = { sizeof(unsigned long) * indexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
	indexData = { indices, 0, 0 };
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

}

// Send Geometry data to the GPU
void MyQuadMesh::sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType_Colour);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
}

void MyQuadMesh::CreatePlane(VertexType_Colour* vertices, unsigned long* indices)
{
	//for (int x = 0; x < 2; x++)
	//{	
	//		// Load the vertex array with data.
	//		vertices[x].position = XMFLOAT3(x, x + 1.0f, 0.0f);  // Top right.
	//		vertices[x].colour = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	//		vertices[x + 1].position = XMFLOAT3(x - 1.0f, x + 1.0f, 0.0f);  // top left.
	//		vertices[x + 1].colour = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	//		vertices[x + 2].position = XMFLOAT3(x - 1.0f, x, 0.0f);  // bottom left.
	//		vertices[x + 2].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	//		vertices[x + 3].position = XMFLOAT3(x, x, 0.0f);  // bottom right.
	//		vertices[x + 3].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	//		vertices[x + 4].position = XMFLOAT3(x + 1.0f, x + 1.0f, 0.0f);  // top right2.
	//		vertices[x +4].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	//		vertices[x + 5].position = XMFLOAT3(x + 1.0f, x, 0.0f);  // bottom right2.
	//		vertices[x + 5].colour = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	//		// Load the index array with data.
	//		indices[x] = 0;  // Top right/
	//		indices[x+1] = 1;  // top left.
	//		indices[x+2] = 2;  // bottom left.
	//		indices[x+3] = 3;  // bottom right

	//		indices[x + 4] = 4;  // top right 2
	//		indices[x + 5] = 0;  // top left 2;
	//		indices[x + 6] = 3;  // bottom left
	//		indices[x + 7] = 5;  //bottom right
	//}
}