#pragma once
#include "Execute.h"

class ExeRect : public Execute
{
private:
	class ColorBuffer;

public:
	ExeRect(ExecuteValues* values);
	~ExeRect();

	// Execute을(를) 통해 상속됨
	 void Update() ;
	 void PreRender() ;
	 void Render() ;
	 void PostRender() ;
	 void ResizeScreen() ;

private:
	Shader * shader;
	WorldBuffer* worldBuffer;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	UINT vertexCount, indexCount;

	VertexColor* vertices;
	UINT* indices;

	ColorBuffer* colorBuffer;

private:
	class ColorBuffer : public ShaderBuffer {
	public:
		ColorBuffer()
			:ShaderBuffer(&Data,sizeof(Data))
		{
			Data.Color = D3DXCOLOR(1, 1, 1, 1);
		}
		~ColorBuffer() 
		{
		
		}
		struct Struct {
			D3DXCOLOR Color;
		} Data;
	};

};