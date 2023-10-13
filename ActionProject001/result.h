//============================================
//
// ���U���g�w�b�_�[[result.h]
// Author�F��������
//
//============================================
#ifndef _RESULT_H_			//���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CResultTime;				// ���U���g�^�C�}�[

//--------------------------------------------
// �N���X(���S��ʃN���X)
//--------------------------------------------
class CResult : public CScene
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_TIMEDISP = 0,		// �^�C���\�����
		STATE_SCOREDISP,		// �X�R�A�\�����
		STATE_STOP,				// ��~���
		STATE_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum RANK
	{
		RANK_SS = 0,			// SS�����N
		RANK_S,					// S�����N
		RANK_A,					// A�����N
		RANK_B,					// B�����N
		RANK_C,					// C�����N
		RANK_MAX				// ���̗񋓌^�̑���
	};

	CResult();		// �R���X�g���N�^
	~CResult();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	// �Z�b�g�E�Q�b�g�֌W
	static void SetState(const STATE state);		// ��Ԃ̐ݒ菈��
	static STATE GetState(void);					// ��Ԃ̎擾����

private:					// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	static STATE m_state;			// ���
};

#endif