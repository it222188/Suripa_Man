//-------------------------------------------------------------------------------------
// File: Grass.h
//
// render floor by primitive
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Grass.h"
#include <PrimitiveBatch.h> 
#include <VertexTypes.h> 
#include <WICTextureLoader.h> 

using namespace DirectX;

const VertexPositionTexture tito::Grass::VERTICES[4] =
{						  //�@	�\���͈́@�傫���Ȃ�				//	UV���W�E�u�P�v���ꖇ�Ƃ��� �����𑝂₷�Ɩ�����������
	VertexPositionTexture(SimpleMath::Vector3(-0.5f, 1.0f, -0.5f),	SimpleMath::Vector2(0.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3( 0.5f, 1.0f,  0.5f),	SimpleMath::Vector2(1.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3( 0.5f, 0.0f,  0.5f),	SimpleMath::Vector2(1.0f, 1.0f)),
	VertexPositionTexture(SimpleMath::Vector3(-0.5f, 0.0f, -0.5f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

const VertexPositionTexture tito::Grass::VERTICES_BILLBOARD[4] =
{						  //�@	�\���͈́@�傫���Ȃ�				//	UV���W�E�u�P�v���ꖇ�Ƃ��� �����𑝂₷�Ɩ�����������
	VertexPositionTexture(SimpleMath::Vector3(-0.5f, 1.0f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.5f, 1.0f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.5f, 0.0f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
	VertexPositionTexture(SimpleMath::Vector3(-0.5f, 0.0f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

/// <summary>
/// Constractor
/// </summary>
tito::Grass::Grass(ID3D11Device1* device)
{   
	// �G�t�F�N�g�̍쐬 
	m_BatchEffect = std::make_unique<AlphaTestEffect>(device);
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_BatchEffect->SetReferenceAlpha(255);

	// ���̓��C�A�E�g���� 
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_BatchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(
		VertexPositionTexture::InputElements,
		VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_InputLayout.GetAddressOf()
	);

	//���ʃX�e�[�g�̍쐬
	m_States = std::make_unique<CommonStates>(device);

	// �e�N�X�`���̃��[�h 
	CreateWICTextureFromFile(
		device,
		L"Resources/Textures/grass.png",
		nullptr,
		m_Texture.GetAddressOf()
	);

	//	������
	m_position = SimpleMath::Vector3::Zero;
	//m_position = SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	m_billboard = SimpleMath::Matrix::Identity;

}

/// <summary>
/// Destractor
/// </summary>
tito::Grass::~Grass()
{

}

/// <summary>
/// Render 
/// </summary>
void tito::Grass::Render(ID3D11DeviceContext1* context,SimpleMath::Matrix view, SimpleMath::Matrix proj )
{
	// �v���~�e�B�u�o�b�`�̍쐬 
	m_Batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// ���_��� 2��(4*2)�i�|���S���̒��_�j 
	VertexPositionTexture vertex[8];

	for (int i = 0; i < 4; i++)
	{
		//	�P���ڂɒ萔������
		vertex[i] = VERTICES[i];
		//	�Q���ڂɓ����萔������
		vertex[i + 4] = VERTICES[i];
		//	�Q���ڂ�Z���W�𔽓]������
		vertex[i + 4].position.z *= -1;

		//vertex[i].position.x += m_position.x;
		//vertex[i].position.y += m_position.y;
		//vertex[i].position.z += m_position.z;
	}


	// �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j 
	ID3D11SamplerState* samplers[1] = { m_States->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��� 
	context->OMSetDepthStencilState(m_States->DepthDefault(), 0);

	//// �J�����O�͍�����i�����v���j 
	//context->RSSetState(m_States->CullCounterClockwise());

	//	�J�����O�͂��Ȃ�ver�͂�����
	context->RSSetState(m_States->CullNone());

	// �s�����̂ݕ`�悷��ݒ� 
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_BatchEffect->SetReferenceAlpha(0);
	m_BatchEffect->SetWorld(m_billboard);
	m_BatchEffect->SetView(view);
	m_BatchEffect->SetProjection(proj);
	m_BatchEffect->SetTexture(m_Texture.Get());
	m_BatchEffect->Apply(context);
	context->IASetInputLayout(m_InputLayout.Get());

	// ������������`�� 
	m_Batch->Begin();
	m_Batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_Batch->DrawQuad(vertex[4], vertex[5], vertex[6], vertex[7]);
	m_Batch->End();
}


/// <summary>
/// Render 
/// </summary>
void tito::Grass::RenderBillboard(ID3D11DeviceContext1* context, SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	// �v���~�e�B�u�o�b�`�̍쐬 
	m_Batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// ���_���i�|���S���̒��_�j 
	VertexPositionTexture vertex[4];

	for (int i = 0; i < 4; i++)
	{
		vertex[i] = VERTICES_BILLBOARD[i];
	}


	// �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j 
	ID3D11SamplerState* samplers[1] = { m_States->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��� 
	context->OMSetDepthStencilState(m_States->DepthDefault(), 0);

	//// �J�����O�͍�����i�����v���j 
	//context->RSSetState(m_States->CullCounterClockwise());

	//	�J�����O�͂��Ȃ�ver�͂�����
	context->RSSetState(m_States->CullNone());

	// �s�����̂ݕ`�悷��ݒ� 
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_BatchEffect->SetReferenceAlpha(0);
	m_BatchEffect->SetWorld(m_billboard);
	m_BatchEffect->SetView(view);
	m_BatchEffect->SetProjection(proj);
	m_BatchEffect->SetTexture(m_Texture.Get());
	m_BatchEffect->Apply(context);
	context->IASetInputLayout(m_InputLayout.Get());

	// ������������`�� 
	m_Batch->Begin();
	m_Batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_Batch->End();
}


/// <summary>
/// Finalize 
/// </summary>
void tito::Grass::Finalize()
{

}

/// <summary>
///  CreateBillboard (���W�n���t�Ȃ̂ŉ�]�����Ȃ��Ɨ��Ԃ�)
/// </summary>
/// <param name="eye">�J����</param> 
/// <param name="up">�J�����̏�x�N�g��</param>
void tito::Grass::CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up) 
{
	//	�r���{�[�h�s��̍쐬
	/*m_billboard = SimpleMath::Matrix::CreateBillboard(m_position, eye, up);*/
	m_billboard = SimpleMath::Matrix::CreateConstrainedBillboard(m_position, eye, up);

	//	Y��180�x��]�����邽�߂̍s�� (�E����W�v���獶����W�ւ̕ϊ�
	SimpleMath::Matrix rotY = SimpleMath::Matrix::Identity;
			
	//	�r���{�[�h�s���180�x��]������@�s�񂢂��鎞�́u._�v
	rotY._11 = -1;
	rotY._33 = -1;

	//	�s��̏ꍇ�͂����Z������ꍇ�A���Ԃ��厖
	m_billboard = rotY * m_billboard;
						
											// ���W�A��
	/*rotY = SimpleMath::Matrix::CreateRotationY(3.14);
	* 
	//	�P�ʍs����@���@��](180)
	    1 0 0 0	  	   -1 0  0   0
	    0 1 0 0	  	    0 1  0   0
	    0 0 1 0	  	    0 0 -1   0
	    0 0 0 1	  	    0 0  0  -1
						*/
}
