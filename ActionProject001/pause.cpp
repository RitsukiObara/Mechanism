//=======================================
//
// �|�[�Y�̃��C������[pause.cpp]
// Author ��������
//
//=======================================
#include "main.h"
#include "manager.h"
#include "object2D.h"
#include "game.h"
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "texture.h"
#include "useful.h"

//---------------------------------------
// �}�N����`
//---------------------------------------
// �ʒu�֌W
#define BACK_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))		// �w�i�̈ʒu
#define PAUSEMENU_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))		// ���j���[�̈ʒu
#define CONTINUE_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 260.0f, 0.0f))					// �R���e�B�j���[�̈ʒu
#define RESET_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 410.0f, 0.0f))					// ���Z�b�g�̈ʒu
#define TITLE_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 560.0f, 0.0f))					// �^�C�g���̈ʒu

// �T�C�Y�֌W
#define BACK_SIZE				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))		// �w�i�̃T�C�Y
#define MENU_SIZE				(D3DXVECTOR3(SCREEN_WIDTH * 0.45f, SCREEN_HEIGHT * 0.45f, 0.0f))	// ���j���[�̃T�C�Y
#define CONTINUE_SIZE			(D3DXVECTOR3(360.0f, 64.0f, 0.0f))			// �R���e�B�j���[�̃T�C�Y
#define RESET_SIZE				(D3DXVECTOR3(220.0f, 64.0f, 0.0f))			// ���Z�b�g�̃T�C�Y
#define TITLE_SIZE				(D3DXVECTOR3(200.0f, 64.0f, 0.0f))			// �^�C�g���̃T�C�Y

// ���̑�
#define PAUSE_BACK_COL			(D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.4f))			// �w�i�̐F
#define PAUSE_ALPHA				(0.02f)					// �����x�̕ω��̐��l
#define DECIDE_ALPHA			(0.7f)					// ���肵����̓����x�̕ω�
#define NOCHOICE_ALPHA			(0.5f)					// �I��ł��Ȃ��I�����̓����x
#define SIZEDEST_MAGNI			(1.2f)					// �ڕW�̃T�C�Y�̔{��
#define SIZEDEST_CORRECT_VALUE	(0.7f)					// �ڕW�̃T�C�Y�̕␳�̔{��
#define CHOICE_ALPHA_MIN		(0.4f)					// �I�����̓����x�̍ŏ��l
#define SELECT_REPEAT_COUNT		(15)					// �I���̎��̃��s�[�g�̃J�E���g��

// �ÓI�����o�ϐ��錾
const char*CPause::c_apFilename[CPause::POLYGON_MAX] =	// �e�N�X�`���t�@�C����
{
	nullptr,								// �w�i�|���S��
	"data\\TEXTURE\\PauseMenu.png",			// �|�[�Y���j���[�̃e�N�X�`��
	"data\\TEXTURE\\PauseContinue.png",		// �R���e�B�j���[�̃e�N�X�`��
	"data\\TEXTURE\\PauseReset.png",		// ���Z�b�g�̃e�N�X�`��
	"data\\TEXTURE\\PauseTitle.png",		// �^�C�g���̃e�N�X�`��
};

const CPause::Info CPause::c_aPauseInfo[POLYGON_MAX] = 	// �|�[�Y�̏��
{
	{ BACK_POS ,BACK_SIZE },			// �w�i�|���S��
	{ PAUSEMENU_POS ,MENU_SIZE },		// �|�[�Y���j���[
	{ CONTINUE_POS ,CONTINUE_SIZE },	// �R���e�B�j���[
	{ RESET_POS ,RESET_SIZE },			// ���g���C
	{ TITLE_POS ,TITLE_SIZE },			// �^�C�g��
};

//==========================================
// �R���X�g���N�^
//==========================================
CPause::CPause() : CObject(TYPE_PAUSE, PRIORITY_PAUSE)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_apObject[nCnt] = nullptr;						// �|���S���̏��
	}

	m_PauseColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �I�𒆂̑I�����̐F
	sizeDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ڕW�̃T�C�Y
	m_PauseMenu = MENU_CONTINUE;;						// �|�[�Y���j���[
	m_nPauseCounter = 0;								// �J�E���^�[
	m_fPauseAlpha = 0.0f;								// �����x��ω�������ϐ�
	m_bPause = false;									// �|�[�Y��
	m_bDisp = true;										// �`���
}

//==========================================
// �f�X�g���N�^
//==========================================
CPause::~CPause()
{

}

