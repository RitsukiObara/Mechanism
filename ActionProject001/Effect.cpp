//=======================================
//
//�G�t�F�N�g�̃��C������[Effect.cpp]
//Author ��������
//
//=======================================
#include "Effect.h"
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define NORMAL_TEXTURE		"data/TEXTURE/effect000.jpg"			// �ʏ�G�t�F�N�g�̃e�N�X�`��
#define FIRE_TEXTURE		"data/TEXTURE/Smoke.tga"				// ���G�t�F�N�g�̃e�N�X�`��
#define DUST_TEXTURE		"data/TEXTURE/Dust.tga"					// ���G�t�F�N�g�̃e�N�X�`��
#define BIGJUMP_COL_RAND	(3)										// ���W�����v�G�t�F�N�g���̐F�̃����_����
#define BIGJUMP_COL_FIRST	(D3DXCOLOR(1.0f, 0.0f, 0.8f, 1.0f))		// ���W�����v�G�t�F�N�g�̐F(1��)
#define BIGJUMP_COL_SEC		(D3DXCOLOR(0.0f, 1.0f, 0.1f, 1.0f))		// ���W�����v�G�t�F�N�g�̐F(2��)
#define BIGJUMP_COL_THIRD	(D3DXCOLOR(0.0f, 0.7f, 1.0f, 1.0f))		// ���W�����v�G�t�F�N�g�̐F(3��)

//=========================
// �R���X�g���N�^
//=========================
CEffect::CEffect() : CBillboard(CObject::TYPE_EFFECT, CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_nLife = 0;									// ����
	m_fSub = 0.0f;									// �����ɂȂ�Ԋu
	m_fContra = 0.0f;								// ���a�̏k�ފԊu
	m_type = TYPE_NONE;								// ���
	m_bAdd = false;									// ���Z������
}

//=========================
// �f�X�g���N�^
//=========================
CEffect::~CEffect()
{

}

//=========================
// ����������
//=========================
HRESULT CEffect::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_nLife = 0;									// ����
	m_fSub = 0.0f;									// �����ɂȂ�Ԋu
	m_fContra = 0.0f;								// ���a�̏k�ފԊu
	m_type = TYPE_NONE;								// ���
	m_bAdd = false;									// ���Z������

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEffect::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CEffect::Update(void)
{
	// ���[�J���ϐ���錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 size = GetSize();	// �T�C�Y���擾����

	// ���������炵�Ă���
	m_nLife--;

	// �ړ�����
	pos += m_move;

	// �����x�����Z������
	m_col.a -= m_fSub;

	// �T�C�Y���k�߂�
	size.x -= m_fContra;
	size.y -= m_fContra;

	if (m_col.a <= 0.0f)
	{ // �����x��0.0f�ȉ��̏ꍇ

		// �����x��␳����
		m_col.a = 0.0f;
	}

	if (size.x <= 0.0f)
	{ // �T�C�Y��0.0f�ȉ��̏ꍇ

		// �T�C�Y��␳����
		size.x = 0.0f;
	}

	if (size.y <= 0.0f)
	{ // �T�C�Y��0.0f�ȉ��̏ꍇ

		// �T�C�Y��␳����
		size.y = 0.0f;
	}

	// �ʒu���X�V����
	SetPos(pos);

	// �T�C�Y���X�V����
	SetSize(size);

	switch (m_type)
	{
	case TYPE_NONE:			// ����

		// ���ɂȂ�

		break;

	case TYPE_FIRE:			// ��

		// ���̍X�V����
		UpdateFire();

		break;

	case TYPE_DUST:			// ��

		// �d�͂𑫂�
		m_move.y -= 0.4f;

		break;
	}

	if (m_nLife <= 0)
	{ // �G�t�F�N�g�̎������s������

		// �j������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���_���W�̐ݒ菈��
	SetVertex();

	// �F�̐ݒ菈��
	SetVtxColor(m_col);
}

//=========================
// �`�揈��
//=========================
void CEffect::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	if (m_bAdd == true)
	{ // ���̎��(tga�t�@�C��)�̏ꍇ

		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �`�揈��
		CBillboard::DrawLightOff();

		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else
	{ // ��L�ȊO

		// �`�揈��
		CBillboard::DrawLightOff();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEffect::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type, const D3DXCOLOR& col, const bool bAdd)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu�ݒ�
	SetSize(D3DXVECTOR3(fRadius, fRadius, 0.0f));	// �T�C�Y�ݒ�

	// �S�Ă̒l������������
	m_type = type;			// ���
	m_nLife = nLife;		// ����
	m_move = move;			// �ړ���
	m_col = col;			// �F
	m_bAdd = bAdd;			// ���Z������

	m_fSub = m_col.a * (1.0f / m_nLife);			// �����ɂȂ�Ԋu
	m_fContra = fRadius * (1.0f / m_nLife);			// ���a�̏k�ފԊu

	// ���_���̏�����
	SetVertex();

	// �F�̐ݒ菈��
	SetVtxColor(m_col);

	if (m_type == TYPE::TYPE_DUST)
	{ // ���̏ꍇ

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(DUST_TEXTURE));
	}
	else if (m_type == TYPE::TYPE_FIRE)
	{ // ���̏ꍇ

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(FIRE_TEXTURE));
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(NORMAL_TEXTURE));
	}
}

//=========================
// ��������
//=========================
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type, const D3DXCOLOR& col, const bool bAdd)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEffect* pEffect = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEffect == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEffect = new CEffect;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEffect != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEffect->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�G�t�F�N�g�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEffect->SetData(pos, move, nLife, fRadius, type, col, bAdd);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pEffect;
}

//=========================
// �����̏���
//=========================
void CEffect::UpdateFire(void)
{
	// G�l�ɉ��Z����
	m_col.g += m_fSub;

	if (m_col.g >= 1.0f)
	{ // �F��1.0f�ȏ�ɂȂ����ꍇ

		// G�l���Œ肷��
		m_col.g = 1.0f;
	}
}