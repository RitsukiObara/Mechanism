//============================================
//
// �v���C���[�̍s����Ԃ̃��C������[player_act.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "player.h"
#include "player_act.h"
#include "player_ability.h"
#include "collision.h"
#include "useful.h"
#include "input.h"

#include "motion.h"
#include "turn.h"
#include "sound.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define CANNON_COUNT			(40)								// ��Ԃ܂ł̃J�E���g
#define ROT_Y_MOVE				(D3DX_PI * 0.1f)					// �����̈ړ���(Y��)
#define JUMP_MOVE				(20.0f)								// �W�����v�̈ړ���
#define CANNON_Y_MOVE			(30.0f)								// ��C��Y���̈ړ���
#define CANNON_Z_MOVE			(15.0f)								// ��C��Z���̈ړ���
#define PLAYER_SPEED			(8.0f)								// �v���C���[�̃X�s�[�h
#define DAMAGE_COUNT			(25)								// �_���[�W��Ԃ̃J�E���g��
#define INVINCIBLE_ALPHA_CHANGE	(6)									// ���G��Ԃ̓����x���ς��J�E���g
#define INVINCIBLE_COUNT		(70)								// ���G��Ԃ̃J�E���g��
#define TURN_SHIFT				(D3DXVECTOR3(55.0f, 25.0f, 0.0f))	// �U������̂������W
#define DEATH_COUNT				(20)								// ���ʂ܂ł̃J�E���g
#define DEATH_JUMP				(20.0f)								// ���񂾂Ƃ��̃W�����v��
#define NONE_GRAVITY			(-0.9f)								// �ʏ��Ԃ̏d��
#define HOVER_GRAVITY			(0.8f)								// �z�o�[��Ԃ̏d��
#define FALL_GRAVITY			(-0.5f)								// ������Ԃ̏d��
#define RUN_SOUND_COUNT			(22)									// ���艹�̖�J�E���g��

