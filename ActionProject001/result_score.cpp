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
#include "result_score.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

#include "game.h"



//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CResultScore* CResultScore::m_pResultScore = nullptr;						// �X�R�A�̏��

//========================
// �R���X�g���N�^
//========================
CResultScore::CResultScore() : CScore(TYPE_GAMESCORE, PRIORITY_UI)
{

}

//========================
// �f�X�g���N�^
//========================
CResultScore::~CResultScore()
{

}

//========================
// ����������
//========================
HRESULT CResultScore::Init(void)
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
void CResultScore::Uninit(void)
{
	// �I������
	CScore::Uninit();

	// �Q�[���̃X�R�A�� NULL �ɂ���
	m_pResultScore = nullptr;
}

//========================
// �X�V����
//========================
void CResultScore::Update(void)
{
	// �X�V����
	CScore::Update();
}

//========================
// �`�揈��
//========================
void CResultScore::Draw(void)
{
	// �`�揈��
	CScore::Draw();
}

//========================
// ���̐ݒ菈��
//========================
void CResultScore::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fShift)
{
	// ����ݒ菈��
	CScore::SetData(pos, rot, size, fShift);

	// �X�R�A��ݒ肷��
	CScore::SetScore(CGame::GetScore());
	CScore::SetScoreDisp(CGame::GetScore());

	// ���l�𔽉f����
	CScore::Update();
}

//========================
// �X�R�A�̎擾����
//========================
CResultScore* CResultScore::Get(void)
{
	if (m_pResultScore != nullptr)
	{ // �Q�[���̃X�R�A�̏�񂪂���ꍇ

		// �Q�[���̃X�R�A�̃|�C���^��Ԃ�
		return m_pResultScore;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// �Q�[���̃X�R�A�̃|�C���^��Ԃ�
		return m_pResultScore;
	}
}

//========================
// ��������
//========================
CResultScore* CResultScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fShift)
{
	if (m_pResultScore == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pResultScore = new CResultScore;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (m_pResultScore != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pResultScore->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pResultScore->SetData(pos, rot, size, fShift);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return m_pResultScore;
}