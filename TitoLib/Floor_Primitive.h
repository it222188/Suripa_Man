//--------------------------------------------------------------------------------------
// File: Floor_Primitive.h
//
// プリミティブによる地面の描画
//
//-------------------------------------------------------------------------------------

#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


namespace tito
{
    class Floor_Primitive {
    private :
        // 入力レイアウト 
        Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

        //共通ステートオブジェクトへのポインタ
        std::unique_ptr<DirectX::CommonStates> m_States;

        // テクスチャハンドル 
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;

        // エフェクト 
        std::unique_ptr<DirectX::AlphaTestEffect> m_BatchEffect;

        // プリミティブバッチ 
        std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_Batch;

    public:
        Floor_Primitive(ID3D11Device1* device);
        ~Floor_Primitive();

        void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
        void Finalize();
    };

}
