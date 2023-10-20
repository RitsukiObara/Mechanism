//===========================================
//
// �C�g�L�����̃��C������[itocan.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "itocan.h"
#include "useful.h"

#include "player.h"
#include "destruction.h"
#include "Particle.h"
#include "fraction.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define COLLISION_SIZE		(D3DXVECTOR3(32.0f, 128.0f, 40.0f))	// �����蔻��̃T�C�Y
#define MOVE_DISTANCE		(1300.0f)							// �ړ����鋗��
#define MOVE				(D3DXVECTOR3(3.0f, 0.0f, 0.0f))		// �ړ���
#define ROT_MOVE_MAGNI		(0.15f)								// �����̈ړ��ʂ̔{��
#define CHECK_COUNT			(15)								// �`�F�b�N����J�E���g��
#define DEATH_SCALE			(0.2f)								// ���S��Ԃ̊g�嗦
#define DEATH_ADD_SCALE		(0.15f)								// ���S��Ԃ̉��Z����g�嗦
#define DEATH_COUNT			(40)								// ���S����܂ł̃J�E���g
#define DEATH_DSTR_SIZE		(D3DXVECTOR3(40.0f,40.0f,0.0f))		// ���S���̌��j�̃T�C�Y
#define DEATH_DSTR_COL		(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f))	// ���S���̌��j�̐F
#define DEATH_DSTR_LIFE		(20)								// ���S���̌��j�̎���
#define FRACTION_COUNT		(8)									// �j�Ђ̐�
#define SMASH_ROTMOVE_X		(0.3f)								// ������Ԍ����̈ړ���(X��)
#define SMASH_ROTMOVE_Z		(0.2f)								// ������Ԍ����̈ړ���(Z��)
#define SMASH_DEATH_COUNT	(70)								// �������Ŏ��S����܂ł̃J�E���g
#define HIT_DSTR_SIZE		(D3DXVECTOR3(40.0f,40.0f,0.0f))		// �q�b�g���̌��j�̃T�C�Y
#define HIT_DSTR_COL		(D3DXCOLOR(1.0f, 0.7f, 0.1f, 1.0f))	// �q�b�g���̌��j�̐F
#define HIT_DSTR_LIFE		(10)								// �q�b�g���̌��j�̎���

//==============================
// �R���X�g���N�^
//==============================
CItocan::CItocan() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_STOP;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
	m_fRotDest = 0.0f;			// �ڕW�̌���
}

