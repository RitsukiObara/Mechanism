//============================================
//
// �l�WUI�w�b�_�[[screwUI.h]
// Author�F��������
//
//============================================
#ifndef _SCREWUI_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SCREWUI_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CObject2D;		// 2D�|���S��
class CNumber;			// ����

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_SCREW_DIGIT		(2)			// �l�W�̌�

//--------------------------------------------
// �N���X��`(�X�R�A)
//--------------------------------------------
class CScrewUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CScrewUI();					// �R���X�g���N�^
	~CScrewUI();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void SetData(void);			// ���̐ݒ菈��
	void SetDataScore(void);	// �X�R�A�̏��̐ݒ菈��
	void SetDataBack(void);		// �w�i�̏��̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetScore(const int nScore);	// �X�R�A�̐ݒ菈��
	int GetScore(void) const;			// �X�R�A�̎擾����

	// �ÓI�����o�ϐ�
	void AddScore(const int nScore);	// �X�R�A�̉��Z����
	static CScrewUI* Create(void);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	HRESULT CreateScore(void);	// �X�R�A�̐�������
	HRESULT CreateBack(void);	// �w�i�̐�������
	void Calculate(void);		// �v�Z����

	// �����o�ϐ�
	CObject2D* m_pBack;		// �w�i
	CNumber *m_apNumber[MAX_SCREW_DIGIT];		// �ԍ��̏��
	int m_nScore;			// �X�R�A
};

#endif