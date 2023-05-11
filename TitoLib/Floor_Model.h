//--------------------------------------------------------------------------------------
// File: Floor_Model.h
//
// ���f���ɂ��n�ʂ̕`��
//
//-------------------------------------------------------------------------------------

#pragma once



namespace tito
{
    class Floor_Model {
    private :

        // ���ʃX�e�[�g�I�u�W�F�N�g�ւ̃|�C���^
        std::unique_ptr<DirectX::CommonStates> m_states;

        // �G�t�F�N�g�t�@�N�g���[
        std::unique_ptr<DirectX::EffectFactory> m_EffectFactory;

        // ���̃��f��
        std::unique_ptr<DirectX::Model> m_floorModel;


        DirectX::SimpleMath::Vector3 position;           //  �ʒu
       
        DirectX::SimpleMath::Vector3 velocity;           //  ���x
       
        DirectX::SimpleMath::Vector3 acceleration;       //  �����x

        bool jumpFlag = false;

    public:
        Floor_Model(ID3D11Device1* device, wchar_t const* fileName = nullptr);
        ~Floor_Model();


        void Update();
        void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
        void Finalize();
    };

}
