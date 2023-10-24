//============================================
//
// �v���C���[�̔\�͂̃��C������[player_ability.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "player.h"
#include "player_ability.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "input.h"
#include "collision.h"
#include "ripple.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define HOVER_COUNT					(100)				// �z�o�[��Ԃ̃J�E���g
#define JETDASH_COUNT				(20)				// �W�F�b�g�_�b�V����Ԃ̃J�E���g
#define JETDASH_POSBL_COUNT			(30)				// �W�F�b�g�_�b�V����Ԃ��g�p�\�ɂȂ�J�E���g
#define GROUNDQUAKE_COUNT			(500)				// �O���E���h�N�G�C�N��Ԃ̋��������J�E���g
#define GROUNDQUAKE_RIPPLE_COUNT	(10)				// �O���E���h�N�G�C�N���̔g�䂪�o��Ԋu
#define GROUNDQUAKE_POSBL_COUNT		(15)				// �O���E���h�N�G�C�N��Ԃ��g�p�\�ɂȂ�J�E���g
#define JETDASH_SPEED				(30.0f)				// �W�F�b�g�_�b�V�����̃X�s�[�h

//============================================
// �R���X�g���N�^
//============================================
CAbility::CAbility()
{
	// �S�Ă̒l���N���A����
	m_pElev = nullptr;				// �N���n�ʂ̃|�C���^
	m_ability = ABILITY_NONE;		// �\��

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aAblCount[nCnt] = 0;				// �J�E���g
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
	m_pElev = nullptr;				// �N���n�ʂ̃|�C���^
	m_ability = ABILITY_NONE;		// �\��

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aPossible[nCnt] = true;			// �\�͂̎g�p��
		m_aAblCount[nCnt] = 0;				// �J�E���g
	}

	// ������Ԃ�
	return S_OK;
}

//============================================
// �I������
//============================================
void CAbility::Uninit(void)
{
	// �N���n�ʂ̃|�C���^�� NULL �ɂ���
	m_pElev = nullptr;

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

		// �\�͑��쏈��
		Ability(player);

		break;

	case ABILITY_HOVER:			// �z�o�[�W�F�b�g

		// �z�o�[�W�F�b�g����
		HoverJet(player);

		break;

	case ABILITY_JETDASH:		// �W�F�b�g�_�b�V��

		// �W�F�b�g�_�b�V������
		SkyDash(player);

		break;

	case ABILITY_DASHJUMP:		// �_�b�V���W�����v

	{
		float f = player.GetSpeed();

		useful::FrameCorrect(8.0f, &f, 0.5f);

		// ���x��K�p����
		player.SetSpeed(f);

		if (f <= 8.0f)
		{ // ���x����萔�ȉ��ɂȂ����ꍇ

			// ���\�͏�Ԃɂ���
			m_ability = ABILITY_NONE;
		}
	}

		break;

	case ABILITY_GROUNDQUAKE:	// �O���E���h�N�G�C�N

		// �O���E���h�N�G�C�N����
		GroundQuake(player);

		// �}�L�i���Ƃ̓����蔻��
		collision::MacchinaHit(player);

		// �G�̋C�⏈��
		collision::EnemyStun(player);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �g�p�\�󋵂̐ݒ菈��
	PossibleProcess(player);
}

//============================================
// ���̐ݒ菈��
//============================================
void CAbility::SetData(void)
{
	// �S�Ă̒l��ݒ肷��
	m_ability = ABILITY_NONE;		// �\��

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aAblCount[nCnt] = 0;				// �J�E���g
	}
}

