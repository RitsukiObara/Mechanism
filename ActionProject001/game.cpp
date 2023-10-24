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
#include "edit.h"
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
#include "skybox.h"

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// �|�[�Y�̏��
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// �Q�[���̐i�s���
int CGame::m_nFinishCount = 0;								// �I���J�E���g

// �f�o�b�O��
#ifdef _DEBUG

CEdit* CGame::m_pEdit = nullptr;			// �G�f�B�b�g�̏��
bool CGame::m_bEdit = false;				// �G�f�B�b�g��Ԃ��ǂ���

#endif

//=========================================
// �R���X�g���N�^
//=========================================
CGame::CGame() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pPause = nullptr;			// �|�[�Y
	m_nFinishCount = 0;			// �I���J�E���g
	m_GameState = STATE_START;	// ���

// �f�o�b�O��
#ifdef _DEBUG

	m_pEdit = nullptr;			// �G�f�B�b�g
	m_bEdit = false;			// �G�f�B�b�g��
#endif

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

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �V�[���̏�����
	CScene::Init();

	// �v���C���[�𐶐�����
	CPlayer::Create(D3DXVECTOR3(-5000.0f, 0.0f, 0.0f));

	// ���[�h����
	CManager::Get()->GetFile()->Load(CFile::TYPE_ITEM);
	CManager::Get()->GetFile()->Load(CFile::TYPE_MACCHINA);
	CManager::Get()->GetFile()->Load(CFile::TYPE_ENEMY);
	CManager::Get()->GetFile()->Load(CFile::TYPE_TABLE);
	CManager::Get()->GetFile()->Load(CFile::TYPE_AIRPLANE);

	//// ��s�@�̐���
	//CAirplane::Create(D3DXVECTOR3(2000.0f, 200.0f, 0.0f), true);

	//// �l�W�̐�������
	//CScrew::Create(D3DXVECTOR3(300.0f, 300.0f, 0.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(1100.0f, 300.0f, 0.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 400.0f, 200.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 500.0f, 300.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 600.0f, 400.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 650.0f, 500.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 600.0f, 600.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 500.0f, 700.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 400.0f, 800.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(2000.0f, 300.0f, 900.0f), NONE_D3DXVECTOR3, false);

	//// �G�̐�������
	//CEnemy::Create(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), CEnemy::TYPE_ITOCAN);
	//CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f), CEnemy::TYPE_ITOCAN);
	//CEnemy::Create(D3DXVECTOR3(2000.0f, 0.0f, 1000.0f), CEnemy::TYPE_ITOCAN);
	//CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), CEnemy::TYPE_MACHIDORI);
	//CEnemy::Create(D3DXVECTOR3(-1500.0f, 0.0f, 0.0f), CEnemy::TYPE_MACHIDORI);
	//CEnemy::Create(D3DXVECTOR3(-2000.0f, 0.0f, 1000.0f), CEnemy::TYPE_MACHIDORI);
	//CEnemy::Create(D3DXVECTOR3(3000.0f, 0.0f, 1000.0f), CEnemy::TYPE_MACHIDORI);

	//CTable::Create(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
	//CTable::Create(D3DXVECTOR3(1500.0f, 200.0f, 0.0f));
	//CTable::Create(D3DXVECTOR3(-1000.0f, 300.0f, 1000.0f));
	//CTable::Create(D3DXVECTOR3(-1200.0f, 350.0f, 1000.0f));
	//CTable::Create(D3DXVECTOR3(2000.0f, 300.0f, 1000.0f));
	//CTable::Create(D3DXVECTOR3(2200.0f, 350.0f, 1000.0f));

	// �X�R�A�𐶐�����
	CGameScore::Create(D3DXVECTOR3(70.0f,500.0f,0.0f),NONE_D3DXVECTOR3,D3DXVECTOR3(25.0f,35.0f,0.0f));

	//// �}�L�i���̐���
	//CMacchina::Create(D3DXVECTOR3(-3000.0f, 0.0f, 100.0f));
	//CMacchina::Create(D3DXVECTOR3(3000.0f, 0.0f, 100.0f));
	//CMacchina::Create(D3DXVECTOR3(3200.0f, 0.0f, 100.0f));
	//CMacchina::Create(D3DXVECTOR3(2000.0f, 0.0f, 1100.0f));
	//CMacchina::Create(D3DXVECTOR3(-3000.0f, 0.0f, 1100.0f));

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

// �f�o�b�O��
#ifdef _DEBUG

	m_pEdit = nullptr;			// �G�f�B�b�g

#endif

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

// �f�o�b�O��
#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F7) == true)
	{ // F7�L�[���������ꍇ

		// �G�f�B�b�g�󋵂����ւ���
		m_bEdit = m_bEdit ? false : true;

		if (m_bEdit == true)
		{ // �G�f�B�b�g�󋵂� true �̏ꍇ

			if (m_pEdit == nullptr)
			{ // �G�f�B�b�g�� NULL ����Ȃ��ꍇ

				// �G�f�B�b�g�𐶐�����
				m_pEdit = CEdit::Create(NONE_D3DXVECTOR3);
			}
			else
			{ // ��L�ȊO

				// ��~
				assert(false);
			}
		}
		else
		{ // ��L�ȊO

			if (m_pEdit != nullptr)
			{ // �G�f�B�b�g�󋵂� NULL ����Ȃ��ꍇ

				// �I������
				m_pEdit->Uninit();
				m_pEdit = nullptr;
			}
			else
			{ // ��L�ȊO

				// ��~
				assert(false);
			}
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F9) == true)
	{ // F9�L�[���������ꍇ

		// �Z�[�u����
		CManager::Get()->GetFile()->Save(CFile::TYPE_ITEM);
		CManager::Get()->GetFile()->Save(CFile::TYPE_MACCHINA);
		CManager::Get()->GetFile()->Save(CFile::TYPE_ENEMY);
		CManager::Get()->GetFile()->Save(CFile::TYPE_TABLE);
		CManager::Get()->GetFile()->Save(CFile::TYPE_AIRPLANE);
	}

#endif

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

#ifdef _DEBUG

	if (m_bEdit == true)
	{ // �G�f�B�b�g�󋵂� true �̏ꍇ

		if (m_pEdit != nullptr)
		{ // �G�f�B�b�g�� NULL ����Ȃ��ꍇ

			// �G�f�B�b�g�̍X�V����
			m_pEdit->Update();
		}
	}
	else
	{ // ��L�ȊO

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // �����_���[�� NULL ����Ȃ��ꍇ

			// �����_���[�̍X�V
			CManager::Get()->GetRenderer()->Update();
		}
	}

#else

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �����_���[�̍X�V
		CManager::Get()->GetRenderer()->Update();
	}

#endif

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

// �f�o�b�O��
#ifdef _DEBUG
//======================================
// �G�f�B�b�g�̎擾����
//======================================
CEdit* CGame::GetEdit(void)
{
	// �G�f�B�b�g�̏���Ԃ�
	return m_pEdit;
}

//======================================
// �G�f�B�b�g�󋵂̎擾����
//======================================
bool CGame::IsEdit(void)
{
	// �G�f�B�b�g�󋵂�Ԃ�
	return m_bEdit;
}

#endif