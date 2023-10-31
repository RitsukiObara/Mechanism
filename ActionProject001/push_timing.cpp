//============================================
//
// �����^�C�~���O�̕\������[push_timing.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "push_timing.h"
#include "input.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define BUTTON_TEXTURE	"data/TEXTURE/PushKey.png"			// �L�[�{�[�h�̃e�N�X�`��
#define GAMEPAD_TEXTURE	"data/TEXTURE/PushGamePad.png"		// �Q�[���{�^���̃e�N�X�`��
#define ANIM_COUNT		(6)			// �A�j���[�V�����J�E���g
#define ANIM_PATTERN	(2)			// �A�j���[�V�����p�^�[��
#define BUTTON_SIZE		(D3DXVECTOR3(60.0f, 30.0f, 0.0f))	// �{�^���̃T�C�Y
#define GAMEPAD_SIZE	(D3DXVECTOR3(30.0f, 30.0f, 0.0f))	// �Q�[���p�b�h�̃T�C�Y

//===========================================
// �R���X�g���N�^
//===========================================
CPushTiming::CPushTiming() : CBillboardAnim(CObject::TYPE_PUSHTIMING,CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_bGamePad = false;		// �Q�[���p�b�h��
}

//===========================================
// �f�X�g���N�^
//===========================================
CPushTiming::~CPushTiming()
{

}

//===========================================
// ����������
//===========================================
HRESULT CPushTiming::Init(void)
{
	if (FAILED(CBillboardAnim::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_bGamePad = false;		// �Q�[���p�b�h��

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CPushTiming::Uninit(void)
{
	// �I��
	CBillboardAnim::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CPushTiming::Update(void)
{
	// �X�V����
	CBillboardAnim::Update();

	if (CManager::Get()->GetInputGamePad() != nullptr &&
		CManager::Get()->GetInputGamePad()->GetConnect() == true)
	{ // �Q�[���p�b�h���ڑ�����Ă���ꍇ

		if (m_bGamePad == false)
		{ // �Q�[���p�b�h�󋵂� false �̏ꍇ

			// �Q�[���p�b�h�󋵂� true �ɂ���
			m_bGamePad = true;

			// �e�N�X�`���̓ǂݍ��ݏ���
			BindTexture(CManager::Get()->GetTexture()->Regist(GAMEPAD_TEXTURE));
		}

		// �T�C�Y��ݒ肷��
		SetSize(GAMEPAD_SIZE);

		// ���_���̐ݒ菈��
		SetVertex();
	}
	else
	{ // ��L�ȊO

		if (m_bGamePad == true)
		{ // �Q�[���p�b�h�󋵂� true �̏ꍇ

			// �Q�[���p�b�h�󋵂� false �ɂ���
			m_bGamePad = false;

			// �e�N�X�`���̓ǂݍ��ݏ���
			BindTexture(CManager::Get()->GetTexture()->Regist(BUTTON_TEXTURE));
		}

		// �T�C�Y��ݒ肷��
		SetSize(BUTTON_SIZE);

		// ���_���̐ݒ菈��
		SetVertex();
	}
}

//===========================================
// �`�揈��
//===========================================
void CPushTiming::Draw(void)
{
	// �`�揈��
	CBillboardAnim::DrawLightOff();
}

//===========================================
// �ݒ菈��
//===========================================
void CPushTiming::SetData(const D3DXVECTOR3& pos)
{
	if (CManager::Get()->GetInputGamePad() != nullptr &&
		CManager::Get()->GetInputGamePad()->GetConnect() == true)
	{ // �Q�[���p�b�h���ڑ�����Ă���ꍇ

		// �Q�[���p�b�h�󋵂� true �ɂ���
		m_bGamePad = true;
	}
	else
	{ // ��L�ȊO

		// �Q�[���p�b�h�󋵂� false �ɂ���
		m_bGamePad = false;
	}

	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetSize(BUTTON_SIZE);		// �T�C�Y�ݒ�

	// �A�j���[�V�����̐ݒ菈��
	SetAnim(ANIM_COUNT, ANIM_PATTERN);

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����̐ݒ菈��
	SetVtxAnim(GetTexPattern(), GetPattern());

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(BUTTON_TEXTURE));
}

//===========================================
// ��������
//===========================================
CPushTiming* CPushTiming::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPushTiming* pPushTiming = nullptr;			// �����^�C�~���O�̃C���X�^���X�𐶐�

	if (pPushTiming == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pPushTiming = new CPushTiming;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPushTiming != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPushTiming->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�����^�C�~���O�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPushTiming->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �����^�C�~���O�̃|�C���^��Ԃ�
	return pPushTiming;
}