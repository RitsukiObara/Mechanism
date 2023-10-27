//============================================
//
// �}�l�[�W���[�̃��C������[manager.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "renderer.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "Objectmesh.h"

#include "file.h"
#include "camera.h"
#include "result_score.h"

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CResult::STATE CResult::m_state = STATE_TIMEDISP;		// ���

//=========================================
// �R���X�g���N�^
//=========================================
CResult::CResult() : CScene(TYPE_NONE, PRIORITY_BG)
{
	m_state = STATE_TIMEDISP;
}

//=========================================
// �f�X�g���N�^
//=========================================
CResult::~CResult()
{

}

//=========================================
//����������
//=========================================
HRESULT CResult::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	// ���U���g�X�R�A�𐶐�����
	CResultScore::Create(D3DXVECTOR3(400.0f, SCREEN_HEIGHT * 0.5f, 0.0f), NONE_D3DXVECTOR3, D3DXVECTOR3(25.0f, 30.0f, 0.0f));

	// �S�Ă̒l������������
	m_state = STATE_TIMEDISP;		// ���

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CResult::Uninit(void)
{
	// �j������
	Release();
}

//======================================
//�X�V����
//======================================
void CResult::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A,0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTER�L�[���������ꍇ

		// �����L���O�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RANKING);

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �X�V����
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//�`�揈��
//======================================
void CResult::Draw(void)
{

}

//======================================
// ��Ԃ̐ݒ菈��
//======================================
void CResult::SetState(const CResult::STATE state)
{
	// ��Ԃ�ݒ肷��
	m_state = state;
}

//======================================
// ��Ԃ̎擾����
//======================================
CResult::STATE CResult::GetState(void)
{
	// ��Ԃ�Ԃ�
	return m_state;
}