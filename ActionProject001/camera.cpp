//===========================================
//
// �J�����̃��C������[camera.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "useful.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "object.h"
#include "model.h"
#include "scene.h"
#include "file.h"
#include "pause.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

// �J�����S��
#define ASPECT_RATIO				(80.0f)				// ��ʂ̃A�X�y�N�g��
#define MIN_DISTANCE				(50.0f)				// �����̍ŏ��l
#define MAX_DISTANCE				(8000.0f)			// �����̍ő�l
#define DRAW_MIN_Z					(10.0f)				// Z���̍ŏ��l
#define DRAW_MAX_Z					(50000.0f)			// Z���̍ő�l

// �����֌W
#define ROT_Y_SPEED					(0.04f)				// Y���̉�]�̑��x
#define ROTATION_SPEED				(0.05f)				// ��荞�ݏ������s����̃��f���̑��x
#define ROTATION_ROT				(0.02f)				// �J�����̊p�x�̕␳�{��

// �ʒu�E�����֌W
#define POS_SPEED					(30.0f)				// �ړ����x
#define DIS_SPEED					(16.0f)				// �����̈ړ���
#define CAMERA_DISTANCE				(600.0f)			// �J�����̋���
#define POSR_POINT					(40.0f)				// �Ǐ]���[�h�̒����_�̈ʒu
#define POSV_POINT					(40.0f)				// �Ǐ]���[�h�̎��_�̈ʒu
#define CORRECT_POSR				(0.22f)				// �����_�̕␳�{��
#define CORRECT_POSV				(0.20f)				// ���_�̕␳�{��
#define RANKING_MOVE				(40.0f)				// �����L���O�J�����̈ړ���
#define RANKING_STOP				(25000.0f)			// �����L���O�J�����̎~�܂���W

#define CHASE_SHIFT_X				(300.0f)			// �ǐՃJ�����̑O�ɂ��炷����

//=======================
// �R���X�g���N�^
//=======================
CCamera::CCamera()
{
	// �S�Ă̏����N���A����
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���_
	m_posVDest = m_posV;						// �ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_
	m_posRDest = m_posR;						// �ړI�̒����_
	m_VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_rotDest = m_rot.y;						// �ړI�̌���
	m_Dis = 0.0f;								// ����
	m_DisDest = 0.0f;							// �ړI�̋���
	m_nSwingCount = 0;							// �h��J�����̃J�E���g
	m_bControl = false;							// �����
}

//=======================
// �f�X�g���N�^
//=======================
CCamera::~CCamera()
{

}

//=======================
// �J�����̏���������
//=======================
HRESULT CCamera::Init(void)
{
	//�J�����̏��̃��Z�b�g����
	Reset();

	// �r���[�|�[�g�̐ݒ菈��
	m_viewport.X = (DWORD)0.0f;				// �`�悷���ʂ̍���X���W
	m_viewport.Y = (DWORD)0.0f;				// �`�悷���ʂ̍���Y���W
	m_viewport.Width = SCREEN_WIDTH;	// �`�悷���ʂ̕�
	m_viewport.Height = SCREEN_HEIGHT;	// �`�悷���ʂ̍���
	m_viewport.MinZ = 0.0f;				// �N���b�v�{�����[���̍ŏ��l
	m_viewport.MaxZ = 1.0f;				// �N���b�v�{�����[���̍ő�l

	// ������Ԃ�
	return S_OK;
}

//=======================
// �J�����̏I������
//=======================
void CCamera::Uninit(void)
{

}

//=======================
// �J�����̍X�V����
//=======================
void CCamera::Update(void)
{
	switch (CManager::Get()->GetMode())
	{
	case CScene::MODE_GAME:		// �Q�[�����[�h

		if (CGame::GetPause() != nullptr &&
			CGame::GetPause()->GetPause() == false)
		{ // �|�[�Y���ȊO�̏ꍇ

			// �Q�[����ʂ̃J��������
			GameCamera();
		}
		else
		{ // ��L�ȊO

// �f�o�b�O���[�h
#ifdef _DEBUG

// �|�[�Y���̃J��������
#if 0
			if (m_bControl == true)
			{ // �{���󋵂� true �̏ꍇ

				// ���쏈��
				Control();
			}
#endif

#endif
		}

		break;

	case CScene::MODE_RANKING:	// �����L���O

		if (m_posV.x <= RANKING_STOP ||
			m_posV.x <= RANKING_STOP)
		{ // �ʒu����萔�ȉ��������ꍇ

			// �J�������ړ�������
			m_posV.x += RANKING_MOVE;
			m_posR.x += RANKING_MOVE;
		}

		break;

	default:					// ��L�ȊO

		// ���̃��Z�b�g����
		Reset();

		break;
	}

	// �����̐��K������
	useful::RotNormalize(&m_rot.y);

#if 0

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // �X�y�[�X�L�[���������ꍇ

		// �J�����̏��̃��Z�b�g����
		Reset();
	}