//============================================
// �\�͂̐ݒ菈��
//============================================
void CAbility::SetAbility(const ABILITY ability, CPlayer& player)
{
	// �\�͂�ݒ肷��
	m_ability = ability;

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

	case ABILITY_DASHJUMP:		// �_�b�V���W�����v

		// ���x��ݒ肷��
		player.SetSpeed(JETDASH_SPEED);

		break;

	case ABILITY_GROUNDQUAKE:	// �O���E���h�N�G�C�N���

		// ���_�̒T������
		SearchVertex(player.GetPos());

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

//============================================
// �\�͂̃��Z�b�g����
//============================================
void CAbility::ResetAbility(void)
{
	// �\�͂�ݒ肷��
	m_ability = ABILITY_NONE;

	// �\�󋵂� true �ɂ���
	m_aPossible[TYPE_HOVER] = true;
	m_aPossible[TYPE_JETDASH] = true;
	m_aPossible[TYPE_GROUNDQUAKE] = true;
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

//=======================================
// �\�͑��쏈��
//=======================================
void CAbility::Ability(CPlayer& player)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_Y) == true &&
		m_aPossible[TYPE_HOVER] == true &&
		player.IsJump() == true)
	{ // �󒆂�Y�L�[���������ꍇ

		// �z�o�[�W�F�b�g��Ԃɂ���
		player.GetAbility()->SetAbility(CAbility::ABILITY_HOVER, player);

		// �g�p�󋵂� false �ɂ���
		m_aPossible[TYPE_HOVER] = false;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_U) == true &&
		m_aPossible[TYPE_JETDASH] == true)
	{ // U�L�[���������ꍇ

		// �W�F�b�g�_�b�V����Ԃɂ���
		player.GetAbility()->SetAbility(CAbility::ABILITY_JETDASH, player);

		// �g�p�󋵂� false �ɂ���
		m_aPossible[TYPE_JETDASH] = false;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_I) == true &&
		m_aPossible[TYPE_GROUNDQUAKE] == true &&
		player.IsJump() == false)
	{ // �n���I�L�[���������ꍇ

		// �O���E���h�N�G�C�N��Ԃɂ���
		player.GetAbility()->SetAbility(CAbility::ABILITY_GROUNDQUAKE, player);

		// �J������U���J�����ɂ���
		CManager::Get()->GetCamera()->SetType(CCamera::TYPE_VIBRATE);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_O) == true)
	{ // O�L�[���������ꍇ

		// ���\�͂ɐݒ肷��
		player.GetAbility()->SetAbility(CAbility::ABILITY_NONE, player);
	}
}

