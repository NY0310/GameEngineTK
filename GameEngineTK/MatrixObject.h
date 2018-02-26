/// <summary>
/// �I�u�W�F�N�g�̍s��N���X
/// </summary>
#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "AStar/Math.h"
#include "FollowCamera.h"

class MatrixObject {
public:
	//�R���X�g���N�^
	MatrixObject();
	//���[���h�s��쐬
	void Update();
	//���[���h���W�ݒ�
	virtual void SetPosition(const D3DXVECTOR3& position) { transfer = position; }
	//���[���h���W�擾
	virtual const D3DXVECTOR3& GetPosition() { return transfer; }
	//�X�P�[���ݒ�
	virtual void SetScale(const D3DXVECTOR3& scale) { this->scale = scale; }
	//�X�P�[���擾
	virtual const D3DXVECTOR3& GetScale() { return  this->scale; }
	//�X�P�[���ݒ�
	virtual void SetRotation(const D3DXVECTOR3& rotation) { this->rotation = rotation; IsUseQuternion = false; }
	//�X�P�[���擾
	virtual const D3DXVECTOR3& GetRotation() { return  this->rotation; }
	//�N�H�[�^�j�I���ݒ�
	virtual void SetQuaternion(const D3DXQUATERNION& quaternion) { this->quaternion = quaternion; IsUseQuternion = true; }
	//�N�H�[�^�j�I���擾
	virtual const D3DXQUATERNION& GetQuaternion() { return  this->quaternion; }
	//���[���h���W�ݒ�
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) { transfer = Math::VectorToD3DXVECTOR3(position); }
	//���[���h���W�擾
	virtual DirectX::SimpleMath::Vector3& GetPositionMath() { return Math::D3DXVECTOR3ToVector(transfer); }
	//�X�P�[���ݒ�
	virtual void SetScale(const DirectX::SimpleMath::Vector3& scale) { this->scale = Math::VectorToD3DXVECTOR3(scale); }
	//�X�P�[���擾
	virtual const DirectX::SimpleMath::Vector3& GetScaleMath() { return Math::D3DXVECTOR3ToVector(this->scale); }
	//��]�ݒ�
	virtual void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { this->rotation = Math::VectorToD3DXVECTOR3(rotation); }
	//��]�擾
	virtual const DirectX::SimpleMath::Vector3& GetRotationMath() { return Math::D3DXVECTOR3ToVector(this->rotation); IsUseQuternion = false; }
	//�N�H�[�^�j�I���ݒ�
	virtual void SetQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { this->quaternion = Math::QuaterniontoD3DXQUATERNION(quaternion); IsUseQuternion = true; }
	//�N�H�[�^�j�I���擾
	virtual const DirectX::SimpleMath::Quaternion& GetQuaternionMath() { return  Math::D3DXQUATERNIONtoQuaternion(this->quaternion); }
	//���[���h�s��擾
	const D3DXMATRIX& GetWorldMatrix() { return worldMatrix; }
	//
	const D3DXMATRIX& GetWVP() { return wvp; }
private:
	//�S�s��쐬
	void CreateAllMatrix();
	//���[���h�s��쐬
	void CreateTransferMatrix();
	//�X�P�[���s��쐬
	void CreateScaleMatrix();
	//��]�s��쐬
	void CreateRotationMatrix();
private:
	D3DXMATRIX worldMatrix;//���[���h�s��
	D3DXVECTOR3 transfer;//�ړ���
	D3DXVECTOR3 scale;//�T�C�Y
	D3DXVECTOR3 rotation;//��]
	D3DXQUATERNION quaternion;//�N�H�[�^�j�I��
	D3DXMATRIX transferMatrix;//�ړ��s��
	D3DXMATRIX scaleMatrix;//�X�P�[���s��
	D3DXMATRIX rotationMatrix;//��]�s��
	D3DXMATRIX wvp;//���[���h�r���[�v���W�F�N�V�����s��
	bool IsUseQuternion = false;//�N�H�[�^�j�I�����g�p���邩
};