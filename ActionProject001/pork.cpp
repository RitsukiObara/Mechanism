//===========================================
//
// �|�[�N�̃��C������[pork.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "pork.h"
#include "pork_manager.h"
#include "useful.h"

#include "signboard.h"
#include "player.h"
#include "player_ability.h"
#include "tutorial.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define DISTINCT_SIZE		(800.0f)		// ���ʂ���Ƃ��̃T�C�Y
#define SIGNBOARD_ADD		(0.5f)			// �Ŕ̒ǉ��̌����̈ړ���
#define PORK_POS_Z			(100.0f)		// �|�[�N�̈ʒu(Z��)

//==============================
// �R���X�g���N�^
//==============================
CPork::CPork() : CModel(CObject::TYPE_PORK, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pSignBoard = nullptr;	// �Ŕ̃|�C���^
	m_type = TYPE_HOVER;	// ���
	m_bTutorial = false;	// �`���[�g���A����

	m_pPrev = nullptr;		// �O�ւ̃|�C���^
	m_pNext = nullptr;		// ���ւ̃|�C���^

	if (CPorkManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CPorkManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CPork::~CPork()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CPork::SetPrev(CPork* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CPork::SetNext(CPork* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CPork* CPork::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CPork* CPork::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CPork::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pSignBoard = nullptr;		// �Ŕ̃|�C���^
	m_type = TYPE_HOVER;		// ���
	m_bTutorial = false;		// �`���[�g���A����

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CPork::Uninit(void)
{
	if (m_pSignBoard != nullptr)
	{ // �Ŕ����݂���ꍇ

		// �I������
		m_pSignBoard->Uninit();
		m_pSignBoard = nullptr;
	}

	// �I������
	CModel::Uninit();

	if (CPorkManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CPorkManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CPork::Update(void)
{
	if (m_bTutorial == true)
	{ // �`���[�g���A���󋵂� true �̏ꍇ

		// �Ŕ̉�]����
		SignBoardCycle();
	}
	else
	{ // ��L�ȊO

		// �v���C���[�̔��ʏ���
		DistinctPlayer();
	}
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CPork::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPork::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z + PORK_POS_Z));								// �ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetPosOld(GetPos());						// �O��̈ʒu
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// �g�嗦
	SetFileData(CXFile::TYPE_PORK);				// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_type = type;				// ���
	m_bTutorial = false;		// �`���[�g���A����

	if (m_pSignBoard == nullptr)
	{ // �Ŕ̃|�C���^�� NULL �̏ꍇ

		// �Ŕ̐�������
		m_pSignBoard = CSignBoard::Create(GetPos());
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	// �`���[�g���A���𐶐�����
	CTutorial::Create(GetPos(), type);
}

//=======================================
// ��������
//=======================================
CPork* CPork::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPork* pPork = nullptr;	// �C���X�^���X�𐶐�

	if (pPork == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pPork = new CPork;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPork != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPork->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPork->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �|�[�N�̃|�C���^��Ԃ�
	return pPork;
}

//=======================================
// �Ŕ̉�]����
//=======================================
void CPork::SignBoardCycle(void)
{
	if (m_pSignBoard != nullptr)
	{ // �Ŕ� NULL ����Ȃ��ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 rot = m_pSignBoard->GetRot();		// �Ŕ̌������擾����

		// ������ڕW�ɋ߂Â��Ă���
		useful::FrameCorrect(D3DX_PI, &rot.y, SIGNBOARD_ADD);
		
		// �Ŕ̌�����K�p����
		m_pSignBoard->SetRot(rot);
	}
}

//=======================================
// �v���C���[�̔��ʏ���
//=======================================
void CPork::DistinctPlayer(void)
{
	// ���[�J���ϐ��錾
	CPlayer* pPlayer = CPlayer::Get();		// �v���C���[

	if (pPlayer != nullptr)
	{ // �v���C���[�̏�񂪂������ꍇ

		if (pPlayer->GetPos().x <= GetPos().x + DISTINCT_SIZE &&
			pPlayer->GetPos().x >= GetPos().x - DISTINCT_SIZE)
		{ // �͈͓��������ꍇ

			switch (m_type)
			{
			case CPork::TYPE_HOVER:		// �z�o�[�W�F�b�g

				if (pPlayer->GetAbility()->GetAbility() == CAbility::ABILITY_HOVER)
				{ // �z�o�[�W�F�b�g��Ԃ̏ꍇ

					// �`���[�g���A���󋵂� true �ɂ���
					m_bTutorial = true;
				}

				break;

			case CPork::TYPE_DASH:		// �W�F�b�g�_�b�V��

				if (pPlayer->GetAbility()->GetAbility() == CAbility::ABILITY_JETDASH)
				{ // �W�F�b�g�_�b�V����Ԃ̏ꍇ

					// �`���[�g���A���󋵂� true �ɂ���
					m_bTutorial = true;
				}

				break;

			case CPork::TYPE_QUAKE:		// �O���E���h�N�G�C�N

				if (pPlayer->GetAbility()->GetAbility() == CAbility::ABILITY_GROUNDQUAKE)
				{ // �O���E���h�N�G�C�N��Ԃ̏ꍇ

					// �`���[�g���A���󋵂� true �ɂ���
					m_bTutorial = true;
				}

				break;

			default:

				// ��~
				assert(false);

				break;
			}
		}
	}
}