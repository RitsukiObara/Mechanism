//============================================
//
// ���ԏ���[time.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "player.h"
#include "player_ability.h"
#include "player_act.h"
#include "ability_UI.h"
#include "object2D.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define BIGUI_SIZE			(D3DXVECTOR3(60.0f, 120.0f, 0.0f))		// �傫��UI�̃T�C�Y
#define SMALLUI_SIZE		(D3DXVECTOR3(40.0f, 80.0f, 0.0f))		// ������UI�̃T�C�Y
#define GROUND_COL			(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		// ���n�̃T�C�Y

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
const char* CAbilityUI::m_acTextureFileName[CAbility::TYPE_MAX] = 			// �e�N�X�`���̖��O
{
	"data\\TEXTURE\\HoverMark.png",			// �z�o�[�W�F�b�g
	"data\\TEXTURE\\SkyDashMark.png",		// �󒆃_�b�V��
	"data\\TEXTURE\\",						// �O���E���h�N�G�C�N
	"data\\TEXTURE\\",						// �X�^�[�h���b�v
};

//========================
// �R���X�g���N�^
//========================
CAbilityUI::CAbilityUI() : CObject(CObject::TYPE_ABILITYUI, CObject::PRIORITY_UI)
{
	for (int nCntUI = 0; nCntUI < GAGE_MAX; nCntUI++)
	{
		m_apObjectUI[nCntUI] = nullptr;		// �|���S���̏��
	}

	for (int nCntTex = 0; nCntTex < CAbility::TYPE_MAX; nCntTex++)
	{
		m_aTexInfo[nCntTex].m_nTexIdx = NONE_TEXIDX;	// �e�N�X�`���̔ԍ�
		m_aTexInfo[nCntTex].m_fTexSizeY = 1.0f;			// �e�N�X�`���̏c�T�C�Y
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
	for (int nCntTex = 0; nCntTex < CAbility::TYPE_MAX; nCntTex++)
	{
		m_aTexInfo[nCntTex].m_nTexIdx = CManager::Get()->GetTexture()->Regist(m_acTextureFileName[nCntTex]);		// �e�N�X�`���̓o�^����
		m_aTexInfo[nCntTex].m_fTexSizeY = 1.0f;						// �e�N�X�`���̏c�T�C�Y
	}

	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apObjectUI[nCnt] = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// �x����
			MessageBox(NULL, "�\��UI�̃����������Ɏg���Ă���I", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apObjectUI[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apObjectUI[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// �x����
				MessageBox(NULL, "�\��UI�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

				// ���s��Ԃ�
				return E_FAIL;
			}

			if (nCnt <= GAGE_BIG_METER)
			{ // ��Z�̏ꍇ

				// �e�N�X�`���̊��蓖�ď���
				m_apObjectUI[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_HOVER].m_nTexIdx);
			}
			else
			{ // ���Z�̏ꍇ

				// �e�N�X�`���̊��蓖�ď���
				m_apObjectUI[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_SKYDASH].m_nTexIdx);
			}
		}
		else
		{ // �|�C���^���@NULL �̏ꍇ

			// �x����
			MessageBox(NULL, "�\��UI�̃������̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

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
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] != nullptr)
		{ // ���Ԃ̃|�C���^�� NULL ����Ȃ��ꍇ

			// �I������
			m_apObjectUI[nCnt]->Uninit();
			m_apObjectUI[nCnt] = nullptr;
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
	// ���[�J���ϐ��錾
	CPlayer* player = CPlayer::Get();		// �v���C���[�̏����擾����

	switch (player->GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// �A�N���o�b�g���[�h

		// �T�C�Y�ύX����
		Size(CAbility::TYPE_HOVER, CAbilityUI::GAGE_BIG_METER, HOVER_INTERVAL, (BIGUI_SIZE.y / HOVER_INTERVAL));			// �z�o�[�W�F�b�g
		Size(CAbility::TYPE_SKYDASH, CAbilityUI::GAGE_SMALL_METER, SKYDASH_INTERVAL, (SMALLUI_SIZE.y / SKYDASH_INTERVAL));	// �󒆃_�b�V��

		break;

	case CPlayer::MODE_MASSIVE:		// �}�b�V�u���[�h

		break;

	case CPlayer::MODE_REBOOT:		// ���u�[�g�h���C�u���[�h

		break;
	}

	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		// ���_���W�̐ݒ菈��
		m_apObjectUI[nCnt]->SetVtxUnderHeightGage();
	}
}

//========================
// �`�揈��
//========================
void CAbilityUI::Draw(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apObjectUI[nCnt]->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CAbilityUI::SetData(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			if (nCnt <= GAGE::GAGE_BIG_METER)
			{ // �傫���Q�[�W�̏ꍇ

				// �ݒ菈��
				m_apObjectUI[nCnt]->SetPos(posBig);				// �ʒu�ݒ�
				m_apObjectUI[nCnt]->SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
				m_apObjectUI[nCnt]->SetSize(BIGUI_SIZE);		// �T�C�Y�ݒ�
			}
			else
			{ // �������Q�[�W�̏ꍇ

				// �ݒ菈��
				m_apObjectUI[nCnt]->SetPos(posSmall);			// �ʒu�ݒ�
				m_apObjectUI[nCnt]->SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
				m_apObjectUI[nCnt]->SetSize(SMALLUI_SIZE);		// �T�C�Y�ݒ�
			}
			m_apObjectUI[nCnt]->SetLength();			// �����ݒ�
			m_apObjectUI[nCnt]->SetAngle();				// �����ݒ�

			// ���_���̐ݒ菈��
			m_apObjectUI[nCnt]->SetVtxUnderHeightGage();

			if (nCnt % 2 == 0)
			{ // ���n�̏ꍇ

				// ���_�J���[�̐ݒ菈��
				m_apObjectUI[nCnt]->SetVtxColor(GROUND_COL);
			}
		}
	}
}

//========================
// ��������
//========================
CAbilityUI* CAbilityUI::Create(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAbilityUI* pTime = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pTime == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTime = new CAbilityUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTime != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTime->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�\��UI�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTime->SetData(posBig, posSmall);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pTime;
}

//========================
// �T�C�Y�ݒ菈��
//========================
void CAbilityUI::Size(const CAbility::TYPE type, const CAbilityUI::GAGE gage, const int nInterval, float fSizeMove)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 size = m_apObjectUI[gage]->GetSize();				// ��Z�̃T�C�Y
	int nCount = CPlayer::Get()->GetAbility()->GetInterval(type);	// �J�E���g

	// �T�C�Y��ݒ肷��
	size.y = ((nInterval - nCount) * fSizeMove);
	m_aTexInfo[type].m_fTexSizeY = (float)((1.0f / nInterval) * nCount);

	// �T�C�Y��K�p����
	m_apObjectUI[gage]->SetSize(size);
	
	// �����S�̏c�̃e�N�X�`�����W�̐ݒ菈��
	m_apObjectUI[gage]->SetVtxTextureUnderHeight(m_aTexInfo[type].m_fTexSizeY);
}