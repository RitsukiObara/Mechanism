//============================================
//
// �R���{�X�R�A����[combo_score.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "combo_score.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define SCORE_TEXTURE		"data\\TEXTURE\\Number.png"		// �X�R�A�̃e�N�X�`��
#define DISP_ADD_SCORE		(10)							// �`��p�X�R�A�̉��Z��

//========================
// �R���X�g���N�^
//========================
CComboScore::CComboScore() : CObject(TYPE_NONE, PRIORITY_UI)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_COMBO_SCORE_DIGIT; nCnt++)
	{
		// �����̏��
		m_apNumber[nCnt] = nullptr;
	}

	m_nScore = 0;		// �X�R�A
	m_nDispScore = 0;	// �\���p�X�R�A
}

//========================
// �f�X�g���N�^
//========================
CComboScore::~CComboScore()
{

}

//========================
// ����������
//========================
HRESULT CComboScore::Init(void)
{
	//���[�J���ϐ��錾
	int nTexIdx = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X

	// �e�N�X�`���̓ǂݍ��ݏ���
	nTexIdx = CManager::Get()->GetTexture()->Regist(SCORE_TEXTURE);

	// �S�Ă̒l������������
	m_nScore = 0;		// �X�R�A
	m_nDispScore = 0;	// �\���p�X�R�A

	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_COMBO_SCORE_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apNumber[nCnt] = new CNumber(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apNumber[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apNumber[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}

			// �e�N�X�`���̊��蓖�ď���
			m_apNumber[nCnt]->BindTexture(nTexIdx);
		}
		else
		{ // �|�C���^���@NULL �̏ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CComboScore::Uninit(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_COMBO_SCORE_DIGIT; nCnt++)
	{
		// �I������
		m_apNumber[nCnt]->Uninit();
	}

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CComboScore::Update(void)
{
	if (m_nDispScore >= m_nScore)
	{ // �`��p�X�R�A�����ۂ̃X�R�A���������ꍇ

		// �`��p�X�R�A��ݒ肷��
		m_nDispScore = m_nScore;
	}
	else
	{ // ��L�ȊO

		// �`��p�X�R�A�����Z����
		m_nDispScore += DISP_ADD_SCORE;
	}

	// �v�Z����
	Calculate();

	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_COMBO_SCORE_DIGIT; nCnt++)
	{
		// �e�N�X�`�����W�̐ݒ菈��
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_apNumber[nCnt]->GetNumber());
	}
}

//========================
// �`�揈��
//========================
void CComboScore::Draw(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_COMBO_SCORE_DIGIT; nCnt++)
	{
		// �`�揈��
		m_apNumber[nCnt]->Draw();
	}
}

//========================
// ���̐ݒ菈��
//========================
void CComboScore::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size,const float fShift)
{
	for (int nCnt = 0; nCnt < MAX_COMBO_SCORE_DIGIT; nCnt++)
	{
		// �ݒ菈��
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(pos.x + (nCnt * fShift), pos.y, 0.0f));		// �ʒu�ݒ�
		m_apNumber[nCnt]->SetRot(rot);				// �����ݒ�
		m_apNumber[nCnt]->SetSize(size);			// �T�C�Y�ݒ�
		m_apNumber[nCnt]->SetLength();				// �����ݒ�
		m_apNumber[nCnt]->SetAngle();				// �����ݒ�

		m_apNumber[nCnt]->SetType(CNumber::TYPE_DECIMAL);	// �ԍ��̎��
		m_apNumber[nCnt]->SetNumber(0);				// �ԍ���ݒ肷��

		// ���_���̐ݒ菈��
		m_apNumber[nCnt]->SetVertex();

		// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, 0);
	}
}

//========================
// �v�Z����
//========================
void CComboScore::Calculate(void)
{
	// ���[�J���ϐ��錾
	int aNum[MAX_COMBO_SCORE_DIGIT];		// ���l

	// 10�i���ւ̌v�Z����
	useful::DecimalCalculation(MAX_COMBO_SCORE_DIGIT, m_nDispScore, &aNum[0]);

	for (int nCnt = 0; nCnt < MAX_COMBO_SCORE_DIGIT; nCnt++)
	{
		//�l�̌v�Z
		m_apNumber[nCnt]->SetNumber(aNum[nCnt]);
	}
}

//========================
// �X�R�A�̐ݒ菈��
//========================
void CComboScore::SetScore(const int nScore)
{
	// �X�R�A��ݒ肷��
	m_nScore = nScore;
}

//========================
// �X�R�A�̎擾����
//========================
int CComboScore::GetScore(void) const
{
	// �X�R�A��Ԃ�
	return m_nScore;
}

//========================
// �X�R�A�̉��Z����
//========================
void CComboScore::AddScore(const int nScore)
{
	// �X�R�A��ݒ肷��
	m_nScore += nScore;
}

//========================
// ��������
//========================
CComboScore* CComboScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fShift)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CComboScore* pScore = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pScore == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pScore = new CComboScore;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScore != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScore->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pScore->SetData(pos, rot, size, fShift);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pScore;
}