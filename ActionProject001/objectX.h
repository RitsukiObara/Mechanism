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
#define INIT_PLAYER		(CXFile::TYPE_PLAYERWAIST)						// �v���C���[�̍ŏ��̐���

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
		TYPE_SCREW,				// �l�W(�A�C�e��)
		TYPE_FRAC_SCREW,		// �l�W(�j��)
		TYPE_FRAC_GEAR,			// ����(�j��)
		TYPE_FRAC_RING,			// ��(�j��)
		TYPE_FRAC_WOOD,			// �ؕ�(�j��)
		TYPE_FRAC_REDRUST,		// �Ԃ���(�j��)
		TYPE_TABLE,				// ��
		TYPE_MACCHINA,			// �}�L�i��
		TYPE_GOAL,				// �S�[��
		TYPE_GOALPOINT,			// �S�[���̒��S
		TYPE_RIPPLE,			// �g��
		TYPE_PORK,				// �|�[�N
		TYPE_SIGNBOARD,			// �Ŕ�
		TYPE_NEEDLE,			// ��
		TYPE_IRONBLOCK,			// �S��
		TYPE_WOODBLOCK,			// �ؔ�

		// �G���f��
		TYPE_ITOCAN,			// �C�g�L����
		TYPE_MACHIDORI,			// �}�V���h���[
		TYPE_GARREJANTE,		// �K���W�����e

		// �v���C���[���f��
		TYPE_PLAYERWAIST,		// ��
		TYPE_PLAYERBODY,		// ��
		TYPE_PLAYERNECK,		// ��
		TYPE_PLAYERHEAD,		// ��
		TYPE_PLAYERRIGHTARM,	// �E�r
		TYPE_PLAYERLEFTARM,		// ���r
		TYPE_PLAYERRIGHTUPPER,	// �E��r
		TYPE_PLAYERLEFTUPPER,	// ����r
		TYPE_PLAYERRIGHTHAND,	// �E��
		TYPE_PLAYERLEFTHAND,	// ����
		TYPE_PLAYERRIGHTLEG,	// �E�r
		TYPE_PLAYERLEFTLEG,		// ���r
		TYPE_PLAYERRIGHTSHIN,	// �E��
		TYPE_PLAYERLEFTSHIN,	// ����
		TYPE_PLAYERRIGHTFOOT,	// �E��
		TYPE_PLAYERLEFTFOOT,	// ����

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