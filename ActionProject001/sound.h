//=============================================================================
//
// �T�E���h���� [sound.h]
// Author ��������
//
//=============================================================================
#ifndef _SOUND_H_					//���̃}�N����`������Ă��Ȃ�������
#define _SOUND_H_					//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

// �N���X��`(CSound)
class CSound
{
public:			// �N�ł��A�N�Z�X�o����

	//-------------------------------------------------------------------------
	// �T�E���h�ꗗ
	//-------------------------------------------------------------------------
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,		// �^�C�g��BGM
		SOUND_LABEL_BGM_TUTORIAL,		// �`���[�g���A��BGM
		SOUND_LABEL_BGM_GAME,			// �Q�[��BGM
		SOUND_LABEL_BGM_RESULT,			// ���U���gBGM
		SOUND_LABEL_BGM_RANKING,		// �����L���OBGM
		SOUND_LABEL_SE_RUNSTART,		// ����n�߉�
		SOUND_LABEL_SE_JUMP,			// �W�����v��
		SOUND_LABEL_SE_BIGJUMP,			// ��W�����v��
		SOUND_LABEL_SE_CLIFFCATCH,		// �R�߂܂�
		SOUND_LABEL_SE_WALLKICK,		// �ǃL�b�N
		SOUND_LABEL_SE_TURBO,			// �^�[�{
		SOUND_LABEL_SE_LANDINGMISS,		// ���n�~�X
		SOUND_LABEL_SE_CRUSH,			// �j��
		SOUND_LABEL_SE_METALCRUSH,		// �������j��
		SOUND_LABEL_SE_LANDING,			// ���n��
		SOUND_LABEL_SE_BIGLANDING,		// �����Ƃ��납��̒��n��
		SOUND_LABEL_SE_GOALCHEERS,		// �S�[�����̊���
		SOUND_LABEL_SE_DASH,			// ���s��
		SOUND_LABEL_SE_DRINKGET,		// �h�����N�Q�b�g
		SOUND_LABEL_SE_COUNTDOWN,		// �J�E���g�_�E��
		SOUND_LABEL_SE_LAMPCREAK,		// �X�����a�މ�
		SOUND_LABEL_SE_LAMPJUMP,		// �X���W�����v
		SOUND_LABEL_SE_CLIFFSUCCESS,	// �R���n����
		SOUND_LABEL_SE_CLIFFFAILED,		// �R���n���s
		SOUND_LABEL_SE_PRESSVOICE,		// �ׂꂽ�Ƃ��̐�
		SOUND_LABEL_SE_RUBBING,			// �̂��C�鉹
		SOUND_LABEL_SE_SELECT,			// �I����
		SOUND_LABEL_SE_DECIDE,			// ���艹
		SOUND_LABEL_SE_START,			// �X�^�[�g��
		SOUND_LABEL_SE_DRUMROLL,		// �h�����ʂ̓]���鉹
		SOUND_LABEL_SE_SIGNPOLE_FALL,	// �W���̓|��鉹
		SOUND_LABEL_SE_SIGNPOLE_STOP,	// �W���̎~�܂鉹
		SOUND_LABEL_SE_SUPERDASH_START,	// �X�[�p�[�u�[�X�g�X�^�[�g
		SOUND_LABEL_SE_SUPERDASH,		// �X�[�p�[�u�[�X�g��
		SOUND_LABEL_SE_CLIFFLAND,		// �R���n�̉�
		SOUND_LABEL_SE_LAMPCATCH,		// �X���͂މ�
		SOUND_LABEL_SE_FALLING,			// ������
		SOUND_LABEL_SE_ATTACK,			// �U����
		SOUND_LABEL_SE_JUMPCHARGE,		// ���W�����v�`���[�W��
		SOUND_LABEL_SE_VENDING_SWING,	// ���̋@�̗h��鉹
		SOUND_LABEL_SE_ITEM_APPEAR,		// �A�C�e���̏o����
		SOUND_LABEL_SE_SKIPCIRCLE,		// �X�L�b�v�~�̏o����
		SOUND_LABEL_SE_RANKAPPEAR,		// �����N�̏o����
		SOUND_LABEL_SE_NEWRECORD,		// �V�L�^�̉�
		SOUND_LABEL_MAX					// ���̗񋓌^�̑���
	};

	//-----------------------------------------------------------------------------
	// �T�E���h���̍\���̒�`
	//-----------------------------------------------------------------------------
	struct SOUNDINFO
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	};

	CSound();			// �R���X�g���N�^
	~CSound();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �����o�ϐ�
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDINFO m_aSoundInfo[CSound::SOUND_LABEL_MAX];	// �T�E���h�̏��
};

#endif
