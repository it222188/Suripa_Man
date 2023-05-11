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
    // ���ʃX�e�[�g�I�u�W�F�N�g�̍쐬
    m_states = std::make_unique<CommonStates>(device);

    // �����f���̓ǂݍ���
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
    /*  �Ε����˂̎菇
    int ct = 1;

    dbl_ct = (double)ct / 10.0;

    �P.�ω����鏉���x��ݒ�  v0
    �Q.�ω�����p�x��ݒ�
    �R.�w�� = �����x * cos(�� * �p�x / 180.0) * dbl_ct;
    �S.�x�� = �����x * sin(�� * �p�x / 180.0) * dbl_ct
            -0.5 ���d�͉����x(9.8) * pow(dbl_ct, 2);
    */


    auto keystate = Keyboard::Get().GetState();

    velocity = SimpleMath::Vector3::Zero;


    
    //  �n�ʂɂ�����W�����v�I��
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

    //  �����x�̌v�Z
     
    //  ���x�ɉ����x�����Z
    velocity.x = 0.2;

    velocity.y = 1.0;


    acceleration.y += ((9.8/ 60.0f));
    velocity.y -= acceleration.y;
     
    velocity.x = velocity.x * cosf(45 * 3.14f / 180.0f);
    velocity.y = velocity.y * sinf(45 * 3.14f / 180.0f);
                   

    //  �ʒu�ɑ��x�����Z
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

    // ���̕`��
    m_floorModel->Draw(context, *m_states.get(), world, view, proj, false, [&]()
        {                                               //  ���E�����ڂ������ǂ���
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
    // �V�[���̃N���[���A�b�v
    m_EffectFactory.reset();
    m_floorModel.reset();
}
