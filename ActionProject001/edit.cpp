// �f�o�b�O��
#ifdef _DEBUG
//===========================================
//
// �G�f�B�b�g�̃��C������[edit.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "input.h"
#include "edit.h"
#include "useful.h"
#include "debugproc.h"

#include "screw.h"
#include "screw_manager.h"
#include "macchina.h"
#include "macchina_manager.h"
#include "enemy_manager.h"
#include "table.h"
#include "table_manager.h"
#include "airplane.h"
#include "airplane_manager.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define NORMAL_SPEED		(16.0f)		// �ʏ펞�̑��x
#define ADJUST_SPEED		(2.0f)		// ���������̑��x
#define MACCHINA_SHIFT		(100.0f)	// �}�L�i���̂��炷��
#define NEAR_POS			(0.0f)		// ��O�̈ʒu
#define FAR_POS				(1000.0f)	// ���s�̈ʒu

//==============================
// �R���X�g���N�^
//==============================
CEdit::CEdit() : CModel(CObject::TYPE_EDIT, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_type = TYPE_ITEM;					// ���
	m_enemyType = CEnemy::TYPE_ITOCAN;	// �G�̎��
	m_fAddDepth = 0.0f;					// �ǉ��̉��s
	m_bFront = true;					// ���s��
	m_bAirplaneFront = true;			// ��s�@�̌����̏�
}