//============================================
// �z�o�[�W�F�b�g����
//============================================
void CAbility::HoverJet(CPlayer& player)
{
	// �W�����v��Ԃɂ���
	player.SetEnableJump(true);

	// �J�E���g�����Z����
	m_aAblCount[TYPE_HOVER]++;

	if (m_aAblCount[TYPE_HOVER] >= HOVER_COUNT)
	{ // �J�E���g����萔�ȏ�̏ꍇ

		// �J�E���g������������
		m_aAblCount[TYPE_HOVER] = 0;

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

	// �\�̓J�E���g�����Z����
	m_aAblCount[TYPE_JETDASH]++;

	if (m_aAblCount[TYPE_JETDASH] >= JETDASH_COUNT)
	{ // �J�E���g����萔�ȏ�̏ꍇ

		if (player.IsJump() == true)
		{ // �W�����v�󋵂� true �̏ꍇ

			// �\�̓J�E���g������������
			m_aAblCount[TYPE_JETDASH] = 0;

			// �_�b�V���W�����v��Ԃɂ���
			SetAbility(ABILITY_DASHJUMP, player);
		}
		else
		{ // ��L�ȊO

			// ���\�͏�Ԃɂ���
			m_ability = ABILITY_NONE;
		}
	}

	// �ʒu��K�p����
	player.SetPos(pos);
}

//============================================
// �O���E���h�N�G�C�N����
//============================================
void CAbility::GroundQuake(CPlayer& player)
{
	if (m_aAblCount[TYPE_GROUNDQUAKE] % GROUNDQUAKE_RIPPLE_COUNT == 0)
	{ // ���Ԋu���Ƃ�

		// �g��̐�������
		CRipple::Create(player.GetPos(), NONE_D3DXVECTOR3);
	}

	// �\�̓J�E���g�����Z����
	m_aAblCount[TYPE_GROUNDQUAKE]++;

	if (CManager::Get()->GetInputKeyboard()->GetRelease(DIK_I) == true ||
		m_aAblCount[TYPE_GROUNDQUAKE] >= GROUNDQUAKE_COUNT)
	{ // I�L�[�𗣂����܂��́A���J�E���g���𒴂����ꍇ

		// ���\�͏�Ԃɂ���
		SetAbility(CAbility::ABILITY_NONE, player);

		// �g�p�󋵂� false �ɂ���
		m_aPossible[TYPE_GROUNDQUAKE] = false;

		// �\�̓J�E���g��ݒ肷��
		m_aAblCount[TYPE_GROUNDQUAKE] = GROUNDQUAKE_POSBL_COUNT;
	}
}

//============================================
// �\�󋵔��菈��
//============================================
void CAbility::PossibleProcess(CPlayer& player)
{
	// �z�o�[�̎g�p��
	if (player.IsJump() == false)
	{ // �n��ɗ����Ă��鎞

		// �\�̓J�E���g������������
		m_aAblCount[TYPE_HOVER] = 0;

		// �g�p�󋵂� true �ɂ���
		m_aPossible[TYPE_HOVER] = true;
	}

	// �W�F�b�g�_�b�V���̎g�p��
	if (m_aPossible[TYPE_JETDASH] == false &&
		m_ability != ABILITY_JETDASH)
	{ // �W�F�b�g�_�b�V�����g���Ȃ��ꍇ

		// �\�̓J�E���g�����Z����
		m_aAblCount[TYPE_JETDASH]++;

		if (m_aAblCount[TYPE_JETDASH] >= JETDASH_POSBL_COUNT)
		{ // �\�̓J�E���g����萔�ȏ�̏ꍇ

			// �\�̓J�E���g������������
			m_aAblCount[TYPE_JETDASH] = 0;

			// �g�p�\�ɂ���
			m_aPossible[TYPE_JETDASH] = true;
		}
	}

	// �O���E���h�N�G�C�N�̎g�p��
	if (m_aPossible[TYPE_GROUNDQUAKE] == false)
	{ // �O���E���h�N�G�C�N���g���Ȃ��ꍇ

		// �\�̓J�E���g�����Z����
		m_aAblCount[TYPE_GROUNDQUAKE]--;

		if (m_aAblCount[TYPE_GROUNDQUAKE] <= 0)
		{ // �\�̓J�E���g����萔�ȉ��ɂȂ����ꍇ

			// �\�̓J�E���g��ݒ肷��
			m_aAblCount[TYPE_GROUNDQUAKE] = 0;

			// �g�p�\�ɂ���
			m_aPossible[TYPE_GROUNDQUAKE] = true;
		}
	}
}

//============================================
// �N���n�ʂ̒��_�̒T������
//============================================
void CAbility::SearchVertex(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	CElevation* pElev = CElevationManager::Get()->GetTop();		// �N���n�ʂ��擾����
	int nVtxIdx;			// ���_�̔ԍ�

	while (pElev != nullptr)
	{ // �N���n�ʂ�������葱��

		if (pos.x <= pElev->GetPos().x + pElev->GetSize().x &&
			pos.x >= pElev->GetPos().x - pElev->GetSize().x &&
			pos.z <= pElev->GetPos().z + pElev->GetSize().z &&
			pos.z >= pElev->GetPos().z - pElev->GetSize().z)
		{ // �|���S���̒��ɂ����ꍇ

			// �߂��̔ԍ����擾����
			nVtxIdx = pElev->NearVertexSearch(pos);

			// �N���̒n�ʂ�ݒ肷��
			m_pElev = pElev;
		}

		// ���̃|�C���^���擾����
		pElev = pElev->GetNext();
	}
}