#endif

	//// �ړI�̒����_��ݒ肷��
	//m_posRDest.x = pos.x;
	//m_posRDest.z = pos.z;

	//// �ړI�̎��_��ݒ肷��
	//m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * -m_Dis;
	//m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * -m_Dis;

	//// �ړI�̌�����ݒ肷��
	//m_rotDest = 0.0f;
}

//=======================
// �J�����̐ݒ菈��
//=======================
void CCamera::Set(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

// �f�o�b�O�p
#ifdef _DEBUG

		// �v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,									// �v���W�F�N�V�����}�g���b�N�X
		D3DXToRadian(ASPECT_RATIO),							// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			// ��ʂ̃A�X�y�N�g��
		DRAW_MIN_Z,											// Z�l�̍ŏ��l
		DRAW_MAX_Z											// Z�l�̍ő�l
	);

// �����[�X�p
#else

	// �v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,									// �v���W�F�N�V�����}�g���b�N�X
		D3DXToRadian(ASPECT_RATIO),							// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			// ��ʂ̃A�X�y�N�g��
		DRAW_MIN_Z,											// Z�l�̍ŏ��l
		DRAW_MAX_Z											// Z�l�̍ő�l
	);

	//// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
	//D3DXMatrixOrthoLH
	//(
	//	&m_mtxProjection,									// �r���[�}�g���b�N�X
	//	SCREEN_WIDTH,										// ��ʂ̕�
	//	SCREEN_HEIGHT,										// ��ʂ̍���
	//	DRAW_MIN_Z,											// Z���̍ŏ��l
	//	DRAW_MAX_Z											// Z���̍ő�l
	//);

#endif

	// �v���W�F�N�g�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH
	(
		&m_mtxView,										// �r���[�}�g���b�N�X
		&m_posV,										// ���_
		&m_posR,										// �����_
		&m_VecU											// ������x�N�g��
	);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=======================
// ���_�̈ʒu�̐ݒ菈��
//=======================
void CCamera::SetPosV(const D3DXVECTOR3 posV)
{
	// ���_�̈ʒu��ݒ肷��
	m_posV = posV;
}

//=======================
// ���_�̈ʒu�̎擾����
//=======================
D3DXVECTOR3 CCamera::GetPosV(void) const
{
	// ���_�̈ʒu��Ԃ�
	return m_posV;
}

//=======================
// �����_�̈ʒu�̐ݒ菈��
//=======================
void CCamera::SetPosR(const D3DXVECTOR3 posR)
{
	// �����_�̈ʒu��ݒ肷��
	m_posR = posR;
}

//=======================
// �����_�̈ʒu�̎擾����
//=======================
D3DXVECTOR3 CCamera::GetPosR(void) const
{
	// �����_�̈ʒu��Ԃ�
	return m_posR;
}

//=======================
// �����̐ݒ菈��
//=======================
void CCamera::SetRot(const D3DXVECTOR3& rot)
{
	// �����̏���ݒ肷��
	m_rot = rot;
}

//=======================
// �����̎擾����
//=======================
D3DXVECTOR3 CCamera::GetRot(void) const
{
	// �����̏���Ԃ�
	return m_rot;
}

//=======================
// �����̐ݒ菈��
//=======================
void CCamera::SetDistance(const float fDis)
{
	// ������ݒ肷��
	m_Dis = fDis;

	// �ړI�̎��_��ݒ肷��
	m_posV.x = m_posR.x + sinf(m_rot.y) * -m_Dis;
	m_posV.z = m_posR.z + cosf(m_rot.y) * -m_Dis;
}

//=======================
// �����̎擾����
//=======================
float CCamera::GetDistance(void) const
{
	// ������Ԃ�
	return m_Dis;
}

//=======================
// �J�����̑���󋵂̐؂�ւ�����
//=======================
void CCamera::ChangeControl(void)
{
	// ����󋵂�؂�ւ���
	m_bControl = m_bControl ? false : true;
}

