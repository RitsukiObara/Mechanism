//============================================
//
// �{�[�i�X����[bonus.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "bonus.h"
#include "objectbillboard.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define NUMBER_TEXTURE_PATTERN		(0.1f)		// �����̃e�N�X�`���̃p�^�[����
#define MAX_BONUS					(999)		// �{�[�i�X�̍ő吔

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CBonus* CBonus::m_pBonus = nullptr;						// �X�R�A�̏��

//========================
// �R���X�g���N�^
//========================
CBonus::CBonus() : CObject(TYPE_BONUSCOMBO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < NUM_BONUS_DIGIT; nCnt++)
	{
		m_aNumber[nCnt] = nullptr;		// �����̏��
	}
	m_posShift = NONE_D3DXVECTOR3;		// �ʒu�̐ݒ菈��
	m_nBonusCombo = 0;					// �{�[�i�X��
}

//========================
// �f�X�g���N�^
//========================
CBonus::~CBonus()
{

}

//========================
// ����������
//========================
HRESULT CBonus::Init(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < NUM_BONUS_DIGIT; nCnt++)
	{
		if (m_aNumber[nCnt] == nullptr)
		{ // ��� NULL ����Ȃ��ꍇ

			// ���������m�ۂ���
			m_aNumber[nCnt] = new CBillboardAnim(TYPE_NONE, PRIORITY_UI);
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_aNumber[nCnt] != nullptr)
		{ // �����̏�� NULL ����Ȃ��ꍇ

			if (FAILED(m_aNumber[nCnt]->Init()))
			{ // �������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// �S�Ă̒l������������
	m_posShift = NONE_D3DXVECTOR3;		// �ʒu�̐ݒ菈��
	m_nBonusCombo = 0;					// �{�[�i�X��

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CBonus::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_BONUS_DIGIT; nCnt++)
	{
		if (m_aNumber[nCnt] != nullptr)
		{ // �����̏�񂪂���ꍇ

			// �I������
			m_aNumber[nCnt]->Uninit();
			m_aNumber[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();

	// �{�[�i�X�� NULL �ɂ���
	m_pBonus = nullptr;
}

//========================
// �X�V����
//========================
void CBonus::Update(void)
{
	// ���炷���̐ݒ菈��
	SetShift();

	// ���[�J���ϐ��錾
	int aNum[NUM_BONUS_DIGIT];		// ���l

	// 10�i���ւ̌v�Z����
	useful::DecimalCalculation(NUM_BONUS_DIGIT, m_nBonusCombo, &aNum[0]);

	for (int nCnt = 0; nCnt < NUM_BONUS_DIGIT; nCnt++)
	{
		//�l�̌v�Z
		m_aNumber[nCnt]->SetVtxAnim(NUMBER_TEXTURE_PATTERN, aNum[nCnt]);
	}
}

//========================
// �`�揈��
//========================
void CBonus::Draw(void)
{
	for (int nCnt = 0; nCnt < NUM_BONUS_DIGIT; nCnt++)
	{
		if (m_aNumber[nCnt] != nullptr)
		{ // �����̏�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_aNumber[nCnt]->DrawShift(D3DXVECTOR3(m_posShift.x * nCnt, m_posShift.y * nCnt, m_posShift.z * nCnt));
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CBonus::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < NUM_BONUS_DIGIT; nCnt++)
	{
		if (m_aNumber[nCnt] != nullptr)
		{ // �����̏�� NULL �̏ꍇ

			// ����ݒ肷��
			m_aNumber[nCnt]->SetPos(pos);		// �ʒu
			m_aNumber[nCnt]->SetPosOld(pos);	// �O��̈ʒu
			m_aNumber[nCnt]->SetSize(D3DXVECTOR3(30.0f, 45.0f, 0.0f));		// �T�C�Y
			m_aNumber[nCnt]->SetAnim(0, 10);	// �e�N�X�`���̃p�^�[��

			// ���_����ݒ�
			m_aNumber[nCnt]->SetVertex();

			// �e�N�X�`�����W�̐ݒ菈��
			m_aNumber[nCnt]->SetVtxAnim(NUMBER_TEXTURE_PATTERN, 0);

			// �e�N�X�`���̊��蓖�ď���
			m_aNumber[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\Number.png"));
		}
	}

	// �S�Ă̒l������������
	m_posShift = NONE_D3DXVECTOR3;		// �ʒu�̐ݒ菈��
	m_nBonusCombo = 0;					// �{�[�i�X��
}

//========================
// �{�[�i�X�̎擾����
//========================
int CBonus::GetBonus(void) const
{
	// �{�[�i�X����Ԃ�
	return m_nBonusCombo;
}

//========================
// �{�[�i�X�̉��Z����
//========================
void CBonus::AddBonus(void)
{
	// �{�[�i�X�������Z����
	m_nBonusCombo++;

	if (m_nBonusCombo > MAX_BONUS)
	{ // �{�[�i�X�̍ő吔�𒴉߂����ꍇ

		// �{�[�i�X����␳����
		m_nBonusCombo = MAX_BONUS;
	}
}

//========================
// �X�R�A�̎擾����
//========================
CBonus* CBonus::Get(void)
{
	if (m_pBonus != nullptr)
	{ // �{�[�i�X�̏�񂪂���ꍇ

		// �{�[�i�X�̃|�C���^��Ԃ�
		return m_pBonus;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// �{�[�i�X�̃|�C���^��Ԃ�
		return m_pBonus;
	}
}

//========================
// ��������
//========================
CBonus* CBonus::Create(const D3DXVECTOR3& pos)
{
	if (m_pBonus == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pBonus = new CBonus;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (m_pBonus != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pBonus->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pBonus->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return m_pBonus;
}

//========================
// ���炷���̐ݒ菈��
//========================
void CBonus::SetShift(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posR = CManager::Get()->Get()->GetCamera()->GetPosR();		// �����_
	D3DXVECTOR3 posV = CManager::Get()->Get()->GetCamera()->GetPosV();		// ���_
	float fRot;

	// ������ݒ肷��
	fRot = atan2f(posR.x - posV.x, posR.z - posV.z);

	// ���������Z����
	fRot += D3DX_PI * 0.5f;

	// �����𐳋K������
	useful::RotNormalize(&fRot);

	// ���炷����ݒ肷��
	m_posShift.x = sinf(fRot) * 60.0f;		// ���炷��
	m_posShift.y = 0.0f;					// ���炷��
	m_posShift.z = cosf(fRot) * 60.0f;		// ���炷��
}