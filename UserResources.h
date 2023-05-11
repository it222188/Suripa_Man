//--------------------------------------------------------------------------------------
// File: UserResources.h
//
// �V�[���֓n�����[�U�[���\�[�X�N���X�i�T���v���j
//
// Date: 2023.3.25
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "ImaseLib/DebugFont.h"

// �e�V�[���ɓn�����ʃ��\�[�X���L�q���Ă�������
class UserResources
{
private:

	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_deviceResources;

	// ���ʃX�e�[�g
	DirectX::CommonStates* m_states;

	// �X�e�b�v�^�C�}�[
	DX::StepTimer* m_timer;

	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker* m_tracker;

	// �f�o�b�O�p������\���I�u�W�F�N�g�ւ̃|�C���^
	Imase::DebugFont* m_font;

public:

	// �R���X�g���N�^
	UserResources()
		: m_deviceResources(nullptr), m_states(nullptr), m_timer(nullptr), m_tracker(nullptr), m_font(nullptr)
	{
	}

	// �f�o�C�X���\�[�X��ݒ肷��֐�
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_deviceResources = deviceResources; }

	// �f�o�C�X���\�[�X���擾����֐�
	const DX::DeviceResources* GetDeviceResources() { return m_deviceResources; }

	// ���ʃX�e�[�g��ݒ肷��֐�
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }

	// ���ʃX�e�[�g���擾����֐�
	const DirectX::CommonStates* GetCommonStates() { return m_states; }

	// �X�e�b�v�^�C�}�[��ݒ肷��֐�
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }

	// �X�e�b�v�^�C�}�[���擾����֐�
	const DX::StepTimer* GetStepTimer() { return m_timer; }

	// �L�[�{�[�h�X�e�[�g�g���b�J�[��ݒ肷��֐�
	void SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* tracker) { m_tracker = tracker; }

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����֐�
	const DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() { return m_tracker; }

	// �L�[�{�[�h�X�e�[�g�g���b�J�[��ݒ肷��֐�
	void SetDebugFont(Imase::DebugFont* font) { m_font = font; }

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����֐�
	Imase::DebugFont* GetDebugFont() { return m_font; }

};

