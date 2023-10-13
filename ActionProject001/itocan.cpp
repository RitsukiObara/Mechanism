//===========================================
//
// �C�g�L�����̃��C������[itocan.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "itocan.h"
#include "collision.h"
#include "useful.h"

#include "player.h"

//==============================
// �R���X�g���N�^
//==============================
CItocan::CItocan() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{

}

//==============================
// �f�X�g���N�^
//==============================
CItocan::~CItocan()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CItocan::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CItocan::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CItocan::Update(void)
{
	// �v���C���[�̔��菈��
	CheckPlayer();

	// �d�͏���
	Gravity();

	// �N���n�ʂƂ̓����蔻��
	ElevationCollision();
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CItocan::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=====================================
// �q�b�g����
//=====================================
void CItocan::Hit(void)
{

}

//=====================================
// ���̐ݒ菈��
//=====================================
void CItocan::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	CEnemy::SetData(pos);
}

//=======================================
// �v���C���[�̔��菈��
//=======================================
void CItocan::CheckPlayer(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// �v���C���[�̈ʒu���擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 rot = GetRot();		// �������擾����

	if (posPlayer.x >= pos.x)
	{ // �v���C���[�̈ʒu�����g�����E�ɂ���ꍇ

		// ������ݒ肷��
		rot.y = -D3DX_PI * 0.5f;
	}
	else
	{ // ��L�ȊO

		// ������ݒ肷��
		rot.y = D3DX_PI * 0.5f;
	}

	// ������ݒ肷��
	SetRot(rot);
}