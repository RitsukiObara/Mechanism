//============================================
//
// �l�WUI����[screwUI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "screwUI.h"
#include "number.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"

#include "player.h"

// �}�N����`
#define BACK_TEXTURE		"data\\TEXTURE\\ScrewUI.png"							// �w�i�̃e�N�X�`��
#define SCORE_TEXTURE		"data\\TEXTURE\\Number.png"								// �X�R�A�̃e�N�X�`��
#define BACK_POS			(D3DXVECTOR3(100.0f, 150.0f, 0.0f))						// �w�i�̈ʒu
#define SCORE_POS			(D3DXVECTOR3(BACK_POS.x, BACK_POS.y + 10.0f, 0.0f))		// ���l�̈ʒu
#define SCORE_SHIFT			(40.0f)													// ���l�̂��炷��
#define BACK_SIZE			(D3DXVECTOR3(80.0f, 60.0f, 0.0f))						// �w�i�̃T�C�Y
#define SCORE_SIZE			(D3DXVECTOR3(20.0f, 30.0f, 0.0f))						// ���l�̃T�C�Y
#define ADD_LIFE_SCORE		(100)													// �̗͂�������X�R�A

//========================
// �R���X�g���N�^
//========================
CScrewUI::CScrewUI() : CObject(TYPE_SCREWUI, PRIORITY_UI)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_SCREW_DIGIT; nCnt++)
	{
		// �����̏��
		m_apNumber[nCnt] = nullptr;
	}
	m_pBack = nullptr;	// �w�i
	m_nScore = 0;		// �X�R�A
}

//========================
// �f�X�g���N�^
//========================
CScrewUI::~CScrewUI()
{

}

//========================
// ����������
//========================
HRESULT CScrewUI::Init(void)
{
	// �S�Ă̒l������������
	m_nScore = 0;		// �X�R�A
 
	// �X�R�A�̐�������
	if (FAILED(CreateScore()))
	{ // ���s�����ꍇ
		
		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �w�i�̐�������
	if (FAILED(CreateBack()))
	{ // ���s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CScrewUI::Uninit(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_SCREW_DIGIT; nCnt++)
	{
		// �����̏I������
		m_apNumber[nCnt]->Uninit();
	}

	// �w�i�̏I������
	m_pBack->Uninit();

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CScrewUI::Update(void)
{
	// �v�Z����
	Calculate();

	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_SCREW_DIGIT; nCnt++)
	{
		// �e�N�X�`�����W�̐ݒ菈��
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_apNumber[nCnt]->GetNumber());
	}
}

//========================
// �`�揈��
//========================
void CScrewUI::Draw(void)
{
	if (m_pBack != nullptr)
	{ // �w�i�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pBack->Draw();
	}

	for (int nCnt = 0; nCnt < MAX_SCREW_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // ������ NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apNumber[nCnt]->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CScrewUI::SetData(void)
{
	// �X�R�A�̏��̐ݒ菈��
	SetDataScore();

	// �w�i�̏��̐ݒ菈��
	SetDataBack();
}

//========================
// �X�R�A�̏��̐ݒ菈��
//========================
void CScrewUI::SetDataScore(void)
{
	for (int nCnt = 0; nCnt < MAX_SCREW_DIGIT; nCnt++)
	{
		// �ݒ菈��
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(SCORE_POS.x + (nCnt * SCORE_SHIFT), SCORE_POS.y, 0.0f));				// �ʒu�ݒ�
		m_apNumber[nCnt]->SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
		m_apNumber[nCnt]->SetSize(SCORE_SIZE);			// �T�C�Y�ݒ�
		m_apNumber[nCnt]->SetLength();					// �����ݒ�
		m_apNumber[nCnt]->SetAngle();					// �����ݒ�

		m_apNumber[nCnt]->SetType(CNumber::TYPE_DECIMAL);	// �ԍ��̎��
		m_apNumber[nCnt]->SetNumber(0);					// �ԍ���ݒ肷��

		// ���_���̐ݒ菈��
		m_apNumber[nCnt]->SetVertex();

		// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, 0);
	}
}

//========================
// �w�i�̏��̐ݒ菈��
//========================
void CScrewUI::SetDataBack(void)
{
	// �ݒ菈��
	m_pBack->SetPos(BACK_POS);				// �ʒu�ݒ�
	m_pBack->SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
	m_pBack->SetSize(BACK_SIZE);			// �T�C�Y�ݒ�
	m_pBack->SetLength();					// �����ݒ�
	m_pBack->SetAngle();					// �����ݒ�

	// ���_���̐ݒ菈��
	m_pBack->SetVertex();
}

//========================
// �X�R�A�̐�������
//========================
HRESULT CScrewUI::CreateScore(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_SCREW_DIGIT; nCnt++)
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
			m_apNumber[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(SCORE_TEXTURE));
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
// �w�i�̐�������
//========================
HRESULT CScrewUI::CreateBack(void)
{
	if (m_pBack == nullptr)
	{ // �|�C���^�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pBack = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pBack != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pBack->Init()))
		{ // �����������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		// �e�N�X�`���̊��蓖�ď���
		m_pBack->BindTexture(CManager::Get()->GetTexture()->Regist(BACK_TEXTURE));
	}
	else
	{ // �|�C���^���@NULL �̏ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �v�Z����
//========================
void CScrewUI::Calculate(void)
{
	// ���[�J���ϐ��錾
	int aNum[MAX_SCREW_DIGIT];		// ���l

	// 10�i���ւ̌v�Z����
	useful::DecimalCalculation(MAX_SCREW_DIGIT, m_nScore, &aNum[0]);

	for (int nCnt = 0; nCnt < MAX_SCREW_DIGIT; nCnt++)
	{
		//�l�̌v�Z
		m_apNumber[nCnt]->SetNumber(aNum[nCnt]);
	}
}

//========================
// �X�R�A�̐ݒ菈��
//========================
void CScrewUI::SetScore(const int nScore)
{
	// �X�R�A��������
	m_nScore = nScore;
}

//========================
// �X�R�A�̎擾����
//========================
int CScrewUI::GetScore(void) const
{
	// �X�R�A��Ԃ�
	return m_nScore;
}

//========================
// �X�R�A�̉��Z����
//========================
void CScrewUI::AddScore(const int nScore)
{
	// �X�R�A��ݒ肷��
	m_nScore += nScore;

	if (m_nScore >= ADD_LIFE_SCORE)
	{ // �X�R�A����萔�ɒB�����ꍇ

		// �X�R�A������������
		m_nScore = 0;

		// �̗͂�1���₷
		CPlayer::Get()->SetLife(CPlayer::Get()->GetLife() + 1);
	}
}

//========================
// ��������
//========================
CScrewUI* CScrewUI::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CScrewUI* pScrew = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pScrew == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pScrew = new CScrewUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScrew != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScrew->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pScrew->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�WUI�̃|�C���^��Ԃ�
	return pScrew;
}