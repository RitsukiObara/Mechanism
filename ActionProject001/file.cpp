//============================================
//
// �t�@�C���̃��C������[file.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "scene.h"
#include "file.h"
#include "object.h"

#include "screw.h"
#include "screw_manager.h"
#include "macchina.h"
#include "macchina_manager.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "table.h"
#include "table_manager.h"
#include "airplane.h"
#include "airplane_manager.h"

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
const char* CFile::c_apBooleanDisp[2] =					// bool�^�̕\��
{
	"FALSE",							// TRUE
	"TRUE",								// FALSE
};

//===========================================
// �R���X�g���N�^
//===========================================
CFile::CFile()
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_FILE_DATA; nCnt++)
	{
		m_pItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// �A�C�e���̈ʒu
	}

	m_pItemInfo.nNum = 0;				// ����
	m_pItemInfo.bSuccess = false;		// ������
}

//===========================================
// �f�X�g���N�^
//===========================================
CFile::~CFile()
{

}

//===========================================
// �Z�[�u����
//===========================================
HRESULT CFile::Save(const TYPE type)
{
	switch (type)
	{
	case TYPE_ITEM:			// �A�C�e��

		// �A�C�e���̃Z�[�u����
		if (FAILED(SaveItem()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MACCHINA:		// �}�L�i��

		// �}�L�i���̃Z�[�u����
		if (FAILED(SaveMacchina()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_ENEMY:		// �G

		// �G�̃Z�[�u����
		if(FAILED(SaveEnemy()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TABLE:		// ��

		// �e�[�u���̃Z�[�u����
		if(FAILED(SaveTable()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_AIRPLANE:		// ��s�@

		// ��s�@�̃Z�[�u����
		if (FAILED(SaveAirplane()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// ���[�h����
//===========================================
HRESULT CFile::Load(const TYPE type)
{
	switch (type)
	{
	case TYPE_ITEM:			// �A�C�e��

		// �A�C�e���̃��[�h����
		if(FAILED(LoadItem()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MACCHINA:		// �}�L�i��

		// �}�L�i���̃��[�h����
		if(FAILED(LoadMacchina()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_ENEMY:		// �G

		// �G�̃��[�h����
		if(FAILED(LoadEnemy()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TABLE:		// ��

		// ��̃��[�h����
		if(FAILED(LoadTable()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_AIRPLANE:		// ��s�@

		// ��s�@�̃��[�h����
		if (FAILED(LoadAirplane()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���ʂ�Ԃ�
	return S_OK;
}

//===========================================
// ����������
//===========================================
HRESULT CFile::Init(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_FILE_DATA; nCnt++)
	{
		m_pItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// �A�C�e���̈ʒu
	}

	m_pItemInfo.nNum = 0;				// ����
	m_pItemInfo.bSuccess = false;		// ������

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CFile::Uninit(void)
{
	
}

//===========================================
// �A�C�e���̃Z�[�u����
//===========================================
HRESULT CFile::SaveItem(void)
{
	// ���[�J���ϐ��錾
	CScrew* pScrew = CScrewManager::Get()->GetTop();		// �擪�̃l�W��������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen("data\\TXT\\Screw.txt", "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pScrew != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_SCREW\n");		// �l�W�̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pScrew->GetPos().x, pScrew->GetPos().y, pScrew->GetPos().z);			// �ʒu����������

			// ���������������
			fprintf(pFile, "END_SET_SCREW\n\n");			// �l�W�̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pScrew = pScrew->GetNext();
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �}�L�i���̃Z�[�u����
//===========================================
HRESULT CFile::SaveMacchina(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// �G�̃Z�[�u����
//===========================================
HRESULT CFile::SaveEnemy(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// ��̃Z�[�u����
//===========================================
HRESULT CFile::SaveTable(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// ��s�@�̃Z�[�u����
//===========================================
HRESULT CFile::SaveAirplane(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// �A�C�e���̃��[�h����
//===========================================
HRESULT CFile::LoadItem(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// �}�L�i���̃��[�h����
//===========================================
HRESULT CFile::LoadMacchina(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// �G�̃��[�h����
//===========================================
HRESULT CFile::LoadEnemy(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// ��̃��[�h����
//===========================================
HRESULT CFile::LoadTable(void)
{
	// ������Ԃ�
	return S_OK;
}

//===========================================
// ��s�@�̃��[�h����
//===========================================
HRESULT CFile::LoadAirplane(void)
{
	// ������Ԃ�
	return S_OK;
}