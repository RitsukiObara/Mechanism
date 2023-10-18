//===========================================
//
// ���C�g�̃��C������[light.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"

#include "input.h"
#include "debugproc.h"

// �}�N����`
#define ONE_LIGHT_VEC		(D3DXVECTOR3(0.22f, -0.87f, 0.22f))		// ��ڂ̃��C�g�̕���
#define TWO_LIGHT_VEC		(D3DXVECTOR3(-0.9f, -0.2f, 0.2f))		// ��ڂ̃��C�g�̕���
#define THREE_LIGHT_VEC		(D3DXVECTOR3(0.55f, 0.3f, 0.88f))		// �O�ڂ̃��C�g�̕���

//=========================
// �R���X�g���N�^
//=========================
CLight::CLight()
{
	for (int nCntSet = 0; nCntSet < NUM_LIGHT; nCntSet++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_light[nCntSet], sizeof(D3DLIGHT9));
	}
}

//=========================
// �f�X�g���N�^
//=========================
CLight::~CLight()
{

}

//=========================
// ���C�g�̏���������
//=========================
HRESULT CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;				// �ݒ�p�����x�N�g��

	for (int nCntSet = 0; nCntSet < NUM_LIGHT; nCntSet++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_light[nCntSet], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntSet].Type = D3DLIGHT_DIRECTIONAL;

		switch (nCntSet)
		{
		case 0:

			// ���C�g�̊g�U����ݒ�
			m_light[nCntSet].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir = ONE_LIGHT_VEC;

			break;				// �����o��

		case 1:

			// ���C�g�̊g�U����ݒ�
			m_light[nCntSet].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir = TWO_LIGHT_VEC;

			break;				// �����o��

		case 2:

			// ���C�g�̊g�U����ݒ�
			m_light[nCntSet].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir = THREE_LIGHT_VEC;

			break;				// �����o��

		default:

			// ��~
			assert(false);

			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);				// �x�N�g���𐳋K������

		m_light[nCntSet].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntSet, &m_light[nCntSet]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntSet, TRUE);
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// ���C�g�̏I������
//=========================
void CLight::Uninit(void)
{

}

//=========================
// ���C�g�̍X�V����
//=========================
void CLight::Update(void)
{

}