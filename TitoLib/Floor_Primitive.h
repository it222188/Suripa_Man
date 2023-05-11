//--------------------------------------------------------------------------------------
// File: Floor_Primitive.h
//
// �v���~�e�B�u�ɂ��n�ʂ̕`��
//
//-------------------------------------------------------------------------------------

#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


namespace tito
{
    class Floor_Primitive {
    private :
        // ���̓��C�A�E�g 
        Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

        //���ʃX�e�[�g�I�u�W�F�N�g�ւ̃|�C���^
        std::unique_ptr<DirectX::CommonStates> m_States;

        // �e�N�X�`���n���h�� 
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;

        // �G�t�F�N�g 
        std::unique_ptr<DirectX::AlphaTestEffect> m_BatchEffect;

        // �v���~�e�B�u�o�b�` 
        std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_Batch;

    public:
        Floor_Primitive(ID3D11Device1* device);
        ~Floor_Primitive();

        void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
        void Finalize();
    };

}
