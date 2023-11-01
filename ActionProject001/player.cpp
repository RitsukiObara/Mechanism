//============================================
//
// �v���C���[�̃��C������[player.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "player.h"
#include "player_act.h"
#include "player_ability.h"
#include "screwUI.h"
#include "lifeUI.h"
#include "combo.h"
#include "combo_magni.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "sound.h"
#include "useful.h"
#include "texture.h"

#include "camera.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "Particle.h"
#include "motion.h"
#include "shadowCircle.h"
#include "game_score.h"
#include "goal.h"
#include "bonus.h"
#include "destruction.h"
#include "ripple.h"
#include "push_timing.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_LIFE				(3)			// �̗͂̍ő吔
#define STEPHIT_JUMP			(20.0f)		// ���݂����Ƃ��̃W�����v��
#define COLLISION_WIDTH			(20.0f)		// �����蔻�莞�Ɏg�����̕�
#define COLLISION_HEIGHT		(150.0f)	// �����蔻�莞�Ɏg�����̍���
#define COLLISION_DEPTH			(20.0f)		// �����蔻�莞�Ɏg�����̉��s
#define START_CAMERA_POSR_Y		(100.0f)	// �X�^�[�g���̃J�����̒����_(Y��)
#define START_CAMERA_POSV_Y		(130.0f)	// �X�^�[�g���̃J�����̎��_(Y��)
#define START_CAMERA_DISTANCE	(200.0f)	// �X�^�[�g���̃J�����̋���
#define START_COUNT				(40)		// �X�^�[�g�̃J�E���g
#define PUNCH_COUNT				(150)		// �p���`��Ԃ̃J�E���g��
#define GOAL_COUNT				(80)		// �S�[����Ԃ̃J�E���g��
#define LEAVE_GRAVITY			(0.4f)		// �ޏ��Ԃ̏d��
#define FINISH_GRAVITY			(-0.6f)		// �I����Ԃ̏d��
#define NEAR_POS				(0.0f)		// ��O�̈ʒu
#define FAR_POS					(1000.0f)	// ���s�̈ʒu
#define ADD_GRAVITY				(-50.0f)	// �ǉ��̏d��
#define BOUND_SPEED				(-5.0f)		// �o�E���h���̃X�s�[�h
#define FALL_HEIGHT				(-600.0f)	// ���������肪�ʂ鏊
#define PUNCH_DSTR_SHIFT		(D3DXVECTOR3(40.0f, 100.0f, 0.0f))		// �p���`���̌��j�̂��炷��
#define PUNCH_DSTR_SIZE			(D3DXVECTOR3(100.0f, 100.0f, 0.0f))		// �p���`���̌��j�̃T�C�Y
#define PUNCH_DSTR_COL			(D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f))		// �p���`���̌��j�̐F
#define PUNCH_DSTR_LIFE			(6)			// �p���`���̌��j�̎���
#define PUNCH_RIPPLE_SHIFT		(D3DXVECTOR3(45.0f, 100.0f, 0.0f))		// �p���`���̔g��̂��炷��
#define OUT_RANGE_GRAVITY		(-5.0f)		// �͈͊O�ɏo���Ƃ��̏d��
#define ADD_START_POS			(D3DXVECTOR3(20.0f, -20.0f, 0.0f))		// �X�^�[�g��Ԃ̉��Z����ʒu

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPlayer* CPlayer::m_pPlayer = nullptr;		// �v���C���[�̃|�C���^

//=========================================
// �R���X�g���N�^
//=========================================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;			// ���[�V�����̏��
	m_pAction = nullptr;			// �v���C���[�̍s���̏��
	m_pAbility = nullptr;			// �\�͂̏��
	m_pScrewUI = nullptr;			// �l�WUI�̏��
	m_pLifeUI = nullptr;			// �̗�UI�̏��
	m_pCombo = nullptr;				// �R���{�̏��
	m_pPushTiming = nullptr;		// �����{�^���̃^�C�~���O
	m_pBlock = nullptr;				// �u���b�N�̏��
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_nStartCount = 0;				// �X�^�[�g�J�E���g
	m_nGoalCount = 0;				// �S�[�����̃J�E���g
	m_nLife = MAX_LIFE;				// �̗�
	m_fSpeed = 0.0f;				// ���x
	m_fAlpha = 1.0f;				// �����x
	m_bMove = false;				// �ړ���
	m_bRight = true;				// �E������
	m_bJump = false;				// �W�����v��
	m_bPunch = false;				// �p���`��
}

