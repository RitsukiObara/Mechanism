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
		m_ItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// �A�C�e���̈ʒu
		m_MacchinaInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// �}�L�i���̈ʒu
		m_EnemyInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// �G�̈ʒu
		m_EnemyInfo.type[nCnt] = CEnemy::TYPE_ITOCAN;	// �G�̎��
		m_TableInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// ��̈ʒu
		m_AirplaneInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// ��s�@�̈ʒu
		m_AirplaneInfo.bFront[nCnt] = false;			// ��s�@�̌���
	}

	// �������N���A����
	m_ItemInfo.nNum = 0;				// �A�C�e��
	m_MacchinaInfo.nNum = 0;			// �}�L�i��
	m_EnemyInfo.nNum = 0;				// �G
	m_TableInfo.nNum = 0;				// ��
	m_AirplaneInfo.nNum = 0;			// ��s�@

	// �����󋵂��N���A����
	m_ItemInfo.bSuccess = false;		// �A�C�e��
	m_MacchinaInfo.bSuccess = false;	// �}�L�i��
	m_EnemyInfo.bSuccess = false;		// �G
	m_TableInfo.bSuccess = false;		// ��
	m_AirplaneInfo.bSuccess = false;	// ��s�@
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
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_FILE_DATA; nCnt++)
	{
		m_ItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// �A�C�e���̈ʒu
		m_MacchinaInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// �}�L�i���̈ʒu
		m_EnemyInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// �G�̈ʒu
		m_EnemyInfo.type[nCnt] = CEnemy::TYPE_ITOCAN;	// �G�̎��
		m_TableInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// ��̈ʒu
		m_AirplaneInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// ��s�@�̈ʒu
		m_AirplaneInfo.bFront[nCnt] = false;			// ��s�@�̌���
	}

	// �������N���A����
	m_ItemInfo.nNum = 0;				// �A�C�e��
	m_MacchinaInfo.nNum = 0;			// �}�L�i��
	m_EnemyInfo.nNum = 0;				// �G
	m_TableInfo.nNum = 0;				// ��
	m_AirplaneInfo.nNum = 0;			// ��s�@

	// �����󋵂��N���A����
	m_ItemInfo.bSuccess = false;		// �A�C�e��
	m_MacchinaInfo.bSuccess = false;	// �}�L�i��
	m_EnemyInfo.bSuccess = false;		// �G
	m_TableInfo.bSuccess = false;		// ��
	m_AirplaneInfo.bSuccess = false;	// ��s�@

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
	// ���[�J���ϐ��錾
	CMacchina* pScrew = CMacchinaManager::Get()->GetTop();		// �擪�̃}�L�i����������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen("data\\TXT\\Macchina.txt", "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pScrew != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_MACCHINA\n");	// �}�L�i���̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pScrew->GetPos().x, pScrew->GetPos().y, pScrew->GetPos().z);			// �ʒu����������

			// ���������������
			fprintf(pFile, "END_SET_MACCHINA\n\n");		// �}�L�i���̐ݒ�̏I������������

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
// �G�̃Z�[�u����
//===========================================
HRESULT CFile::SaveEnemy(void)
{
	// ���[�J���ϐ��錾
	CEnemy* pEnemy = CEnemyManager::Get()->GetTop();		// �擪�̓G��������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen("data\\TXT\\Enemy.txt", "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pEnemy != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_ENEMY\n");		// �G�̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pEnemy->GetPos().x, pEnemy->GetPos().y, pEnemy->GetPos().z);			// �ʒu����������

			fprintf(pFile, "\tTYPE = ");		// ��ނ̐ݒ����������
			fprintf(pFile, "%d\n", pEnemy->GetType());			// ��ނ���������

			// ���������������
			fprintf(pFile, "END_SET_ENEMY\n\n");		// �G�̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pEnemy = pEnemy->GetNext();
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
// ��̃Z�[�u����
//===========================================
HRESULT CFile::SaveTable(void)
{
	// ���[�J���ϐ��錾
	CTable* pTable = CTableManager::Get()->GetTop();		// �擪�̑��������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen("data\\TXT\\Table.txt", "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pTable != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_TABLE\n");		// ��̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pTable->GetPos().x, pTable->GetPos().y, pTable->GetPos().z);			// �ʒu����������

			// ���������������
			fprintf(pFile, "END_SET_TABLE\n\n");	// ��̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pTable = pTable->GetNext();
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
// ��s�@�̃Z�[�u����
//===========================================
HRESULT CFile::SaveAirplane(void)
{
	// ���[�J���ϐ��錾
	CAirplane* pAirplane = CAirplaneManager::Get()->GetTop();		// �擪�̔�s�@��������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen("data\\TXT\\Airplane.txt", "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pAirplane != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_AIRPLANE\n");	// ��s�@�̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pAirplane->GetPos().x, pAirplane->GetPos().y, pAirplane->GetPos().z);			// �ʒu����������

			fprintf(pFile, "\tFRONT = ");		// �O��󋵂̐ݒ����������
			fprintf(pFile, "%s\n", c_apBooleanDisp[(int)(pAirplane->GetFront())]);		// �O��󋵂���������

			// ���������������
			fprintf(pFile, "END_SET_AIRPLANE\n\n");		// ��s�@�̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pAirplane = pAirplane->GetNext();
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