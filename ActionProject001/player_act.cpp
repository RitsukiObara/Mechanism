//============================================
//
// �v���C���[�̍s����Ԃ̃��C������[player_act.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "player.h"
#include "motion.h"
#include "player_act.h"
#include "player_ability.h"
#include "ability_UI.h"
#include "useful.h"
#include "manager.h"
#include "input.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define CANNON_COUNT			(60)				// ��Ԃ܂ł̃J�E���g
#define ROT_Y_MOVE				(D3DX_PI * 0.1f)	// �����̈ړ���(Y��)
#define JUMP_MOVE				(20.0f)				// �W�����v�̈ړ���
#define CANNON_Y_MOVE			(30.0f)				// ��C��Y���̈ړ���
#define CANNON_Z_MOVE			(15.0f)				// ��C��Z���̈ړ���
#define PLAYER_ACROBAT_SPEED	(7.0f)				// �A�N���o�b�g��Ԃ̃X�s�[�h

// �d�͊֌W
#define ACROBAT_GRAVITY		(-0.9f)					// �A�N���o�b�g���[�h�̏d��
#define HOVER_GRAVITY		(0.8f)					// �z�o�[��Ԃ̏d��
#define MASSIVE_GRAVITY		(-1.2f)					// �}�b�V�u���[�h�̏d��
#define FLY_GRAVITY			(-0.9f)					// �t���C��Ԃ̏d��

//============================================
// �R���X�g���N�^
//============================================
CPlayerAct::CPlayerAct()
{
	// �S�Ă̒l���N���A����
	m_act = ACT_NONE;			// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
	m_bFront = true;			// �O���
}

//============================================
// �f�X�g���N�^
//============================================
CPlayerAct::~CPlayerAct()
{

}

//============================================
// ����������
//============================================
HRESULT CPlayerAct::Init(void)
{
	// �S�Ă̒l������������
	m_act = ACT_NONE;			// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
	m_bFront = true;			// �O���

	// ������Ԃ�
	return S_OK;
}

//============================================
// �I������
//============================================
void CPlayerAct::Uninit(void)
{
	// �����̃��������������
	delete this;
}

//============================================
// �X�V����
//============================================
void CPlayerAct::Update(CPlayer& player)
{
	switch (m_act)
	{
	case ACT_NONE:		// �ʏ���

		// ���쏈��
		Control(player);

		// �d�͏���
		Gravity(player);

		// �\�͑��쏈��
		Ability(player);

		// �����̈ړ�����
		RotMove(player);

		// �ړ�����
		Move(player);

		// �\�͂̍X�V����
		player.GetAbility()->Update(player);

		// �\��UI�̍X�V����
		player.GetAbilityUI()->Update();

		break;

	case ACT_CANNON:	// ��C�������

		// ��C�Ō�����ς��鏈��
		CannonRot(player);

		// �d�͂̃��Z�b�g����
		GravityReset(player);

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		if (m_nStateCount % CANNON_COUNT == 0)
		{ // ��ԃJ�E���g����萔�̏ꍇ

			// ��C�Ŕ�ԏ���
			FlyMove(player);

			// ���ł����Ԃɂ���
			SetAct(ACT_FLY);
		}

		break;

	case ACT_FLY:		// ���ł�����

		{
			// ���[�J���ϐ��錾
			D3DXVECTOR3 pos = player.GetPos();			// �ʒu���擾����
			D3DXVECTOR3 move = player.GetMove();		// �ړ��ʂ��擾����

			// �d�͂����Z����
			move.y += FLY_GRAVITY;

			// �ړ��ʂ�ݒ肷��
			pos += move;

			// �ʒu��ݒ肷��
			player.SetPos(pos);

			// �ړ��ʂ�ݒ肷��
			player.SetMove(move);
		}

		break;
	}
}

//============================================
// ���̐ݒ菈��
//============================================
void CPlayerAct::SetData(void)
{
	// �S�Ă̒l������������
	m_act = ACT_NONE;		// ���
	m_nStateCount = 0;		// ��ԃJ�E���g
	m_bFront = true;		// �O��֌W
}

//============================================
// ��Ԃ̐ݒ菈��
//============================================
void CPlayerAct::SetAct(const ACT act)
{
	// �s����Ԃ�ݒ肷��
	m_act = act;

	// ��ԃJ�E���g������������
	m_nStateCount = 0;
}

//============================================
// ��Ԃ̎擾����
//============================================
CPlayerAct::ACT CPlayerAct::GetAct(void) const
{
	// �s����Ԃ�Ԃ�
	return m_act;
}

//============================================
// �O��󋵂̐ݒ菈��
//============================================
void CPlayerAct::SetFront(bool bFront)
{
	// �O��󋵂�ݒ肷��
	m_bFront = bFront;
}

//============================================
// �O��󋵂̎擾����
//============================================
bool CPlayerAct::GetFront(void) const
{
	// �O��󋵂�Ԃ�
	return m_bFront;
}

