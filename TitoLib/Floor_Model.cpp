//-------------------------------------------------------------------------------------
// File: Floor_Model.h
//
// render floor by model
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Floor_Model.h"

using namespace DirectX;

/// <summary>
/// Constractor
/// </summary>
tito::Floor_Model::Floor_Model(ID3D11Device1* device, wchar_t const* fileName)
{   
    // 共通ステートオブジェクトの作成
    m_states = std::make_unique<CommonStates>(device);

    // 床モデルの読み込み
    m_EffectFactory = std::make_unique<EffectFactory>(device);
    m_floorModel = Model::CreateFromCMO(device, fileName, *m_EffectFactory.get());

    position = SimpleMath::Vector3::Zero;
    velocity = SimpleMath::Vector3::Zero;
    acceleration = SimpleMath::Vector3::Zero;
}

/// <summary>
/// Destractor
/// </summary>
tito::Floor_Model::~Floor_Model()
{

}

void tito::Floor_Model::Update()
{
    /*  斜方投射の手順
    int ct = 1;

    dbl_ct = (double)ct / 10.0;

    １.変化する初速度を設定  v0
    ２.変化する角度を設定
    ３.Ｘ軸 = 初速度 * cos(π * 角度 / 180.0) * dbl_ct;
    ４.Ｙ軸 = 初速度 * sin(π * 角度 / 180.0) * dbl_ct
            -0.5 ＊重力加速度(9.8) * pow(dbl_ct, 2);
    */


    auto keystate = Keyboard::Get().GetState();

    velocity = SimpleMath::Vector3::Zero;


    
    //  地面についたらジャンプ終了
    if (position.y < 0.0f)
    {
        velocity.y = 0.0f;
        acceleration.y = 0.0f;
        jumpFlag = false;
    }

    if (keystate.Space)
    {
        jumpFlag = true;
    }


    if (!jumpFlag) return;

    //  加速度の計算
     
    //  速度に加速度を加算
    velocity.x = 0.2;

    velocity.y = 1.0;


    acceleration.y += ((9.8/ 60.0f));
    velocity.y -= acceleration.y;
     
    velocity.x = velocity.x * cosf(45 * 3.14f / 180.0f);
    velocity.y = velocity.y * sinf(45 * 3.14f / 180.0f);
                   

    //  位置に速度を加算
    position += velocity;
}

/// <summary>
/// Render 
/// </summary>
void tito::Floor_Model::Render(ID3D11DeviceContext1* context,SimpleMath::Matrix view, SimpleMath::Matrix proj )
{
    SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

    world =DirectX::SimpleMath::Matrix::CreateTranslation(position);
    //world = position

    // 床の描画
    m_floorModel->Draw(context, *m_states.get(), world, view, proj, false, [&]()
        {                                               //  境界線をぼかすかどうか
            ID3D11SamplerState* samplers[] = { m_states->PointWrap() };
            context->PSSetSamplers(0, 1, samplers);
        }
    );
}
/// <summary>
/// Finalize 
/// </summary>
void tito::Floor_Model::Finalize()
{
    // シーンのクリーンアップ
    m_EffectFactory.reset();
    m_floorModel.reset();
}
