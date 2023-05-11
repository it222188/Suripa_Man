//-------------------------------------------------------------------------------------
// File: Floor_Primitive.h
//
// render floor by primitive
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Floor_Primitive.h"
#include <PrimitiveBatch.h> 
#include <VertexTypes.h> 
#include <WICTextureLoader.h> 

using namespace DirectX;

/// <summary>
/// Constractor
/// </summary>
tito::Floor_Primitive::Floor_Primitive(ID3D11Device1* device)
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
		L"Resources/Textures/floor.png",
		nullptr,
		m_Texture.GetAddressOf()
	);
}

/// <summary>
/// Destractor
/// </summary>
tito::Floor_Primitive::~Floor_Primitive()
{

}

/// <summary>
/// Render 
/// </summary>
void tito::Floor_Primitive::Render(ID3D11DeviceContext1* context,SimpleMath::Matrix view, SimpleMath::Matrix proj )
{
	// �v���~�e�B�u�o�b�`�̍쐬 
	m_Batch =
		std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// ���_���i�|���S���̒��_�j 
	VertexPositionTexture vertex[4] =
	{
		VertexPositionTexture(SimpleMath::Vector3(5.0f, 0.5f, 5.0f),	SimpleMath::Vector2(-5.0f, -5.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-5.0f, 0.5f, 5.0f),	SimpleMath::Vector2(5.0f, -5.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-5.0f, 0.5f, -5.0f),	SimpleMath::Vector2(5.0f,5.0f)),
		VertexPositionTexture(SimpleMath::Vector3(5.0f,0.5f, -5.0f),	SimpleMath::Vector2(-5.0f, 5.0f)),
	};

	// �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j 
	ID3D11SamplerState* samplers[1] = { m_States->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��� 
	context->OMSetDepthStencilState(m_States->DepthDefault(), 0);

	// �J�����O�͍�����i�����v���j 
	context->RSSetState(m_States->CullCounterClockwise());

	// �s�����̂ݕ`�悷��ݒ� 
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_BatchEffect->SetReferenceAlpha(0);
	m_BatchEffect->SetWorld(SimpleMath::Matrix::Identity);
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
void tito::Floor_Primitive::Finalize()
{

}
