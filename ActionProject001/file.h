//============================================
//
// �t�@�C���w�b�_�[[file.h]
// Author�F��������
//
//============================================
#ifndef _FILE_H_			//���̃}�N����`������Ă��Ȃ�������
#define _FILE_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "enemy.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_FILE_DATA		(512)		// �t�@�C���̃f�[�^�̍ő吔

//--------------------------------------------
// �N���X(�t�@�C���ǂݍ��݃N���X)
//--------------------------------------------
class CFile
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_ITEM = 0,		// �A�C�e��
		TYPE_MACCHINA,		// �}�L�i��
		TYPE_ENEMY,			// �G
		TYPE_TABLE,			// ��
		TYPE_AIRPLANE,		// ��s�@
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �\���̒�`(�A�C�e���̏��)
	struct SItemInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// �ʒu
		int nNum;							// ����
		bool bSuccess;						// ������
	};

	// �\���̒�`(�}�L�i���̏��)
	struct SMacchinaInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// �ʒu
		int nNum;							// ����
		bool bSuccess;						// ������
	};

	// �\���̒�`(�G�̏��)
	struct SEnemyInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// �ʒu
		CEnemy::TYPE type[MAX_FILE_DATA];	// ���
		int nNum;							// ����
		bool bSuccess;						// ������
	};

	// �\���̒�`(��̏��)
	struct STableInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// �ʒu
		int nNum;							// ����
		bool bSuccess;						// ������
	};

	// �\���̒�`(��s�@�̏��)
	struct SAirplaneInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// �ʒu
		bool bFront[MAX_FILE_DATA];			// �O���
		int nNum;							// ����
		bool bSuccess;						// ������
	};

	CFile();					// �R���X�g���N�^
	~CFile();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������

	HRESULT Save(const TYPE type);	// �Z�[�u����
	HRESULT Load(const TYPE type);	// ���[�h����

private:		// �����̂݃A�N�Z�X�ł���

	// �����o�֐�(�Z�[�u�֌W)
	HRESULT SaveItem(void);			// �A�C�e���̃Z�[�u����
	HRESULT SaveMacchina(void);		// �}�L�i���̃Z�[�u����
	HRESULT SaveEnemy(void);		// �G�̃Z�[�u����
	HRESULT SaveTable(void);		// ��̃Z�[�u����
	HRESULT SaveAirplane(void);		// ��s�@�̃Z�[�u����

	// �����o�֐�(���[�h�֌W)
	HRESULT LoadItem(void);			// �A�C�e���̃��[�h����
	HRESULT LoadMacchina(void);		// �}�L�i���̃��[�h����
	HRESULT LoadEnemy(void);		// �G�̃��[�h����
	HRESULT LoadTable(void);		// ��̃��[�h����
	HRESULT LoadAirplane(void);		// ��s�@�̃��[�h����

	// �����o�ϐ�
	SItemInfo m_ItemInfo;			// �A�C�e���̏��
	SMacchinaInfo m_MacchinaInfo;	// �}�L�i���̏��
	SEnemyInfo m_EnemyInfo;			// �G�̏��
	STableInfo m_TableInfo;			// ��̏��
	SAirplaneInfo m_AirplaneInfo;	// ��s�@�̏��

	// �ÓI�����o�ϐ�
	static const char* c_apBooleanDisp[2];			// bool�^�̕\��
};

#endif