//==============================
// �f�X�g���N�^
//==============================
CEdit::~CEdit()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CEdit::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_type = TYPE_ITEM;					// ���
	m_enemyType = CEnemy::TYPE_ITOCAN;	// �G�̎��
	m_fAddDepth = 0.0f;					// �ǉ��̉��s
	m_bFront = true;					// ���s��
	m_bAirplaneFront = true;			// ��s�@�̌����̏�

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CEdit::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CEdit::Update(void)
{
	// �O��󋵂̐ݒ菈��
	Front();

	switch (m_type)
	{
	case CEdit::TYPE_ITEM:

		// �A�C�e���G�f�B�b�g�̏���
		ItemProcess();

		break;

	case CEdit::TYPE_MACCHINA:

		// �}�L�i���G�f�B�b�g�̏���
		MacchinaProcess();

		break;

	case CEdit::TYPE_ENEMY:

		// �G�̃G�f�B�b�g����
		EnemyProcess();

		break;

	case CEdit::TYPE_TABLE:


		break;

	case CEdit::TYPE_AIRPLANE:

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �ړ��̃C���v�b�g����
	MoveInput();

	// �������ړ��̃C���v�b�g����
	AdjustMoveInput();

	// ��ނ̐ݒ菈��
	Type();

	// �ړ�����
	Move();

	// ��������
	Delete();

	// �ݒu����
	Set();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n��ށF%d\n��O�󋵁F%d(0�F��/1�F��O)\nW/A/S/D�L�[�F�ړ�\nSPACE�L�[�F��ޕύX\nENTER�L�[�F��O�󋵐ݒ�\n0�L�[�F�ݒu\n9�L�[�F����\n", GetPos().x, GetPos().y, GetPos().z, m_type, m_bFront);
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CEdit::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CEdit::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// �g�嗦
	SetFileData(CXFile::TYPE_SCREW);			// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_type = TYPE_ITEM;					// ���
	m_enemyType = CEnemy::TYPE_ITOCAN;	// �G�̎��
	m_fAddDepth = 0.0f;					// �ǉ��̉��s
	m_bFront = true;					// ���s��
	m_bAirplaneFront = true;			// ��s�@�̌����̏�
}

//=======================================
// ��������
//=======================================
CEdit* CEdit::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEdit* pScrew = nullptr;	// �C���X�^���X�𐶐�

	if (pScrew == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pScrew = new CEdit;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScrew != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScrew->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pScrew->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�W�̃|�C���^��Ԃ�
	return pScrew;
}

//=======================================
// �A�C�e���G�f�B�b�g�̏���
//=======================================
void CEdit::ItemProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
		{ // 1�L�[���������ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth += ADJUST_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2) == true)
		{ // 2�L�[���������ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth -= ADJUST_SPEED;
		}
	}
	else
	{ // ��L�ȊO

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_1) == true)
		{ // 1�L�[�������Ă���ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth += NORMAL_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_2) == true)
		{ // 2�L�[�������Ă���ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth -= NORMAL_SPEED;
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_3) == true)
	{ // 3�L�[���������ꍇ

		// �ǉ��̉��s�����Z�b�g����
		m_fAddDepth = 0.0f;
	}
}

//=======================================
// �}�L�i���G�f�B�b�g�̏���
//=======================================
void CEdit::MacchinaProcess(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	if (m_bFront == true)
	{ // ���s�󋵂� true �̏ꍇ

		// ��O�ɒu��
		pos.z = NEAR_POS + MACCHINA_SHIFT;
	}
	else
	{ // ��L�ȊO

		// ���ɒu��
		pos.z = FAR_POS + MACCHINA_SHIFT;
	}

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �G�G�f�B�b�g�̏���
//=======================================
void CEdit::EnemyProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
		{ // 1�L�[���������ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth += ADJUST_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2) == true)
		{ // 2�L�[���������ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth -= ADJUST_SPEED;
		}
	}
	else
	{ // ��L�ȊO

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_1) == true)
		{ // 1�L�[�������Ă���ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth += NORMAL_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_2) == true)
		{ // 2�L�[�������Ă���ꍇ

			// �ǉ��̉��s��ݒ肷��
			m_fAddDepth -= NORMAL_SPEED;
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_3) == true)
	{ // 3�L�[���������ꍇ

		// �ǉ��̉��s��ݒ肷��
		m_fAddDepth = 0.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_4) == true)
	{ // 4�L�[���������ꍇ

		// �G�̎�ނ�؂�ւ���
		m_enemyType = (CEnemy::TYPE)((m_enemyType + 1) % CEnemy::TYPE_MAX);

		switch (m_enemyType)
		{
		case CEnemy::TYPE_ITOCAN:

			// ���f���̏��ݒ菈��
			SetFileData(CXFile::TYPE_ITOCAN);

			break;

		case CEnemy::TYPE_MACHIDORI:

			// ���f���̏��ݒ菈��
			SetFileData(CXFile::TYPE_MACHIDORI);

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
}

//=======================================
// �}�L�i���̐ݒ菈��
//=======================================
void CEdit::SetMaccina(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu

	// �ʒu�����炷
	pos.z += MACCHINA_SHIFT;

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �ړ�����
//=======================================
void CEdit::MoveInput(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ���V�t�g�L�[�������Ă����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // W�L�[�������Ă����ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
		{ // A�L�[���������ꍇ

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(D3DX_PI * -0.25f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * -0.25f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
		{ // D�L�[���������ꍇ

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(D3DX_PI * 0.25f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * 0.25f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else
		{ // ��L�ȊO

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(0.0f) * NORMAL_SPEED;
			m_move.y = cosf(0.0f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // S�L�[�������Ă����ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
		{ // A�L�[���������ꍇ

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(D3DX_PI * -0.75f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * -0.75f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
		{ // D�L�[���������ꍇ

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(D3DX_PI * 0.75f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * 0.75f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else
		{ // ��L�ȊO

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(D3DX_PI) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[���������ꍇ

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(D3DX_PI * -0.5f) * NORMAL_SPEED;
		m_move.y = cosf(D3DX_PI * -0.5f) * NORMAL_SPEED;
		m_move.z = 0.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // D�L�[���������ꍇ

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(D3DX_PI * 0.5f) * NORMAL_SPEED;
		m_move.y = cosf(D3DX_PI * 0.5f) * NORMAL_SPEED;
		m_move.z = 0.0f;
	}
	else
	{ // ��L�ȊO

		// �ړ��ʂ�ݒ肷��
		m_move = NONE_D3DXVECTOR3;
	}
}

//=======================================
// �������ړ��̃C���v�b�g����
//=======================================
void CEdit::AdjustMoveInput(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă����ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true)
		{ // W�L�[�������Ă����ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
			{ // A�L�[���������ꍇ

				// �ړ��ʂ�ݒ肷��
				m_move.x = sinf(D3DX_PI * -0.25f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * -0.25f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
			{ // D�L�[���������ꍇ

				// �ړ��ʂ�ݒ肷��
				m_move.x = sinf(D3DX_PI * 0.25f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * 0.25f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else
			{ // ��L�ȊO

				// �ړ��ʂ�ݒ肷��
				m_move.x = sinf(0.0f) * ADJUST_SPEED;
				m_move.y = cosf(0.0f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true)
		{ // S�L�[�������Ă����ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
			{ // A�L�[���������ꍇ

				// �ړ��ʂ�ݒ肷��
				m_move.x = sinf(D3DX_PI * -0.75f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * -0.75f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
			{ // D�L�[���������ꍇ

				// �ړ��ʂ�ݒ肷��
				m_move.x = sinf(D3DX_PI * 0.75f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * 0.75f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else
			{ // ��L�ȊO

				// �ړ��ʂ�ݒ肷��
				m_move.x = sinf(D3DX_PI) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
		{ // A�L�[���������ꍇ

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(D3DX_PI * -0.5f) * ADJUST_SPEED;
			m_move.y = cosf(D3DX_PI * -0.5f) * ADJUST_SPEED;
			m_move.z = 0.0f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
		{ // D�L�[���������ꍇ

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(D3DX_PI * 0.5f) * ADJUST_SPEED;
			m_move.y = cosf(D3DX_PI * 0.5f) * ADJUST_SPEED;
			m_move.z = 0.0f;
		}
		else
		{ // ��L�ȊO

			// �ړ��ʂ�ݒ肷��
			m_move = NONE_D3DXVECTOR3;
		}
	}
}

//=======================================
// �ړ�����
//=======================================
void CEdit::Move(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	// �ʒu���X�V����
	pos += m_move;

	// �ʒu����̏ꍇ�����ɂ���
	pos.x += ((int)(pos.x) % 2 == 0) ? 0 : 1;
	pos.y += ((int)(pos.y) % 2 == 0) ? 0 : 1;

	// �ʒu��؂�̂Ă���
	pos.x = floorf(pos.x);
	pos.y = floorf(pos.y);

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// ��ޏ���
//=======================================
void CEdit::Type(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // SPACE�L�[���������ꍇ

		// ��ނ�ݒ肷��
		m_type = (TYPE)((m_type + 1) % TYPE_MAX);

		switch (m_type)
		{
		case CEdit::TYPE_ITEM:

			// ���f���̏��ݒ菈��
			SetFileData(CXFile::TYPE_SCREW);

			break;

		case CEdit::TYPE_MACCHINA:

			// ���f���̏��ݒ菈��
			SetFileData(CXFile::TYPE_MACCHINA);

			// �}�L�i���̐ݒ菈��
			SetMaccina();

			break;

		case CEdit::TYPE_ENEMY:

			switch (m_enemyType)
			{
			case CEnemy::TYPE_ITOCAN:

				// ���f���̏��ݒ菈��
				SetFileData(CXFile::TYPE_ITOCAN);

				break;

			case CEnemy::TYPE_MACHIDORI:

				// ���f���̏��ݒ菈��
				SetFileData(CXFile::TYPE_MACHIDORI);

				break;

			default:

				// ��~
				assert(false);

				break;
			}

			break;

		case CEdit::TYPE_TABLE:

			// ���f���̏��ݒ菈��
			SetFileData(CXFile::TYPE_TABLE);

			break;

		case CEdit::TYPE_AIRPLANE:

			// ���f���̏��ݒ菈��
			SetFileData(CXFile::TYPE_AIRPLANE);

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
}

//=======================================
// ���s�ݒ菈��
//=======================================
void CEdit::Front(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 rot = GetRot();		// �������擾����

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // ENTER�L�[���������ꍇ

		// �O��󋵂����ւ���
		m_bFront = m_bFront ? false : true;
	}

	if (m_type == TYPE::TYPE_ITEM ||
		m_type == TYPE::TYPE_ENEMY)
	{ // ��ނ��A�C�e���܂��́A�G�̏ꍇ

		if (m_bFront == true)
		{ // ���s�󋵂� true �̏ꍇ

			// ��O�ɒu��
			pos.z = NEAR_POS + m_fAddDepth;
		}
		else
		{ // ��L�ȊO

			// ���ɒu��
			pos.z = FAR_POS + m_fAddDepth;
		}
	}
	else if(m_type == TYPE::TYPE_AIRPLANE)
	{ // ��s�@�̏ꍇ

		if (m_bFront == true)
		{ // ���s�󋵂� true �̏ꍇ

			// ��O�ɒu��
			pos.z = NEAR_POS;

			// ������ݒ肷��
			rot.y = D3DX_PI;
		}
		else
		{ // ��L�ȊO

			// ���ɒu��
			pos.z = FAR_POS;

			// ������ݒ肷��
			rot.y = 0.0f;
		}
	}
	else
	{ // ��L�ȊO

		if (m_bFront == true)
		{ // ���s�󋵂� true �̏ꍇ

			// ��O�ɒu��
			pos.z = NEAR_POS;
		}
		else
		{ // ��L�ȊO

			// ���ɒu��
			pos.z = FAR_POS;
		}
	}

	// ����K�p����
	SetPos(pos);		// �ʒu
	SetRot(rot);		// ����
}

//=======================================
// �ݒ菈��
//=======================================
void CEdit::Set(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�L�[���������ꍇ

		switch (m_type)
		{
		case CEdit::TYPE_ITEM:

			// �l�W�̐�������
			CScrew::Create(pos, NONE_D3DXVECTOR3, false);

			break;

		case CEdit::TYPE_MACCHINA:

			// �}�L�i���̐�������
			CMacchina::Create(pos);

			break;

		case CEdit::TYPE_ENEMY:

			// �G�̐�������
			CEnemy::Create(pos, m_enemyType);

			break;

		case CEdit::TYPE_TABLE:

			// ��̐�������
			CTable::Create(pos);

			break;

		case CEdit::TYPE_AIRPLANE:

			// ��s�@�̐�������
			CAirplane::Create(pos, m_bFront);

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
}

//=======================================
// ��������
//=======================================
void CEdit::Delete(void)
{
	switch (m_type)
	{
	case CEdit::TYPE_ITEM:

		// �A�C�e���̏�������
		DeleteItem();

		break;

	case CEdit::TYPE_MACCHINA:

		// �}�L�i���̏�������
		DeleteMacchina();

		break;

	case CEdit::TYPE_ENEMY:

		// �G�̏�������
		DeleteEnemy();

		break;

	case CEdit::TYPE_TABLE:

		// ��̏�������
		DeleteTable();

		break;

	case CEdit::TYPE_AIRPLANE:

		// ��s�@�̏�������
		DeleteAirplane();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// ���S���菈��
		CObject::DeathDecision(nCnt);
	}
}

//=======================================
// �A�C�e���̏�������
//=======================================
void CEdit::DeleteItem(void)
{
	// ���[�J���ϐ��錾
	CScrew* pScrew = CScrewManager::Get()->GetTop();		// �A�C�e���̃|�C���^
	CScrew* pScrewNext;										// ���̃A�C�e��

	while (pScrew != nullptr)
	{ // �A�C�e���� NULL ����Ȃ��ꍇ��
		 
		// ���̃A�C�e����ݒ肷��
		pScrewNext = pScrew->GetNext();

		if (useful::RectangleCollisionXY(pScrew->GetPos(), GetPos(), pScrew->GetFileData().collsize, GetFileData().collsize, -pScrew->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pScrew->GetPos(), GetPos(), pScrew->GetFileData().collsize, GetFileData().collsize, -pScrew->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // �����蔻�肪 true �̏ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9�L�[���������ꍇ

				// �A�C�e��������
				pScrew->Uninit();
			}
		}

		// ���̃A�C�e����������
		pScrew = pScrewNext;
	}
}

//=======================================
// �}�L�i���̏�������
//=======================================
void CEdit::DeleteMacchina(void)
{
	// ���[�J���ϐ��錾
	CMacchina* pMacchina = CMacchinaManager::Get()->GetTop();		// �}�L�i���̃|�C���^
	CMacchina* pMacchinaNext;										// ���̃}�L�i��

	while (pMacchina != nullptr)
	{ // �}�L�i���� NULL ����Ȃ��ꍇ��
		 
		// ���̃}�L�i����ݒ肷��
		pMacchinaNext = pMacchina->GetNext();

		if (useful::RectangleCollisionXY(pMacchina->GetPos(), GetPos(), pMacchina->GetFileData().collsize, GetFileData().collsize, -pMacchina->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pMacchina->GetPos(), GetPos(), pMacchina->GetFileData().collsize, GetFileData().collsize, -pMacchina->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // �����蔻�肪 true �̏ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9�L�[���������ꍇ

				// �}�L�i��������
				pMacchina->Uninit();
			}
		}

		// ���̃}�L�i����������
		pMacchina = pMacchinaNext;
	}
}

//=======================================
// �G�̏�������
//=======================================
void CEdit::DeleteEnemy(void)
{
	// ���[�J���ϐ��錾
	CEnemy* pEnemy = CEnemyManager::Get()->GetTop();		// �G�̃|�C���^
	CEnemy* pEnemyNext;										// ���̓G

	while (pEnemy != nullptr)
	{ // �G�� NULL ����Ȃ��ꍇ��
		 
		// ���̓G��ݒ肷��
		pEnemyNext = pEnemy->GetNext();

		if (useful::RectangleCollisionXY(pEnemy->GetPos(), GetPos(), pEnemy->GetFileData().collsize, GetFileData().collsize, -pEnemy->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pEnemy->GetPos(), GetPos(), pEnemy->GetFileData().collsize, GetFileData().collsize, -pEnemy->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // �����蔻�肪 true �̏ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9�L�[���������ꍇ

				// �G������
				pEnemy->Uninit();
			}
		}

		// ���̓G��������
		pEnemy = pEnemyNext;
	}
}

//=======================================
// ��̏�������
//=======================================
void CEdit::DeleteTable(void)
{
	// ���[�J���ϐ��錾
	CTable* pTable = CTableManager::Get()->GetTop();		// ��̃|�C���^
	CTable* pTableNext;										// ���̑�

	while (pTable != nullptr)
	{ // �䂪 NULL ����Ȃ��ꍇ��
		 
		// ���̑��ݒ肷��
		pTableNext = pTable->GetNext();

		if (useful::RectangleCollisionXY(pTable->GetPos(), GetPos(), pTable->GetFileData().collsize, GetFileData().collsize, -pTable->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pTable->GetPos(), GetPos(), pTable->GetFileData().collsize, GetFileData().collsize, -pTable->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // �����蔻�肪 true �̏ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9�L�[���������ꍇ

				// �������
				pTable->Uninit();
			}
		}

		// ���̑��������
		pTable = pTableNext;
	}
}

//=======================================
// ��s�@�̏�������
//=======================================
void CEdit::DeleteAirplane(void)
{
	// ���[�J���ϐ��錾
	CAirplane* pAirplane = CAirplaneManager::Get()->GetTop();		// ��s�@�̃|�C���^
	CAirplane* pAirplaneNext;										// ���̔�s�@

	while (pAirplane != nullptr)
	{ // ��s�@�� NULL ����Ȃ��ꍇ��
		 
		// ���̔�s�@��ݒ肷��
		pAirplaneNext = pAirplane->GetNext();

		if (useful::RectangleCollisionXY(pAirplane->GetPos(), GetPos(), pAirplane->GetFileData().collsize, GetFileData().collsize, -pAirplane->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pAirplane->GetPos(), GetPos(), pAirplane->GetFileData().collsize, GetFileData().collsize, -pAirplane->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // �����蔻�肪 true �̏ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9�L�[���������ꍇ

				// ��s�@������
				pAirplane->Uninit();
			}
		}

		// ���̔�s�@��������
		pAirplane = pAirplaneNext;
	}
}

#endif