//==========================================
// �|�[�Y�̏���������
//==========================================
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{ // �I�u�W�F�N�g�� NULL �̏ꍇ

			// �|���S���̐�������
			m_apObject[nCnt] = m_apObject[nCnt]->Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, PRIORITY_PAUSE);

			// ����ݒ肷��
			m_apObject[nCnt]->SetPos(c_aPauseInfo[nCnt].pos);			// �ʒu
			m_apObject[nCnt]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����
			m_apObject[nCnt]->SetSize(c_aPauseInfo[nCnt].size);			// �T�C�Y
			m_apObject[nCnt]->SetLength();								// ����
			m_apObject[nCnt]->SetAngle();								// ����

			// ���_��ݒ肷��
			m_apObject[nCnt]->SetVertex();

			if (nCnt == POLYGON_BACK)
			{ // �w�i�|���S���̏ꍇ

				// ���_�J���[��ݒ肷��
				m_apObject[nCnt]->SetVtxColor(PAUSE_BACK_COL);
			}

			// �e�N�X�`���̊��蓖�ď���
			m_apObject[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(c_apFilename[nCnt]));
		}
	}

	// �S�Ă̒l������������
	m_PauseMenu = MENU_CONTINUE;						// ���j���[
	m_PauseColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �I�����̐F
	sizeDest = D3DXVECTOR3(c_aPauseInfo[m_PauseMenu].size.x * SIZEDEST_MAGNI, c_aPauseInfo[m_PauseMenu].size.y * SIZEDEST_MAGNI, 0.0f);			// �ڕW�̃T�C�Y
	m_nPauseCounter = 0;								// �J�E���^�[
	m_fPauseAlpha = PAUSE_ALPHA;						// �����x�̕ω���
	m_bPause = false;									// �|�[�Y��
	m_bDisp = true;										// �`���

	// ������Ԃ�
	return S_OK;
}

//========================================
// �|�[�Y�̏I������
//========================================
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// �I������
		m_apObject[nCnt]->Uninit();
	}

	// �j������
	Release();

	// �|�[�Y��NULL������
	CGame::DeletePause();
}

//========================================
// �|�[�Y�̍X�V����
//========================================
void CPause::Update(void)
{
	// �J�E���^�[�����Z����
	m_nPauseCounter++;

	// �|�[�Y�̑I������
	PauseSelect();

	// �|�[�Y�̌��菈��
	if (PauseDecide() == true)
	{ // �ʂ̃��[�h�ɂȂ����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetFade()->GetFade() != CFade::FADE_NONE &&
		CManager::Get()->GetFade()->GetFade() != CFade::FADE_IN)
	{ // �t�F�[�h�A�E�g���Ă���ꍇ

		// �����x�̕ω���ݒ肷��
		m_fPauseAlpha = DECIDE_ALPHA;
	}

	// �����x�␳����
	PauseAlphaCorrect();

	// �I�𒆂̑I�����̓����x��ω�������
	m_PauseColor.a -= m_fPauseAlpha;

	// ���_�ݒ菈��
	PauseVertex();
}

//=====================================
// �|�[�Y�̕`�揈��
//=====================================
void CPause::Draw(void)
{
// �f�o�b�O�p
#ifdef _DEBUG

	if (m_bDisp == true)
	{ // �`��󋵂� true �������ꍇ

		for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
		{
			// �`�揈��
			m_apObject[nCnt]->Draw();
		}
	}

#else

	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// �`�揈��
		m_apObject[nCnt]->Draw();
	}

#endif
}

//=====================================
// �T�C�Y�␳����
//=====================================
void CPause::SizeCorrect(int nIdx)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 size = m_apObject[nIdx]->GetSize();		// �T�C�Y���擾����

	// �T�C�Y�̕␳
	useful::Correct(sizeDest.x, &size.x, SIZEDEST_CORRECT_VALUE);
	useful::Correct(sizeDest.y, &size.y, SIZEDEST_CORRECT_VALUE);

	//�T�C�Y���X�V����
	m_apObject[nIdx]->SetSize(size);
}

//=====================================
// �|�[�Y�󋵂̐ݒ菈��
//=====================================
void CPause::SetPause(const bool bPause)
{
	// �|�[�Y�̏󋵂�ݒ肷��
	m_bPause = bPause;

	if (m_bPause == false)
	{ // �|�[�Y�� false �̏ꍇ

		// �I�����Ă�����̂��R���e�B�j���[�ɂ���
		m_PauseMenu = MENU::MENU_CONTINUE;
	}
}

//=====================================
// �|�[�Y�󋵂̎擾����
//=====================================
bool CPause::GetPause(void)
{
	// �|�[�Y�̏󋵂�Ԃ�
	return m_bPause;
}

