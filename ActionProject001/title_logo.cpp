//============================================
//
// �^�C�g�����S����[title_logo.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "title_logo.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define LOGO_TEXTURE		"data/TEXTURE/TitleLogo.png"							// �^�C�g�����S�̃e�N�X�`��
#define LOGO_POS			(D3DXVECTOR3(-450.0f, SCREEN_HEIGHT * 0.5f, 0.0f))		// �^�C�g�����S�̈ʒu
#define LOGO_SIZE			(D3DXVECTOR3(400.0f, 100.0f, 0.0f))						// �^�C�g�����S�̃T�C�Y
#define LOGO_SPEED			(20.0f)													// �^�C�g�����S�̑��x

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CTitleLogo* CTitleLogo::m_pTitleLogo = nullptr;		// �^�C�g�����S�̃|�C���^

//============================
// �R���X�g���N�^
//============================
CTitleLogo::CTitleLogo() : CObject2D(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_MOVE;		// ���
}

//============================
// �f�X�g���N�^
//============================
CTitleLogo::~CTitleLogo()
{

}

//============================
// ����������
//============================
HRESULT CTitleLogo::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // ���s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_state = STATE_MOVE;		// ���

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CTitleLogo::Uninit(void)
{
	// �I������
	CObject2D::Uninit();

	// �^�C�g�����S�� NULL �ɂ���
	m_pTitleLogo = nullptr;
}

//============================
// �X�V����
//============================
void CTitleLogo::Update(void)
{
	switch (m_state)
	{
	case CTitleLogo::STATE_MOVE:

	{
		D3DXVECTOR3 pos = GetPos();

		pos.x += LOGO_SPEED;

		SetPos(pos);
	}

	if (GetPos().x >= SCREEN_WIDTH * 0.5f)
	{ // ���̈ʒu���߂����ꍇ

		// ��~��Ԃɂ���
		m_state = STATE_STOP;
	}

		break;

	case CTitleLogo::STATE_STOP:


		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���_���̐ݒ菈��
	SetVertex();
}

//============================
// �`�揈��
//============================
void CTitleLogo::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//============================
// ���̐ݒ菈��
//============================
void CTitleLogo::SetData(void)
{
	// ����ݒ肷��
	SetPos(LOGO_POS);			// �ʒu
	SetPosOld(LOGO_POS);		// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);	// ����
	SetSize(LOGO_SIZE);			// �T�C�Y
	SetAngle();					// ����
	SetLength();				// ����

	// �e�N�X�`���̐ݒ菈��
	BindTexture(CManager::Get()->GetTexture()->Regist(LOGO_TEXTURE));

	// ���_��񏈗�
	SetVertex();

	// �S�Ă̒l��ݒ肷��
	m_state = STATE_MOVE;		// ���
}

//============================
// �擾����
//============================
CTitleLogo* CTitleLogo::Get(void)
{
	if (m_pTitleLogo != nullptr)
	{ // �^�C�g�����S�̏�񂪂���ꍇ

		// �^�C�g�����S�̃|�C���^��Ԃ�
		return m_pTitleLogo;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// �^�C�g�����S�̃|�C���^��Ԃ�
		return m_pTitleLogo;
	}
}

//============================
//��������
//============================
CTitleLogo* CTitleLogo::Create(void)
{
	if (m_pTitleLogo == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		m_pTitleLogo = new CTitleLogo;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (m_pTitleLogo != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pTitleLogo->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pTitleLogo->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �^�C�g�����S�̃|�C���^��Ԃ�
	return m_pTitleLogo;
}