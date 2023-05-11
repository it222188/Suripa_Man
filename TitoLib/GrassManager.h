//--------------------------------------------------------------------------------------
// File: GrassManager.h
//
// 草の管理クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include "Grass.h"

namespace tito
{
    class GrassManager {
    private:

        std::vector<std::unique_ptr<tito::Grass>> m_grasses;                   //  Grassクラス型のオブジェ


    public:
        GrassManager();
        ~GrassManager();

        void Add(std::unique_ptr<tito::Grass> grass);

        void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
        void Finalize();
    };

}
