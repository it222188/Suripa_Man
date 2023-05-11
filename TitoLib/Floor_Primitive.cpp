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
	// エフェクトの作成 
	m_BatchEffect = std::make_unique<AlphaTestEffect>(device);
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_BatchEffect->SetReferenceAlpha(255);

	// 入力レイアウト生成 
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_BatchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(
		VertexPositionTexture::InputElements,
		VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_InputLayout.GetAddressOf()
	);

	//共通ステートの作成
	m_States = std::make_unique<CommonStates>(device);

	// テクスチャのロード 
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
	// プリミティブバッチの作成 
	m_Batch =
		std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// 頂点情報（板ポリゴンの頂点） 
	VertexPositionTexture vertex[4] =
	{
		VertexPositionTexture(SimpleMath::Vector3(5.0f, 0.5f, 5.0f),	SimpleMath::Vector2(-5.0f, -5.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-5.0f, 0.5f, 5.0f),	SimpleMath::Vector2(5.0f, -5.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-5.0f, 0.5f, -5.0f),	SimpleMath::Vector2(5.0f,5.0f)),
		VertexPositionTexture(SimpleMath::Vector3(5.0f,0.5f, -5.0f),	SimpleMath::Vector2(-5.0f, 5.0f)),
	};

	// テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード） 
	ID3D11SamplerState* samplers[1] = { m_States->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// 深度バッファに書き込み参照する 
	context->OMSetDepthStencilState(m_States->DepthDefault(), 0);

	// カリングは左周り（反時計回り） 
	context->RSSetState(m_States->CullCounterClockwise());

	// 不透明のみ描画する設定 
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_BatchEffect->SetReferenceAlpha(0);
	m_BatchEffect->SetWorld(SimpleMath::Matrix::Identity);
	m_BatchEffect->SetView(view);
	m_BatchEffect->SetProjection(proj);
	m_BatchEffect->SetTexture(m_Texture.Get());
	m_BatchEffect->Apply(context);
	context->IASetInputLayout(m_InputLayout.Get());

	// 半透明部分を描画 
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