//==============================
// �f�X�g���N�^
//==============================
CItocan::~CItocan()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CItocan::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	m_state = STATE_STOP;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
	m_fRotDest = 0.0f;			// �ڕW�̌���

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CItocan::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CItocan::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_STOP:		// ��~���

		if (m_nStateCount % CHECK_COUNT == 0)
		{ // ���J�E���g���ɂȂ����ꍇ

			// �v���C���[�̔��菈��
			CheckPlayer();
		}

		// ��Ԃ̔��菈��
		CheckState();

		break;

	case STATE_MOVE:		// �ړ����

		if (m_nStateCount % CHECK_COUNT == 0)
		{ // ���J�E���g���ɂȂ����ꍇ

			// �v���C���[�̔��菈��
			CheckPlayer();
		}

		// ��Ԃ̔��菈��
		CheckState();

		// �����̈ړ�����
		RotMove();

		// �ړ�����
		Move();

		break;

	case STATE_DEATH:		// ���S���

		// ���S���̊g�嗦����
		DeathScaling();

		if (m_nStateCount >= DEATH_COUNT)
		{ // ��ԃJ�E���g����萔�ɂȂ����ꍇ

			// ���j�̐�������
			CDestruction::Create(GetPos(), DEATH_DSTR_SIZE, DEATH_DSTR_COL, CDestruction::TYPE_THORN, DEATH_DSTR_LIFE);

			// �p�[�e�B�N���̐�������
			CParticle::Create(GetPos(), CParticle::TYPE_ENEMYDEATH);

			// ���[�J���ϐ��錾
			CFraction::TYPE type = CFraction::TYPE_SCREW;

			for (int nCnt = 0; nCnt < FRACTION_COUNT; nCnt++)
			{
				// ��ނ�ݒ肷��
				type = (CFraction::TYPE)(rand() % CFraction::TYPE_MAX);

				// �j�Ђ̐�������
				CFraction::Create(GetPos(), type);
			}

			// �I������
			Uninit();

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	case STATE_SMASH:		// ������я��

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		// ������я�ԏ���
		Smash();

		if (m_nStateCount >= SMASH_DEATH_COUNT)
		{ // ��ԃJ�E���g����萔�ɂȂ����ꍇ

			// �I������
			Uninit();

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �d�͏���
	Gravity();

	// �N���n�ʂƂ̓����蔻��
	ElevationCollision();

	// ��Ƃ̓����蔻��
	if (TableCollision() == true)
	{ // ���n���肪 true �̏ꍇ

		// ��̒��n���菈��
		TableLand();
	}

	// ��ԃJ�E���g�����Z����
	m_nStateCount++;
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CItocan::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=====================================
// �q�b�g����
//=====================================
void CItocan::Hit(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posDstr = GetPos();		// ���j���o���ʒu

	// �����蔻��󋵂� OFF �ɂ���
	SetEnableCollision(false);

	// ��ԃJ�E���g������������
	m_nStateCount = 0;

	// ���S��Ԃɐݒ肷��
	m_state = STATE_DEATH;

	// �G�t�F�N�g���o���ʒu��ݒ肷��
	posDstr.y += GetCollSize().y;

	// ���j�̐�������
	CDestruction::Create(posDstr, HIT_DSTR_SIZE, HIT_DSTR_COL, CDestruction::TYPE_AIRY, HIT_DSTR_LIFE);
}

//=====================================
// ������уq�b�g����
//=====================================
void CItocan::SmashHit(void)
{
	// ������΂�����
	CEnemy::SmashHit();

	// �����蔻��󋵂� OFF �ɂ���
	SetEnableCollision(false);

	// ��ԃJ�E���g������������
	m_nStateCount = 0;

	// ������я�Ԃɐݒ肷��
	m_state = STATE_SMASH;

	// ���j�̐�������
	CDestruction::Create(GetPos(), DEATH_DSTR_SIZE, DEATH_DSTR_COL, CDestruction::TYPE_THORN, DEATH_DSTR_LIFE);

	// �p�[�e�B�N���̐�������
	CParticle::Create(GetPos(), CParticle::TYPE_ENEMYDEATH);

	// ���[�J���ϐ��錾
	CFraction::TYPE type = CFraction::TYPE_SCREW;

	for (int nCnt = 0; nCnt < FRACTION_COUNT; nCnt++)
	{
		// ��ނ�ݒ肷��
		type = (CFraction::TYPE)(rand() % CFraction::TYPE_MAX);

		// �j�Ђ̐�������
		CFraction::Create(GetPos(), type);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CItocan::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	CEnemy::SetData(pos);

	// ���f���̏���ݒ肷��
	SetFileData(CXFile::TYPE_ITOCAN);

	// �S�Ă̒l���N���A����
	m_state = STATE_STOP;			// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
	m_fRotDest = 0.0f;			// �ڕW�̌���

	// ���̐ݒ菈��
	SetEnableStep(true);			// ���݂�����ݒ�
	SetMove(MOVE);					// �ړ���
	SetCollSize(COLLISION_SIZE);	// �����蔻��̃T�C�Y
}

//=======================================
// �v���C���[�̔��菈��
//=======================================
void CItocan::CheckPlayer(void)
{
	if (CPlayer::Get() != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// �v���C���[�̈ʒu
		D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

		if (posPlayer.x >= pos.x)
		{ // �v���C���[�̈ʒu�����g�����E�ɂ���ꍇ

			// ������ݒ肷��
			m_fRotDest = -D3DX_PI * 0.5f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			m_fRotDest = D3DX_PI * 0.5f;
		}
	}
}

//=======================================
// ��Ԃ̔��菈��
//=======================================
void CItocan::CheckState(void)
{
	// ���[�J���|�C���^�錾
	CPlayer* pPlayer = CPlayer::Get();				// �v���C���[�̏����擾����
	D3DXVECTOR3 pos = GetPos();						// �ʒu
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;		// �ő�l
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;		// �ŏ��l

	if (pPlayer != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

		if (pPlayer->GetPos().z <= pos.z + vtxMax.z &&
			pPlayer->GetPos().z >= pos.z + vtxMin.z &&
			fabsf(pos.x - pPlayer->GetPos().x) <= MOVE_DISTANCE)
		{ // ��苗�����̏ꍇ

			// �ړ���Ԃɂ���
			m_state = STATE_MOVE;
		}
		else
		{ // ��L�ȊO

			// �ʒu��ݒ肷��
			pos = GetInitPos();

			// �O��̈ʒu��ݒ肷��
			SetPosOld(GetInitPos());

			// ��~��Ԃɂ���
			m_state = STATE_STOP;
		}
	}
	else
	{ // ��L�ȊO

		// ��~��Ԃɂ���
		m_state = STATE_STOP;
	}

	// ����K�p����
	SetPos(pos);		// �ʒu
}

//=======================================
// �ړ�����
//=======================================
void CItocan::Move(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����
	D3DXVECTOR3 move = GetMove();	// �ړ���

	// �ړ��ʂ�ݒ肷��
	pos.x += sinf(-rot.y) * move.x;

	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=======================================
// �����ړ�����
//=======================================
void CItocan::RotMove(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();		// �������擾����

	// �����̐ݒ菈��
	useful::RotCorrect(m_fRotDest, &rot.y, ROT_MOVE_MAGNI);

	// ������K�p����
	SetRot(rot);
}

//=======================================
// ���S���̊g�嗦����
//=======================================
void CItocan::DeathScaling(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 scale = GetScale();		// �g�嗦���擾����

	// �g�嗦�̐ݒ菈��
	useful::FrameCorrect(DEATH_SCALE, &scale.y, DEATH_ADD_SCALE);

	// �g�嗦�̐ݒ菈��
	SetScale(scale);
}

//=======================================
// ������я�ԏ���
//=======================================
void CItocan::Smash(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����
	D3DXVECTOR3 move = GetMove();	// �ړ���

	// ������ݒ肷��
	rot.x += SMASH_ROTMOVE_X;
	rot.z += SMASH_ROTMOVE_Z;

	// �����̐��K������
	useful::RotNormalize(&rot.x);
	useful::RotNormalize(&rot.z);

	// �ʒu���X�V����
	pos.x += move.x;
	pos.z += move.z;

	// ����K�p����
	SetPos(pos);		// �ʒu
	SetRot(rot);		// ����
}

//=======================================
// ��̒��n���菈��
//=======================================
void CItocan::TableLand(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move = GetMove();		// �ړ��ʂ��擾����

	// �d�͂�0.0f�ɂ���
	move.y = 0.0f;

	// �ړ��ʂ�K�p����
	SetMove(move);
}