//=====================================
// �`��󋵂̐؂�ւ�����
//=====================================
void CPause::ChangeDisp(void)
{
	// �`��󋵂�؂�ւ���
	m_bDisp = m_bDisp ? false : true;
}

//=====================================
// �|�[�Y�̑I������
//=====================================
void CPause::PauseSelect(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true ||
		CManager::Get()->GetInputKeyboard()->GetRepeat(DIK_W, SELECT_REPEAT_COUNT) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_UP, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYTrigger(0) == true)
	{ // W�L�[���������ꍇ

		// �|�[�Y�̐ݒ�
		m_PauseMenu = (MENU)((m_PauseMenu + (MENU_MAX - 1)) % MENU_MAX);

		// �����x�̕ω���ݒ肷��
		m_fPauseAlpha = PAUSE_ALPHA;

		// �I������炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true ||
		CManager::Get()->GetInputKeyboard()->GetRepeat(DIK_S, SELECT_REPEAT_COUNT) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_DOWN, 0) == true)
	{ // S�L�[���������ꍇ

		// �|�[�Y�̐ݒ�
		m_PauseMenu = (MENU)((m_PauseMenu + 1) % MENU_MAX);

		// �����x�̕ω���ݒ肷��
		m_fPauseAlpha = PAUSE_ALPHA;

		// �I������炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
	}

	// �ڕW�̃T�C�Y�̐ݒ菈��
	sizeDest = D3DXVECTOR3(c_aPauseInfo[m_PauseMenu + POLYGON_CONTINUE].size.x * SIZEDEST_MAGNI, c_aPauseInfo[m_PauseMenu + POLYGON_CONTINUE].size.y * SIZEDEST_MAGNI, 0.0f);
}

//=====================================
// �|�[�Y�̌��菈��
//=====================================
bool CPause::PauseDecide(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
	{ // ENTER�L�[���������ꍇ

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // �t�F�[�h���s���Ă��Ȃ��Ƃ�

			switch (m_PauseMenu)
			{
			case MENU_CONTINUE:		// �R���e�B�j���[���w���Ă����ꍇ

				break;

			case MENU_RESET:			// ���g���C���w���Ă����ꍇ

				// �I������
				Uninit();

				// ���[�h�ݒ�(�Q�[���Ɉڍs)
				CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);

				break;

			case MENU_TITLE:			// �^�C�g�����w���Ă����ꍇ

				// �I������
				Uninit();

				// ���[�h�ݒ�(�^�C�g���Ɉڍs)
				CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

				break;

			default:

				// ��~
				assert(false);

				break;
			}

			// �|�[�Y����������
			m_bPause = false;
		}

		// ���艹��炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �|�[�Y�̓����x�␳����
//=====================================
void CPause::PauseAlphaCorrect(void)
{
	if (m_PauseColor.a > 1.0f)
	{ // �A���t�@�l��1.0f���ゾ�����ꍇ

		// �A���t�@�l��1.0f�ɐݒ肷��
		m_PauseColor.a = 1.0f;

		// �A���t�@�l�̕������t�ɕς���
		m_fPauseAlpha *= -1;
	}
	else if (m_PauseColor.a < CHOICE_ALPHA_MIN)
	{ // �A���t�@�l����萔�����������ꍇ

		// �A���t�@�l���ŏ��l�ɐݒ肷��
		m_PauseColor.a = CHOICE_ALPHA_MIN;

		// �A���t�@�l�̕������t�ɕς���
		m_fPauseAlpha *= -1;
	}
}

//=====================================
// �|�[�Y�̒��_�ݒ菈��
//=====================================
void CPause::PauseVertex(void)
{
	for (int nPauseCnt = 0; nPauseCnt < MENU_MAX; nPauseCnt++)
	{
		if (m_PauseMenu == nPauseCnt)
		{ // �I�𒆂̑I�����̏ꍇ

			// �F��ݒ肷��
			m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_PauseColor.a));

			// �T�C�Y�̕␳����
			SizeCorrect(nPauseCnt + POLYGON_CONTINUE);
		}
		else
		{ // �I�����Ă��Ȃ��I�����̏ꍇ

			// �F��ݒ肷��
			m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, NOCHOICE_ALPHA));

			// �T�C�Y�̐ݒ菈��
			m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetSize(c_aPauseInfo[nPauseCnt + POLYGON_CONTINUE].size);
		}

		// ���_���W�̐ݒ菈��
		m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetVertex();
	}
}

//=====================================
// ��������
//=====================================
CPause* CPause::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPause* pPause = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pPause == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pPause = new CPause;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPause != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPause->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �|�[�Y�̃|�C���^��Ԃ�
	return pPause;
}