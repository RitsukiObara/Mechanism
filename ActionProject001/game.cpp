//============================================
//
// �Q�[���̃��C������[game.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "airplane.h"
#include "objectElevation.h"
#include "player.h"
#include "screw.h"
#include "enemy.h"
#include "table.h"
#include "macchina.h"
#include "game_score.h"
#include "goal.h"

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// �|�[�Y�̏��
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// �Q�[���̐i�s���
int CGame::m_nFinishCount = 0;								// �I���J�E���g

//=========================================
// �R���X�g���N�^
//=========================================
CGame::CGame() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pPause = nullptr;			// �|�[�Y�X�R�A
	m_nFinishCount = 0;			// �I���J�E���g
	m_GameState = STATE_START;	// ���
}

//=========================================
// �f�X�g���N�^
//=========================================
CGame::~CGame()
{

}

//=========================================
//����������
//=========================================
HRESULT CGame::Init(void)
{
	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	//if (m_pField == NULL)
	//{ // �t�B�[���h�ւ̃|�C���^�� NULL �̏ꍇ

	//	// �t�B�[���h�̐ݒ菈��
	//	m_pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
	//}

	// �V�[���̏�����
	CScene::Init();

	// �v���C���[�𐶐�����
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��s�@�̐���
	CAirplane::Create(D3DXVECTOR3(2000.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// �l�W�̐�������
	CScrew::Create(D3DXVECTOR3(300.0f, 300.0f, 0.0f));
	CScrew::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f));
	CScrew::Create(D3DXVECTOR3(1100.0f, 300.0f, 0.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 400.0f, 200.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 500.0f, 300.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 600.0f, 400.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 650.0f, 500.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 600.0f, 600.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 500.0f, 700.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 400.0f, 800.0f));
	CScrew::Create(D3DXVECTOR3(2000.0f, 300.0f, 900.0f));

	// �G�̐�������
	CEnemy::Create(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), CEnemy::TYPE_ITOCAN);
	CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f), CEnemy::TYPE_ITOCAN);
	CEnemy::Create(D3DXVECTOR3(2000.0f, 0.0f, 1000.0f), CEnemy::TYPE_ITOCAN);
	CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), CEnemy::TYPE_MACHIDORI);
	CEnemy::Create(D3DXVECTOR3(-1500.0f, 0.0f, 0.0f), CEnemy::TYPE_MACHIDORI);
	CEnemy::Create(D3DXVECTOR3(-2000.0f, 0.0f, 1000.0f), CEnemy::TYPE_MACHIDORI);
	CEnemy::Create(D3DXVECTOR3(3000.0f, 0.0f, 1000.0f), CEnemy::TYPE_MACHIDORI);

	CTable::Create(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
	CTable::Create(D3DXVECTOR3(1500.0f, 200.0f, 0.0f));
	CTable::Create(D3DXVECTOR3(-1000.0f, 300.0f, 1000.0f));
	CTable::Create(D3DXVECTOR3(-1200.0f, 350.0f, 1000.0f));
	CTable::Create(D3DXVECTOR3(2000.0f, 300.0f, 1000.0f));
	CTable::Create(D3DXVECTOR3(2200.0f, 350.0f, 1000.0f));

	// �X�R�A�𐶐�����
	CGameScore::Create(D3DXVECTOR3(70.0f,500.0f,0.0f),NONE_D3DXVECTOR3,D3DXVECTOR3(25.0f,35.0f,0.0f));

	// �}�L�i���̐���
	CMacchina::Create(D3DXVECTOR3(-3000.0f, 0.0f, 100.0f));
	CMacchina::Create(D3DXVECTOR3(3000.0f, 0.0f, 100.0f));
	CMacchina::Create(D3DXVECTOR3(3200.0f, 0.0f, 100.0f));
	CMacchina::Create(D3DXVECTOR3(2000.0f, 0.0f, 1100.0f));
	CMacchina::Create(D3DXVECTOR3(-3000.0f, 0.0f, 1100.0f));

	// �S�[���̐���
	CGoal::Create(D3DXVECTOR3(4000.0f, 300.0f, 1000.0f));

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
	m_GameState = STATE_START;		// ���

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CGame::Uninit(void)
{
	// �|�C���^�� NULL �ɂ���
	m_pPause = nullptr;			// �|�[�Y

	// ��������������
	m_GameState = STATE_START;	// �Q�[���̐i�s���

	// �I���J�E���g������������
	m_nFinishCount = 0;

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CGame::Update(void)
{
	switch (m_GameState)
	{
	case CGame::STATE_START:

		// �|�[�Y����
		Pause();

		break;

	case CGame::STATE_PLAY:

		// �|�[�Y����
		Pause();

		break;

	case CGame::STATE_GOAL:



		break;

	case CGame::STATE_LEAVE:

		break;

	case CGame::STATE_FINISH:

		// �J�ڏ���
		Transition();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �����_���[�̍X�V
		CManager::Get()->GetRenderer()->Update();
	}

	CManager::Get()->GetDebugProc()->Print("��ԁF%d", m_GameState);
}

//======================================
//�`�揈��
//======================================
void CGame::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CGame::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);

	if (m_pPause == nullptr)
	{ // �|�[�Y�ւ̃|�C���^�� NULL �̏ꍇ

		// �|�[�Y�̐�������
		m_pPause = CPause::Create();
	}

	// �X�^�[�g��Ԃɂ���
	m_GameState = STATE_PLAY;

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
}

//======================================
// �|�[�Y����
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true)
	{ // P�L�[���������ꍇ

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // �t�F�[�h������Ԃ��A�I���ȊO�̏ꍇ

			if (m_pPause->GetPause() == false)
			{ // �|�[�Y�� false �������ꍇ

				// �|�[�Y�󋵂� true �ɂ���
				m_pPause->SetPause(true);
			}
			else
			{ // �|�[�Y�� true �������ꍇ

				// �|�[�Y�󋵂� false �ɂ���
				m_pPause->SetPause(false);
			}

			// ���艹��炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// �J�ڏ���
//======================================
void CGame::Transition(void)
{
	// �I���J�E���g�����Z����
	m_nFinishCount++;

	if (m_nFinishCount % 80 == 0)
	{ // �I���J�E���g����萔�𒴂����ꍇ

		// ���U���g�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// �|�[�Y�̎擾����
//======================================
CPause* CGame::GetPause(void)
{
	// �|�[�Y�̏���Ԃ�
	return m_pPause;
}

//======================================
// �Q�[���̐i�s��Ԃ̐ݒ菈��
//======================================
void CGame::SetState(const STATE state)
{
	// �Q�[���̐i�s��Ԃ�ݒ肷��
	m_GameState = state;
}

//======================================
// �Q�[���̐i�s��Ԃ̎擾����
//======================================
CGame::STATE CGame::GetState(void)
{
	// �Q�[���̐i�s��Ԃ�Ԃ�
	return m_GameState;
}

//======================================
// �|�[�Y��NULL������
//======================================
void CGame::DeletePause(void)
{
	// �|�[�Y�̃|�C���^�� NULL �ɂ���
	m_pPause = nullptr;
}