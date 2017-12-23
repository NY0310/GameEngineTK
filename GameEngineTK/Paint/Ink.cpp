#include "Ink.h"



HRESULT Campus::InitD3D()
{
	shadermanager = ShaderManager::Get();
	//�C���N�p�e�N�X�`�����쐬
	D3D11_TEXTURE2D_DESC inkdesc;
	ZeroMemory(&inkdesc, sizeof(D3D11_TEXTURE2D_DESC));
	inkdesc.Width = Devices::Get().Width() * 2;
	inkdesc.Height = Devices::Get().Height() * 2;
	inkdesc.MipLevels = 1;
	inkdesc.ArraySize = 1;
	inkdesc.MiscFlags = 0;
	inkdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	inkdesc.SampleDesc.Count = 1;
	inkdesc.SampleDesc.Quality = 0;
	inkdesc.Usage = D3D11_USAGE_DEFAULT;
	inkdesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	inkdesc.CPUAccessFlags = 0;

	device->CreateTexture2D(&inkdesc, nullptr, &inkTex);

	//�C���N�e�N�X�`���[�p�@�����_�[�^�[�Q�b�g�r���[�쐬
	D3D11_RENDER_TARGET_VIEW_DESC inkDescRT;
	inkDescRT.Format = inkdesc.Format;
	inkDescRT.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	inkDescRT.Texture2D.MipSlice = 0;

	device->CreateRenderTargetView(inkTex, &inkDescRT, &inkTexRTV);


	//�[�x�e�N�X�`���p�@�[�x�X�e���V���r���[�e�N�X�`���[�쐬
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = Devices::Get().Width() * 2;
	descDepth.Height = Devices::Get().Height() * 2;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	device->CreateTexture2D(&descDepth, nullptr, &inkTexDS);

	////�C���N�p�e�N�X�`���@�V�F�[�_�[���\�[�X�r���[�쐬�i�e�N�X�`���[�m�F���p�j	
	D3D11_SHADER_RESOURCE_VIEW_DESC inkSRVDesc;
	ZeroMemory(&inkSRVDesc, sizeof(inkSRVDesc));
	inkSRVDesc.Format = inkdesc.Format;
	inkSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	inkSRVDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(inkTex, &inkSRVDesc, &inkTexSRV);



	//���̃e�N�X�`���[�ɑ΂��f�v�X�X�e���V���r���[(DSV)���쐬
	device->CreateDepthStencilView(inkTexDS, nullptr, &inkDSTexDSV);

	ID3DBlob *pCompiledShader = nullptr;
	//�C���N�e�N�X�`���p�o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(shadermanager.MakeShader("Resources/HLSL/Campus.hlsl", "VS", "vs_5_0", (void**)&inkVertexShader, &pCompiledShader)))return E_FAIL;
	//�C���N�e�N�X�`���p���_�C���v�b�g���C�A�E�g���Z�b�g
	D3D11_INPUT_ELEMENT_DESC inkInputLayout[]
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(inkInputLayout) / sizeof(inkInputLayout[0]);
	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(device->CreateInputLayout(inkInputLayout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &inkVertexLayout)))return E_FAIL;
	//�C���N�e�N�X�`���p�s�N�Z���V�F�[�_�[�쐬
	if (FAILED(shadermanager.MakeShader("Resources/HLSL/Campus.hlsl", "PS", "ps_5_0", (void**)&inkPixelShader, &pCompiledShader)))return E_FAIL;

	//�C���N�p�e�N�X�`���p�R���X�^���g�o�b�t�@
	D3D11_BUFFER_DESC Inkcb;
	Inkcb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Inkcb.ByteWidth = sizeof(InkData);
	Inkcb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Inkcb.MiscFlags = 0;
	Inkcb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(device->CreateBuffer(&Inkcb, nullptr, &inkConstantBuffer)))
	{
		return E_FAIL;
	}

	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	device->CreateSamplerState(&SamDesc, &sampleLimear);

	//�C���N�e�N�X�`�����쐬	
	if (FAILED(D3DX11CreateShaderResourceViewFromFileA(device, "Resources/PNG/pink1.png", nullptr, nullptr, &inkTexture, nullptr)))
	{
		return E_FAIL;
	}

	return S_OK;

}