//=========================================
// �f�X�g���N�^
//=========================================
CPlayer::~CPlayer()
{

}

//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �x�^�ł�
	SetNumModel(16);

	// �f�[�^�̐ݒ菈��
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // ���[�V������ NULL �������ꍇ

		// ���[�V�����̐�������
		m_pMotion = CMotion::Create();
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ���[�V�����̏����擾����
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ���[�h����
		m_pMotion->Load(CMotion::TYPE_PLAYER);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	m_pMotion->Set(MOTIONTYPE_APPEAR);

	if (m_pAction == nullptr)
	{ // �s����Ԃ� NULL �̏ꍇ

		// �v���C���[�̍s����Ԃ𐶐�
		m_pAction = CPlayerAct::Create();
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pAbility == nullptr)
	{ // �\�͏�Ԃ� NULL �̏ꍇ

		// �\�͂̏��𐶐�
		m_pAbility = CAbility::Create();
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pScrewUI == nullptr)
	{ // �l�WUI�� NULL �̏ꍇ

		// �l�WUI�̏��𐶐�
		m_pScrewUI = CScrewUI::Create();
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pCombo == nullptr)
	{ // �R���{�� NULL �̏ꍇ

		// �R���{�̏��𐶐�
		m_pCombo = CCombo::Create();
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pLifeUI == nullptr)
	{ // �̗�UI�� NULL �̏ꍇ

		// �̗�UI�̏��𐶐�
		m_pLifeUI = CLifeUI::Create();
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	// �S�Ă̒l������������
	m_pPushTiming = nullptr;		// �����{�^���̃^�C�~���O
	m_pBlock = nullptr;				// �u���b�N�̏��
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_nStartCount = 0;				// �X�^�[�g�J�E���g
	m_nGoalCount = 0;				// �S�[�����̃J�E���g
	m_nLife = MAX_LIFE;				// �̗�
	m_fSpeed = 0.0f;				// ���x
	m_fAlpha = 1.0f;				// �����x
	m_bMove = false;				// �ړ���
	m_bRight = true;				// �E������
	m_bJump = false;				// �W�����v��
	m_bPunch = false;				// �p���`��

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CPlayer::Uninit(void)
{
	// ���[�V�����̃��������J������
	delete m_pMotion;
	m_pMotion = nullptr;

	// �s���̏I������
	m_pAction->Uninit();
	m_pAction = nullptr;

	// �\�͂̏I������
	m_pAbility->Uninit();
	m_pAbility = nullptr;

	// �l�WUI�̏I������
	m_pScrewUI->Uninit();
	m_pScrewUI = nullptr;

	// �u���b�N�̃|�C���^�� NULL �ɂ���
	m_pBlock = nullptr;

	// �I������
	CCharacter::Uninit();

	// �v���C���[�� NULL �ɂ���
	m_pPlayer = nullptr;
}

//===========================================
// �X�V����
//===========================================
void CPlayer::Update(void)
{
	// �W�����v�󋵂��擾����
	bool bJump = m_bJump;

	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	switch (CGame::GetState())
	{
	case CGame::STATE_START:

		// �X�^�[�g��Ԃ̏���
		StartProcess();

		break;

	case CGame::STATE_PLAY:

		// �s���̍X�V����
		m_pAction->Update(*this);

		// ��s�@�Ƃ̓����蔻��
		collision::AirplaneHit(*this);

		// �l�W�Ƃ̓����蔻��
		collision::ScrewHit(*this);

		// �G�Ƃ̓����蔻��
		collision::EnemyHit(*this);

		// �G�Ƃ̂߂荞�ݔ��菈��
		collision::EnemyPenetrate(*this);

		// �S�[���Ƃ̓����蔻��
		collision::GoalHit(*this);

		// ���Ƃ̓����蔻��
		collision::NeedleHit(*this);

		break;

	case CGame::STATE_GOAL:

		// �S�[����Ԃ̏���
		GoalProcess();

		break;

	case CGame::STATE_LEAVE:

		// �ޏ��Ԃ̏���
		LeaveProcess();

		break;

	case CGame::STATE_FINISH:

		// �I����Ԃ̏���
		FinishProcess();

		break;

	case CGame::STATE_DEATH:

		// �s���̍X�V����
		m_pAction->Update(*this);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	// �̗�UI�̍X�V����
	m_pLifeUI->Update();

	if (m_pAction->GetState() != CPlayerAct::STATE_FALL)
	{ // ������ԈȊO�̏ꍇ

		// �N���n�ʂƂ̓����蔻�菈��
		ElevationCollision();

		// �u���b�N�Ƃ̓����蔻��
		BlockCollision();

		// ��Ƃ̓����蔻��
		TableCollision();

		// �s����������
		CollisionMagicWall();
	}

	if (m_bJump == false &&
		bJump == true)
	{ // ���n�����u��

		if (m_pMotion->GetType() != MOTIONTYPE_JETDASH &&
			m_pMotion->GetType() != MOTIONTYPE_APPEAR)
		{ // �W�F�b�g�_�b�V�����[�V�����ȊO�̏ꍇ

			// ���n���[�V������ݒ肷��
			m_pMotion->Set(MOTIONTYPE_LANDING);
		}

		// ���n����炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_LANDING);
	}

	// �������菈��
	FallCheck();

	if (m_bJump == true)
	{ // �W�����v���Ă���ꍇ

		// �e�̈ʒu�����̐ݒ菈��
		CShadowCircle::SetPosRotXZ(m_nShadowIdx, GetPos(), GetRot());
	}
	else
	{ // �W�����v���Ă��Ȃ��ꍇ

		// �e�̈ʒu�����̐ݒ菈��
		CShadowCircle::SetPosRot(m_nShadowIdx, GetPos(), GetRot());
	}

	// �͈͊O�̓����蔻��
	OutRangeCollision();

	// �v���C���[�̏���\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�ړ��ʁF%f %f %f\n�v���C���[�̏�ԁF%d\n�W�����v�󋵁F%d\n", GetPos().x, GetPos().y, GetPos().z, m_move.x, m_move.y, m_move.z, m_pAction->GetState(), m_bJump);
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	switch (m_pAction->GetState())
	{
	case CPlayerAct::STATE_INVINCIBLE:		// ���G���

		// �`�揈��
		CCharacter::Draw(m_fAlpha);

		break;

	case CPlayerAct::STATE_DEATH:			// ���S���
	case CPlayerAct::STATE_DAMAGE:			// �_���[�W���

		// Z�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);					//Z�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//Z�e�X�g�̗L��/�����ݒ�

		// �`�揈��
		CCharacter::Draw(m_fAlpha);

		// Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Z�e�X�g�̗L��/�����ݒ�

		break;

	default:

		// �`�揈��
		CCharacter::Draw();

		break;
	}
}

//===========================================
// ���[�V�����̏��̐ݒ菈��
//===========================================
CMotion* CPlayer::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//===========================================
// �A�N�V�����̏��̐ݒ菈��
//===========================================
CPlayerAct* CPlayer::GetAction(void) const
{
	// �s����Ԃ̏���Ԃ�
	return m_pAction;
}

//===========================================
// �\�͂̏��̐ݒ菈��
//===========================================
CAbility* CPlayer::GetAbility(void) const
{
	// �\�͂̏���Ԃ�
	return m_pAbility;
}

//===========================================
// �l�WUI�̏��̎擾����
//===========================================
CScrewUI* CPlayer::GetScrewUI(void) const
{
	// �l�WUI�̏���Ԃ�
	return m_pScrewUI;
}

//===========================================
// �̗�UI�̏��̎擾����
//===========================================
CLifeUI* CPlayer::GetLifeUI(void) const
{
	// �̗�UI�̏���Ԃ�
	return m_pLifeUI;
}

//===========================================
// �R���{�̏��̎擾����
//===========================================
CCombo* CPlayer::GetCombo(void) const
{
	// �R���{�̏���Ԃ�
	return m_pCombo;
}

//===========================================
// �����{�^���̏��̐ݒ菈��
//===========================================
void CPlayer::SetPushTiming(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �����{�^���𐶐�
	m_pPushTiming = CPushTiming::Create(D3DXVECTOR3(pos.x + sinf(-rot.y) * 100.0f, pos.y + 160.0f, pos.z));
}

//===========================================
// �����{�^���̏��̎擾����
//===========================================
CPushTiming* CPlayer::GetPushTiming(void) const
{
	// �����{�^����Ԃ�
	return m_pPushTiming;
}

//===========================================
// �u���b�N�̏��̎擾����
//===========================================
CBlock* CPlayer::GetBlock(void) const
{
	// �u���b�N�̏���Ԃ�
	return m_pBlock;
}

//===========================================
// �u���b�N��NULL������
//===========================================
void CPlayer::DeleteBlock(void)
{
	// �u���b�N�̃|�C���^�� NULL �ɂ���
	m_pBlock = nullptr;
}

//===========================================
// �擾����
//===========================================
CPlayer* CPlayer::Get(void)
{
	if (m_pPlayer != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

		// �v���C���[�̃|�C���^��Ԃ�
		return m_pPlayer;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// �v���C���[�̃|�C���^��Ԃ�
		return m_pPlayer;
	}
}

//===========================================
// ��������
//===========================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos)
{
	if (m_pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pPlayer = new CPlayer;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return m_pPlayer;
	}

	if (m_pPlayer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�v���C���[�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pPlayer->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return m_pPlayer;
}

//=======================================
// �q�b�g����
//=======================================
void CPlayer::Hit(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	if (m_pAction->GetState() != CPlayerAct::STATE_DAMAGE &&
		m_pAction->GetState() != CPlayerAct::STATE_INVINCIBLE &&
		m_pAction->GetState() != CPlayerAct::STATE_CANNON &&
		m_pAction->GetState() != CPlayerAct::STATE_DEATH &&
		m_pAction->GetState() != CPlayerAct::STATE_FALL)
	{ // ���̏�ԈȊO�̏ꍇ

		// �_���[�W����炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);
		
		// �̗͂����Z����
		m_nLife--;

		if (m_nLife <= 0)
		{ // �����������Ȃ��ꍇ

			// �̗͂�0�ɂ���
			m_nLife = 0;

			// ���S��Ԃɂ���
			m_pAction->SetState(CPlayerAct::STATE_DEATH);

			// �Q�[���̏�Ԃ����S��Ԃɂ���
			CGame::SetState(CGame::STATE_DEATH);

			// �ړ��ʂ�����������
			m_move = NONE_D3DXVECTOR3;

			// ���x������������
			m_fSpeed = 0.0f;
		}
		else
		{ // ��L�ȊO

			// �_���[�W��Ԃɂ���
			m_pAction->SetState(CPlayerAct::STATE_DAMAGE);
		}

		// �_���[�W���[�V������ݒ肷��
		m_pMotion->Set(MOTIONTYPE_DAMAGE);

		// ������ݒ肷��
		rot.y = D3DX_PI;

		// �����p�[�e�B�N���𐶐�
		CParticle::Create(GetPos(), CParticle::TYPE_FIRE);

		// ���\�͏�Ԃɂ���
		m_pAbility->SetAbility(CAbility::ABILITY_NONE, *this);

		// ���j�̐�������
		CDestruction::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 100.0f, GetPos().z), D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CDestruction::TYPE_EXPLOSION, 20);
	}

	// ������K�p����
	SetRot(rot);
}

//=======================================
// ���݂����̏���
//=======================================
void CPlayer::StepHit(void)
{
	// �ړ��ʂ��グ��
	m_move.y = STEPHIT_JUMP;

	// ���݂�����炷
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_STEPPING);

	// �R���{�̉��Z����
	m_pCombo->AddCombo(100);
}

//=======================================
// �o�E���h����
//=======================================
void CPlayer::BoundHit(void)
{
	if (m_pAction->GetState() != CPlayerAct::STATE_BOUND &&
		m_pAction->GetState() != CPlayerAct::STATE_DAMAGE &&
		m_pAction->GetState() != CPlayerAct::STATE_INVINCIBLE)
	{ // ���̏�ԈȊO�̏ꍇ

		// �o�E���h��Ԃɂ���
		m_pAction->SetState(CPlayerAct::STATE_BOUND);

		// ���\�͏�Ԃɂ���
		m_pAbility->SetAbility(CAbility::ABILITY_NONE, *this);

		// ���x��ݒ肷��
		m_fSpeed = BOUND_SPEED;
	}
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CPlayer::SetData(const D3DXVECTOR3& pos)
{
	// �S�Ă̒l������������
	m_posDest = pos;	// �ړI�̈ʒu
	SetPos(D3DXVECTOR3(pos.x - 500.0f, pos.y + 400.0f, pos.z));		// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));				// ����
	SetScale(NONE_SCALE);			// �g�嗦

	m_rotDest = GetRot();	// �ړI�̌�����ݒ肷��

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// ����������
		GetHierarchy(nCntData)->SetPos(pos);										// �ʒu
		GetHierarchy(nCntData)->SetPosOld(pos);										// �O��̈ʒu
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));	// �f�[�^�̐ݒ菈��
	}

	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = nullptr;		// �e�ւ̃|�C���^

	// �e�̐ݒ菈��
	pShadow = CShadowCircle::Create(pos, GetRot(), 40.0f);

	if (pShadow != nullptr)
	{ // �e�̃|�C���^�� NULL�ȊO�̏ꍇ

		// �e�̃C���f�b�N�X�ݒ�
		m_nShadowIdx = pShadow->GetNumID();
	}

	// ���[�V�����̐ݒ菈��
	m_pMotion->Set(MOTIONTYPE_APPEAR);

	// �J������ݒ肷��
	CManager::Get()->GetCamera()->SetPosR(D3DXVECTOR3(pos.x, pos.y + START_CAMERA_POSR_Y, pos.z));
	CManager::Get()->GetCamera()->SetPosV(D3DXVECTOR3(pos.x, pos.y + START_CAMERA_POSV_Y, pos.z));
	CManager::Get()->GetCamera()->SetDistance(START_CAMERA_DISTANCE);
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
D3DXVECTOR3 CPlayer::GetMove(void) const
{
	// �ړ��ʂ�Ԃ�
	return m_move;
}

//=======================================
// �ڕW�̌����̐ݒ菈��
//=======================================
void CPlayer::SetRotDest(const D3DXVECTOR3& rot)
{
	// �ڕW�̌�����ݒ肷��
	m_rotDest = rot;
}

//=======================================
// �ڕW�̌����̎擾����
//=======================================
D3DXVECTOR3 CPlayer::GetRotDest(void) const
{
	// �ڕW�̌�����Ԃ�
	return m_rotDest;
}

//=======================================
// �̗͂̐ݒ菈��
//=======================================
void CPlayer::SetLife(const int nLife)
{
	if (nLife > MAX_LIFE)
	{ // �̗͂����ȏ�̏ꍇ

		// �̗͂��ő�ɐݒ肷��
		m_nLife = MAX_LIFE;
	}
	else
	{ // ��L�ȊO

		// �̗͂�ݒ肷��
		m_nLife = nLife;
	}
}

//=======================================
// �̗͂̎擾����
//=======================================
int CPlayer::GetLife(void) const
{
	// �̗͂�Ԃ�
	return m_nLife;
}

//=======================================
// ���x�̐ݒ菈��
//=======================================
void CPlayer::SetSpeed(float fSpeed)
{
	// ���x��ݒ肷��
	m_fSpeed = fSpeed;
}

//=======================================
// ���x�̎擾����
//=======================================
float CPlayer::GetSpeed(void) const
{
	// ���x��Ԃ�
	return m_fSpeed;
}

//=======================================
// �����x�̐ݒ菈��
//=======================================
void CPlayer::SetAlpha(const float fAlpha)
{
	// �����x��ݒ肷��
	m_fAlpha = fAlpha;
}

//=======================================
// �����x�̓���ւ�����
//=======================================
void CPlayer::SwapAlpha(void)
{
	// �����x�����ւ���
	m_fAlpha = (m_fAlpha >= 1.0f) ? 0.0f : 1.0f;
}

//=======================================
// �����x�̎擾����
//=======================================
float CPlayer::GetAlpha(void) const
{
	// �����x��Ԃ�
	return m_fAlpha;
}

//=======================================
// �ړ��󋵂̐ݒ菈��
//=======================================
void CPlayer::SetEnableMove(bool bMove)
{
	// �ړ��󋵂�ݒ肷��
	m_bMove = bMove;
}

//=======================================
// �ړ��󋵂̎擾����
//=======================================
bool CPlayer::IsMove(void) const
{
	// �ړ��󋵂�Ԃ�
	return m_bMove;
}

//=======================================
// �E�����󋵂̐ݒ菈��
//=======================================
void CPlayer::SetEnableRight(bool bRight)
{
	// �E�����󋵂�ݒ肷��
	m_bRight = bRight;
}

//=======================================
// �E�����󋵂̎擾����
//=======================================
bool CPlayer::IsRight(void) const
{
	// �E�����󋵂��擾����
	return m_bRight;
}

//=======================================
// �W�����v�󋵂̐ݒ菈��
//=======================================
void CPlayer::SetEnableJump(bool bJump)
{
	// �W�����v�󋵂�ݒ肷��
	m_bJump = bJump;
}

//=======================================
// �W�����v�󋵂̎擾����
//=======================================
bool CPlayer::IsJump(void) const
{
	// �W�����v�󋵂�Ԃ�
	return m_bJump;
}

//=======================================
// �p���`�󋵂̐ݒ菈��
//=======================================
void CPlayer::SetEnablePunch(bool bPunch)
{
	// �p���`�󋵂�ݒ肷��
	m_bPunch = bPunch;
}

//=======================================
// �p���`�󋵂̎擾����
//=======================================
bool CPlayer::IsPunch(void) const
{
	// �p���`�󋵂�Ԃ�
	return m_bPunch;
}

//=======================================
// �N���n�ʂ̓����蔻�菈��
//=======================================
void CPlayer::ElevationCollision(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	float fHeight = 0.0f;			// ����
	bool bJump = true;				// �W�����v��
	bool bRange = false;			// �͈͓���

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos, bRange);
		
		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight;

			// �d�͂�ݒ肷��
			m_move.y = ADD_GRAVITY;

			// �W�����v�󋵂� false �ɂ���
			bJump = false;

			if (m_pAction->GetState() == CPlayerAct::STATE_CANNON ||
				m_pAction->GetState() == CPlayerAct::STATE_FLY)
			{ // �ʏ��ԈȊO�̏ꍇ

				// �ʏ��Ԃ̐ݒ菈��
				SetNone();

				if (m_pAction->GetFront() == true)
				{ // �O��󋵂�ݒ肷��

					// ���ɂ���
					pos.z = FAR_POS;

					// �O��󋵂�ݒ肷��
					m_pAction->SetFront(false);
				}
				else
				{ // ��L�ȊO

					// ��O�ɂ���
					pos.z = NEAR_POS;

					// �O��󋵂�ݒ肷��
					m_pAction->SetFront(true);
				}

				// ���Z�b�g����
				m_pAbility->ResetAbility();
			}

			if (CGame::GetState() == CGame::STATE_LEAVE)
			{ // �ޏ��Ԃ̏ꍇ

				// �ړ��ʂ�ݒ肷��
				m_move.x = 0.0f;
				m_move.y = 0.0f;

				// �I����Ԃɂ���
				CGame::SetState(CGame::STATE_FINISH);
			}
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	if (bRange == false &&
		m_bJump != bJump)
	{ // �͈͊O�ɏo���u��

		// �d�͂𖳂���
		m_move.y = OUT_RANGE_GRAVITY;
	}

	// �W�����v�󋵂�������
	m_bJump = bJump;

	// �ʒu���X�V����
	SetPos(pos);
}

//=======================================
// ���n���̒ʏ��Ԃ̐ݒ菈��
//=======================================
void CPlayer::SetNone(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();		// �������擾����

	// �ʏ��Ԃɂ���
	m_pAction->SetState(CPlayerAct::STATE_NONE);

	// �ړ��ʂ�ݒ肷��
	m_move.z = 0.0f;

	// ������ݒ肷��
	rot.x = 0.0f;
	rot.z = 0.0f;

	if (m_bRight == true)
	{ // �E�����󋵂� true �̏ꍇ

		// �E����������
		rot.y = D3DX_PI * 0.5f;
	}
	else
	{ // ��L�ȊO

		// ������������
		rot.y = -D3DX_PI * 0.5f;
	}

	// ���̐ݒ菈��
	SetRot(rot);			// ������ݒ肷��
}

//=======================================
// �ړ���������
//=======================================
void CPlayer::CollisionMagicWall(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	if (pos.z >= FAR_POS)
	{ // �ʒu�����ȏ�ɂȂ����ꍇ

		// �ʒu��␳����
		pos.z = FAR_POS;
	}

	if (pos.z <= NEAR_POS)
	{ // �ʒu�����ȉ��ɂȂ����ꍇ

		// �ʒu��␳����
		pos.z = NEAR_POS;
	}

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �u���b�N�̓����蔻��
//=======================================
void CPlayer::BlockCollision(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu

	// �u���b�N�Ƃ̓����蔻��
	if (collision::BlockCollision(&pos, posOld, COLLISION_WIDTH, COLLISION_HEIGHT, m_bJump, &m_pBlock))
	{ // ���n�����ꍇ

		// �W�����v���Ă��Ȃ�
		m_bJump = false;

		// �ړ��ʂ�0�ɂ���
		m_move.y = 0.0f;
	}
	else
	{ // ��L�ȊO

		// �u���b�N�̃|�C���^�� NULL �ɂ���
		m_pBlock = nullptr;
	}

	// ����ݒ肷��
	SetPos(pos);	// �ʒu
}

//=======================================
// ��Ƃ̓����蔻��
//=======================================
void CPlayer::TableCollision(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu

	if (collision::TableCollision(&pos, posOld, COLLISION_WIDTH, COLLISION_DEPTH) == true)
	{ // ��Ƃ̓����蔻�肪 true �������ꍇ

		// �c�̈ړ��ʂ𖳂���
		m_move.y = 0.0f;

		// �W�����v�󋵂� false �ɂ���
		m_bJump = false;

		if (m_pAction->GetState() == CPlayerAct::STATE_CANNON ||
			m_pAction->GetState() == CPlayerAct::STATE_FLY)
		{ // �ʏ��ԈȊO�̏ꍇ

			// �ʏ��Ԃ̐ݒ菈��
			SetNone();

			if (m_pAction->GetFront() == true)
			{ // �O��󋵂�ݒ肷��

				// ���ɂ���
				pos.z = FAR_POS;

				// �O��󋵂�ݒ肷��
				m_pAction->SetFront(false);
			}
			else
			{ // ��L�ȊO

				// ���ɂ���
				pos.z = NEAR_POS;

				// �O��󋵂�ݒ肷��
				m_pAction->SetFront(true);
			}

			// ���Z�b�g����
			m_pAbility->ResetAbility();
		}
	}

	// �ʒu��K�p������
	SetPos(pos);
}

//=======================================
// �����̔��菈��
//=======================================
void CPlayer::FallCheck(void)
{
	if (GetPos().y <= FALL_HEIGHT &&
		m_pAction->GetState() != CPlayerAct::STATE_FALL)
	{ // ���S�ɗ����؂����ꍇ

		// �ړ��ʂ�����������
		m_move = NONE_D3DXVECTOR3;

		// ���x��0�ɂ���
		m_fSpeed = 0.0f;

		// ������Ԃɂ���
		m_pAction->SetState(CPlayerAct::STATE_FALL);

		// �Q�[���̏�Ԃ����S��Ԃɂ���
		CGame::SetState(CGame::STATE_DEATH);

		// ���C�t��S�ď���
		m_nLife = 0;
	}
}

//=======================================
// �͈͊O�̓����蔻��
//=======================================
void CPlayer::OutRangeCollision(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �N���͈͊O�̓����蔻�菈��
	if (collision::ElevOutRangeCollision(&pos, GetPosOld(), COLLISION_WIDTH) == true)
	{ // �����蔻�肪�ʂ����ꍇ

		// �ړ��ʂ�0.0f�ɂ���
		m_move.x = 0.0f;

		// ���x��0.0f�ɂ���
		m_fSpeed = 0.0f;

		// ���\�͏�Ԃɂ���
		m_pAbility->SetAbility(CAbility::ABILITY_NONE, *this);
	}

	// �ʒu�̐ݒ菈��
	SetPos(pos);
}

//=======================================
// �X�^�[�g��Ԃ̏���
//=======================================
void CPlayer::StartProcess(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	// �ʒu�����Z����
	pos += ADD_START_POS;

	if (pos.x >= m_posDest.x)
	{ // �ʒu���ړI�𒴂����ꍇ

		// �ʒu��␳����
		pos = m_posDest;

		if (m_nStartCount == 0)
		{ // �ŏ��̂�

			// �g��̐���
			CRipple::Create(GetPos(), NONE_D3DXVECTOR3);
		}

		// �X�^�[�g�J�E���g�����Z����
		m_nStartCount++;
	}

	if (m_nStartCount >= START_COUNT)
	{ // �X�^�[�g�J�E���g��ݒ肷��

		// �ʏ탂�[�V������ݒ肷��
		m_pMotion->Set(MOTIONTYPE_NEUTRAL);

		// �V�я�Ԃɂ���
		CGame::SetState(CGame::STATE_PLAY);
	}

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �S�[����Ԃ̏���
//=======================================
void CPlayer::GoalProcess(void)
{
	// �ʏ��Ԃɂ���
	m_pAction->SetState(CPlayerAct::STATE_NONE);

	// �S�[�����̃J�E���g�����Z����
	m_nGoalCount++;

	if (m_bPunch == true)
	{ // �p���`��Ԃ̏ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
		{ // SPACE�L�[���������ꍇ

			// ���[�V�����̎�ނ��擾����
			int nMotionType = m_pMotion->GetType();

			// ���[�V�����̎�ނ�ݒ肷��
			nMotionType = (nMotionType + 1) % 2;

			// ���[�V������ݒ肷��
			m_pMotion->Set(MOTIONTYPE_SCRATCH001 + nMotionType);

			// �{�[�i�X�̉��Z����
			CBonus::Get()->AddBonus();

			if (CGoal::Get() != nullptr)
			{ // �S�[���̏�񂪂������ꍇ

				// �S�[���̌���
				D3DXVECTOR3 rot = NONE_D3DXVECTOR3;

				// ������ݒ肷��
				rot.x = (rand() % 80 - 40) * 0.01f;
				rot.z = (rand() % 80 - 40) * 0.01f;

				// �S�[���̌�����ݒ肷��
				CGoal::Get()->GetModel(CGoal::MODEL_BODY)->SetRot(rot);
				CGoal::Get()->GetModel(CGoal::MODEL_POINT)->SetRot(rot);
			}

			// ���j�̐ݒ菈��
			CDestruction::Create
			(
				D3DXVECTOR3(GetPos().x + sinf(GetRot().y) * (PUNCH_DSTR_SHIFT.x + (rand() % 20)), GetPos().y + (PUNCH_DSTR_SHIFT.y + (rand() % 50 - 25)), GetPos().z),
				PUNCH_DSTR_SIZE,
				PUNCH_DSTR_COL,
				CDestruction::TYPE_THORN,
				PUNCH_DSTR_LIFE
			);

			// �g��𐶐�����
			CRipple::Create(D3DXVECTOR3(GetPos().x + sinf(GetRot().y) * PUNCH_RIPPLE_SHIFT.x, GetPos().y + PUNCH_RIPPLE_SHIFT.y, GetPos().z), D3DXVECTOR3(0.0f, 0.0f, GetRot().y));
		}

		if (m_nGoalCount >= PUNCH_COUNT)
		{ // ���J�E���g�ȏ�ɂȂ����ꍇ

			// �ޏ��Ԃɂ���
			CGame::SetState(CGame::STATE_LEAVE);

			// �S�[���J�E���g������������
			m_nGoalCount = 0;

			// �Q�[���X�R�A�̉��Z����
			CGameScore::Get()->AddScore(CBonus::Get()->GetBonus() * 100);

			if (CGoal::Get() != nullptr)
			{ // �S�[�����������ꍇ

				// �j�󏈗�
				CGoal::Get()->Break();

				// �S�[���̏I������
				CGoal::Get()->Uninit();
			}

			if (m_pPushTiming != nullptr)
			{ // �����{�^���� NULL ����Ȃ��ꍇ

				// �I������
				m_pPushTiming->Uninit();
				m_pPushTiming = nullptr;
			}
		}
	}
	else
	{ // ��L�ȊO

		if (m_nGoalCount >= GOAL_COUNT)
		{ // ���J�E���g�ȏ�ɂȂ����ꍇ

			// �ޏ��Ԃɂ���
			CGame::SetState(CGame::STATE_LEAVE);

			// �S�[���J�E���g������������
			m_nGoalCount = 0;
		}
	}
}

//=======================================
// �ޏ��Ԃ̏���
//=======================================
void CPlayer::LeaveProcess(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu

	// �d�͏���
	useful::Gravity(&m_move.y, pos, LEAVE_GRAVITY);

	// �ʒu���X�V����
	pos.x += m_move.x;

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �I����Ԃ̏���
//=======================================
void CPlayer::FinishProcess(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu��ݒ肷��

	// �d�͏���
	useful::Gravity(&m_move.y, pos, FINISH_GRAVITY);

	// �ʒu��K�p����
	SetPos(pos);
}