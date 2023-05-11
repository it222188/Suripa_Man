//-------------------------------------------------------------------------------------
// File: GrassManger.cpp
//
// manage grass class
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Grass.h"
#include <PrimitiveBatch.h> 
#include <VertexTypes.h> 
#include <WICTextureLoader.h> 
#include "GrassManager.h"

using namespace DirectX;

tito::GrassManager::GrassManager()
{
	m_grasses.clear();
}

tito::GrassManager::~GrassManager()
{
}

void tito::GrassManager::Add(std::unique_ptr<tito::Grass> grass)
{
	m_grasses.push_back(std::move(grass));
}

void tito::GrassManager::Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{

	//for (int i = 0; i < m_grasses.size(); i++)
	//{
	//	m_grasses[i]->Render(context, view, proj);
	//}


	//	stl‹¤’Ê‚ÅŽg‚¦‚éver (vector map list‚È‚Ç)
	//for (std::vector<std::unique_ptr<Grass>>::iterator it = m_grasses.begin();
	//	it < m_grasses.end(); ++it)
	//{
	//	(*it)->Render(context, view, proj);
	//}


	for (auto& vec : m_grasses)
	{
		vec->Render(context, view, proj);
	}



}

void tito::GrassManager::Finalize()
{
}
