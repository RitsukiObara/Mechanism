//============================================
//
// �\��UI�̏���[ability_UI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "player.h"
#include "player_ability.h"
#include "ability_UI.h"
#include "objectbillboard.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define UI_SIZE				(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// �傫��UI�̃T�C�Y
#define SHIFT				(D3DXVECTOR3(65.0f, 130.0f, 0.0f))		// ���炷��
#define GROUND_COL			(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f))		// ���n�̃T�C�Y

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
const char* CAbilityUI::m_acTextureFileName[CAbility::TYPE_MAX] = 			// �e�N�X�`���̖��O
{
	"data\\TEXTURE\\HoverMark.png",			// �z�o�[�W�F�b�g
	"data\\TEXTURE\\SkyDashMark.png",		// �W�F�b�g�_�b�V��
	"data\\TEXTURE\\",						// �O���E���h�N�G�C�N
};

//========================
// �R���X�g���N�^
//========================
CAbilityUI::CAbilityUI() : CObject(CObject::TYPE_ABILITYUI, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCntUI = 0; nCntUI < CAbility::TYPE_MAX; nCntUI++)
	{
		m_apAbilityUI[nCntUI] = nullptr;	// �\��UI�̏��
	}
}

//========================
// �f�X�g���N�^
//========================
CAbilityUI::~CAbilityUI()
{

}

//========================
// ����������
//========================
HRESULT CAbilityUI::Init(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apAbilityUI[nCnt] = new CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apAbilityUI[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apAbilityUI[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}

			// �e�N�X�`���̊��蓖�ď���
			m_apAbilityUI[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(m_acTextureFileName[nCnt]));
		}
		else
		{ // �|�C���^���@NULL �̏ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CAbilityUI::Uninit(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // �\��UI�� NULL ����Ȃ��ꍇ

			// �I������
			m_apAbilityUI[nCnt]->Uninit();
			m_apAbilityUI[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//========================
// �X�V����
//========================
void CAbilityUI::Update(void)
{
	// �g�p�󋵂̐ݒ菈��
	PossibleColor();

	// �ʒu�ǔ�����
	PosChase();
}

//========================
// �`�揈��
//========================
void CAbilityUI::Draw(void)
{
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // ��� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apAbilityUI[nCnt]->DrawLightOff();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CAbilityUI::SetData(const D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			m_apAbilityUI[nCnt]->SetPos(D3DXVECTOR3(pos.x - (SHIFT.x * (nCnt - 1)), pos.y + SHIFT.y, pos.z));		// �ʒu�ݒ�
			m_apAbilityUI[nCnt]->SetSize(UI_SIZE);		// �T�C�Y�ݒ�

			// ���_���̐ݒ菈��
			m_apAbilityUI[nCnt]->SetVertex();
		}
	}
}

//========================
// ��������
//========================
CAbilityUI* CAbilityUI::Create(const D3DXVECTOR3 pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAbilityUI* pAblt = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pAblt == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pAblt = new CAbilityUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAblt != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAblt->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAblt->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �\��UI�̃|�C���^��Ԃ�
	return pAblt;
}

//========================
// �g�p�󋵂̐ݒ菈��
//========================
void CAbilityUI::PossibleColor(void)
{
	// ���[�J���ϐ��錾
	CAbility* pAblt = CPlayer::Get()->GetAbility();		// �\�͂̏��

	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (pAblt->GetPossible((CAbility::TYPE)(nCnt)) == true)
		{ // �z�o�[�W�F�b�g���g�p�ł���ꍇ

			// �F��ݒ肷��
			m_apAbilityUI[nCnt]->SetVtxColor(NONE_D3DXCOLOR);
		}
		else
		{ // ��L�ȊO

			// �F��ݒ肷��
			m_apAbilityUI[nCnt]->SetVtxColor(GROUND_COL);
		}
	}
}

//========================
// �ʒu�ǔ�����
//========================
void CAbilityUI::PosChase(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = CPlayer::Get()->GetPos();

	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			m_apAbilityUI[nCnt]->SetPos(D3DXVECTOR3(pos.x + (SHIFT.x * (nCnt - 1)), pos.y + SHIFT.y, pos.z));		// �ʒu�ݒ�
		}
	}
}