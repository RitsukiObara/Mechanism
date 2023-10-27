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

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define NUMBER_SHIFT		(50.0f)							// �����̂��炷��

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CGameScore* CGameScore::m_pGameScore = nullptr;						// �X�R�A�̏��

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

	// �Q�[���̃X�R�A�� NULL �ɂ���
	m_pGameScore = nullptr;
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
	CScore::SetData(pos, rot, size, NUMBER_SHIFT);
}

//========================
// �X�R�A�̎擾����
//========================
CGameScore* CGameScore::Get(void)
{
	if (m_pGameScore != nullptr)
	{ // �Q�[���̃X�R�A�̏�񂪂���ꍇ

		// �Q�[���̃X�R�A�̃|�C���^��Ԃ�
		return m_pGameScore;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// �Q�[���̃X�R�A�̃|�C���^��Ԃ�
		return m_pGameScore;
	}
}

//========================
// ��������
//========================
CGameScore* CGameScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size)
{
	if (m_pGameScore == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pGameScore = new CGameScore;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (m_pGameScore != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pGameScore->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pGameScore->SetData(pos, rot, size);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return m_pGameScore;
}