#include "stdafx.h"
#include "ExeRect.h"

ExeRect::ExeRect(ExecuteValues * values)
	:Execute(values)
	,vertexCount(4),indexCount(6)
{
	shader = new Shader(Shaders+L"003_Color.hlsl");
	worldBuffer = new WorldBuffer();

	colorBuffer = new ColorBuffer();

	vertices = new VertexColor[vertexCount];
	vertices[0].Position = D3DXVECTOR3(0, 0, 0);
	vertices[1].Position = D3DXVECTOR3(0, 1, 0);
	vertices[2].Position = D3DXVECTOR3(1, 0, 0);
	vertices[3].Position = D3DXVECTOR3(1, 1, 0);

	vertices[0].Color = D3DXCOLOR(0, 0, 0,1);
	vertices[1].Color = D3DXCOLOR(0, 1, 0,1);
	vertices[2].Color = D3DXCOLOR(1, 0, 0,1);
	vertices[3].Color = D3DXCOLOR(1, 1, 0,1);

	indices = new UINT[indexCount]{ 0,1,2,2,1,3 };

	//CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexColor) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		
		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;	//单捞磐 林家

		HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	//CreateIndexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = indices;	//单捞磐 林家

		HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
		assert(SUCCEEDED(hr));
	}
}

ExeRect::~ExeRect()
{
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);

	SAFE_DELETE_ARRAY(indices);
	SAFE_DELETE_ARRAY(vertices);

	SAFE_DELETE(colorBuffer);

	SAFE_DELETE(worldBuffer);
	SAFE_DELETE(shader);
}

void ExeRect::Update()
{
}

void ExeRect::PreRender()
{

}

void ExeRect::Render()
{
	UINT stride = sizeof(VertexColor);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	colorBuffer->SetPSBuffer(0);	//register num
	worldBuffer->SetVSBuffer(1);
	shader->Render();

	//角力 弊副 内靛
	D3D::GetDC()->DrawIndexed(indexCount, 0, 0);
}

void ExeRect::PostRender()
{
	ImGui::Begin("Color");
	{
		ImGui::SliderFloat3("Color", (float*)&colorBuffer->Data.Color, 0, 1);
	}
	ImGui::End();
}

void ExeRect::ResizeScreen()
{
}
