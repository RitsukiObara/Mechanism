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
#include "player_ability.h"
#include "objectElevation.h"
#include "elevation_manager.h"
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
	case ABILITY_NONE:			// �����

		// �J�E���g������������
		m_nAblCount = 0;

		break;

	case ABILITY_HOVER:			// �z�o�[�W�F�b�g

		// �z�o�[�W�F�b�g����
		HoverJet(player);

		break;

	case ABILITY_JETDASH:		// �W�F�b�g�_�b�V��

		// �W�F�b�g�_�b�V������
		SkyDash(player);

		break;

	case ABILITY_GROUNDQUAKE:	// �O���E���h�N�G�C�N

		// �O���E���h�N�G�C�N����
		GroundQuake(player);

		break;

	case ABILITY_STARDROP:		// �X�^�[�h���b�v

		// �X�^�[�h���b�v����
		StarDrop(player);

		break;

	default:

		// ��~
		assert(false);

		break;
	}
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
void CAbility::SetAbility(const ABILITY ability, CPlayer& player)
{
	// �\�͂�ݒ肷��
	m_ability = ability;

	// �J�E���g������������
	m_nAblCount = 0;

	switch (m_ability)
	{
	case ABILITY_NONE:			// �ʏ���

		break;

	case ABILITY_HOVER:			// �z�o�[�W�F�b�g���

		break;

	case ABILITY_JETDASH:		// �W�F�b�g�_�b�V�����

	{
		// ���[�J���ϐ��錾
		D3DXVECTOR3 move = player.GetMove();		// �ړ��ʂ��擾����

		// �ړ��ʂ�ݒ肷��
		move.y = 0.0f;

		// �ړ��ʂ�K�p����
		player.SetMove(move);
	}

		break;

	case ABILITY_GROUNDQUAKE:	// �O���E���h�N�G�C�N���

		// ���_�̒T������
		SearchVertex(player.GetPos());

		break;

	case ABILITY_STARDROP:		// �X�^�[�h���b�v���

		break;

	default:

		// ��~
		assert(false);

		break;
	}
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
// �O���E���h�N�G�C�N����
//============================================
void CAbility::GroundQuake(CPlayer& player)
{

}

//============================================
// �X�^�[�h���b�v����
//============================================
void CAbility::StarDrop(CPlayer& player)
{

}

//============================================
// �N���n�ʂ̒��_�̒T������
//============================================
void CAbility::SearchVertex(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	CElevation* pElev = CElevationManager::Get()->GetTop();		// �N���n�ʂ��擾����
	int nNum;

	while (pElev != nullptr)
	{ // �N���n�ʂ�������葱��

		if (pos.x <= pElev->GetPos().x + pElev->GetSize().x &&
			pos.x >= pElev->GetPos().x - pElev->GetSize().x &&
			pos.z <= pElev->GetPos().z + pElev->GetSize().z &&
			pos.z >= pElev->GetPos().z - pElev->GetSize().z)
		{ // �|���S���̒��ɂ����ꍇ

			// �߂��̔ԍ����擾����
			nNum = pElev->NearVertexSearch(pos);

			// ���_���グ��
			pElev->AddVertex(nNum, 200.0f);
		}

		// ���̃|�C���^���擾����
		pElev = pElev->GetNext();
	}
}