//===================================
//
// �����L���O�̏��ʕ\���w�b�_�[[ranking_precedence.h]
// Author ��������
//
//===================================
#ifndef _RANKING_PRECEDENCE_H_			//���̃}�N����`������Ă��Ȃ�������
#define _RANKING_PRECEDENCE_H_			//2�d�C���N���[�h�h�~�̃}�N����ݒ肷��

//-----------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------
#include "ranking.h"
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CObject2D;	// �I�u�W�F�N�g2D

// �N���X��`(�����L���O)
class CRankingPrece : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CRankingPrece();					// �R���X�g���N�^
	~CRankingPrece();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// �����L���O��ʂ̏���������
	void Uninit(void);			// �����L���O��ʂ̏I������
	void Update(void);			// �����L���O��ʂ̍X�V
	void Draw(void);			// �����L���O��ʂ̕`�揈��

	// �ÓI�����o�֐�
	static CRankingPrece* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CObject2D* m_apRank[MAX_RANKING];	// �����N(����)
};

#endif