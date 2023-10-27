//===========================================
//
// �`���[�g���A���ӂ������̃��C������[tutorial.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "tutorial.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//-------------------------------------------
// ���O���(�e�N�X�`��)
//-------------------------------------------
namespace
{
	static const char* c_apTextureFileNameKey[CPork::TYPE_MAX] =		// �L�[�{�[�h�̃e�N�X�`���̖��O
	{
		"data\\TEXTURE\\KeyTutorial001.png",
		"data\\TEXTURE\\KeyTutorial002.png",
		"data\\TEXTURE\\KeyTutorial003.png",
	};
	static const char* c_apTextureFileNameButton[CPork::TYPE_MAX] =		// �Q�[���p�b�h�̃e�N�X�`���̖��O
	{
		"data\\TEXTURE\\ButTutorial001.png",
		"data\\TEXTURE\\ButTutorial002.png",
		"data\\TEXTURE\\ButTutorial003.png",
	};
}

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define TUTORIAL_SIZE		(D3DXVECTOR3(100.0f, 100.0f, 0.0f))		// �`���[�g���A���̃T�C�Y
#define SHIFT				(D3DXVECTOR3(-90.0f, 220.0f, 0.0f))		// ���炷��

//==============================
// �R���X�g���N�^
//==============================
CTutorial::CTutorial() : CBillboard(CObject::TYPE_TUTORIAL, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_type = CPork::TYPE_HOVER;		// ���
}

//==============================
// �f�X�g���N�^
//==============================
CTutorial::~CTutorial()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CTutorial::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_type = CPork::TYPE_HOVER;		// ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CTutorial::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CTutorial::Update(void)
{
	if (CManager::Get()->GetInputGamePad()->GetConnect() == true)
	{ // �Q�[���p�b�h���q���ł����ꍇ

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(c_apTextureFileNameButton[m_type]));
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(c_apTextureFileNameKey[m_type]));
	}
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CTutorial::Draw(void)
{
	// �`�揈��
	CBillboard::DrawLightOff();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTutorial::SetData(const D3DXVECTOR3& pos, const CPork::TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos + SHIFT);			// �ʒu
	SetPosOld(pos + SHIFT);			// �O��̈ʒu
	SetSize(TUTORIAL_SIZE);			// �T�C�Y

	// �S�Ă̒l��ݒ肷��
	m_type = type;		// ���

	if (CManager::Get()->GetInputGamePad()->GetConnect() == true)
	{ // �Q�[���p�b�h���q���ł����ꍇ

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(c_apTextureFileNameButton[m_type]));
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(c_apTextureFileNameKey[m_type]));
	}

	// �����S�̒��_���ݒ菈��
	CBillboard::SetVtxPosUnder();
}

//=======================================
// ��������
//=======================================
CTutorial* CTutorial::Create(const D3DXVECTOR3& pos, const CPork::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTutorial* pSign = nullptr;	// �C���X�^���X�𐶐�

	if (pSign == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pSign = new CTutorial;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSign != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pSign->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSign->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �Ŕ̃|�C���^��Ԃ�
	return pSign;
}