void Campus::CreateInk(D3DXVECTOR4& Color, D3DXVECTOR2& uv, float sclae)
{
	InkData inkdata;
	inkdata.Color = Color;
	inkdata.Uv = uv;
	inkdata.Scale  = 0.1f;
	inkdata.vertexBuffer = CreateVertexBuffer(inkdata);
	inkData.emplace_back(inkdata);
}

ID3D11Buffer* Campus::CreateVertexBuffer(InkData & inkdata)
{
	//�C���N�T�C�Y�𐳋K�f�o�C�X���W�n�ɂ���
	float uvSize = inkdata.Scale;
	D3DXVECTOR2 Uv = inkdata.Uv;

	CampusVertex vertex[] = {
		{ ChangeRegularDevice(D3DXVECTOR3(Uv.x - uvSize,Uv.y - uvSize,0)),D3DXVECTOR2(0,1) },
		{ ChangeRegularDevice(D3DXVECTOR3(Uv.x - uvSize,Uv.y + uvSize, 0)),	D3DXVECTOR2(0,0) },
		{ ChangeRegularDevice(D3DXVECTOR3(Uv.x + uvSize,Uv.y - uvSize,0)),	D3DXVECTOR2(1,1) },
		{ ChangeRegularDevice(D3DXVECTOR3(Uv.x + uvSize,Uv.y + uvSize,0)), 	D3DXVECTOR2(1,0) },
	};



	//��̒��_�Ńo�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CampusVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertex;
	
	device->CreateBuffer(&bd, &InitData, &canvasVertexBuffer);
	return canvasVertexBuffer;
}




void Campus::InkRender()
{
	D3DXMATRIX View = shadermanager.MatrixToD3DXMATRIX(camera->GetView());
	D3DXMATRIX Proj = shadermanager.MatrixToD3DXMATRIX(camera->GetProjection());

	//////�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = Devices::Get().Width() * 2;
	vp.Height = Devices::Get().Height() * 2;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &vp);
	deviceContext->OMSetRenderTargets(1, &inkTexRTV, inkDSTexDSV);

	float ClearColor[4] = { 1,1,1,0 };
	deviceContext->ClearRenderTargetView(inkTexRTV, ClearColor);
	deviceContext->ClearDepthStencilView(inkDSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//�[�x�o�b�t�@�N���A

																				  //���̃p�X�Ŏg�p����V�F�[�_�[�̓o�^
	deviceContext->VSSetShader(inkVertexShader, nullptr, 0);
	deviceContext->PSSetShader(inkPixelShader, nullptr, 0);



	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	deviceContext->PSSetSamplers(0, 1, &sampleLimear);
	deviceContext->PSSetShaderResources(0, 1, &inkTexture);

	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	deviceContext->VSSetConstantBuffers(0, 1, &inkConstantBuffer);
	deviceContext->PSSetConstantBuffers(0, 1, &inkConstantBuffer);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	deviceContext->IASetInputLayout(inkVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);



	for (auto ink : inkData)
	{

		//�C���N�̐F��n��
		D3DXVECTOR4 color = Colors::Green;
		//ink.Color = color;
		this->InkRender(ink);
	}
}



void Campus::InkRender(InkData& ink)
{
	D3DXMATRIX View = shadermanager.MatrixToD3DXMATRIX(camera->GetView());
	D3DXMATRIX Proj = shadermanager.MatrixToD3DXMATRIX(camera->GetProjection());





	D3D11_MAPPED_SUBRESOURCE pData;
	InkDataBuffer cb;
	if (SUCCEEDED(deviceContext->Map(inkConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//cb.Uv = ink.Uv;
		D3DXVECTOR4 color = Colors::Blue;
		cb.Color = ink.Color;
		//cb.Scale = ink.Scale;
		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(InkDataBuffer));
		deviceContext->Unmap(inkConstantBuffer, 0);

	}
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(CampusVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &ink.vertexBuffer, &stride, &offset);

	//�v���~�e�B�u�������_�����O
	deviceContext->Draw(4, 0);


}

