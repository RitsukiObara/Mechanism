//============================================
//
// �S�[���w�b�_�[[goal.h]
// Author�F��������
//
//============================================
#ifndef _GOAL_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _GOAL_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CModel;		// ���f��

//--------------------------------------------
// �N���X��`(�S�[��)
//--------------------------------------------
class CGoal : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���f���̎��)
	enum MODEL
	{
		MODEL_BODY = 0,		// �{��
		MODEL_POINT,		// ���_
		MODEL_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_PUNCH = 0,		// �p���`
		TYPE_SMALL_R,		// �E�́u+1000�v
		TYPE_BIG,			// +2000
		TYPE_SMALL_L,		// ���́u+2000�v
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_CYCLE = 0,	// ��]����
		STATE_STOP,			// ��~����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CGoal();				// �R���X�g���N�^
	~CGoal();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);			// �q�b�g����
	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	CModel* GetModel(const MODEL model);		// ���f���̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CGoal* Create(const D3DXVECTOR3& pos);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void RotDecide(float* m_fRot);	// �����̌��菈��
	void RotCorrect(void);			// �����̕␳����

	// �����o�ϐ�
	CModel* m_aGoal[MODEL_MAX];			// �S�[���̕ϐ�
	TYPE m_type;						// ���
	STATE m_state;						// ���
	int m_nStateCount;					// ��ԃJ�E���g
	float m_fRotDest;					// �ڕW�̌���
};

#endif