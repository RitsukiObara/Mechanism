//============================================
//
// �^�C�g����ʂ̃��C������[title.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "title.h"
#include "fade.h"
#include "Objectmesh.h"

#include "title_logo.h"
#include "skybox.h"

// �}�N����`
#define SET_RANKING_TIMER		(600)		// �����L���O��ʂɑJ�ڂ���J�E���g��

//=========================================
// �R���X�g���N�^
//=========================================
CTitle::CTitle() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_nTransCount = 0;
}

//=========================================
// �f�X�g���N�^
//=========================================
CTitle::~CTitle()
{

}

//=========================================
//����������
//=========================================
HRESULT CTitle::Init(void)
{
	//�@�V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �^�C�g�����S�̐���
	CTitleLogo::Create();

	// �S�Ă̒l������������
	m_nTransCount = 0;

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTitle::Uninit(void)
{
	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CTitle::Update(void)
{
	// �J�ڃJ�E���g�����Z����
	m_nTransCount++;

	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();

	if (m_nTransCount % SET_RANKING_TIMER == 0)
	{ // �J�ڃJ�E���g����萔�ɒB�����ꍇ

		// �����L���O�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RANKING);

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
	{ // ENTER�L�[���������ꍇ

		// �`���[�g���A���ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);

		// ���̐�̏������s��Ȃ�
		return;
	}
}

//======================================
//�`�揈��
//======================================
void CTitle::Draw(void)
{

}