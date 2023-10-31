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
#include "needle.h"
#include "needle_manager.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define ITEM_TXT			"data\\TXT\\Screw.txt"			// �A�C�e��(�l�W)�̃e�L�X�g
#define MACCHINA_TXT		"data\\TXT\\Macchina.txt"		// �}�L�i���̃e�L�X�g
#define ENEMY_TXT			"data\\TXT\\Enemy.txt"			// �G�̃e�L�X�g
#define TABLE_TXT			"data\\TXT\\Table.txt"			// ��̃e�L�X�g
#define AIRPLANE_TXT		"data\\TXT\\Airplane.txt"		// ��s�@�̃e�L�X�g
#define NEEDLE_TXT			"data\\TXT\\Needle.txt"			// ���̃e�L�X�g
#define RANKING_BIN			"data\\BIN\\Ranking.bin"		// �����L���O�̃e�L�X�g

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
		m_NeedleInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// ���̈ʒu
		m_NeedleInfo.rot[nCnt] = NONE_D3DXVECTOR3;		// ���̌���
	}

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		m_RankingInfo.aRank[nCntRank] = 0;				// �����L���O�̒l
	}

	// �������N���A����
	m_ItemInfo.nNum = 0;				// �A�C�e��
	m_MacchinaInfo.nNum = 0;			// �}�L�i��
	m_EnemyInfo.nNum = 0;				// �G
	m_TableInfo.nNum = 0;				// ��
	m_AirplaneInfo.nNum = 0;			// ��s�@
	m_NeedleInfo.nNum = 0;				// ��

	// �����󋵂��N���A����
	m_ItemInfo.bSuccess = false;		// �A�C�e��
	m_MacchinaInfo.bSuccess = false;	// �}�L�i��
	m_EnemyInfo.bSuccess = false;		// �G
	m_TableInfo.bSuccess = false;		// ��
	m_AirplaneInfo.bSuccess = false;	// ��s�@
	m_NeedleInfo.bSuccess = false;		// ��
	m_RankingInfo.bSuccess = false;		// �����L���O
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

	case TYPE_NEEDLE:		// ��

		// ���̃Z�[�u����
		if (FAILED(SaveNeedle()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_RANKING:

		// �����L���O�̃Z�[�u����
		if (FAILED(SaveRanking()))
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

		if (m_ItemInfo.bSuccess == true)
		{ // �ǂݍ��݂ɐ������Ă����ꍇ

			for (int nCnt = 0; nCnt < m_ItemInfo.nNum; nCnt++)
			{
				// �l�W�̐�������
				CScrew::Create(m_ItemInfo.pos[nCnt], NONE_D3DXVECTOR3, false);
			}
		}

		break;

	case TYPE_MACCHINA:		// �}�L�i��

		// �}�L�i���̃��[�h����
		if(FAILED(LoadMacchina()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_MacchinaInfo.bSuccess == true)
		{ // �ǂݍ��݂ɐ������Ă����ꍇ

			for (int nCnt = 0; nCnt < m_MacchinaInfo.nNum; nCnt++)
			{
				// �}�L�i���̐�������
				CMacchina::Create(m_MacchinaInfo.pos[nCnt]);
			}
		}

		break;

	case TYPE_ENEMY:		// �G

		// �G�̃��[�h����
		if(FAILED(LoadEnemy()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_EnemyInfo.bSuccess == true)
		{ // �ǂݍ��݂ɐ������Ă����ꍇ

			for (int nCnt = 0; nCnt < m_EnemyInfo.nNum; nCnt++)
			{
				// �G�̐�������
				CEnemy::Create(m_EnemyInfo.pos[nCnt], m_EnemyInfo.type[nCnt]);
			}
		}

		break;

	case TYPE_TABLE:		// ��

		// ��̃��[�h����
		if(FAILED(LoadTable()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_TableInfo.bSuccess == true)
		{ // �ǂݍ��݂ɐ������Ă����ꍇ

			for (int nCnt = 0; nCnt < m_TableInfo.nNum; nCnt++)
			{
				// �G�̐�������
				CTable::Create(m_TableInfo.pos[nCnt]);
			}
		}

		break;

	case TYPE_AIRPLANE:		// ��s�@

		// ��s�@�̃��[�h����
		if (FAILED(LoadAirplane()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_AirplaneInfo.bSuccess == true)
		{ // �ǂݍ��݂ɐ������Ă����ꍇ

			for (int nCnt = 0; nCnt < m_AirplaneInfo.nNum; nCnt++)
			{
				// �G�̐�������
				CAirplane::Create(m_AirplaneInfo.pos[nCnt], m_AirplaneInfo.bFront[nCnt], CAirplane::STATE_NONE);
			}
		}

		break;

	case TYPE_NEEDLE:

		// ���̃��[�h����
		if (FAILED(LoadNeedle()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_NeedleInfo.bSuccess == true)
		{ // �ǂݍ��݂ɐ������Ă����ꍇ

			for (int nCnt = 0; nCnt < m_NeedleInfo.nNum; nCnt++)
			{
				// �G�̐�������
				CNeedle::Create(m_NeedleInfo.pos[nCnt], m_NeedleInfo.rot[nCnt]);
			}
		}

		break;

	case TYPE_RANKING:

		// �����L���O�̃��[�h����
		if (FAILED(LoadRanking()))
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
// �����L���O�̐ݒ菈��
//===========================================
void CFile::SetRankingInfo(int* pRank)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++, pRank++)
	{
		// �����L���O�̏���ݒ肷��
		m_RankingInfo.aRank[nCnt] = *pRank;
	}
}

//===========================================
// �����L���O�̎擾����
//===========================================
CFile::SRankingInfo CFile::GetRankingInfo(void)
{
	// �����L���O�̏���Ԃ�
	return m_RankingInfo;
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
	pFile = fopen(ITEM_TXT, "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pScrew != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_ITEM\n");		// �l�W�̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pScrew->GetPos().x, pScrew->GetPos().y, pScrew->GetPos().z);			// �ʒu����������

			// ���������������
			fprintf(pFile, "END_SET_ITEM\n\n");			// �l�W�̐ݒ�̏I������������

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
	pFile = fopen(MACCHINA_TXT, "w");

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
	pFile = fopen(ENEMY_TXT, "w");

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
	pFile = fopen(TABLE_TXT, "w");

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
	pFile = fopen(AIRPLANE_TXT, "w");

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
// ���̃Z�[�u����
//===========================================
HRESULT CFile::SaveNeedle(void)
{
	// ���[�J���ϐ��錾
	CNeedle* pNeedle = CNeedleManager::Get()->GetTop();		// �擪�̞���������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(NEEDLE_TXT, "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pNeedle != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_NEEDLE\n");			// ���̐ݒ����������

			fprintf(pFile, "\tPOS = ");				// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pNeedle->GetPos().x, pNeedle->GetPos().y, pNeedle->GetPos().z);		// �ʒu����������

			fprintf(pFile, "\tROT = ");				// �����̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pNeedle->GetRot().x, pNeedle->GetRot().y, pNeedle->GetRot().z);		// ��������������

			// ���������������
			fprintf(pFile, "END_SET_NEEDLE\n\n");	// ���̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pNeedle = pNeedle->GetNext();
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
// �����L���O�̃Z�[�u����
//===========================================
HRESULT CFile::SaveRanking(void)
{
	FILE *pFile;												// �t�@�C���|�C���^��錾
	m_RankingInfo.bSuccess = false;								// ������

	// �t�@�C�����J��
	pFile = fopen(RANKING_BIN, "wb");			// �o�C�i���t�@�C���ɏ������ނ��߂ɊJ��

	// �t�@�C�����r����
	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		// �t�@�C�����琔�l�������o��
		fwrite(&m_RankingInfo.aRank[0], sizeof(int), MAX_RANKING, pFile);

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_RankingInfo.bSuccess = true;

		// ������Ԃ�
		return S_OK;
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}
}

//===========================================
// �A�C�e���̃��[�h����
//===========================================
HRESULT CFile::LoadItem(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_ItemInfo.nNum = 0;				// ����
	m_ItemInfo.bSuccess = false;		// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(ITEM_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_ITEM") == 0)
			{ // �ǂݍ��񂾕����� SET_ITEM �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_ITEM �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_ItemInfo.pos[m_ItemInfo.nNum].x,
							&m_ItemInfo.pos[m_ItemInfo.nNum].y,
							&m_ItemInfo.pos[m_ItemInfo.nNum].z);		// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_ITEM") != 0);		// �ǂݍ��񂾕����� END_SET_ITEM �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_ItemInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_ItemInfo.bSuccess = true;
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
// �}�L�i���̃��[�h����
//===========================================
HRESULT CFile::LoadMacchina(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_MacchinaInfo.nNum = 0;			// ����
	m_MacchinaInfo.bSuccess = false;	// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(MACCHINA_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_MACCHINA") == 0)
			{ // �ǂݍ��񂾕����� SET_MACCHINA �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_MACCHINA �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_MacchinaInfo.pos[m_MacchinaInfo.nNum].x,
							&m_MacchinaInfo.pos[m_MacchinaInfo.nNum].y,
							&m_MacchinaInfo.pos[m_MacchinaInfo.nNum].z);	// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_MACCHINA") != 0);		// �ǂݍ��񂾕����� END_SET_MACCHINA �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_MacchinaInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_MacchinaInfo.bSuccess = true;
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
// �G�̃��[�h����
//===========================================
HRESULT CFile::LoadEnemy(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_EnemyInfo.nNum = 0;				// ����
	m_EnemyInfo.bSuccess = false;		// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(ENEMY_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_ENEMY") == 0)
			{ // �ǂݍ��񂾕����� SET_ENEMY �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_ENEMY �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_EnemyInfo.pos[m_EnemyInfo.nNum].x,
							&m_EnemyInfo.pos[m_EnemyInfo.nNum].y,
							&m_EnemyInfo.pos[m_EnemyInfo.nNum].z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // �ǂݍ��񂾕����� TYPE �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d",
							&m_EnemyInfo.type[m_EnemyInfo.nNum]);		// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_ENEMY") != 0);		// �ǂݍ��񂾕����� END_SET_ENEMY �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_EnemyInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_EnemyInfo.bSuccess = true;
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
// ��̃��[�h����
//===========================================
HRESULT CFile::LoadTable(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_TableInfo.nNum = 0;				// ����
	m_TableInfo.bSuccess = false;		// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(TABLE_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_TABLE") == 0)
			{ // �ǂݍ��񂾕����� SET_TABLE �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_TABLE �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_TableInfo.pos[m_TableInfo.nNum].x,
							&m_TableInfo.pos[m_TableInfo.nNum].y,
							&m_TableInfo.pos[m_TableInfo.nNum].z);		// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_TABLE") != 0);		// �ǂݍ��񂾕����� END_SET_TABLE �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_TableInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_TableInfo.bSuccess = true;
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
// ��s�@�̃��[�h����
//===========================================
HRESULT CFile::LoadAirplane(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_AirplaneInfo.nNum = 0;			// ����
	m_AirplaneInfo.bSuccess = false;	// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(AIRPLANE_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_AIRPLANE") == 0)
			{ // �ǂݍ��񂾕����� SET_AIRPLANE �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_AIRPLANE �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_AirplaneInfo.pos[m_AirplaneInfo.nNum].x,
							&m_AirplaneInfo.pos[m_AirplaneInfo.nNum].y,
							&m_AirplaneInfo.pos[m_AirplaneInfo.nNum].z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "FRONT") == 0)
					{ // �ǂݍ��񂾕����� FRONT �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);			// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aString[0]);			// �ʒu��ǂݍ���

						if (strcmp(&aString[0], c_apBooleanDisp[0]) == 0)
						{ // FALSE��ǂݍ��񂾏ꍇ

							// false ��ݒ肷��
							m_AirplaneInfo.bFront[m_AirplaneInfo.nNum] = false;
						}
						else
						{ // ��L�ȊO

							// true ��ݒ肷��
							m_AirplaneInfo.bFront[m_AirplaneInfo.nNum] = true;
						}
					}

				} while (strcmp(&aString[0], "END_SET_AIRPLANE") != 0);		// �ǂݍ��񂾕����� END_SET_AIRPLANE �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_AirplaneInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_AirplaneInfo.bSuccess = true;
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
// ���̃��[�h����
//===========================================
HRESULT CFile::LoadNeedle(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_NeedleInfo.nNum = 0;				// ����
	m_NeedleInfo.bSuccess = false;		// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(NEEDLE_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_NEEDLE") == 0)
			{ // �ǂݍ��񂾕����� SET_NEEDLE �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_NEEDLE �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_NeedleInfo.pos[m_NeedleInfo.nNum].x,
							&m_NeedleInfo.pos[m_NeedleInfo.nNum].y,
							&m_NeedleInfo.pos[m_NeedleInfo.nNum].z);	// �ʒu��ǂݍ���
					}
					if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� ROT �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_NeedleInfo.rot[m_NeedleInfo.nNum].x,
							&m_NeedleInfo.rot[m_NeedleInfo.nNum].y,
							&m_NeedleInfo.rot[m_NeedleInfo.nNum].z);	// ������ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_NEEDLE") != 0);		// �ǂݍ��񂾕����� END_SET_NEEDLE �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_NeedleInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_NeedleInfo.bSuccess = true;
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
// �����L���O�̃��[�h����
//===========================================
HRESULT CFile::LoadRanking(void)
{
	FILE *pFile;						// �t�@�C���|�C���^��錾
	m_RankingInfo.bSuccess = false;		// ������

	// �t�@�C�����J��
	pFile = fopen(RANKING_BIN, "rb");			// �o�C�i���t�@�C������ǂݍ��ނ��߂ɊJ��

	// �t�@�C�����r����
	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		// �t�@�C�����琔�l��ǂݍ���
		fread(&m_RankingInfo.aRank[0], sizeof(int), MAX_RANKING, pFile);

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_RankingInfo.bSuccess = true;

		// ������Ԃ�
		return S_OK;
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			// ���l��ݒ肷��
			m_RankingInfo.aRank[0] = 0;
		}

		// ���s��Ԃ�
		return E_FAIL;
	}
}