//============================================================
//
// X�t�@�C���w�b�_�[ [xfile.h]
// Author�F��������
//
//============================================================
#ifndef _XFILE_H_	// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _XFILE_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------
#define INIT_VTX_MIN	(D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))		// ���f���̍ŏ��̒��_���W�̏����l
#define INIT_VTX_MAX	(D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))		// ���f���̍ő�̒��_���W�̏����l
#define INIT_SIZE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))					// ���f���T�C�Y�̏����l
#define INIT_PLAYER		(CXFile::TYPE_PLAYERPANTS)						// �v���C���[�̍ŏ��̐���

//------------------------------------------------------------
// �N���X��`(X�t�@�C��)
//------------------------------------------------------------
class CXFile
{
public:			// �N�ł��A�N�Z�X�ł���

	//************************************************************
	//	�񋓌^��` (TYPE)
	//************************************************************
	enum TYPE
	{
		// �ʏ탂�f��
		TYPE_AIRPLANE = 0,		// ��s�@
		TYPE_SCREW,				// �l�W

		// �G���f��
		TYPE_ITOCAN,			// �C�g�L����

		// �v���C���[���f��
		TYPE_PLAYERPANTS,		// ��
		TYPE_PLAYERBODY,		// ��
		TYPE_PLAYERNECK,		// ��
		TYPE_PLAYERHEAD,		// ��
		TYPE_PLAYERLEFTUPPER,	// ����r
		TYPE_PLAYERRIGHTUPPER,	// �E��r
		TYPE_PLAYERLEFTARM,		// ���r
		TYPE_PLAYERRIGHTARM,	// �E�r
		TYPE_PLAYERLEFTLEG,		// ���r
		TYPE_PLAYERRIGHTLEG,	// �E�r
		TYPE_PLAYERLEFTSHIN,	// ����
		TYPE_PLAYERRIGHTSHIN,	// �E��
		TYPE_PLAYERLEFTFOOT,	// ����
		TYPE_PLAYERRIGHTFOOT,	// �E��

		// �G�f�B�b�g���f��
		TYPE_MAX,				// �S���f���̑���
	};

	//************************************************************
	//	�\���̒�` (SXFile)
	//************************************************************
	struct SXFile
	{
		LPD3DXMESH	 pMesh;						// ���b�V�� (���_���) �ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;					// �}�e���A���ւ̃|�C���^
		DWORD		 dwNumMat;					// �}�e���A���̐�
		D3DXVECTOR3	 vtxMin;					// �ŏ��̒��_���W
		D3DXVECTOR3	 vtxMax;					// �ő�̒��_���W
		D3DXVECTOR3	 collsize;					// �����蔻��̃T�C�Y
		float		 fRadius;					// ���a
		int			 m_nTexIdx[MAX_MATERIAL];	// �e�N�X�`���̃C���f�b�N�X
	};

	CXFile();			// �R���X�g���N�^
	~CXFile();			// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Init(void);		// X�t�@�C���̏���������
	static void Uninit(void);		// X�t�@�C���̏I������

	// �Z�b�g�E�Q�b�g�֐�
	static SXFile GetXFile(TYPE type);	// X�t�@�C���̎擾����

private:

	// �����o�֐�
	static HRESULT LoadXFile(void);		// x�t�@�C���̓ǂݍ���
	static void SetCollision(void);		// �����蔻��̍쐬
	static HRESULT LoadTexture(void);	// �e�N�X�`���̓ǂݍ���

	// �ÓI�����o�ϐ�
	static const char *c_apModelData[CXFile::TYPE_MAX];			// ���f���̖��O
	static SXFile m_apModel[CXFile::TYPE_MAX];					// ���f���̏��
};

#endif