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
#include "ability_UI.h"
#include "screwUI.h"
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

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define DAMAGE_COL				(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f))		// �_���[�W��Ԃ̐F
#define STEPHIT_JUMP			(20.0f)		// ���݂����Ƃ��̃W�����v��
#define TABLE_COLLISION_WIDTH	(20.0f)		// ��Ƃ̓����蔻��̎��̕�

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
	m_pAbilityUI = nullptr;			// �\��UI�̏��
	m_pScrewUI = nullptr;			// �l�WUI�̏��
	m_pCombo = nullptr;				// �R���{�̏��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_fSpeed = 0.0f;				// ���x
	m_fAlpha = 1.0f;				// �����x
	m_bMove = false;				// �ړ���
	m_bRight = true;				// �E������
	m_bJump = false;				// �W�����v��
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
	SetNumModel(14);

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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

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

	// �S�Ă̒l������������
	m_pAbilityUI = nullptr;			// �\��UI
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_fSpeed = 0.0f;				// ���x
	m_fAlpha = 1.0f;				// �����x
	m_bMove = false;				// �ړ���
	m_bRight = true;				// �E������
	m_bJump = false;				// �W�����v��

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

	// �\��UI�̏I������
	m_pAbilityUI->Uninit();
	m_pAbilityUI = nullptr;

	// �l�WUI�̏I������
	m_pScrewUI->Uninit();
	m_pScrewUI = nullptr;

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
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	// �s���̍X�V����
	m_pAction->Update(*this);

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	// ��s�@�Ƃ̓����蔻��
	collision::AirplaneHit(*this);

	// �l�W�Ƃ̓����蔻��
	collision::ScrewHit(*this);

	// �G�Ƃ̓����蔻��
	collision::EnemyHit(*this);

	// �G�Ƃ̂߂荞�ݔ��菈��
	collision::EnemyPenetrate(*this);

	// �N���n�ʂƂ̓����蔻�菈��
	ElevationCollision();

	// ��Ƃ̓����蔻��
	TableCollision();

	// �e�̈ʒu�����ݒ菈��
	CShadowCircle::SetPosRotXZ(m_nShadowIdx, GetPos(), GetRot());

	// �s����������
	CollisionMagicWall();

	// �v���C���[�̏���\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�ړ��ʁF%f %f %f\n�v���C���[�̏�ԁF%d\n�W�����v�󋵁F%d\n", GetPos().x, GetPos().y, GetPos().z, m_move.x, m_move.y, m_move.z, m_pAction->GetState(), m_bJump);
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CPlayer::Draw(void)
{
	switch (m_pAction->GetState())
	{
	case CPlayerAct::STATE_INVINCIBLE:		// ���G���

		// �`�揈��
		CCharacter::Draw(m_fAlpha);

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
// �\��UI�̏��̎擾����
//===========================================
CAbilityUI* CPlayer::GetAbilityUI(void) const
{
	// �\��UI�̏���Ԃ�
	return m_pAbilityUI;
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
// �R���{�̏��̎擾����
//===========================================
CCombo* CPlayer::GetCombo(void) const
{
	// �R���{�̏���Ԃ�
	return m_pCombo;
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
	if (m_pAction->GetState() != CPlayerAct::STATE_DAMAGE &&
		m_pAction->GetState() != CPlayerAct::STATE_INVINCIBLE &&
		m_pAction->GetState() != CPlayerAct::STATE_CANNON)
	{ // ���̏�ԈȊO�̏ꍇ

		// �����p�[�e�B�N���𐶐�
		CParticle::Create(GetPos(), CParticle::TYPE_FIRE);

		// �_���[�W��Ԃɂ���
		m_pAction->SetState(CPlayerAct::STATE_DAMAGE);
	}
}

//=======================================
// ���݂����̏���
//=======================================
void CPlayer::StepHit(void)
{
	// �ړ��ʂ��グ��
	m_move.y = STEPHIT_JUMP;

	// �R���{�̉��Z����
	m_pCombo->AddCombo(100);
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CPlayer::SetData(const D3DXVECTOR3& pos)
{
	// �S�Ă̒l������������
	SetPos(pos);			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));			// ����
	SetScale(NONE_SCALE);	// �g�嗦

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

		if (m_pAbilityUI == nullptr)
	{ // �\��UI�� NULL �̏ꍇ

		// �\��UI�̏��𐶐�
		m_pAbilityUI = CAbilityUI::Create(GetPos());
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}
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
// �N���n�ʂ̓����蔻�菈��
//=======================================
void CPlayer::ElevationCollision(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);
		
		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight;

			// �d�͂�ݒ肷��
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
					pos.z = 1000.0f;

					// �O��󋵂�ݒ肷��
					m_pAction->SetFront(false);
				}
				else
				{ // ��L�ȊO

					// ���ɂ���
					pos.z = 0.0f;

					// �O��󋵂�ݒ肷��
					m_pAction->SetFront(true);
				}
			}
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

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

	if (pos.z >= 1000.0f)
	{ // �ʒu�����ȏ�ɂȂ����ꍇ

		// �ʒu��␳����
		pos.z = 1000.0f;
	}

	if (pos.z <= 0.0f)
	{ // �ʒu�����ȉ��ɂȂ����ꍇ

		// �ʒu��␳����
		pos.z = 0.0f;
	}

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// ��Ƃ̓����蔻��
//=======================================
void CPlayer::TableCollision(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu

	if (collision::TableCollision(&pos, posOld, TABLE_COLLISION_WIDTH) == true)
	{ // ��Ƃ̓����蔻�肪 true �������ꍇ

		// �c�̈ړ��ʂ𖳂���
		m_move.y = 0.0f;

		// �W�����v�󋵂� false �ɂ���
		m_bJump = false;
	}

	// �ʒu��K�p������
	SetPos(pos);
}