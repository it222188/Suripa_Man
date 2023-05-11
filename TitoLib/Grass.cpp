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
{						  //　	表示範囲　大きくなる				//	UV座標・「１」を一枚とする 数字を増やすと枚数が増える
	VertexPositionTexture(SimpleMath::Vector3(-0.5f, 1.0f, -0.5f),	SimpleMath::Vector2(0.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3( 0.5f, 1.0f,  0.5f),	SimpleMath::Vector2(1.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3( 0.5f, 0.0f,  0.5f),	SimpleMath::Vector2(1.0f, 1.0f)),
	VertexPositionTexture(SimpleMath::Vector3(-0.5f, 0.0f, -0.5f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

const VertexPositionTexture tito::Grass::VERTICES_BILLBOARD[4] =
{						  //　	表示範囲　大きくなる				//	UV座標・「１」を一枚とする 数字を増やすと枚数が増える
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
		L"Resources/Textures/grass.png",
		nullptr,
		m_Texture.GetAddressOf()
	);

	//	初期化
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
	// プリミティブバッチの作成 
	m_Batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// 頂点情報 2枚(4*2)（板ポリゴンの頂点） 
	VertexPositionTexture vertex[8];

	for (int i = 0; i < 4; i++)
	{
		//	１枚目に定数を入れる
		vertex[i] = VERTICES[i];
		//	２枚目に同じ定数を入れる
		vertex[i + 4] = VERTICES[i];
		//	２枚目のZ座標を反転させる
		vertex[i + 4].position.z *= -1;

		//vertex[i].position.x += m_position.x;
		//vertex[i].position.y += m_position.y;
		//vertex[i].position.z += m_position.z;
	}


	// テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード） 
	ID3D11SamplerState* samplers[1] = { m_States->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// 深度バッファに書き込み参照する 
	context->OMSetDepthStencilState(m_States->DepthDefault(), 0);

	//// カリングは左周り（反時計回り） 
	//context->RSSetState(m_States->CullCounterClockwise());

	//	カリングはしないverはこちら
	context->RSSetState(m_States->CullNone());

	// 不透明のみ描画する設定 
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_BatchEffect->SetReferenceAlpha(0);
	m_BatchEffect->SetWorld(m_billboard);
	m_BatchEffect->SetView(view);
	m_BatchEffect->SetProjection(proj);
	m_BatchEffect->SetTexture(m_Texture.Get());
	m_BatchEffect->Apply(context);
	context->IASetInputLayout(m_InputLayout.Get());

	// 半透明部分を描画 
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
	// プリミティブバッチの作成 
	m_Batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// 頂点情報（板ポリゴンの頂点） 
	VertexPositionTexture vertex[4];

	for (int i = 0; i < 4; i++)
	{
		vertex[i] = VERTICES_BILLBOARD[i];
	}


	// テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード） 
	ID3D11SamplerState* samplers[1] = { m_States->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// 深度バッファに書き込み参照する 
	context->OMSetDepthStencilState(m_States->DepthDefault(), 0);

	//// カリングは左周り（反時計回り） 
	//context->RSSetState(m_States->CullCounterClockwise());

	//	カリングはしないverはこちら
	context->RSSetState(m_States->CullNone());

	// 不透明のみ描画する設定 
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_BatchEffect->SetReferenceAlpha(0);
	m_BatchEffect->SetWorld(m_billboard);
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
void tito::Grass::Finalize()
{

}

/// <summary>
///  CreateBillboard (座標系が逆なので回転させないと裏返る)
/// </summary>
/// <param name="eye">カメラ</param> 
/// <param name="up">カメラの上ベクトル</param>
void tito::Grass::CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up) 
{
	//	ビルボード行列の作成
	/*m_billboard = SimpleMath::Matrix::CreateBillboard(m_position, eye, up);*/
	m_billboard = SimpleMath::Matrix::CreateConstrainedBillboard(m_position, eye, up);

	//	Y軸180度回転させるための行列 (右手座標計から左手座標への変換
	SimpleMath::Matrix rotY = SimpleMath::Matrix::Identity;
			
	//	ビルボード行列を180度回転させる　行列いじる時は「._」
	rotY._11 = -1;
	rotY._33 = -1;

	//	行列の場合はかけ算をする場合、順番が大事
	m_billboard = rotY * m_billboard;
						
											// ラジアン
	/*rotY = SimpleMath::Matrix::CreateRotationY(3.14);
	* 
	//	単位行列を　→　回転(180)
	    1 0 0 0	  	   -1 0  0   0
	    0 1 0 0	  	    0 1  0   0
	    0 0 1 0	  	    0 0 -1   0
	    0 0 0 1	  	    0 0  0  -1
						*/
}
