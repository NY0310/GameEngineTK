/// <summary>
/// OBJ�t�@�C���̓ǂݍ��ݕ`��
/// 2017/08/09
/// yusuke nakata
/// </summary>

#pragma once
#include <memory>
#include <vector>
#include <map>
#include "../ShaderManager/ShaderManager.h"
#include "../SceneGraph/Node/GameObjectNode.h"
#include "../Light/Light.h"
#include "../../NYLibrary/Math/Lerp.h"

using namespace Microsoft::WRL;

namespace NYLibrary
{
	class Obj : public GameObjectNode
	{
	protected:

		//���_�̍\����
		struct SimpleVertex
		{
			D3DXVECTOR3 Pos; //�ʒu
			D3DXVECTOR3 Normal;//�@��
			D3DXVECTOR2 Tex; //�e�N�X�`���[���W
		};



		//Simple�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
		struct SIMPLESHADER_CONSTANT_BUFFER
		{
			D3DXMATRIX w;//���[���h�s��
			D3DXMATRIX wvp;//���[���h����ˉe�܂ł̕ϊ��s��
			D3DXMATRIX wlp;//���[���h�E�h���C�g�r���[�h�E�v���W�F�N�V�����̍���
			D3DXMATRIX wlpt;//���[���h�E�h���C�g�r���[�h�E�v���W�F�N�V�����E�e�N�X�`�����W�s��̍���
			D3DXVECTOR4 lightDir;//���C�g����
			D3DXVECTOR4 eyesPos;//�J�����ʒu
			ALIGN16 float frame;
		};




		//�I���W�i���@�}�e���A���\����
		struct MY_MATERIAL
		{
			CHAR szName[111];
			D3DXVECTOR4 Ka;//�A���r�G���g
			D3DXVECTOR4 Kd;//�f�B�q���[�Y
			D3DXVECTOR4 Ks;//�X�y�L�����[
			CHAR szTextureName[110];//�e�N�X�`���[�t�@�C����
		};


		//�I���W�i�����b�V��
		struct MY_MESH
		{
			DWORD dwNumVert;
			DWORD dwNumFace;
			ID3D11Buffer* pVertexBuffer;
			ID3D11Buffer* pIndexBuffer;
		};

		struct MeshAndTriangles
		{
			std::vector<Triangle> triangles;
			MY_MESH mesh;
			D3DXVECTOR3 localSize;
		};

		using Vector3 = DirectX::SimpleMath::Vector3;
	public:
		Obj(LPSTR filename);
		Obj() = delete;
		virtual ~Obj();
		//�I�u�W�F�N�g�𐶐����q���Ƃ��ēo�^
		void CreateAddChild();
		//����������
		virtual void Initialize();
		//OBJ�t�@�C���ǂݍ���
		void LoadOBJFile(LPSTR filename) { InitStaticMesh(filename, &mesh); }
		//�e�N�X�`���ǂݍ���
		void LoadTextuerFile(LPSTR filename) { D3DX11CreateShaderResourceViewFromFileA(device, filename, nullptr, nullptr, texture.GetAddressOf(), nullptr); }
		//�`��
		void Render();
		//�[�x�l�̕`��
		void ShadowRender();
		//�j��J�E���g��ݒ�
		void SetBreakTime(float breakTime) {
	/*	breakLerp->SetTime(this->breakTime); */useBreakLerp = false;	}
		//�j��J�E���g���擾
		int GetBreakTime() { return breakTime;}
		//�j����J�n
		void BreakStart() { breakLerp->EnableUpdate(); useBreakLerp = true; }
		void BreakClear() { breakLerp->Clear(); useBreakLerp = true;}
		//�j�󂪏I�������
		bool IsBreakEnd() { return breakLerp->IsLerpEnd(); }
		//�j�󂳂�I������Ƃ��ɌĂяo�����
		virtual void OnBreakEnd(){}
		//�j�󂳂ꂽ�Ɣ��f�����o�ߎ���
		static const int BREAK_CNT = 60;

	private:
		//�V�F�[�_�[�쐬
		HRESULT CreateShader();
		//���_�C���v�b�g���C�A�E�g�쐬
		HRESULT CreateVertexInputLayout(ID3DBlob * compiledshader);
		//�R���X�^���g�o�b�t�@�쐬
		ID3D11Buffer* CreateConstantBuffer(UINT size);
		//�T���v���[�쐬
		HRESULT CreateSampler();
		//OBJ�t�@�C���ǂݍ���
		HRESULT InitStaticMesh(LPSTR FileName, MY_MESH * pMesh);
		//�}�e���A���t�@�C���ǂݍ���
		HRESULT LoadMaterialFromFile(LPSTR FileName, MY_MATERIAL * pMarial);
	protected:
		/// <summary>
		/// ���b�V��
		/// </summary>
		MY_MESH mesh;//���b�V�����
		MY_MATERIAL material;//�}�e���A���\����
		ComPtr<ID3D11VertexShader> vertexShader;//�o�b�e�b�N�X�V�F�[�_�[
		ComPtr<ID3D11PixelShader> pixelShader;//�s�N�Z���V�F�[�_�[
		ComPtr<ID3D11GeometryShader> geometryShader;//�W�I���g���V�F�[�_�[
		ComPtr<ID3D11Buffer> constantBuffer;//�R���X�^���g�o�b�t�@
		ComPtr<ID3D11InputLayout> vertexLayout;//���_�C���v�b�g���C�A�E�g
		ComPtr<ID3D11SamplerState> sampleLimear;//�e�N�X�`���T���v��
		ComPtr<ID3D11ShaderResourceView> texture;//�e�N�X�`��
		static std::map<LPSTR, MeshAndTriangles> modelDatas;//OBJ���f�����
		std::vector<Triangle> triangles;
		
		float breakTime;//�󂷃J�E���g
		static const float MAX_BREAK_CNT;//�j��J�E���g�̏��

		/// <summary>
		/// �Ϗ�
		/// </summary>
		ID3D11Device* device = Devices::Get().Device().Get();//�f�o�C�X
		ID3D11DeviceContext* deviceContext = Devices::Get().Context().Get();//�f�o�C�X�R���e�L�X�g
		FollowCamera* camera = FollowCamera::GetInstance();

		D3DXMATRIX clipToUV;//�e�N�X�`���s��
		D3DXMATRIX mLight;//���C�g�s��
		std::shared_ptr<Lerp> breakLerp;//�j��̃��[�v
		bool useBreakLerp;//�j��̃��[�v���g�p���邩
	};

};
