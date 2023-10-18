//============================================
//
// �Q�[���̃X�R�A����[game_score.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "game_score.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//========================
// �R���X�g���N�^
//========================
CGameScore::CGameScore() : CScore(TYPE_GAMESCORE, PRIORITY_UI)
{

}

//========================
// �f�X�g���N�^
//========================
CGameScore::~CGameScore()
{

}

//========================
// ����������
//========================
HRESULT CGameScore::Init(void)
{
	if (FAILED(CScore::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CGameScore::Uninit(void)
{
	// �I������
	CScore::Uninit();
}

//========================
// �X�V����
//========================
void CGameScore::Update(void)
{
	// �X�V����
	CScore::Update();
}

//========================
// �`�揈��
//========================
void CGameScore::Draw(void)
{
	// �`�揈��
	CScore::Draw();
}

//========================
// ���̐ݒ菈��
//========================
void CGameScore::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size)
{
	// ����ݒ菈��
	CScore::SetData(pos, rot, size);
}