//============================================
// ��������
//============================================
CPlayerAct* CPlayerAct::Create(void)
{
	// ���[�J���ϐ��錾
	CPlayerAct* pAct = nullptr;		// �s�����

	if (pAct == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		pAct = new CPlayerAct;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return pAct;
	}

	if (pAct != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAct->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�v���C���[�̍s���̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAct->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pAct;
}

//=======================================
// ���쏈��
//=======================================
void CPlayerAct::Control(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move = player.GetMove();		// �ړ���
	D3DXVECTOR3 rotDest = player.GetRotDest();	// �ڕW�̌���

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // D�L�[���������ꍇ

		// ���[�h���Ƃ̃X�s�[�h����
		ModeSpeed(player);

		// �ړ��̊�{����
		MoveProcess(player);

		// �E�����󋵂� true �ɂ���
		player.SetEnableRight(true);

		// �ڕW�̌�����ݒ肷��
		rotDest.y = D3DX_PI * 0.5f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[���������ꍇ

		// ���[�h���Ƃ̃X�s�[�h����
		ModeSpeed(player);

		// �ړ��̊�{����
		MoveProcess(player);

		// �E�����󋵂� false �ɂ���
		player.SetEnableRight(false);

		// �ڕW�̌�����ݒ肷��
		rotDest.y = -D3DX_PI * 0.5f;
	}
	else
	{ // ��L�ȊO

		// ���x��ݒ肷��
		player.SetSpeed(0.0f);

		// �ړ��󋵂� false �ɂ���
		player.SetEnableMove(false);

		if (player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_NEUTRAL)
		{ // �ҋ@���[�V��������Ȃ��ꍇ

			// �ҋ@���[�V������ݒ肷��
			player.GetMotion()->Set(CPlayer::MOTIONTYPE_NEUTRAL);
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		player.IsJump() == false)
	{ // SPACE�L�[���������ꍇ

		// �W�����v�̈ړ��ʂ�ݒ肷��
		move.y = JUMP_MOVE;

		// �W�����v�󋵂� true �ɂ���
		player.SetEnableJump(true);
	}

	// �ڕW�̌�����K�p����
	player.SetRotDest(rotDest);

	// �ړ��ʂ�K�p����
	player.SetMove(move);
}

//=======================================
// �ړ��̊�{����
//=======================================
void CPlayerAct::MoveProcess(CPlayer& player)
{
	// �ړ��󋵂� true �ɂ���
	player.SetEnableMove(true);

	if (player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_MOVE)
	{ // �ړ����[�V��������Ȃ��ꍇ

		// �ړ����[�V������ݒ肷��
		player.GetMotion()->Set(CPlayer::MOTIONTYPE_MOVE);
	}
}

//=======================================
// ���[�h���Ƃ̃X�s�[�h����
//=======================================
void CPlayerAct::ModeSpeed(CPlayer& player)
{
	switch (player.GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// �A�N���o�b�g���[�h

		switch (player.GetAbility()->GetAbility())
		{
		case CAbility::ABILITY_JETDASH:		// �W�F�b�g�_�b�V��

			// ���x��ݒ肷��
			player.SetSpeed(0.0f);

			break;

		default:

			// ���x��ݒ肷��
			player.SetSpeed(PLAYER_ACROBAT_SPEED);

			break;
		}

		break;

	case CPlayer::MODE_MASSIVE:		// �}�b�V�u���[�h

		break;

	case CPlayer::MODE_REBOOT:		// ���u�[�g�h���C�u���[�h

		break;
	}
}

//=======================================
// �\�͑��쏈��
//=======================================
void CPlayerAct::Ability(CPlayer& player)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_U) == true)
	{ // U�L�[���������ꍇ

		switch (player.GetMode())
		{
		case CPlayer::MODE_ACROBAT:		// �A�N���o�b�g���[�h

			if (player.GetAbility()->GetPossible(CAbility::TYPE_HOVER) == true &&
				player.IsJump() == true)
			{ // �W�����v�󋵂� true �̏ꍇ

				// �z�o�[�W�F�b�g��Ԃɂ���
				player.GetAbility()->SetAbility(CAbility::ABILITY_HOVER);

				// �g�p�\�󋵂� false �ɂ���
				player.GetAbility()->SetPossible(CAbility::TYPE_HOVER, false);

				// �Ԋu�J�E���g��ݒ肷��
				player.GetAbility()->SetInterval(CAbility::TYPE_HOVER, HOVER_INTERVAL);
			}

			break;

		case CPlayer::MODE_MASSIVE:		// �}�b�V�u���[�h

			break;

		case CPlayer::MODE_REBOOT:		// ���u�[�g�h���C�u

			break;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_I) == true)
	{ // I�L�[���������ꍇ

		switch (player.GetMode())
		{
		case CPlayer::MODE_ACROBAT:		// �A�N���o�b�g���[�h

			if (player.GetAbility()->GetPossible(CAbility::TYPE_JETDASH) == true)
			{ // �W�����v�󋵂� true �̏ꍇ

				// �W�F�b�g�_�b�V����Ԃɂ���
				player.GetAbility()->SetAbility(CAbility::ABILITY_JETDASH);

				// �g�p�\�󋵂� false �ɂ���
				player.GetAbility()->SetPossible(CAbility::TYPE_JETDASH, false);

				// �Ԋu�J�E���g��ݒ肷��
				player.GetAbility()->SetInterval(CAbility::TYPE_JETDASH, JETDASH_INTERVAL);
			}

			break;

		case CPlayer::MODE_MASSIVE:		// �}�b�V�u���[�h

			break;

		case CPlayer::MODE_REBOOT:		// ���u�[�g�h���C�u

			break;
		}
	}
}

