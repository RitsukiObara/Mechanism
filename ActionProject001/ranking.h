//===================================
//
//�����L���O��ʃw�b�_�[[ranking.h]
//Author ��������
//
//===================================
#ifndef _RANKING_H_			//���̃}�N����`������Ă��Ȃ�������
#define _RANKING_H_			//2�d�C���N���[�h�h�~�̃}�N����ݒ肷��

//-----------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------
#include "scene.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CTime;		// �^�C��
class CScroll;		// �X�N���[��
class CObject2D;	// �I�u�W�F�N�g2D

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_RANKING		(5)			// �����L���O�̍ő吔

// �N���X��`(�����L���O)
class CRanking : public CScene
{
public:			// �N�ł��A�N�Z�X�ł���

	CRanking();					// �R���X�g���N�^
	~CRanking();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V
	void Draw(void);			// �`�揈��

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nTransCount;		// �����J�ڃJ�E���g
};

#endif