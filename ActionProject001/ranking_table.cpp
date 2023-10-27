//============================================
//
// �����L���O�X�R�A����[ranking_score.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "ranking_table.h"
#include "manager.h"
#include "sound.h"

#include "file.h"
#include "score.h"
#include "game.h"
#include "new_record.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define SCORE_WIDTH_SHIFT		(70.0f)									// �X�R�A�̉��̂��炷��
#define SCORE_HEIGHT_SHIFT		(110.0f)								// �X�R�A�̏c�̂��炷��
#define SCORE_SIZE				(D3DXVECTOR3(30.0f, 40.0f, 0.0f))		// �X�R�A�̃T�C�Y
#define SCORE_SHIFT				(60.0f)									// �X�R�A�̃T�C�Y
#define SCORE_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 150.0f, 220.0f, 0.0f))		// �X�R�A�̈ʒu
#define SCORE_TRANS_POS			(D3DXVECTOR3(500.0f, 220.0f, 0.0f))		// �����J�ڌ�̃X�R�A�̈ʒu
#define NO_NEW_RECORD			(0)										// �V�L�^����Ȃ��Ƃ��̐��l
#define SCOREDOT_SIZE			(D3DXVECTOR3(8.0f, 8.0f, 0.0f))			// �X�R�A�̓_�̃T�C�Y
#define SOUND_COUNT				(70)									// ������J�E���g��

//========================
// �R���X�g���N�^
//========================
CRankingTable::CRankingTable() : CObject(CObject::TYPE_RANKINGTABLE, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_apScore[nCnt] = nullptr;				// ���Ԃ̃|�C���^
	}

	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_nNewRecordRank = NO_NEW_RECORD;			// �V�L�^�̏���
	m_nSoundCount = 0;							// ����炷�J�E���g
}

//========================
// �f�X�g���N�^
//========================
CRankingTable::~CRankingTable()
{

}

//========================
// ����������
//========================
HRESULT CRankingTable::Init(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_apScore[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apScore[nCnt] = new CScore(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apScore[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apScore[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}
		}
		else
		{ // �|�C���^���@NULL �̏ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// �S�Ă̒l������������
	m_pos = SCORE_POS;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	m_nNewRecordRank = NO_NEW_RECORD;			// �V�L�^�̏���
	m_nSoundCount = 0;							// ����炷�J�E���g

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CRankingTable::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_apScore[nCnt] != nullptr)
		{ // �^�C�}�[�̏�� NULL ����Ȃ��ꍇ

			// �I������
			m_apScore[nCnt]->Uninit();
			m_apScore[nCnt] = nullptr;
		}
	}

	// �j������
	Release();
}

//========================
// �X�V����
//========================
void CRankingTable::Update(void)
{
	if (m_nNewRecordRank > NO_NEW_RECORD && 
		m_nNewRecordRank <= MAX_RANKING &&
		m_apScore[m_nNewRecordRank - 1] != nullptr)
	{ // �V�L�^����������A�����̃|�C���^���������ꍇ

		for (int nCnt = 0; nCnt < MAX_SCORE_DIGIT; nCnt++)
		{
			// �F��ݒ肷��
			m_apScore[m_nNewRecordRank - 1]->GetNumber(nCnt)->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}

	if (m_nNewRecordRank != NO_NEW_RECORD)
	{ // �V�L�^������Ă����ꍇ

		// ����炷�J�E���g�����Z����
		m_nSoundCount++;

		if (m_nSoundCount % SOUND_COUNT == 0)
		{ // �J�E���g������萔�ɒB�����ꍇ

			// �V�L�^�̉���炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_NEWRECORD);
		}
	}
}

//========================
// �`�揈��
//========================
void CRankingTable::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// �`�揈��
		m_apScore[nCnt]->Draw();
	}
}

//========================
// ���̐ݒ菈��
//========================
void CRankingTable::SetData(void)
{
	// �����L���O�̃��[�h����
	CManager::Get()->GetFile()->Load(CFile::TYPE_RANKING);

	// �����L���O�̓���ւ�����
	RankSwap(CGame::GetScore());

	// ���ʂ̃Z�[�u����
	CManager::Get()->GetFile()->Save(CFile::TYPE_RANKING);

	// �ʒu��ݒ肷��
	D3DXVECTOR3 pos;

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		// �ʒu��ݒ肷��
		pos.x = m_pos.x;
		pos.y = m_pos.y + (nCntRank * SCORE_HEIGHT_SHIFT);
		pos.z = 0.0f;

		// �X�R�A�̏��̐ݒ菈��
		m_apScore[nCntRank]->SetData(pos, NONE_D3DXVECTOR3, SCORE_SIZE, SCORE_SHIFT);

		// �X�R�A��ݒ肷��
		m_apScore[nCntRank]->SetScore(CManager::Get()->GetFile()->GetRankingInfo().aRank[nCntRank]);
		m_apScore[nCntRank]->SetScoreDisp(CManager::Get()->GetFile()->GetRankingInfo().aRank[nCntRank]);

		// �e�N�X�`���̐ݒ菈��
		m_apScore[nCntRank]->Update();

		if (nCntRank == m_nNewRecordRank - 1)
		{ // �V�L�^�������ꍇ

			// �V�L�^�\���̐���
			CNewRecord::Create(m_apScore[nCntRank]->GetNumber(0)->GetPos());
		}
	}
}

//========================================
// �����L���O�̓���ւ�����
//========================================
void CRankingTable::RankSwap(int nScore)
{
	// ���[�J���ϐ��錾
	int aScore[MAX_RANKING];		// �X�R�A
	int nTemp;						// �ꎞ�I�ȕϐ�
	bool bUpdate = false;			// �V�L�^���X�V���ꂽ���ǂ���

	// �����L���O���擾����
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		aScore[nCnt] = CManager::Get()->GetFile()->GetRankingInfo().aRank[nCnt];
	}

	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{ // �����L���O���r����

		if (aScore[nCount] <= nScore)
		{ // ����̃X�R�A�̐��l�̕����傫�������ꍇ

			// �ꎞ�I�ȕϐ��Ƀ����L���O�̐��l��������
			nTemp = aScore[nCount];

			// ���ʂ������L���O�̒��ɑ������
			aScore[nCount] = nScore;

			// ���ʂ��ꎞ�I�ȕϐ��ɕς���
			nScore = nTemp;

			if (bUpdate == false)
			{ // �V�L�^���X�V����Ă��Ȃ������ꍇ

				// ���̃J�E���g��V�L�^�̔ԍ��Ƃ���
				m_nNewRecordRank = nCount + 1;

				// �V�L�^�X�V
				bUpdate = true;
			}
		}
	}

	// �����L���O�̐ݒ菈��
	CManager::Get()->GetFile()->SetRankingInfo(aScore);
}

//========================
// ��������
//========================
CRankingTable* CRankingTable::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRankingTable* pTime = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pTime == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �I�u�W�F�N�g�𐶐�
		pTime = new CRankingTable;
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

		// ���̐ݒ菈��
		pTime->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // NULL ��Ԃ�
		return nullptr;
	}

	// ���Ԃ̃|�C���^��Ԃ�
	return pTime;
}