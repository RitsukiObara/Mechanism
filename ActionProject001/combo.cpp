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
#include "texture.h"
#include "useful.h"

// �}�N����`
#define SCORE_TEXTURE		"data\\TEXTURE\\Number.png"					// ���l�̃e�N�X�`��
#define LIMIT_POS			(D3DXVECTOR3(1080.0f, 70.0f, 0.0f))			// �R���{�����̈ʒu
#define LIMIT_SIZE			(40.0f)										// �R���{�����̃T�C�Y
#define LIMIT_DISTANCE		(25.0f)										// �R���{�����̋���
#define LIMIT_DIVI			(96)										// �R���{�����̕�����
#define COMBO_POS			(D3DXVECTOR3(900.0f, 70.0f, 0.0f))			// �R���{�̐��l�̈ʒu
#define COMBO_SIZE			(D3DXVECTOR3(20.0f, 30.0f, 0.0f))			// �R���{�̐��l�̃T�C�Y
#define COMBO_SHIFT			(40.0f)										// �R���{�̐��l�̂��炷��

//========================
// �R���X�g���N�^
//========================
CCombo::CCombo() : CObject(TYPE_COMBO, PRIORITY_UI)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// �����̏��
		m_apNumber[nCnt] = nullptr;
	}
	m_pTimeLimit = nullptr;		// �R���{�̐���
	m_nCombo = 0;				// �R���{��
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
	// �S�Ă̒l������������
	m_nCombo = 0;		// �R���{��
 
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

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CCombo::Uninit(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// �����̏I������
		m_apNumber[nCnt]->Uninit();
	}

	// �R���{�����̏I������
	m_pTimeLimit->Uninit();

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CCombo::Update(void)
{
	// �v�Z����
	Calculate();

	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// �e�N�X�`�����W�̐ݒ菈��
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_apNumber[nCnt]->GetNumber());
	}

	// �R���{�̐����~�̍X�V����
	m_pTimeLimit->Update();
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

	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
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
void CCombo::SetData(void)
{
	// �R���{�̏��̐ݒ菈��
	SetDataCombo();
}

//========================
// �R���{�̏��̐ݒ菈��
//========================
void CCombo::SetDataCombo(void)
{
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// �ݒ菈��
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(COMBO_POS.x + (nCnt * COMBO_SHIFT), COMBO_POS.y, 0.0f));				// �ʒu�ݒ�
		m_apNumber[nCnt]->SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
		m_apNumber[nCnt]->SetSize(COMBO_SIZE);			// �T�C�Y�ݒ�
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
// �R���{�̐�������
//========================
HRESULT CCombo::CreateCombo(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
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
// �v�Z����
//========================
void CCombo::Calculate(void)
{
	// ���[�J���ϐ��錾
	int aNum[MAX_COMBO_DIGIT];		// ���l

	// 10�i���ւ̌v�Z����
	useful::DecimalCalculation(MAX_COMBO_DIGIT, m_nCombo, &aNum[0]);

	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		//�l�̌v�Z
		m_apNumber[nCnt]->SetNumber(aNum[nCnt]);
	}
}

//========================
// �R���{�̐ݒ菈��
//========================
void CCombo::SetCombo(const int nCombo)
{
	// �R���{����ݒ肷��
	m_nCombo = nCombo;
}

//========================
// �R���{�̎擾����
//========================
int CCombo::GetCombo(void) const
{
	// �R���{��Ԃ�
	return m_nCombo;
}

//========================
// �R���{�̉��Z����
//========================
void CCombo::AddCombo(void)
{
	// �R���{��ݒ肷��
	m_nCombo++;

	// ���_�̃��Z�b�g����
	m_pTimeLimit->ResetNumVtx();
}

//========================
// ��������
//========================
CCombo* CCombo::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCombo* pScrew = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pScrew == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pScrew = new CCombo;
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