//=======================================
// �ړ�����
//=======================================
void CPlayerAct::Move(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = player.GetPos();		// �ʒu���擾����
	D3DXVECTOR3 rot = player.GetRot();		// �������擾����
	D3DXVECTOR3 move = player.GetMove();	// �ړ��ʂ��擾����
	
	// �ړ��ʂ�ݒ肷��
	move.x = sinf(rot.y) * player.GetSpeed();

	// �ʒu��ݒ肷��
	pos += move;

	// �ʒu���X�V����
	player.SetPos(pos);
	player.SetMove(move);
}

//=======================================
// �d�͏���
//=======================================
void CPlayerAct::Gravity(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move = player.GetMove();		// �ړ��ʂ��擾����

	switch (player.GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// �A�N���o�b�g���[�h

		switch (player.GetAbility()->GetAbility())
		{
		case CAbility::ABILITY_NONE:

			// �d�͂����Z����
			move.y += ACROBAT_GRAVITY;

			break;

		case CAbility::ABILITY_HOVER:

			// �d�͂����Z����
			move.y = HOVER_GRAVITY;

			break;

		case CAbility::ABILITY_JETDASH:

			// �d�͂����Z����
			move.y = 0.0f;

			break;
		}

		break;

	case CPlayer::MODE_MASSIVE:		// �}�b�V�u���[�h

		// �d�͂����Z����
		move.y += MASSIVE_GRAVITY;

		break;

	case CPlayer::MODE_REBOOT:		// ���u�[�g�h���C�u���[�h

		break;
	}

	// �ړ��ʂ�K�p����
	player.SetMove(move);
}

//=======================================
// �����̈ړ�����
//=======================================
void CPlayerAct::RotMove(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = player.GetRot();				// �������擾����
	D3DXVECTOR3 rotDest = player.GetRotDest();		// �ړI�̌������擾����

	if (rot.y > rotDest.y - ROT_Y_MOVE &&
		rot.y < rotDest.y + ROT_Y_MOVE)
	{ // ��������萔�͈̔͂ɓ������ꍇ

		// ������␳����
		rot.y = rotDest.y;
	}
	else
	{ // ��L�ȊO

		if (player.IsRight() == true)
		{ // �E�����󋵂̏ꍇ

			// ���������Z����
			rot.y -= ROT_Y_MOVE;
		}
		else
		{ // ��L�ȊO

			// ���������Z����
			rot.y += ROT_Y_MOVE;
		}

		// �����𐳋K������
		useful::RotNormalize(&rot.y);
	}

	// �������X�V����
	player.SetRot(rot);
}

//============================================
// ��C�Ō�����ς��鏈��
//============================================
void CPlayerAct::CannonRot(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = player.GetRot();		// �������擾����

	// ������ݒ肷��
	rot.x = -D3DX_PI * 0.5f;

	if (m_bFront == true)
	{ // ��O�ɂ���ꍇ

		// ������ݒ肷��
		rot.y = 0.0f;
	}
	else
	{ // ���ɂ���ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI;
	}

	// �������X�V����
	player.SetRot(rot);
}

//============================================
// �d�͂̃��Z�b�g����
//============================================
void CPlayerAct::GravityReset(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move = player.GetMove();		// �ړ��ʂ��擾����

	// �c�̈ړ��ʂ�ݒ肷��
	move.y = 0.0f;

	// �ړ��ʂ�K�p����
	player.SetMove(move);
}

//============================================
// ��C�Ŕ�ԏ���
//============================================
void CPlayerAct::FlyMove(CPlayer& player)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = player.GetRot();
	D3DXVECTOR3 move = player.GetMove();		// �ړ��ʂ��擾����

	// �ړ��ʂ�����������
	move.x = 0.0f;
	move.y = CANNON_Y_MOVE;
	move.z = cosf(rot.y) * CANNON_Z_MOVE;

	// �ړ��ʂ�K�p����
	player.SetMove(move);
}