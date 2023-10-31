//===========================================
//
// ��s�@�̃��C������[airplane.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "airplane.h"
#include "airplane_manager.h"
#include "useful.h"

// �}�N����`
#define APPEAR_SCALE		(D3DXVECTOR3(0.5f, 0.5f, 0.5f))		// �o����Ԃ̊g�嗦
#define APPEAR_ADD_SCALE	(0.01f)								// �o����Ԃ̉��Z����g�嗦
#define APPEAR_ADD_ROT		(D3DX_PI / 25.0f)					// �o����Ԃ̉��Z�������
#define APPEAR_ADD_POS_Y	(2.0f)								// �o����Ԃ̉��Z����ʒu(Y��)

//==============================
// �R���X�g���N�^
//==============================
CAirplane::CAirplane() : CModel(CObject::TYPE_AIRPLANE, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_NONE;	// ���
	m_bFront = false;		// �O���
	m_bCollision = true;	// �����蔻���
	m_pPrev = nullptr;		// �O�ւ̃|�C���^
	m_pNext = nullptr;		// ���ւ̃|�C���^

	if (CAirplaneManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CAirplaneManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CAirplane::~CAirplane()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CAirplane::SetPrev(CAirplane* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CAirplane::SetNext(CAirplane* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CAirplane* CAirplane::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CAirplane* CAirplane::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
// ��s�@�̏���������
//==============================
HRESULT CAirplane::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_state = STATE_NONE;	// ���
	m_bFront = false;		// �O���
	m_bCollision = true;	// �����蔻���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// ��s�@�̏I������
//========================================
void CAirplane::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CAirplaneManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CAirplaneManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
// ��s�@�̍X�V����
//========================================
void CAirplane::Update(void)
{
	switch (m_state)
	{
	case CAirplane::STATE_APPEAR:		// �o�����

		// �o����Ԃ̏���
		Appear();

		break;

	case CAirplane::STATE_NONE:			// �ʏ���

		// ���ɏ�������

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=====================================
// ��s�@�̕`�揈��
//=====================================
void CAirplane::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CAirplane::SetData(const D3DXVECTOR3& pos, const bool bFront, const STATE state)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetFileData(CXFile::TYPE_AIRPLANE);			// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_state = state;		// ���
	m_bFront = bFront;		// �O���

	switch (m_state)
	{
	case CAirplane::STATE_APPEAR:

		// �����蔻�肪�Ȃ�
		m_bCollision = false;

		// �g�嗦��ݒ肷��
		SetScale(APPEAR_SCALE);

		break;

	case CAirplane::STATE_NONE:

		// �����蔻�肪���݂���
		m_bCollision = true;

		// �g�嗦��ݒ肷��
		SetScale(NONE_SCALE);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (m_bFront == true)
	{ // �O��󋵂� true �̏ꍇ

		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));	// ������ݒ肷��
	}
	else
	{ // ��L�ȊO

		SetRot(NONE_D3DXVECTOR3);					// ������ݒ肷��
	}
}

//=======================================
// �O��󋵂̎擾����
//=======================================
bool CAirplane::GetFront(void) const
{
	// �O��󋵂�Ԃ�
	return m_bFront;
}

//=======================================
// �����蔻��󋵂̎擾����
//=======================================
bool CAirplane::GetCollision(void) const
{
	// �����蔻��󋵂�Ԃ�
	return m_bCollision;
}

//=======================================
// ��������
//=======================================
CAirplane* CAirplane::Create(const D3DXVECTOR3& pos, const bool bFront, const STATE state)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAirplane* pAirplane = nullptr;	// �C���X�^���X�𐶐�

	if (pAirplane == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pAirplane = new CAirplane;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAirplane != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAirplane->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAirplane->SetData(pos, bFront, state);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��s�@�̃|�C���^��Ԃ�
	return pAirplane;
}

//=======================================
// �o����Ԃ̏���
//=======================================
void CAirplane::Appear(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu���擾����
	D3DXVECTOR3 rot = GetRot();			// �������擾����
	D3DXVECTOR3 scale = GetScale();		// �g�嗦���擾����

	// �g�嗦�����Z����
	scale.x += APPEAR_ADD_SCALE;
	scale.y += APPEAR_ADD_SCALE;
	scale.z += APPEAR_ADD_SCALE;

	// ���������Z����
	rot.x += APPEAR_ADD_ROT;

	// �ʒu�����Z����
	pos.y += APPEAR_ADD_POS_Y;

	if (scale.x >= 1.0f ||
		scale.y >= 1.0f ||
		scale.z >= 1.0f)
	{ // �g�嗦�� 1,0f �ȏ�̏ꍇ

		// �g�嗦��␳����
		scale = NONE_SCALE;

		// ������␳����
		rot.x = 0.0f;

		// �����蔻��󋵂� true �ɂ���
		m_bCollision = true;

		// �ʏ��Ԃɂ���
		m_state = STATE_NONE;
	}

	// ����K�p����
	SetPos(pos);			// �ʒu
	SetRot(rot);			// ����
	SetScale(scale);		// �g�嗦
}