//===========================================
//
// �}�L�i���̃��C������[macchina.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "macchina.h"
#include "macchina_manager.h"
#include "useful.h"

#include"screw.h"

// �}�N����`
#define NONE_SCALE			(D3DXVECTOR3(1.0f, 1.0f, 1.0f))		// �ʏ��Ԃ̊g�嗦
#define NONE_SCALE_COUNT	(20)								// �ʏ��Ԃ̓����J�E���g
#define NONE_SCALE_REDUCE	(D3DXVECTOR3(0.9f, 1.1f, 0.9f))		// �ʏ��Ԃ̏k�񂾍ۂ̊g�嗦
#define NONE_ADD_CORRECT	(0.008f)							// �ʏ��Ԃ̕␳���鎞�̉��Z��
#define REDUCE_SCALE_DEST	(D3DXVECTOR3(1.6f, 0.6f, 1.6f))		// �k����Ԃ̖ړI�̃T�C�Y
#define REDUCE_ADD_CORRECT	(0.2f)								// �k����Ԃ̕␳����Ƃ��̉��Z��
#define REDUCE_COUNT		(3)									// �k����Ԃ̃J�E���g
#define EXPANSE_SCALE_DEST	(D3DXVECTOR3(0.6f, 1.5f, 0.6f))		// �L�я�Ԃ̖ړI�̃T�C�Y
#define EXPANSE_ADD_CORRECT	(0.07f)								// �L�я�Ԃ̕␳����Ƃ��̉��Z��
#define EXPANSE_COUNT		(10)								// �L�я�Ԃ̃J�E���g
#define EJECT_SCALE_DEST	(D3DXVECTOR3(1.6f, 0.5f, 1.6f))		// �r�o��Ԃ̖ړI�̃T�C�Y
#define EJECT_ADD_CORRECT	(0.01f)								// �r�o��Ԃ̕␳����Ƃ��̉��Z��
#define SCREW_SHIFT_Z		(100.0f)							// �l�W�̂��炷��(Z��)
#define SCREW_MOVE_Y		(20.0f)								// �l�W�̈ړ���(Y��)

