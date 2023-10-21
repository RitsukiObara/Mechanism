//============================================
//
// �Q�[���X�R�A�w�b�_�[[game_score.h]
// Author�F��������
//
//============================================
#ifndef _GAME_SCORE_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _GAME_SCORE_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "score.h"

//--------------------------------------------
// �N���X��`(�X�R�A)
//--------------------------------------------
class CGameScore : public CScore
{
public:				// �N�ł��A�N�Z�X�ł���

	CGameScore();			// �R���X�g���N�^
	~CGameScore();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CGameScore* Get(void);		// �X�R�A�̎擾����
	static CGameScore* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �ÓI�����o�ϐ�
	static CGameScore* m_pGameScore;	// �X�R�A�̏��
};

#endif