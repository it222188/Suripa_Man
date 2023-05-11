//--------------------------------------------------------------------------------------
// File: Grass.h
//
// プリミティブによる地面の描画
//
//-------------------------------------------------------------------------------------

#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


namespace tito
{
    class Grass {
    private :
        //  四角形なので４つの配列
        const static DirectX::VertexPositionTexture VERTICES[4];
        const static DirectX::VertexPositionTexture VERTICES_BILLBOARD[4];


        DirectX::SimpleMath::Vector3 m_position;

        //  ビルボード行列
        DirectX::SimpleMath::Matrix m_billboard;


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
        Grass(ID3D11Device1* device);
        ~Grass();

        void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

        void RenderBillboard(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

        void Finalize();

        void CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up);
    };

}