//==============================
// �R���X�g���N�^
//==============================
CMacchina::CMacchina() : CModel(CObject::TYPE_VIVLIO, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_scaleDest = NONE_SCALE;		// �ړI�̃T�C�Y
	m_state = STATE_NONE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_bCollision = true;			// �����蔻��̗L��

	m_pPrev = nullptr;		// �O�ւ̃|�C���^
	m_pNext = nullptr;		// ���ւ̃|�C���^

	if (CMacchinaManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CMacchinaManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CMacchina::~CMacchina()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CMacchina::SetPrev(CMacchina* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CMacchina::SetNext(CMacchina* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CMacchina* CMacchina::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CMacchina* CMacchina::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CMacchina::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_scaleDest = NONE_SCALE;		// �ړI�̃T�C�Y
	m_state = STATE_NONE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_bCollision = true;			// �����蔻��̗L��

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CMacchina::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CMacchinaManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CMacchinaManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CMacchina::Update(void)
{
	switch (m_state)
	{
	case STATE_NONE:		// �ʏ���

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		// �ʏ��Ԃ̊g�嗦�ω�����
		NoneRescale();

		break;

	case STATE_REDUCE:		// �k�����

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		// �k����Ԃ̊g�嗦�ω�����
		ReduceScale();

		if (m_nStateCount >= REDUCE_COUNT)
		{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

			// ��ԃJ�E���g������������
			m_nStateCount = 0;

			// �L�я�Ԃɂ���
			m_state = STATE_EXPANSE;

			// �ړI�̊g�嗦��ݒ肷��
			m_scaleDest = EXPANSE_SCALE_DEST;
		}

		break;

	case STATE_EXPANSE:		// �L�я��

		// ��ԃJ�E���g������������
		m_nStateCount++;

		// �L�я�Ԃ̊g�嗦�ω�����
		ExpanseScale();

		if (m_nStateCount >= EXPANSE_COUNT)
		{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

			// ��ԃJ�E���g������������
			m_nStateCount = 0;

			// �r�o��Ԃɂ���
			m_state = STATE_EJECT;

			// �ړI�̊g�嗦��ݒ肷��
			m_scaleDest = EJECT_SCALE_DEST;

			// �l�W�̐�������
			CScrew::Create(D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z - SCREW_SHIFT_Z), D3DXVECTOR3(0.0f, SCREW_MOVE_Y, 0.0f), true);
		}

		break;

	case STATE_EJECT:		// �r�o���

		// �r�o��Ԃ̊g�嗦�ω�����
		EjectScale();

		break;

	default:				// ��L�ȊO

		// ��~
		assert(false);

		break;
	}
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CMacchina::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// �q�b�g����
//=====================================
void CMacchina::Hit(void)
{
	// ��Ԃ�ݒ肷��
	m_state = STATE_REDUCE;

	// ��ԃJ�E���g������������
	m_nStateCount = 0;

	// �ړI�̊g�嗦��ݒ肷��
	m_scaleDest = REDUCE_SCALE_DEST;

	// �����蔻��� false �ɂ���
	m_bCollision = false;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CMacchina::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// �g�嗦
	SetFileData(CXFile::TYPE_MACCHINA);			// ���f���̏��

	// �S�Ă̒l������������
	m_scaleDest = NONE_SCALE;		// �ړI�̃T�C�Y
	m_state = STATE_NONE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_bCollision = true;			// �����蔻��̗L��
}

//=====================================
// �����蔻��̎擾����
//=====================================
bool CMacchina::GetCollision(void)
{
	// �����蔻��̗L����Ԃ�
	return m_bCollision;
}

//=======================================
// ��������
//=======================================
CMacchina* CMacchina::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMacchina* pMacchina = nullptr;	// �C���X�^���X�𐶐�

	if (pMacchina == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pMacchina = new CMacchina;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMacchina != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pMacchina->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pMacchina->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �}�L�i���̃|�C���^��Ԃ�
	return pMacchina;
}

//=======================================
// �ʏ��Ԃ̊g�嗦�̕ω�����
//=======================================
void CMacchina::NoneRescale(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 scale = GetScale();		// �g�嗦���擾����

	if (m_nStateCount % NONE_SCALE_COUNT == 0)
	{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

		// �ړI�̃T�C�Y��ݒ肷��
		m_scaleDest = (m_scaleDest.x <= NONE_SCALE_REDUCE.x) ? NONE_SCALE : NONE_SCALE_REDUCE;
	}

	// �T�C�Y�̕␳����
	useful::FrameCorrect(m_scaleDest.x, &scale.x, NONE_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.y, &scale.y, NONE_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.z, &scale.z, NONE_ADD_CORRECT);

	// �g�嗦��K�p����
	SetScale(scale);
}

//=======================================
// �k����Ԃ̊g�嗦�̕ω�����
//=======================================
void CMacchina::ReduceScale(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 scale = GetScale();		// �g�嗦���擾����

	// �T�C�Y�̕␳����
	useful::FrameCorrect(m_scaleDest.x, &scale.x, REDUCE_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.y, &scale.y, REDUCE_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.z, &scale.z, REDUCE_ADD_CORRECT);

	// �g�嗦��K�p����
	SetScale(scale);
}

//=======================================
// �L�я�Ԃ̊g�嗦�̕ω�����
//=======================================
void CMacchina::ExpanseScale(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 scale = GetScale();		// �g�嗦���擾����

	// �T�C�Y�̕␳����
	useful::FrameCorrect(m_scaleDest.x, &scale.x, EXPANSE_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.y, &scale.y, EXPANSE_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.z, &scale.z, EXPANSE_ADD_CORRECT);

	// �g�嗦��K�p����
	SetScale(scale);
}

//=======================================
// �r�o��Ԃ̊g�嗦�̕ω�����
//=======================================
void CMacchina::EjectScale(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 scale = GetScale();		// �g�嗦���擾����

	// �T�C�Y�̕␳����
	useful::FrameCorrect(m_scaleDest.x, &scale.x, EJECT_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.y, &scale.y, EJECT_ADD_CORRECT);
	useful::FrameCorrect(m_scaleDest.z, &scale.z, EJECT_ADD_CORRECT);

	// �g�嗦��K�p����
	SetScale(scale);
}