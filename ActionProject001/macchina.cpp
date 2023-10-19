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

// �}�N����`
#define NONE_SCALE			(D3DXVECTOR3(1.0f, 1.0f, 1.0f))		// �ʏ��Ԃ̊g�嗦
#define NONE_SCALE_COUNT	(20)								// �ʏ��Ԃ̓����J�E���g
#define NONE_SCALE_REDUCE	(D3DXVECTOR3(0.9f, 1.1f, 0.9f))		// �ʏ��Ԃ̏k�񂾍ۂ̊g�嗦

//==============================
// �R���X�g���N�^
//==============================
CMacchina::CMacchina() : CModel(CObject::TYPE_VIVLIO, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_scaleDest = NONE_SCALE;		// �ړI�̃T�C�Y
	m_state = STATE_NONE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g

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



		break;

	case STATE_EJECT:		// �r�o���


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
	useful::FrameCorrect(m_scaleDest.x, &scale.x, 0.008f);
	useful::FrameCorrect(m_scaleDest.y, &scale.y, 0.008f);
	useful::FrameCorrect(m_scaleDest.z, &scale.z, 0.008f);

	// �g�嗦��K�p����
	SetScale(scale);
}