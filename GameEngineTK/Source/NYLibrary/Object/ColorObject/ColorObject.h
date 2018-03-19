#pragma once
#include <D3DX10math.h>
#include <DirectXColors.h>
#include "../Object.h"

namespace NYLibrary
{
	class ColorObject : public virtual Object
	{
	public:
		//色を設定する
		void SetColor(const D3DXVECTOR4& color) { this->color = color; }
		//色を取得する
		const D3DXVECTOR4& GetColor() { return color; }
	private:
		//色
		D3DXVECTOR4 color;
	};
}