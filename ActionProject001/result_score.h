//============================================
//
// ���U���g�X�R�A�w�b�_�[[result_score.h]
// Author�F��������
//
//============================================
#ifndef _RESULT_SCORE_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _RESULT_SCORE_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "score.h"

//--------------------------------------------
// �N���X��`(�X�R�A)
//--------------------------------------------
class CResultScore : public CScore
{
public:				// �N�ł��A�N�Z�X�ł���

	CResultScore();			// �R���X�g���N�^
	~CResultScore();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CResultScore* Get(void);		// �X�R�A�̎擾����
	static CResultScore* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �ÓI�����o�ϐ�
	static CResultScore* m_pResultScore;	// �X�R�A�̏��
};

#endif