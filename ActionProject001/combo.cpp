//============================================
//
// �R���{����[combo.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "number.h"
#include "combo.h"
#include "combo_circle.h"
#include "combo_score.h"
#include "combo_magni.h"
#include "game.h"
#include "score.h"
#include "texture.h"
#include "useful.h"

// �}�N����`
#define LIMIT_POS			(D3DXVECTOR3(1080.0f, 70.0f, 0.0f))			// �R���{�����̈ʒu
#define LIMIT_SIZE			(40.0f)										// �R���{�����̃T�C�Y
#define LIMIT_DISTANCE		(25.0f)										// �R���{�����̋���
#define LIMIT_DIVI			(96)										// �R���{�����̕�����

#define COMBO_POS			(D3DXVECTOR3(900.0f, 70.0f, 0.0f))			// �R���{�̐��l�̈ʒu
#define COMBO_SIZE			(D3DXVECTOR3(20.0f, 30.0f, 0.0f))			// �R���{�̐��l�̃T�C�Y
#define COMBO_SHIFT			(40.0f)										// �R���{�̐��l�̂��炷��

#define SCORE_POS			(D3DXVECTOR3(1050.0f, 40.0f, 0.0f))			// �X�R�A�̈ʒu
#define SCORE_SIZE			(D3DXVECTOR3(10.0f, 15.0f, 0.0f))			// �X�R�A�̃T�C�Y
#define SCORE_SHIFT			(20.0f)										// �X�R�A�̂��炷��

//========================
// �R���X�g���N�^
//========================
CCombo::CCombo() : CObject(TYPE_COMBO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pMagni = nullptr;			// �R���{�̔{��
	m_pTimeLimit = nullptr;		// �R���{�̐���
	m_pScore = nullptr;			// �R���{�X�R�A
}

//========================
// �f�X�g���N�^
//========================
CCombo::~CCombo()
{

}

//========================
// ����������
//========================
HRESULT CCombo::Init(void)
{ 
	// �R���{�̐�������
	if (FAILED(CreateCombo()))
	{ // ���s�����ꍇ
		
		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �R���{�����̐�������
	if (FAILED(CreateLimit()))
	{ // ���s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �R���{�X�R�A�̐�������
	if (FAILED(CreateComboScore()))
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
void CCombo::Uninit(void)
{
	// �R���{�{���̏I������
	m_pMagni->Uninit();

	// �R���{�����̏I������
	m_pTimeLimit->Uninit();

	// �R���{�X�R�A�̏I������
	m_pScore->Uninit();

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CCombo::Update(void)
{
	// �R���{�{���̍X�V����
	m_pMagni->Update();

	// �R���{�̐����~�̍X�V����
	m_pTimeLimit->Update();

	// �R���{�X�R�A�̍X�V����
	m_pScore->Update();

	if (m_pTimeLimit->GetEnd() == true)
	{ // �I���󋵂ɂ���

		// �X�R�A�����Z����
		CGame::GetScore()->AddScore(m_pMagni->GetMagni() * m_pScore->GetScore());

		// �X�R�A������������
		m_pScore->SetScore(0);

		// �{��������������
		m_pMagni->SetMagni(0);
	}
}

//========================
// �`�揈��
//========================
void CCombo::Draw(void)
{
	if (m_pTimeLimit != nullptr)
	{ // �R���{������ NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pTimeLimit->Draw();
	}

	if (m_pScore != nullptr)
	{ // �R���{�X�R�A�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pScore->Draw();
	}

	if (m_pMagni != nullptr)
	{ // �R���{�{���� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pMagni->Draw();
	}
}

//========================
// �R���{�̉��Z����
//========================
void CCombo::AddCombo(const int nScore)
{
	// �{���̉��Z����
	m_pMagni->AddMagni();

	// �������Ԃ̃��Z�b�g����
	m_pTimeLimit->ResetNumVtx();

	// �X�R�A�̉��Z����
	m_pScore->AddScore(nScore);
}

//========================
// ��������
//========================
CCombo* CCombo::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCombo* pCombo = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCombo == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCombo = new CCombo;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCombo != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCombo->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �R���{�̃|�C���^��Ԃ�
	return pCombo;
}

//========================
// �R���{�̐�������
//========================
HRESULT CCombo::CreateCombo(void)
{
	if (m_pMagni == nullptr)
	{ // �|�C���^�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pMagni = CComboMagni::Create(COMBO_POS, NONE_D3DXVECTOR3, COMBO_SIZE, COMBO_SHIFT);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �R���{�����̐�������
//========================
HRESULT CCombo::CreateLimit(void)
{
	if (m_pTimeLimit == nullptr)
	{ // �|�C���^�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pTimeLimit = CComboCircle::Create(LIMIT_POS, LIMIT_SIZE, LIMIT_DISTANCE, LIMIT_DIVI);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pTimeLimit != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// �e�N�X�`���̊��蓖�ď���
		m_pTimeLimit->BindTexture(CManager::Get()->GetTexture()->Regist(nullptr));
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
// �R���{�X�R�A�̐�������
//========================
HRESULT CCombo::CreateComboScore(void)
{
	if (m_pScore == nullptr)
	{ // �|�C���^�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pScore = CComboScore::Create(LIMIT_POS, NONE_D3DXVECTOR3, SCORE_SIZE, SCORE_SHIFT);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}