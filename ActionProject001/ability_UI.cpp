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
#define SHIFT				(40.0f)									// ���炷��
#define GROUND_COL			(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		// ���n�̃T�C�Y

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
const char* CAbilityUI::m_acTextureFileName[CAbility::TYPE_MAX] = 			// �e�N�X�`���̖��O
{
	"data\\TEXTURE\\HoverMark.png",			// �z�o�[�W�F�b�g
	"data\\TEXTURE\\SkyDashMark.png",		// �W�F�b�g�_�b�V��
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
		m_apAcrobat[nCntUI] = nullptr;			// �A�N���o�b�g�̏��
		m_apMassive[nCntUI] = nullptr;			// �}�b�V�u�̏��
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

	// �A�N���o�b�g�̐�������
	if (FAILED(AcrobatCreate()))
	{ // �����Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �}�b�V�u�̐�������
	if (FAILED(MassiveCreate()))
	{ // �����Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
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
		if (m_apAcrobat[nCnt] != nullptr)
		{ // �A�N���o�b�g�̃|�C���^�� NULL ����Ȃ��ꍇ

			// �I������
			m_apAcrobat[nCnt]->Uninit();
			m_apAcrobat[nCnt] = nullptr;
		}

		if (m_apMassive[nCnt] != nullptr)
		{ // �A�N���o�b�g�̃|�C���^�� NULL ����Ȃ��ꍇ

			// �I������
			m_apMassive[nCnt]->Uninit();
			m_apMassive[nCnt] = nullptr;
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
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		// ���_���W�̐ݒ菈��
		m_apAcrobat[nCnt]->SetVtxUnderHeightGage();
		m_apMassive[nCnt]->SetVtxUnderHeightGage();
	}
}

//========================
// �`�揈��
//========================
void CAbilityUI::Draw(void)
{
	switch (CPlayer::Get()->GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// �A�N���o�b�g���[�h

		// �}�b�V�u�̕`�揈��
		DrawMassive();

		// �A�N���o�b�g�̕`�揈��
		DrawAcrobat();

		break;

	case CPlayer::MODE_MASSIVE:		// �}�b�V�u���[�h

		// �A�N���o�b�g�̕`�揈��
		DrawAcrobat();

		// �}�b�V�u�̕`�揈��
		DrawMassive();

		break;

	case CPlayer::MODE_REBOOT:		// ���u�[�g�h���C�u���[�h

		break;
	}
}

//========================
// �A�N���o�b�g�̕`�揈��
//========================
void CAbilityUI::DrawAcrobat(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apAcrobat[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apAcrobat[nCnt]->Draw();
		}
	}
}

//========================
// �}�b�V�u�̕`�揈��
//========================
void CAbilityUI::DrawMassive(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apMassive[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apMassive[nCnt]->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CAbilityUI::SetData(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	// �A�N���o�b�g�̐ݒ菈��
	SetDataAcrobat(posBig, posSmall);

	// �}�b�V�u�̐ݒ菈��
	SetDataMassive(posBig, posSmall);
}

//========================
// �A�N���o�b�g�̐ݒ菈��
//========================
void CAbilityUI::SetDataAcrobat(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apAcrobat[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			if (nCnt <= GAGE::GAGE_BIG_METER)
			{ // �傫���Q�[�W�̏ꍇ

				// �ݒ菈��
				m_apAcrobat[nCnt]->SetPos(posBig);			// �ʒu�ݒ�
				m_apAcrobat[nCnt]->SetSize(BIGUI_SIZE);		// �T�C�Y�ݒ�
			}
			else
			{ // �������Q�[�W�̏ꍇ

				// �ݒ菈��
				m_apAcrobat[nCnt]->SetPos(posSmall);		// �ʒu�ݒ�
				m_apAcrobat[nCnt]->SetSize(SMALLUI_SIZE);	// �T�C�Y�ݒ�
			}

			m_apAcrobat[nCnt]->SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
			m_apAcrobat[nCnt]->SetLength();					// �����ݒ�
			m_apAcrobat[nCnt]->SetAngle();					// �����ݒ�

			// ���_���̐ݒ菈��
			m_apAcrobat[nCnt]->SetVtxUnderHeightGage();

			if (nCnt % 2 == 0)
			{ // ���n�̏ꍇ

				// ���_�J���[�̐ݒ菈��
				m_apAcrobat[nCnt]->SetVtxColor(GROUND_COL);
			}
		}
	}
}

//========================
// �}�b�V�u�̐ݒ菈��
//========================
void CAbilityUI::SetDataMassive(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apMassive[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			if (nCnt <= GAGE::GAGE_BIG_METER)
			{ // �傫���Q�[�W�̏ꍇ

				// �ݒ菈��
				m_apMassive[nCnt]->SetPos(D3DXVECTOR3(posBig.x + SHIFT, posBig.y, 0.0f));			// �ʒu�ݒ�
				m_apMassive[nCnt]->SetSize(BIGUI_SIZE);		// �T�C�Y�ݒ�
			}
			else
			{ // �������Q�[�W�̏ꍇ

				// �ݒ菈��
				m_apMassive[nCnt]->SetPos(D3DXVECTOR3(posSmall.x + SHIFT, posSmall.y, 0.0f));		// �ʒu�ݒ�
				m_apMassive[nCnt]->SetSize(SMALLUI_SIZE);	// �T�C�Y�ݒ�
			}

			m_apMassive[nCnt]->SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
			m_apMassive[nCnt]->SetLength();					// �����ݒ�
			m_apMassive[nCnt]->SetAngle();					// �����ݒ�

			// ���_���̐ݒ菈��
			m_apMassive[nCnt]->SetVtxUnderHeightGage();

			if (nCnt % 2 == 0)
			{ // ���n�̏ꍇ

				// ���_�J���[�̐ݒ菈��
				m_apMassive[nCnt]->SetVtxColor(GROUND_COL);
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
		pAblt->SetData(posBig, posSmall);
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
// �A�N���o�b�g�̐�������
//========================
HRESULT CAbilityUI::AcrobatCreate(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apAcrobat[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apAcrobat[nCnt] = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apAcrobat[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apAcrobat[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}

			if (nCnt <= GAGE_BIG_METER)
			{ // ��Z�̏ꍇ

				// �e�N�X�`���̊��蓖�ď���
				m_apAcrobat[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_HOVER].m_nTexIdx);
			}
			else
			{ // ���Z�̏ꍇ

				// �e�N�X�`���̊��蓖�ď���
				m_apAcrobat[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_JETDASH].m_nTexIdx);
			}
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
// �}�b�V�u�̐�������
//========================
HRESULT CAbilityUI::MassiveCreate(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apMassive[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apMassive[nCnt] = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apMassive[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apMassive[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}

			if (nCnt <= GAGE_BIG_METER)
			{ // ��Z�̏ꍇ

				// �e�N�X�`���̊��蓖�ď���
				m_apMassive[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_GROUNDQUAKE].m_nTexIdx);
			}
			else
			{ // ���Z�̏ꍇ

				// �e�N�X�`���̊��蓖�ď���
				m_apMassive[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_STARDROP].m_nTexIdx);
			}
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