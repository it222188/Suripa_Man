//--------------------------------------------------------------------------------------
// File: Floor_Model.h
//
// モデルによる地面の描画
//
//-------------------------------------------------------------------------------------

#pragma once



namespace tito
{
    class Floor_Model {
    private :

        // 共通ステートオブジェクトへのポインタ
        std::unique_ptr<DirectX::CommonStates> m_states;

        // エフェクトファクトリー
        std::unique_ptr<DirectX::EffectFactory> m_EffectFactory;

        // 床のモデル
        std::unique_ptr<DirectX::Model> m_floorModel;


        DirectX::SimpleMath::Vector3 position;           //  位置
       
        DirectX::SimpleMath::Vector3 velocity;           //  速度
       
        DirectX::SimpleMath::Vector3 acceleration;       //  加速度

        bool jumpFlag = false;

    public:
        Floor_Model(ID3D11Device1* device, wchar_t const* fileName = nullptr);
        ~Floor_Model();


        void Update();
        void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
        void Finalize();
    };

}
