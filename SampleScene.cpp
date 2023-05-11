//--------------------------------------------------------------------------------------
// File: SampleScene.cpp
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
// Date: 2023.3.25
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SampleScene.h"
#include "ImaseLib/DebugFont.h"

using namespace DirectX;

SampleScene::SampleScene()
	: m_sampleTask(nullptr)
{
}

// ������
void SampleScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	// �T���v���^�X�N��o�^
	m_sampleTask = m_taskManager.AddTask<SampleTask>(GetUserResources()->GetDebugFont());
}

// �X�V
void SampleScene::Update(float elapsedTime)
{
	UserResources* userResources = GetUserResources();
	Imase::DebugFont* font = userResources->GetDebugFont();
	font->AddString(L"SampleScene", SimpleMath::Vector2(0.0f, font->GetFontHeight()), Colors::Yellow);

	// �^�X�N�}�l�[�W���[�̍X�V
	m_taskManager.Update(elapsedTime);
}

// �`��
void SampleScene::Render()
{
	// �^�X�N�}�l�[�W���[�̕`��
	m_taskManager.Render();
}

// �I������
void SampleScene::Finalize()
{
}

// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
void SampleScene::CreateDeviceDependentResources()
{
}

// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
void SampleScene::CreateWindowSizeDependentResources()
{
}

// �f�o�C�X���X�g�������ɌĂяo�����֐�
void SampleScene::OnDeviceLost()
{
}
