//============================================
//
// �U������̃��C������[turn.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "turn.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define TURN_TEXTURE		"data/TEXTURE/SmokeStaging.png"		// �U������̃e�N�X�`��
#define TURN_SIZE			(D3DXVECTOR3(50.0f, 40.0f, 0.0f))	// �U������̃T�C�Y
#define TURN_COUNT			(2)									// �U������̃J�E���g
#define TURN_PATTERN		(8)									// �U������̃p�^�[����

//===========================================
// �R���X�g���N�^
//===========================================
CTurn::CTurn() : CBillboardAnim(CObject::TYPE_TURN,CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
	m_nLife = 0;				// ����
}

//===========================================
// �f�X�g���N�^
//===========================================
CTurn::~CTurn()
{

}

//===========================================
// ����������
//===========================================
HRESULT CTurn::Init(void)
{
	if (FAILED(CBillboardAnim::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nLife = 0;				// ����

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CTurn::Uninit(void)
{
	// �I��
	CBillboardAnim::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CTurn::Update(void)
{
	// ���������炷
	m_nLife--;

	// �X�V����
	CBillboardAnim::Update();

	if (m_bRight == true)
	{ // �E�����̏ꍇ

		// �e�N�X�`�����W�̐ݒ菈��
		SetVtxAnimRev(GetTexPattern(), GetPattern());
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`�����W�̐ݒ菈��
		SetVtxAnim(GetTexPattern(), GetPattern());
	}

	if (m_nLife <= 0)
	{ // �p�^�[�������ő吔�𒴂����ꍇ

		// �I������
		Uninit();
	}
}

//===========================================
// �`�揈��
//===========================================
void CTurn::Draw(void)
{
	// �`�揈��
	CBillboardAnim::DrawLightOff();
}

//===========================================
// �ݒ菈��
//===========================================
void CTurn::SetData(const D3DXVECTOR3& pos, const bool bRight)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetSize(TURN_SIZE);			// �T�C�Y�ݒ�

	// �A�j���[�V�����̐ݒ菈��
	SetAnim(TURN_COUNT, TURN_PATTERN);

	// �S�Ă̒l������������
	m_nLife = TURN_COUNT * TURN_PATTERN;	// ����
	m_bRight = bRight;						// �E������

	// ���_���̏�����
	SetVertex();

	if (m_bRight == true)
	{ // �E�����̏ꍇ

		// �e�N�X�`�����W�̐ݒ菈��
		SetVtxAnimRev(GetTexPattern(), GetPattern());
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`�����W�̐ݒ菈��
		SetVtxAnim(GetTexPattern(), GetPattern());
	}

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TURN_TEXTURE));
}

//===========================================
// ��������
//===========================================
CTurn* CTurn::Create(const D3DXVECTOR3& pos, const bool bRight)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTurn* pTurn = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pTurn == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTurn = new CTurn;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTurn != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pTurn->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTurn->SetData(pos, bRight);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �U������̃|�C���^��Ԃ�
	return pTurn;
}