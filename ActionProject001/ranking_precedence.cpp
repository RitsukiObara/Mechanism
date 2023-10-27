//============================================
//
// �����L���O�̏��ʕ\������[ranking_precedence.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "ranking_precedence.h"
#include "object.h"
#include "object2D.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define RANK_HEIGHT_SHIFT		(110.0f)								// �X�R�A�̏c�̂��炷��
#define RANK_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 220.0f, 0.0f))		// ���ʂ̈ʒu
#define RANK_TRANS_POS			(D3DXVECTOR3(300.0f, 220.0f, 0.0f))		// ���ʂ̎����J�ڂ̈ʒu
#define RANK_SIZE				(D3DXVECTOR3(80.0f, 40.0f, 0.0f))		// ���ʂ̃T�C�Y
#define RANK_TEXTURE_PATTERN	(0.2f)									// ���ʂ̃e�N�X�`���̃p�^�[��
#define RANK_TEXTURE			"data/TEXTURE/Rank.png"					// ���ʕ\���̃e�N�X�`��

//========================
// �R���X�g���N�^
//========================
CRankingPrece::CRankingPrece() : CObject(CObject::TYPE_RANKINGPRECE, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_apRank[nCnt] = nullptr;				// ���Ԃ̃|�C���^
	}
}

//========================
// �f�X�g���N�^
//========================
CRankingPrece::~CRankingPrece()
{

}

//========================
// ����������
//========================
HRESULT CRankingPrece::Init(void)
{
	// ���[�J���ϐ��錾
	int nTexIdx = 0;		// �e�N�X�`���̃C���f�b�N�X

	// �e�N�X�`���̐ݒ菈��
	nTexIdx = CManager::Get()->GetTexture()->Regist(RANK_TEXTURE);

	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// ��������
		m_apRank[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);

		if (m_apRank[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			//// ���̐ݒ�
			//if (CManager::GetClear() == true)
			//{ // �N���A��̏ꍇ

				m_apRank[nCnt]->SetPos(D3DXVECTOR3(RANK_POS.x, RANK_POS.y + (RANK_HEIGHT_SHIFT * nCnt), 0.0f));		// �ʒu
			//}
			//else
			//{ // ��L�ȊO

			//	m_apRank[nCnt]->SetPos(D3DXVECTOR3(RANK_TRANS_POS.x, RANK_TRANS_POS.y + (RANK_HEIGHT_SHIFT * nCnt), 0.0f));		// �ʒu
			//}

			m_apRank[nCnt]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
			m_apRank[nCnt]->SetSize(RANK_SIZE);									// �T�C�Y
			m_apRank[nCnt]->SetAngle();											// ����
			m_apRank[nCnt]->SetLength();										// ����

			m_apRank[nCnt]->BindTexture(nTexIdx);								// �e�N�X�`���̊��蓖�ď���

			m_apRank[nCnt]->SetVertex();										// ���_���̐ݒ菈��
			m_apRank[nCnt]->SetVtxTextureAnim(RANK_TEXTURE_PATTERN, nCnt);		// �e�N�X�`�����W�̐ݒ菈��
		}
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CRankingPrece::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// �I������
		m_apRank[nCnt]->Uninit();
	}

	// �j������
	Release();
}

//========================
// �X�V����
//========================
void CRankingPrece::Update(void)
{

}

//========================
// �`�揈��
//========================
void CRankingPrece::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// �`�揈��
		m_apRank[nCnt]->Draw();
	}
}

//========================
// ��������
//========================
CRankingPrece* CRankingPrece::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRankingPrece* pTime = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pTime == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �I�u�W�F�N�g�𐶐�
		pTime = new CRankingPrece;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // NULL ��Ԃ�
		return nullptr;
	}

	if (pTime != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pTime->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "���Ԃ̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // NULL ��Ԃ�
		return nullptr;
	}

	// ���Ԃ̃|�C���^��Ԃ�
	return pTime;
}