//============================================
// �R���X�g���N�^
//============================================
CPlayerAct::CPlayerAct()
{
	// �S�Ă̒l���N���A����
	m_state = STATE_NONE;			// ���
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
	m_state = STATE_NONE;			// ���
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
	switch (m_state)
	{
	case STATE_NONE:		// �ʏ���

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		// �ʏ펞�̑��쏈��
		NoneControl(player);

		// �����x�̐ݒ菈��
		player.SetAlpha(1.0f);

		break;

	case STATE_DAMAGE:			// �_���[�W���

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		if (m_nStateCount >= DAMAGE_COUNT)
		{ // ��ԃJ�E���g����萔�ȏ�̏ꍇ

			// ��Ԃ̐ݒ菈��
			SetState(STATE_INVINCIBLE);

			// �_���[�W��Ԃɂ���
			player.GetMotion()->Set(CPlayer::MOTIONTYPE_DAMAGE);

			// �����̌��菈��
			RotDecide(player);

			// �����x��ݒ肷��
			player.SetAlpha(0.0f);
		}

		break;

	case STATE_INVINCIBLE:			// ���G���

		// �ʏ펞�̑��쏈��
		NoneControl(player);

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		if (m_nStateCount % INVINCIBLE_ALPHA_CHANGE == 0)
		{ // ��ԃJ�E���g����萔�ɒB���邲�Ƃ�

			// �����x�̓���ւ�����
			player.SwapAlpha();
		}

		if (m_nStateCount >= INVINCIBLE_COUNT)
		{ // ��ԃJ�E���g����萔�ȏゾ�����ꍇ

			// �����x��ݒ肷��
			player.SetAlpha(1.0f);

			// ��Ԃ̐ݒ菈��
			SetState(STATE_NONE);
		}

		break;

	case STATE_BOUND:		// �o�E���h���

		// �d�͏���
		Gravity(player);

		// �ړ�����
		Move(player);

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		if (m_nStateCount >= 10)
		{ // ��ԃJ�E���g����萔�ȏ�̏ꍇ

			// ��Ԃ̐ݒ菈��
			SetState(STATE_NONE);
		}

		break;

	case STATE_CANNON:		// ��C�������

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
			SetState(STATE_FLY);

			// ��C�Ŕ�ԉ���炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CANNON);
		}

		break;

	case STATE_FLY:			// ���ł�����

		{
			// ���[�J���ϐ��錾
			D3DXVECTOR3 pos = player.GetPos();			// �ʒu���擾����
			D3DXVECTOR3 move = player.GetMove();		// �ړ��ʂ��擾����

			// �d�͂����Z����
			move.y += NONE_GRAVITY;

			// �ړ��ʂ�ݒ肷��
			pos += move;

			// �ʒu��ݒ肷��
			player.SetPos(pos);

			// �ړ��ʂ�ݒ肷��
			player.SetMove(move);
		}

		break;

	case STATE_DEATH:		// ���S���

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		if (m_nStateCount % DEATH_COUNT == 0)
		{ // ��ԃJ�E���g����萔�ɒB�����ꍇ

			// �ړ��ʂ��擾����
			D3DXVECTOR3 move = player.GetMove();

			// ������Ԃɂ���
			m_state = STATE_FALL;

			// �ړ��ʂ�ݒ肷��
			move.y = DEATH_JUMP;

			// �ړ��ʂ�K�p����
			player.SetMove(move);
		}

		break;

	case STATE_FALL:		// �������

		// �d�͏���
		Gravity(player);

		// �ړ�����
		Move(player);

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
void CPlayerAct::SetData(void)
{
	// �S�Ă̒l������������
	m_state = STATE_NONE;		// ���
	m_nStateCount = 0;		// ��ԃJ�E���g
	m_bFront = true;		// �O��֌W
}

//============================================
// ��Ԃ̐ݒ菈��
//============================================
void CPlayerAct::SetState(const STATE act)
{
	// �s����Ԃ�ݒ肷��
	m_state = act;

	// ��ԃJ�E���g������������
	m_nStateCount = 0;
}

//============================================
// ��Ԃ̎擾����
//============================================
CPlayerAct::STATE CPlayerAct::GetState(void) const
{
	// �s����Ԃ�Ԃ�
	return m_state;
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
// �ʏ펞�̑��쏈��
//=======================================
void CPlayerAct::NoneControl(CPlayer& player)
{
	if (player.GetAbility()->GetAbility() != CAbility::ABILITY_GROUNDQUAKE)
	{ // �O���E���h�N�G�C�N��ԈȊO�̏ꍇ

		// ���쏈��
		Control(player);

		// �d�͏���
		Gravity(player);

		// �����̈ړ�����
		RotMove(player);

		// �ړ�����
		Move(player);
	}
	else
	{ // ��L�ȊO

		// �O���E���h�N�G�C�N����
		GroundQuake(player);
	}

	// �\�͂̍X�V����
	player.GetAbility()->Update(player);
}

//=======================================
// �O���E���h�N�G�C�N����
//=======================================
void CPlayerAct::GroundQuake(CPlayer& player)
{
	// �ʒu���擾����
	D3DXVECTOR3 move = player.GetMove();

	// ���x��ݒ肷��
	player.SetSpeed(0.0f);

	// �ړ��ʂ�ݒ肷��
	move.x = 0.0f;
	move.z = 0.0f;

	// �d�͏���
	Gravity(player);

	// �ړ�����
	Move(player);

	// �ړ��ʂ�ݒ肷��
	player.SetMove(move);
}

//=======================================
// �����̌��菈��
//=======================================
void CPlayerAct::RotDecide(CPlayer& player)
{
	// �������擾����
	D3DXVECTOR3 rot = player.GetRot();

	if (player.IsRight() == true)
	{ // �E�����̏ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI * 0.5f;
	}
	else
	{ // ��L�ȊO

		// ������ݒ肷��
		rot.y = -D3DX_PI * 0.5f;
	}

	// ������K�p����
	player.SetRot(rot);
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

		if (player.GetAbility()->GetAbility() != CAbility::ABILITY_JETDASH &&
			player.GetAbility()->GetAbility() != CAbility::ABILITY_DASHJUMP)
		{ // ���̏�ԈȊO�̏ꍇ

			if (player.IsRight() == false)
			{ // �������������ꍇ

				// �E�����ɂ���
				player.SetEnableRight(true);

				if (player.GetAbility()->GetAbility() != CAbility::ABILITY_JETDASH &&
					player.GetAbility()->GetAbility() != CAbility::ABILITY_DASHJUMP &&
					player.IsJump() == false)
				{ //�n�ʂŐU��������ꍇ

					// �U������̈ʒu��ݒ肷��
					D3DXVECTOR3 pos = D3DXVECTOR3(player.GetPos().x + sinf(player.GetRot().y) * TURN_SHIFT.x, player.GetPos().y + TURN_SHIFT.y, player.GetPos().z);

					// �U��������o�̐���
					CTurn::Create(pos, player.IsRight());
				}
			}

			// �ڕW�̌�����ݒ肷��
			rotDest.y = D3DX_PI * 0.5f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[���������ꍇ

		// ���[�h���Ƃ̃X�s�[�h����
		ModeSpeed(player);

		// �ړ��̊�{����
		MoveProcess(player);

		if (player.GetAbility()->GetAbility() != CAbility::ABILITY_JETDASH &&
			player.GetAbility()->GetAbility() != CAbility::ABILITY_DASHJUMP)
		{ // ���̏�ԈȊO�̏ꍇ

			if (player.IsRight() == true)
			{ // �E�����������ꍇ

				// �������󋵂ɂ���
				player.SetEnableRight(false);

				if (player.GetAbility()->GetAbility() != CAbility::ABILITY_JETDASH &&
					player.GetAbility()->GetAbility() != CAbility::ABILITY_DASHJUMP &&
					player.IsJump() == false)
				{ //�n�ʂŐU��������ꍇ

					// �U������̈ʒu��ݒ肷��
					D3DXVECTOR3 pos = D3DXVECTOR3(player.GetPos().x + sinf(player.GetRot().y) * TURN_SHIFT.x, player.GetPos().y + TURN_SHIFT.y, player.GetPos().z);

					// �U��������o�̐���
					CTurn::Create(pos, player.IsRight());
				}
			}

			// �ڕW�̌�����ݒ肷��
			rotDest.y = -D3DX_PI * 0.5f;
		}
	}
	else
	{ // ��L�ȊO

		// ���x��ݒ肷��
		player.SetSpeed(0.0f);

		// �ړ��󋵂� false �ɂ���
		player.SetEnableMove(false);

		if (player.GetAbility()->GetAbility() == CAbility::ABILITY_NONE &&
			player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_NEUTRAL &&
			player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_JUMP &&
			player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_LANDING &&
			player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_APPEAR)
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

		// �W�����v����炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);

		if (player.GetAbility()->GetAbility() == CAbility::ABILITY_NONE &&
			player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_JUMP)
		{ // �W�����v���[�V��������Ȃ��ꍇ

			// �W�����v���[�V������ݒ肷��
			player.GetMotion()->Set(CPlayer::MOTIONTYPE_JUMP);
		}
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
	if (player.IsMove() == false)
	{
		// �ړ��󋵂� true �ɂ���
		player.SetEnableMove(true);

		if (player.IsJump() == false)
		{ // �n��̏ꍇ

			// ����n�߉���炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_RUNSTART);
		}
	}

	if (player.GetAbility()->GetAbility() == CAbility::ABILITY_NONE &&
		player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_MOVE &&
		player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_JUMP &&
		player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_LANDING)
	{ // �ړ����[�V��������Ȃ��ꍇ

		// �ړ����[�V������ݒ肷��
		player.GetMotion()->Set(CPlayer::MOTIONTYPE_MOVE);
	}

	if (player.IsJump() == false &&
		player.GetAbility()->GetAbility() != CAbility::ABILITY_JETDASH &&
		m_nStateCount % RUN_SOUND_COUNT == 0)
	{ // �n��𓮂��Ĉ�莞�Ԍo�߂����ꍇ

		// ���艹��炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_RUN);
	}
}

//=======================================
// ���[�h���Ƃ̃X�s�[�h����
//=======================================
void CPlayerAct::ModeSpeed(CPlayer& player)
{
	switch (player.GetAbility()->GetAbility())
	{
	case CAbility::ABILITY_JETDASH:		// �W�F�b�g�_�b�V��

		// ���x��ݒ肷��
		player.SetSpeed(0.0f);

		break;

	case CAbility::ABILITY_DASHJUMP:	// �_�b�V���W�����v

		// �ʂ̂Ƃ���ő��x�Ɋւ��鏈�����s���Ă���̂Ŗ���

		break;

	default:

		// ���x��ݒ肷��
		player.SetSpeed(PLAYER_SPEED);

		break;
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

	if (player.GetAbility()->GetAbility() == CAbility::ABILITY_HOVER)
	{ // �z�o�[�W�F�b�g��Ԃ̏ꍇ

		// �d�͂�ݒ肷��
		move.y = HOVER_GRAVITY;
	}
	else if (m_state == STATE_FALL)
	{ // ������Ԃ̏ꍇ

		// �d�͂����Z����
		move.y += FALL_GRAVITY;
	}
	else
	{ // ��L�ȊO

		// �d�͂����Z����
		move.y += NONE_GRAVITY;
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