//=======================
// �J�����̏��̃��Z�b�g����
//=======================
void CCamera::Reset(void)
{
	// �S�Ă̒l�����Z�b�g����
	m_Dis = CAMERA_DISTANCE;					// ���_�ƒ����_�̋���
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -m_Dis);	// ���_�̈ʒu
	m_posVDest = m_posV;						// �ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_�̈ʒu
	m_posRDest = m_posR;						// �ړI�̒����_
	m_VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_rotDest = m_rot.y;						// �ړI�̌���
	m_DisDest = CAMERA_DISTANCE;				// �ړI�̋���
	m_nSwingCount = 0;							// �h��J�����̃J�E���g
	m_bControl = false;							// �����
}

//=======================
// �J�����̉�荞�ݏ���
//=======================
void CCamera::Rotation(void)
{
	////�J�����̖ړI�̌�����ݒ肷��
	//m_rotDest = (pModelrot->y);

	////�J�����̌����̍�����ݒ肷��
	//m_rotDiff = m_rotDest - m_rot.y;

	//if (m_rotDiff > D3DX_PI)
	//{//�p�x��3.14f���傫�������ꍇ
	// //�p�x����1�������炷
	//	m_rotDiff -= (2 * D3DX_PI);
	//}
	//else if (m_rotDiff < -D3DX_PI)
	//{//�p�x��-3.14f��菬���������ꍇ
	// //�p�x��1����������
	//	m_rotDiff += (2 * D3DX_PI);
	//}

	////�J�����̌�����␳����
	//m_rot.y += m_rotDiff * ROTATION_ROT;

	//if (m_rot.y > D3DX_PI)
	//{//�p�x��3.14f���傫�������ꍇ
	// //�p�x����1�������炷
	//	m_rot.y = -D3DX_PI;
	//}
	//else if (m_rot.y < -D3DX_PI)
	//{//�p�x��-3.14f��菬���������ꍇ
	// //�p�x��1����������
	//	m_rot.y = D3DX_PI;
	//}
}

//=======================
// �J�����̈ړ�����
//=======================
void CCamera::Move(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_UP) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRYPress(0) > 0)
	{ // W�L�[���������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RIGHT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) > 0)
		{ // D�L�[���������ꍇ

			m_posR.x += sinf(D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;
			m_posV.x += sinf(D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;
			
			m_posR.z += cosf(D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;
			m_posV.z += cosf(D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LEFT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) < 0)
		{ // A�L�[���������ꍇ

			m_posR.x += sinf(-D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;
			m_posV.x += sinf(-D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;

			m_posR.z += cosf(-D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;
			m_posV.z += cosf(-D3DX_PI * 0.25f + m_rot.y) * POS_SPEED;
		}
		else
		{ // W�L�[�݂̂��������ꍇ

			m_posR.x += sinf(m_rot.y) * POS_SPEED;
			m_posV.x += sinf(m_rot.y) * POS_SPEED;

			m_posR.z += cosf(m_rot.y) * POS_SPEED;
			m_posV.z += cosf(m_rot.y) * POS_SPEED;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_DOWN) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRYPress(0) < 0)
	{ // S�L�[���������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RIGHT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) > 0)
		{ // D�L�[���������ꍇ

			m_posR.x += sinf(D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;
			m_posV.x += sinf(D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;

			m_posR.z += cosf(D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;
			m_posV.z += cosf(D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LEFT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) < 0)
		{ // A�L�[���������ꍇ

			m_posR.x += sinf(-D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;
			m_posV.x += sinf(-D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;

			m_posR.z += cosf(-D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;
			m_posV.z += cosf(-D3DX_PI * 0.75f + m_rot.y) * POS_SPEED;
		}
		else
		{ // S�L�[�݂̂��������ꍇ

			m_posR.x -= sinf(m_rot.y) * POS_SPEED;
			m_posV.x -= sinf(m_rot.y) * POS_SPEED;

			m_posR.z -= cosf(m_rot.y) * POS_SPEED;
			m_posV.z -= cosf(m_rot.y) * POS_SPEED;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RIGHT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) > 0)
	{ // D�L�[���������ꍇ

		m_posR.x += sinf(D3DX_PI * 0.5f + m_rot.y) * POS_SPEED;
		m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * POS_SPEED;

		m_posR.z += cosf(D3DX_PI * 0.5f + m_rot.y) * POS_SPEED;
		m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * POS_SPEED;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LEFT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) < 0)
	{ // A�L�[���������ꍇ

		m_posR.x -= sinf(D3DX_PI * 0.5f + m_rot.y) * POS_SPEED;
		m_posV.x -= sinf(D3DX_PI * 0.5f + m_rot.y) * POS_SPEED;

		m_posR.z += cosf(D3DX_PI * 0.5f - m_rot.y) * POS_SPEED;
		m_posV.z += cosf(D3DX_PI * 0.5f - m_rot.y) * POS_SPEED;
	}
}

//=======================
// �J�����̎��_���쏈��
//=======================
void CCamera::MovePosV(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_Y) == true)
	{ // Y�L�[���������ꍇ
		
		// ���_����ɓ�����
		m_posV.y += POS_SPEED;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_N) == true)
	{ // N�L�[���������ꍇ

		// ���_�����ɓ�����
		m_posV.y -= POS_SPEED;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_Z) == true)
	{ // Z�L�[���������ꍇ

		// ���_���E�ɉ�
		m_rot.y -= ROT_Y_SPEED;

		// �J�����̎��_���X�V����
		m_posV.x = m_posR.x + sinf(m_rot.y) * -m_Dis;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -m_Dis;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_C) == true)
	{ // C�L�[���������ꍇ

		// ���_�����ɉ�
		m_rot.y += ROT_Y_SPEED;

		// �J�����̎��_���X�V����
		m_posV.x = m_posR.x + sinf(m_rot.y) * -m_Dis;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -m_Dis;
	}
}

//=======================
// �J�����̒����_���쏈��
//=======================
void CCamera::MovePosR(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_T) == true)
	{ // T�L�[���������ꍇ

		// �����_����ɓ�����
		m_posR.y += POS_SPEED;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_B) == true)
	{ // B�L�[���������ꍇ

		// �����_�����ɓ�����
		m_posR.y -= POS_SPEED;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_Q) == true)
	{ // Q�L�[���������ꍇ

		// �����_���E�ɉ�
		m_rot.y -= ROT_Y_SPEED;

		// �����_���X�V����
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_Dis;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_Dis;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E) == true)
	{ // E�L�[���������ꍇ

		// �����_�����ɉ�
		m_rot.y += ROT_Y_SPEED;

		// �����_���X�V����
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_Dis;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_Dis;
	}
}

