//===================================
//
// �����L���O�̕����w�b�_�[[ranking_word.h]
// Author ��������
//
//===================================
#ifndef _RANKING_WORD_H_			//���̃}�N����`������Ă��Ȃ�������
#define _RANKING_WORD_H_			//2�d�C���N���[�h�h�~�̃}�N����ݒ肷��

//-----------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------
#include "object2D.h"

//-----------------------------------
// �N���X��`(�����L���O�̕���)
//-----------------------------------
class CRankingWord : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CRankingWord();		// �R���X�g���N�^
	~CRankingWord();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// �����L���O�̕����̏���������
	void Uninit(void);	// �����L���O�̕����̏I������
	void Update(void);	// �����L���O�̕����̍X�V
	void Draw(void);	// �����L���O�̕����̕`�揈��

	// �ÓI�����o�֐�
	static CRankingWord* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif