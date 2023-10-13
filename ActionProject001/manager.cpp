//============================================
//
// �}�l�[�W���[�̃��C������[manager.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "file.h"
#include "debugproc.h"
#include "texture.h"
#include "objectX.h"
#include "camera.h"
#include "light.h"
#include "fade.h"

#include "elevation_manager.h"
#include "airplane_manager.h"
#include "screw_manager.h"
#include "enemy_manager.h"

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CManager* CManager::m_pManager = nullptr;			// �}�l�[�W���[�̏��

//=========================================
// �R���X�g���N�^
//=========================================
CManager::CManager()
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CManager::~CManager()
{

}

//=========================================
//����������
//=========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �}�l�[�W���[�̐�������
	CElevationManager::Create();		// �N���}�l�[�W���[
	CAirplaneManager::Create();			// ��s�@�}�l�[�W���[
	CScrewManager::Create();			// �l�W�}�l�[�W���[
	CEnemyManager::Create();			// �G�}�l�[�W���[

	if (m_pFile == nullptr)
	{ // �t�@�C���ւ̃|�C���^�� nullptr �̏ꍇ

		// �t�@�C���̃��������m�ۂ���
		m_pFile = new CFile;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�t�@�C���̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pDebugProc == nullptr)
	{ // �f�o�b�O�\���ւ̃|�C���^�� nullptr �̏ꍇ

		// �f�o�b�O�\���̃��������m�ۂ���
		m_pDebugProc = new CDebugProc;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�f�o�b�O�\���̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pRenderer == nullptr)
	{ // �����_���[�ւ̃|�C���^�� NULL �̏ꍇ

		// �����_���[�̃��������m�ۂ���
		m_pRenderer = new CRenderer;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�����_���[�̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pInputKeyboard == nullptr)
	{ // �L�[�{�[�h�ւ̃|�C���^�� NULL �̏ꍇ

		// �L�[�{�[�h�̃��������m�ۂ���
		m_pInputKeyboard = new CInputKeyboard;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�L�[�{�[�h�̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pInputGamePad == nullptr)
	{ // �Q�[���p�b�h�ւ̃|�C���^�� NULL �̏ꍇ

		// �Q�[���p�b�h�̃��������m�ۂ���
		m_pInputGamePad = new CInputGamePad;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�Q�[���p�b�h�̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pSound == nullptr)
	{ // �T�E���h�ւ̃|�C���^�� NULL �̏ꍇ

		// �T�E���h�̃��������m�ۂ���
		m_pSound = new CSound;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�T�E���h�̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pCamera == nullptr)
	{ // �J�����ւ̃|�C���^�� NULL �̏ꍇ

		// �J�����̃��������m�ۂ���
		m_pCamera = new CCamera;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�J�����̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pLight == nullptr)
	{ // ���C�g�ւ̃|�C���^�� NULL �̏ꍇ

		// ���C�g�̃��������m�ۂ���
		m_pLight = new CLight;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "���C�g�̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pTexture == nullptr)
	{ // �e�N�X�`���ւ̃|�C���^�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pTexture = new CTexture;
	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�e�N�X�`���̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	if (m_pRenderer != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{ // ���������������s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // �m�ۂɎ��s���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�����_���[�̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pInputKeyboard != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{ // ���������������s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // �m�ۂɎ��s���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�L�[�{�[�h�̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pInputGamePad != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		if (FAILED(m_pInputGamePad->Init(hInstance, hWnd)))
		{ // ���������������s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // �m�ۂɎ��s���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�Q�[���p�b�h�̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pSound != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		if (FAILED(m_pSound->Init(hWnd)))
		{ // ���������������s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // �m�ۂɎ��s���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�T�E���h�̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pDebugProc != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		m_pDebugProc->Init();
	}
	else
	{ // �m�ۂɎ��s���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�f�o�b�O�\���̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pCamera != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		if (FAILED(m_pCamera->Init()))
		{ // �J�����̏������Ɏ��s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // �m�ۂɎ��s���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�J�����̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pLight != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		if (FAILED(m_pLight->Init()))
		{ // ���C�g�̏������Ɏ��s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // �m�ۂɎ��s���Ă����ꍇ

		// �x����
		MessageBox(NULL, "���C�g�̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pTexture != nullptr)
	{ // �m�ۂɐ������Ă����ꍇ

		// ����������
		if (FAILED(m_pTexture->Init()))
		{ // �e�N�X�`���̏������Ɏ��s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // �m�ۂɎ��s�����ꍇ

		// �x����
		MessageBox(NULL, "�e�N�X�`���̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �e�N�X�`���̓ǂݍ��ݏ���
	if (FAILED(TexLoad()))
	{ // �ǂݍ��݂Ɏ��s�����ꍇ

		// �x����
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pFade == nullptr)
	{ // �t�F�[�h�ւ̃|�C���^�� nullptr �̏ꍇ

#ifdef _DEBUG

		// �t�F�[�h�̃��������m�ۂ���
		m_pFade = m_pFade->Create(CScene::MODE_GAME);
#else

		// �V�[���̃��������m�ۂ���
		m_pFade = m_pFade->Create(CScene::MODE_GAME);
#endif 

	}
	else
	{ // �|�C���^���g���Ă����ꍇ

		// �x����
		MessageBox(NULL, "�t�F�[�h�̃|�C���^���g���Ă���I", "�x���I", MB_ICONWARNING);
	}

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CManager::Uninit(void)
{
	if (m_pSound != nullptr)
	{ // �T�E���h�̃��������m�ۂ���Ă����ꍇ

		// �T�E���h�̒�~
		m_pSound->Stop();
	}

	// �e�N�X�`���̔j������
	TexUnload();

	if (m_pRenderer != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �I������
		m_pRenderer->Uninit();

		// ���������J������
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pInputKeyboard != nullptr)
	{ // �L�[�{�[�h�� NULL ����Ȃ��ꍇ

		// �I������
		m_pInputKeyboard->Uninit();

		// ���������J������
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	if (m_pInputGamePad != nullptr)
	{ // �Q�[���p�b�h�� NULL ����Ȃ��ꍇ

		// �I������
		m_pInputGamePad->Uninit();

		// ���������J������
		delete m_pInputGamePad;
		m_pInputGamePad = nullptr;
	}

	if (m_pSound != nullptr)
	{ // �T�E���h�� NULL ����Ȃ��ꍇ

		// �I������
		m_pSound->Uninit();

		// ���������J������
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pFile != nullptr)
	{ // �t�@�C���� NULL ����Ȃ��ꍇ

		// �I������
		m_pFile->Uninit();

		// ���������J������
		delete m_pFile;
		m_pFile = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{ // �f�o�b�O�\���� NULL ����Ȃ��ꍇ

		// �I������
		m_pDebugProc->Uninit();

		// ���������J������
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	if (m_pCamera != nullptr)
	{ // �J������ NULL ����Ȃ��ꍇ

		// �I������
		m_pCamera->Uninit();

		// ���������J������
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pLight != nullptr)
	{ // ���C�g�� NULL ����Ȃ��ꍇ

		// �I������
		m_pLight->Uninit();

		// ���������J������
		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pTexture != nullptr)
	{ // �e�N�X�`���� NULL ����Ȃ��ꍇ

		// �e�N�X�`���̔j������
		m_pTexture->Unload();

		// ���������J������
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pFade != nullptr)
	{ // �t�F�[�h�� NULL ����Ȃ��ꍇ

		// �t�F�[�h�̔j������
		m_pFade->Uninit();

		// ���������J������
		delete m_pFade;
		m_pFade = nullptr;
	}

	// �V�[���ւ̃|�C���^�� NULL �ɂ���
	m_pScene = nullptr;

	// �}�l�[�W���[�̏I������
	CElevationManager::Get()->Uninit();		// �N���}�l�[�W���[
	CAirplaneManager::Get()->Uninit();		// ��s�@�}�l�[�W���[
	CScrewManager::Get()->Uninit();			// �l�W�}�l�[�W���[
	CEnemyManager::Get()->Uninit();			// �G�}�l�[�W���[

	// �}�l�[�W���[�̃��������������
	delete m_pManager;
	m_pManager = nullptr;
}

//======================================
//�X�V����
//======================================
void CManager::Update(void)
{
	if (m_pFade != nullptr)
	{ // �t�F�[�h�� NULL ����Ȃ��ꍇ

		// �t�F�[�h�̍X�V
		m_pFade->Update();
	}

	if (m_pInputKeyboard != nullptr)
	{ // �L�[�{�[�h�� NULL ����Ȃ��ꍇ

		// �L�[�{�[�h�̍X�V
		m_pInputKeyboard->Update();
	}

	if (m_pInputGamePad != nullptr)
	{ // �Q�[���p�b�h�� NULL ����Ȃ��ꍇ

		// �Q�[���p�b�h�̍X�V
		m_pInputGamePad->Update();
	}

	if (m_pCamera != nullptr)
	{ // �J������ NULL ����Ȃ��ꍇ

		// �J�����̍X�V
		m_pCamera->Update();
	}

	if (m_pLight != nullptr)
	{ // ���C�g�� NULL ����Ȃ��ꍇ

		// ���C�g�̍X�V
		m_pLight->Update();
	}

#ifdef _DEBUG		// �f�o�b�O�p

	if (m_pDebugProc != nullptr)
	{ // �f�o�b�O�\���� NULL ����Ȃ��ꍇ

		// �f�o�b�O�\���̍X�V
		m_pDebugProc->Update();
	}

	if (m_pInputKeyboard->GetTrigger(DIK_F6) == true)
	{ // F6�L�[���������ꍇ

		// ���C���[�t���[����ON/OFF
		m_bWire = m_bWire ? false : true;

		if (m_bWire == true)
		{ // ���C���[���[�hON�̏ꍇ

			// ���C���[�t���[����ON�ɂ���
			m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{ // ���C���[���[�hOFF�̏ꍇ

			// ���C���[�t���[����OFF�ɂ���
			m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

#endif

	if (m_pScene != nullptr)
	{ // �V�[���� NULL ����Ȃ��ꍇ

		// �V�[���̍X�V����
		m_pScene->Update();
	}

	//if (m_pRenderer != nullptr)
	//{ // �����_���[�� NULL ����Ȃ��ꍇ

	//	// �X�V����
	//	m_pRenderer->Update();
	//}

	m_pDebugProc->Print("���[�h�F%d", m_pScene->GetMode());
}

//======================================
//�`�揈��
//======================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pRenderer->Draw();
	}

	if (m_pScene != nullptr)
	{ // �V�[���� NULL ����Ȃ��ꍇ

		// �V�[���̕`�揈��
		m_pScene->Draw();
	}
}

//======================================
// �e�N�X�`���̓ǂݍ��ݏ���
//======================================
HRESULT CManager::TexLoad(void)
{
	// X�t�@�C���̏���������
	CXFile::Init();

	// �e�N�X�`���̃��[�h����
	m_pTexture->Load();

	// ������Ԃ�
	return S_OK;
}

//======================================
// �e�N�X�`���̔j������
//======================================
void CManager::TexUnload(void)
{
	// X�t�@�C���̏I������
	CXFile::Uninit();

	// �S�ẴI�u�W�F�N�g�̔j������
	CObject::ReleaseAll();
}

//======================================
// �����_���[�̎擾����
//======================================
CRenderer* CManager::GetRenderer(void)
{
	// �����_���[�̏���Ԃ�
	return m_pRenderer;
}

//======================================
// �L�[�{�[�h�̎擾����
//======================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	// �L�[�{�[�h�̏���Ԃ�
	return m_pInputKeyboard;
}

//======================================
// �Q�[���p�b�h�̎擾����
//======================================
CInputGamePad* CManager::GetInputGamePad(void)
{
	// �Q�[���p�b�h�̏���Ԃ�
	return m_pInputGamePad;
}

//======================================
// �T�E���h�̎擾����
//======================================
CSound* CManager::GetSound(void)
{
	// �T�E���h�̏���Ԃ�
	return m_pSound;
}

//======================================
// �t�@�C���̎擾����
//======================================
CFile* CManager::GetFile(void)
{
	// �t�@�C���̏���Ԃ�
	return m_pFile;
}

//======================================
// �f�o�b�O�\���̎擾����
//======================================
CDebugProc* CManager::GetDebugProc(void)
{
	// �f�o�b�O�\���̏���Ԃ�
	return m_pDebugProc;
}

//======================================
// �J�����\���̎擾����
//======================================
CCamera* CManager::GetCamera(void)
{
	// �J�����̏���Ԃ�
	return m_pCamera;
}

//======================================
// ���C�g�̎擾����
//======================================
CLight* CManager::GetLight(void)
{
	// ���C�g�̏���Ԃ�
	return m_pLight;
}

//======================================
// �e�N�X�`���̎擾����
//======================================
CTexture* CManager::GetTexture(void)
{
	// �e�N�X�`���̏���Ԃ�
	return m_pTexture;
}

//======================================
// �t�F�[�h�̎擾����
//======================================
CFade* CManager::GetFade(void)
{
	// �t�F�[�h�̏���Ԃ�
	return m_pFade;
}

//======================================
// ���[�h�̐ݒ菈��
//======================================
void CManager::SetMode(const CScene::MODE mode)
{
	if (m_pSound != nullptr)
	{ // �T�E���h�� NULL ����Ȃ��ꍇ

		// �T�E���h�̒�~����
		m_pSound->Stop();
	}

	// �S�ẴI�u�W�F�N�g�̔j������
	CObject::ReleaseAll();

	// �V�[���� NULL �ɂ���
	m_pScene = nullptr;

	if (m_pScene == nullptr)
	{ // �V�[���� NULL ����Ȃ��ꍇ

		// ��������
		m_pScene = m_pScene->Create(mode);
	}
}

//======================================
// ���[�h�̎擾����
//======================================
CScene::MODE CManager::GetMode(void)
{
	// ���[�h��Ԃ�
	return m_pScene->GetMode();
}

//======================================
// �}�l�[�W���[�̐�������
//======================================
CManager* CManager::Create(void)
{
	if (m_pManager == nullptr)
	{ // �}�l�[�W���[�� NULL �̏ꍇ

		// �}�l�[�W���[�𐶐�����
		m_pManager = new CManager;

		// �}�l�[�W���[�̏���Ԃ�
		return m_pManager;
	}
	else
	{ // ��L�ȊO

		// �}�l�[�W���[�̏���Ԃ�
		return m_pManager;
	}
}

//======================================
// �}�l�[�W���[�̎擾����
//======================================
CManager* CManager::Get(void)
{
	if (m_pManager != nullptr)
	{ // �}�l�[�W���[�� NULL ����Ȃ��ꍇ

		// �}�l�[�W���[�̏���Ԃ�
		return m_pManager;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// �}�l�[�W���[�𐶐�����
		return CManager::Create();
	}
}