//===========================================
//
// �S�[���̃��C������[goal.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "goal.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define CYCLE_COUNT		(40)			// �������ς��J�E���g

//==============================
// �R���X�g���N�^
//==============================
CGoal::CGoal() : CObject(CObject::TYPE_GOAL, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_aGoal[nCnt] = nullptr;	// �S�[���̕ϐ�
	}
	m_type = TYPE_PUNCH;			// ���
	m_state = STATE_CYCLE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_fRotDest = 0.0f;				// �ڕW�̌���
}

//==============================
// �f�X�g���N�^
//==============================
CGoal::~CGoal()
{

}

//==============================
// �S�[���̏���������
//==============================
HRESULT CGoal::Init(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		if (m_aGoal[nCnt] == nullptr)
		{ // �I�u�W�F�N�g�� NULL �̏ꍇ

			// �C���X�^���X�𐶐�
			m_aGoal[nCnt] = new CModel(TYPE_NONE, PRIORITY_PLAYER);
		}
		else
		{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s ��Ԃ�
			return E_FAIL;
		}

		if (m_aGoal[nCnt] != nullptr)
		{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_aGoal[nCnt]->Init()))
			{ // �������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s ��Ԃ�
				return E_FAIL;
			}
		}
		else
		{ // �I�u�W�F�N�g�� NULL �̏ꍇ

			// ��~
			assert(false);

			// ���s ��Ԃ�
			return E_FAIL;
		}
	}

	// �S�Ă̒l������������
	m_type = TYPE_PUNCH;			// ���
	m_state = STATE_CYCLE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_fRotDest = 0.0f;				// �ڕW�̌���

	// ������Ԃ�
	return S_OK;
}

//========================================
// �S�[���̏I������
//========================================
void CGoal::Uninit(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// �I������
		m_aGoal[nCnt]->Uninit();
		m_aGoal[nCnt] = nullptr;
	}

	// �{�̂̏I������
	Release();

	// �S�[���̏�������
	CGame::DeleteGoal();
}

//========================================
// �S�[���̍X�V����
//========================================
void CGoal::Update(void)
{
	switch (m_state)
	{
	case CGoal::STATE_CYCLE:		// ��]���

			// �����̌��菈��
		RotDecide(&m_fRotDest);

		// �����̕␳����
		RotCorrect();

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		if (m_nStateCount % CYCLE_COUNT == 0)
		{ // ��ԃJ�E���g����萔�ɂȂ����ꍇ

			// ��ނ�ς���
			m_type = (TYPE)((m_type + 1) % TYPE::TYPE_MAX);
		}

		break;

	case CGoal::STATE_STOP:			// ��~���


		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=====================================
// �S�[���̕`�揈��
//=====================================
void CGoal::Draw(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// �`�揈��
		m_aGoal[nCnt]->Draw();
	}
}

//=====================================
// �q�b�g����
//=====================================
void CGoal::Hit(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = m_aGoal[MODEL_POINT]->GetRot();		// �������擾����

	// �����̌��菈��
	RotDecide(&rot.y);

	// ������K�p����
	m_aGoal[MODEL_POINT]->SetRot(rot);

	// ��~��Ԃɂ���
	m_state = STATE_STOP;

	// ��ԃJ�E���g������������
	m_nStateCount = 0;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CGoal::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// ���̐ݒ菈��
		m_aGoal[nCnt]->SetPos(pos);									// �ʒu
		m_aGoal[nCnt]->SetPosOld(pos);								// �O��̈ʒu
		m_aGoal[nCnt]->SetRot(NONE_D3DXVECTOR3);					// ����
		m_aGoal[nCnt]->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));		// �g�嗦

		// ���f���̏��
		switch (nCnt)
		{
		case MODEL_BODY:			// �{��

			m_aGoal[nCnt]->SetFileData(CXFile::TYPE_GOAL);

			break;

		case MODEL_POINT:			// ���_

			m_aGoal[nCnt]->SetFileData(CXFile::TYPE_GOALPOINT);

			break;
		}
	}

	// �S�Ă̒l��ݒ肷��
	m_type = TYPE_PUNCH;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_fRotDest = 0.0f;				// �ڕW�̌���
}

//=======================================
// ���f���̐ݒ菈��
//=======================================
CModel* CGoal::GetModel(const MODEL model)
{
	// ���f���̏���Ԃ�
	return m_aGoal[model];
}

//=======================================
// ��������
//=======================================
CGoal* CGoal::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CGoal* pGoal = nullptr;		// �C���X�^���X�𐶐�

	if (pGoal == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pGoal = new CGoal;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pGoal != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pGoal->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pGoal->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �S�[���̃|�C���^��Ԃ�
	return pGoal;
}

//=======================================
// �����̌��菈��
//=======================================
void CGoal::RotDecide(float* m_fRot)
{
	switch (m_type)
	{
	case CGoal::TYPE_PUNCH:		// �p���`

		*m_fRot = 0.0f;

		break;

	case CGoal::TYPE_SMALL_R:	// +1000

		*m_fRot = -D3DX_PI * 0.5f;

		break;

	case CGoal::TYPE_BIG:		// +2000

		*m_fRot = D3DX_PI;

		break;

	case CGoal::TYPE_SMALL_L:	// +1000

		*m_fRot = D3DX_PI* 0.5f;

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// �����̕␳����
//=======================================
void CGoal::RotCorrect(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = m_aGoal[MODEL_POINT]->GetRot();		// �������擾����

	// �����̐��K��
	useful::RotCorrect(m_fRotDest, &rot.y, 0.5f);

	// ������K�p����
	m_aGoal[MODEL_POINT]->SetRot(rot);
}