//=======================
// �J�����̋������쏈��
//=======================
void CCamera::MoveRange(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_U) == true)
		{ // U�L�[���������ꍇ

			// ���������Z����
			m_Dis -= DIS_SPEED;

			if (m_Dis <= MIN_DISTANCE)
			{ // 100.0f�ȉ��̏ꍇ

				// 100.0f�ɂ���
				m_Dis = MIN_DISTANCE;
			}

			// �J�����̎��_���X�V����
			m_posV.x = m_posR.x + sinf(m_rot.y) * -m_Dis;
			m_posV.z = m_posR.z + cosf(m_rot.y) * -m_Dis;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_M) == true)
		{ // M�L�[���������ꍇ

			// ���������Z����
			m_Dis += DIS_SPEED;

			if (m_Dis >= MAX_DISTANCE)
			{ // 800.0f�ȏ�̏ꍇ

				// 800.0f�ɂ���
				m_Dis = MAX_DISTANCE;
			}

			// �J�����̎��_���X�V����
			m_posV.x = m_posR.x + sinf(m_rot.y) * -m_Dis;
			m_posV.z = m_posR.z + cosf(m_rot.y) * -m_Dis;
		}
	}
}

//=======================
// ���쏈��
//=======================
void CCamera::Control(void)
{
	//�J�����̈ړ�����
	Move();

	// �J�����̎��_���쏈��
	MovePosV();

	// �J�����̒����_���쏈��
	MovePosR();

	// �J�����̋������쏈��
	MoveRange();
}

//=======================
// �J�����̈ʒu�̐ݒ菈��
//=======================
void CCamera::PosSet(void)
{
	// �J�����̎��_���X�V����
	m_posV.x = m_posR.x + sinf(m_rot.y) * -m_Dis;
	m_posV.z = m_posR.z + cosf(m_rot.y) * -m_Dis;

	// �J�����̒����_���X�V����
	m_posR.x = m_posV.x + sinf(m_rot.y) * m_Dis;
	m_posR.z = m_posV.z + cosf(m_rot.y) * m_Dis;
}

