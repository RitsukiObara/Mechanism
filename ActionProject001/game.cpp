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

#include "objectElevation.h"
#include "player.h"
#include "game_score.h"
#include "goal.h"
#include "skybox.h"
#include "pork.h"
#include "needle.h"
#include "block.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define SUCCESS_TRANS_COUNT		(80)		// �������̑J�ڃJ�E���g
#define FAILED_TRANS_COUNT		(200)		// ���s���̑J�ڃJ�E���g

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// �|�[�Y�̏��
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// �Q�[���̐i�s���
int CGame::m_nFinishCount = 0;								// �I���J�E���g
int CGame::m_nScore = 0;									// �X�R�A

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
	m_nScore = 0;				// �X�R�A

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

	// ���b�V���̓ǂݍ��ݏ���
	CMesh::TxtSet();

	// ���b�V���̃e�L�X�g�ǂݍ���
	//CMesh::TxtSet();

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
	CPlayer::Create(D3DXVECTOR3(-4500.0f, 0.0f, 0.0f));

	// ���[�h����
	CManager::Get()->GetFile()->Load(CFile::TYPE_ITEM);
	CManager::Get()->GetFile()->Load(CFile::TYPE_MACCHINA);
	CManager::Get()->GetFile()->Load(CFile::TYPE_ENEMY);
	CManager::Get()->GetFile()->Load(CFile::TYPE_TABLE);
	CManager::Get()->GetFile()->Load(CFile::TYPE_AIRPLANE);
	CManager::Get()->GetFile()->Load(CFile::TYPE_NEEDLE);

	// �X�R�A�𐶐�����
	CGameScore::Create(D3DXVECTOR3(50.0f,680.0f,0.0f),NONE_D3DXVECTOR3,D3DXVECTOR3(25.0f,35.0f,0.0f));

	// �S�[���̐���
	CGoal::Create(D3DXVECTOR3(20000.0f, 300.0f, 0.0f));

	// �|�[�N�̐���
	CPork::Create(D3DXVECTOR3(-3500.0f, 0.0f, 0.0f), CPork::TYPE_HOVER);
	CPork::Create(D3DXVECTOR3(2950.0f, 0.0f, 0.0f), CPork::TYPE_DASH);
	CPork::Create(D3DXVECTOR3(5600.0f, 0.0f, 1000.0f), CPork::TYPE_QUAKE);

	// ��s���̊Ԋu
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 200.0f, 100.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 300.0f, 200.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 370.0f, 300.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 470.0f, 400.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 510.0f, 500.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 510.0f, 600.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 470.0f, 700.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 370.0f, 800.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 250.0f, 900.0f), NONE_D3DXVECTOR3, false);
	//CScrew::Create(D3DXVECTOR3(4800.0f, ��s�@�̈ʒu + 100.0f, 1000.0f), NONE_D3DXVECTOR3, false);

	CBlock::Create(D3DXVECTOR3(-4000.0f, 0.0f, 0.0f), NONE_D3DXVECTOR3, D3DXVECTOR3(1.0f, 1.0f, 1.0f), CBlock::TYPE::TYPE_WOOD);

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
		CManager::Get()->GetFile()->Save(CFile::TYPE_NEEDLE);
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

	case CGame::STATE_DEATH:

		// ���S���̑J�ڏ���
		DeathTransition();

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

	if (m_nFinishCount % SUCCESS_TRANS_COUNT == 0)
	{ // �I���J�E���g����萔�𒴂����ꍇ

		// ���_��n��
		m_nScore = CGameScore::Get()->GetScore();

		// ���U���g�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// ���S���̑J�ڏ���
//======================================
void CGame::DeathTransition(void)
{
	// �I���J�E���g�����Z����
	m_nFinishCount++;

	if (m_nFinishCount % FAILED_TRANS_COUNT == 0)
	{ // �I���J�E���g����萔�𒴂����ꍇ

		// ���_��n��
		m_nScore = CGameScore::Get()->GetScore();

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
// �X�R�A�̃��Z�b�g����
//======================================
void CGame::ResetScore(void)
{
	// �X�R�A������������
	m_nScore = 0;
}

//======================================
// �X�R�A�̎擾����
//======================================
int CGame::GetScore(void)
{
	// �X�R�A��Ԃ�
	return m_nScore;
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