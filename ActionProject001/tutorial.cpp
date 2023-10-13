//============================================
//
// �`���[�g���A����ʂ̃��C������[tutorial.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "tutorial.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "fade.h"
#include "Objectmesh.h"
#include "sound.h"

//=========================================
// �R���X�g���N�^
//=========================================
CTutorial::CTutorial() : CScene(TYPE_NONE, PRIORITY_BG)
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//����������
//=========================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTutorial::Uninit(void)
{
	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CTutorial::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTER�L�[���������ꍇ

		if (CManager::Get()->GetSound() != nullptr)
		{ // �T�E���h�� NULL ����Ȃ��ꍇ

			// �X�L�b�v�~�̏o������炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SKIPCIRCLE);
		}
	}

	// �Q�[�����[�h�ɂ���
	CManager::Get()->GetFade()->SetFade(MODE_GAME);
}

//======================================
//�`�揈��
//======================================
void CTutorial::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CTutorial::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);
}