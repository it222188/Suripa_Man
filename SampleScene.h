//--------------------------------------------------------------------------------------
// File: SampleScene.h
//
// �V�[���̐��^�Ɏg�p���Ă�������
//
// Date: 2023.3.25
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once
#include "ImaseLib/SceneManager.h"
#include "ImaseLib/TaskManager.h"
#include "UserResources.h"
#include "SampleTask.h"

class SampleScene : public Imase::Scene<UserResources>
{
private:

	// �^�X�N�}�l�[�W���[
	Imase::TaskManager m_taskManager;

	// �T���v���^�X�N�ւ̃|�C���^
	SampleTask* m_sampleTask;

public:

	// �R���X�g���N�^
	SampleScene();

	// ������
	void Initialize() override;

	// �X�V
	void Update(float elapsedTime) override;

	// �`��
	void Render() override;

	// �I������
	void Finalize() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	void OnDeviceLost() override;

};

