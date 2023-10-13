//============================================
//
// �V�[���̃��C������[scene.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "scene.h"

#include "logo.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "sound.h"

#include "manager.h"
#include "file.h"

//======================================
// �R���X�g���N�^
//======================================
CScene::CScene() : CObject(TYPE_NONE, PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//======================================
// �I�[�o�[���[�h�R���X�g���N�^
//======================================
CScene::CScene(TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//======================================
// �f�X�g���N�^
//======================================
CScene::~CScene()
{

}

//======================================
// �R���X�g���N�^�̔�
//======================================
void CScene::Box(void)
{
	// �S�Ă̒l���N���A����
	m_mode = MODE_LOGO;			// ���݂̃��[�h
}

//======================================
// ����������
//======================================
HRESULT CScene::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//======================================
// �I������
//======================================
void CScene::Uninit(void)
{
	// �j������
	Release();
}

//======================================
// �X�V����
//======================================
void CScene::Update(void)
{

}

//======================================
// �`�揈��
//======================================
void CScene::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CScene::SetData(const MODE mode)
{
	// ���[�h��ݒ肷��
	m_mode = mode;

	if (CManager::Get()->GetSound() != nullptr)
	{ // �T�E���h�� NULL ����Ȃ��ꍇ

		//// BGM�𗬂�
		//switch (m_mode)
		//{
		//case MODE_LOGO:

		//	break;

		//case MODE_TITLE:

		//	// �^�C�g��BGM�𗬂�
		//	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);

		//	break;

		//case MODE_TUTORIAL:

		//	// �`���[�g���A��BGM�𗬂�
		//	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TUTORIAL);

		//	break;

		//case MODE_GAME:

		//	// �Q�[��BGM�𗬂�
		//	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

		//	break;

		//case MODE_RESULT:

		//	// ���U���gBGM�𗬂�
		//	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULT);

		//	break;

		//case MODE_RANKING:

		//	// �����L���OBGM�𗬂�
		//	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_RANKING);

		//	break;
		//}
	}
}

//======================================
// ���[�h�̐ݒ菈��
//======================================
void CScene::SetMode(const MODE mode)
{
	// ���[�h��ݒ肷��
	m_mode = mode;
}

//======================================
// ���[�h�̎擾����
//======================================
CScene::MODE CScene::GetMode(void) const
{
	// ���[�h��Ԃ�
	return m_mode;
}

//======================================
// ��������
//======================================
CScene* CScene::Create(const MODE mode)
{
	// ���[�J���|�C���^�錾
	CScene* pScene = nullptr;		// �V�[���ւ̃|�C���^

	if (pScene == nullptr)
	{ // �V�[���� NULL �̏ꍇ

		switch (mode)
		{
		case MODE_LOGO:			// ���S���

			// ���������m�ۂ���
			pScene = new CLogo;

			break;

		case MODE_TITLE:		// �^�C�g�����

			// ���������m�ۂ���
			pScene = new CTitle;

			break;

		case MODE_TUTORIAL:		// �`���[�g���A�����

			// ���������m�ۂ���
			pScene = new CTutorial;

			break;

		case MODE_GAME:			// �Q�[�����

			// ���������m�ۂ���
			pScene = new CGame;

			break;

		case MODE_RESULT:		// ���U���g���

			// ���������m�ۂ���
			pScene = new CResult;

			break;

		case MODE_RANKING:		// �����L���O���

			// ���������m�ۂ���
			pScene = new CRanking;

			break;
		}

		if (pScene != nullptr)
		{ // �V�[���ւ̃|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			pScene->Init();

			// ���̐ݒ菈��
			pScene->SetData(mode);
		}
		else
		{ // �V�[���ւ̃|�C���^�� NULL �̏ꍇ

			// �x����
			MessageBox(NULL, "�V�[���̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �V�[���� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �V�[���ւ̃|�C���^��Ԃ�
	return pScene;
}