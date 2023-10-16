//============================================
//
// �v���C���[�̔\�͂̃��C������[player_ability.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "player.h"
#include "motion.h"
#include "player_ability.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define HOVER_COUNT		(100)				// �z�o�[��Ԃ̃J�E���g
#define JETDASH_COUNT	(20)				// �W�F�b�g�_�b�V����Ԃ̃J�E���g
#define JETDASH_SPEED	(30.0f)				// �W�F�b�g�_�b�V�����̃X�s�[�h

//============================================
// �R���X�g���N�^
//============================================
CAbility::CAbility()
{
	// �S�Ă̒l���N���A����
	m_ability = ABILITY_NONE;		// �\��
	m_nAblCount = 0;				// �J�E���g

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aPossible[nCnt] = true;			// �\�͂̎g�p��
		m_aIntervalCount[nCnt] = 0;			// �Ԋu�J�E���g
	}
}

//============================================
// �f�X�g���N�^
//============================================
CAbility::~CAbility()
{

}

//============================================
// ����������
//============================================
HRESULT CAbility::Init(void)
{
	// �S�Ă̒l������������
	m_ability = ABILITY_NONE;		// �\��
	m_nAblCount = 0;				// �J�E���g

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aPossible[nCnt] = true;			// �\�͂̎g�p��
		m_aIntervalCount[nCnt] = 0;			// �Ԋu�J�E���g
	}

	// ������Ԃ�
	return S_OK;
}

//============================================
// �I������
//============================================
void CAbility::Uninit(void)
{
	// �����̃��������������
	delete this;
}

//============================================
// �X�V����
//============================================
void CAbility::Update(CPlayer& player)
{
	switch (m_ability)
	{
	case ABILITY_NONE:		// �����

		// �J�E���g������������
		m_nAblCount = 0;

		break;

	case ABILITY_HOVER:		// �z�o�[�W�F�b�g

		// �z�o�[�W�F�b�g����
		HoverJet(player);

		break;

	case ABILITY_JETDASH:	// �W�F�b�g�_�b�V��

		// �W�F�b�g�_�b�V������
		SkyDash(player);

		break;
	}

	// �Ԋu�J�E���g����
	Interval();
}

//============================================
// ���̐ݒ菈��
//============================================
void CAbility::SetData(void)
{
	// �S�Ă̒l��ݒ肷��
	m_ability = ABILITY_NONE;		// �\��
	m_nAblCount = 0;				// �J�E���g
}

//============================================
// �\�͂̐ݒ菈��
//============================================
void CAbility::SetAbility(const ABILITY ability)
{
	// �\�͂�ݒ肷��
	m_ability = ability;

	// �J�E���g������������
	m_nAblCount = 0;
}

//============================================
// �\�͂̎擾����
//============================================
CAbility::ABILITY CAbility::GetAbility(void) const
{
	// �\�͂�Ԃ�
	return m_ability;
}

//========================
// �\�󋵂̐ݒ菈��
//========================
void CAbility::SetPossible(const TYPE type, const bool bPossible)
{
	// �\�󋵂�ݒ肷��
	m_aPossible[type] = bPossible;
}

//========================
// �\�󋵂̎擾����
//========================
bool CAbility::GetPossible(const TYPE type)
{
	// �\�󋵂�Ԃ�
	return m_aPossible[type];
}

//============================================
// �Ԋu�J�E���g�̐ݒ菈��
//============================================
void CAbility::SetInterval(const TYPE type, const int nCount)
{
	// �Ԋu�J�E���g��ݒ肷��
	m_aIntervalCount[type] = nCount;
}

//============================================
// �Ԋu�J�E���g�̎擾����
//============================================
int CAbility::GetInterval(const TYPE type) const
{
	// �Ԋu�J�E���g��Ԃ�
	return m_aIntervalCount[type];
}

//============================================
// ��������
//============================================
CAbility* CAbility::Create(void)
{
	// ���[�J���ϐ��錾
	CAbility* pAbility = nullptr;		// �s�����

	if (pAbility == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		pAbility = new CAbility;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return pAbility;
	}

	if (pAbility != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAbility->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�v���C���[�̔\�͂̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAbility->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �\�͂̃|�C���^��Ԃ�
	return pAbility;
}

//============================================
// �z�o�[�W�F�b�g����
//============================================
void CAbility::HoverJet(CPlayer& player)
{
	// �W�����v��Ԃɂ���
	player.SetEnableJump(true);

	// �J�E���g�����Z����
	m_nAblCount++;

	if (m_nAblCount >= HOVER_COUNT)
	{ // �J�E���g����萔�ȏ�̏ꍇ

		// �J�E���g������������
		m_nAblCount = 0;

		// ���\�͏�Ԃɂ���
		m_ability = ABILITY_NONE;
	}
}

//============================================
// �W�F�b�g�_�b�V������
//============================================
void CAbility::SkyDash(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = player.GetPos();		// �ʒu���擾����
	D3DXVECTOR3 rot = player.GetRot();		// �������擾����

	// �ʒu��ݒ肷��
	pos.x += sinf(rot.y) * JETDASH_SPEED;

	// �J�E���g�����Z����
	m_nAblCount++;

	if (m_nAblCount >= JETDASH_COUNT)
	{ // �J�E���g����萔�ȏ�̏ꍇ

		// �J�E���g������������
		m_nAblCount = 0;

		// ���\�͏�Ԃɂ���
		m_ability = ABILITY_NONE;
	}

	// �ʒu��K�p����
	player.SetPos(pos);
}

//============================================
// �Ԋu�J�E���g����
//============================================
void CAbility::Interval(void)
{
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_aPossible[nCnt] == false)
		{ // �\�͏󋵂� false �̏ꍇ

			// �Ԋu�J�E���g���Z����
			m_aIntervalCount[nCnt]--;

			if (m_aIntervalCount[nCnt] <= 0)
			{ // �Ԋu�J�E���g�� 0 �ȏ�ɂȂ����ꍇ

				// �Ԋu�J�E���g�� 0 �ɂ���
				m_aIntervalCount[nCnt] = 0;

				// �g�p�\�󋵂� true �ɂ���
				m_aPossible[nCnt] = true;
			}
		}
	}
}