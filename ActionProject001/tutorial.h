//============================================
//
// �`���[�g���A����ʃw�b�_�[[tutorial.h]
// Author�F��������
//
//============================================
#ifndef _TUTORIAL_H_			//���̃}�N����`������Ă��Ȃ�������
#define _TUTORIAL_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "scene.h"

//--------------------------------------------
// �N���X(�`���[�g���A���N���X)
//--------------------------------------------
class CTutorial : public CScene
{
public:				// �N�ł��A�N�Z�X�ł���

	CTutorial();		// �R���X�g���N�^
	~CTutorial();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	void SetData(const MODE mode);		// ���̐ݒ菈��

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nEndCount;					// �I���܂ł̃J�E���g
};

#endif