//=======================
// �Q�[����ʂ̃J��������
//=======================
void CCamera::GameCamera(void)
{
	switch (CGame::GetState())
	{
	case CGame::STATE_START:		// �X�^�[�g��

		// �ǐՏ���
		Chase();

		break;

	case CGame::STATE_PLAY:			// �v���C���

		// �v���C���̃J��������
		PlayCamera();

		break;

	case CGame::STATE_GOAL:			// �S�[�����

		// �S�[�����̃J��������
		GoalCamera();

		break;

	case CGame::STATE_FINISH:		// �I�����

#if 1
		// ���쏈��
		Chase();
#else

		// ���쏈��
		Control();
#endif

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=======================
// �v���C���̃J��������
//=======================
void CCamera::PlayCamera(void)
{
// �f�o�b�O���[�h
#ifdef _DEBUG

// �|�[�Y�ȊO�̃J����
#if 1

	if (CGame::GetPause() != nullptr &&
		CGame::GetPause()->GetPause() == false)
	{ // �|�[�Y�� NULL ����Ȃ��ꍇ

		// �ǐՏ���
		Chase();
	}

#endif

// �G�f�B�b�g��Ԃ̃J����
#if 0

	// ���쏈��
	Control();

#endif

// �����[�X���[�h
#else

	if (CGame::GetPause() != nullptr &&
		CGame::GetPause()->GetPause() == false)
	{ // �|�[�Y�� NULL ����Ȃ��ꍇ

		// �ǐՏ���
		Chase();
	}

#endif
}

//=======================
// �S�[�����̃J��������
//=======================
void CCamera::GoalCamera(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	CPlayer* pPlayer = CPlayer::Get();	// �v���C���[�̃|�C���^
	m_DisDest = 400.0f;					// �ړI�̋���

	// �����̕␳����
	useful::Correct(m_DisDest, &m_Dis, CORRECT_POSR);

	if (pPlayer != nullptr)
	{ // �v���C���[�� NULL ����Ȃ��ꍇ

		// �v���C���[�̏����擾����
		pos = pPlayer->GetPos();		// �ʒu
		rot = pPlayer->GetRot();		// ����

		// �ړI�̒����_��ݒ肷��
		m_posRDest.x = pos.x + sinf(rot.y) * 100.0f;
		m_posRDest.y = pos.y + 100.0f;
		m_posRDest.z = pos.z;

		// �ړI�̎��_��ݒ肷��
		m_posVDest.x = m_posRDest.x + sinf(rot.y) * 50.0f;
		m_posVDest.y = pos.y + 130.0f;
		m_posVDest.z = m_posRDest.z - m_Dis;

		// �����_��␳
		m_posR.x += (m_posRDest.x - m_posR.x) * 0.08f;
		m_posR.y += (m_posRDest.y - m_posR.y) * 0.08f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.08f;

		// ���_��␳
		m_posV.x += (m_posVDest.x - m_posV.x) * 0.08f;
		m_posV.y += (m_posVDest.y - m_posV.y) * 0.08f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.08f;
	}
}

//=======================
// �J�����̒ǐՏ���
//=======================
void CCamera::Chase(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	CPlayer* pPlayer = CPlayer::Get();	// �v���C���[�̃|�C���^
	m_DisDest = CAMERA_DISTANCE;		// �ړI�̋���

	// �����̕␳����
	useful::Correct(m_DisDest, &m_Dis, CORRECT_POSR);
	useful::Correct(m_rotDest, &m_rot.y, CORRECT_POSR);

	if (pPlayer != nullptr)
	{ // �v���C���[�� NULL ����Ȃ��ꍇ

		// �v���C���[�̏����擾����
		pos = pPlayer->GetPos();		// �ʒu
		rot = pPlayer->GetRot();		// ����

		// �ړI�̒����_��ݒ肷��
		m_posRDest.x = pos.x + CHASE_SHIFT_X;
		m_posRDest.y = pos.y + 100.0f;
		m_posRDest.z = pos.z;

		// �ړI�̎��_��ݒ肷��
		m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * -m_Dis;
		m_posVDest.y = pos.y + 130.0f;
		m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * -m_Dis;

		// �����_��␳
		m_posR.x += (m_posRDest.x - m_posR.x) * CORRECT_POSR;
		m_posR.y += (m_posRDest.y - m_posR.y) * CORRECT_POSR;
		m_posR.z += (m_posRDest.z - m_posR.z) * CORRECT_POSR;

		// ���_��␳
		m_posV.x += (m_posVDest.x - m_posV.x) * CORRECT_POSV;
		m_posV.y += (m_posVDest.y - m_posV.y) * CORRECT_POSR;
		m_posV.z += (m_posVDest.z - m_posV.z) * CORRECT_POSV;
	}
}