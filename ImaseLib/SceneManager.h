//--------------------------------------------------------------------------------------
// File: SceneManager.h
//
// �V�[�����Ǘ�����N���X
//
// Date: 2023.3.25
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

// ESC�L�[�ŏI���������ꍇ�L���ɂ��Ă�������
#define ESC_QUIT_ENABLE

#ifdef ESC_QUIT_ENABLE
#include "Keyboard.h"
#endif

namespace Imase
{
	template <class T>
	class SceneManager;

	// �V�[���̊��N���X
	template <class T>
	class Scene
	{
	private:

		// �V�[���}�l�[�W���[�ւ̃|�C���^
		SceneManager<T>* m_sceneManager;

	public:

		// �R���X�g���N�^
		Scene() : m_sceneManager(nullptr) {}

		// �f�X�g���N�^
		virtual ~Scene() = default;

		// ������
		virtual void Initialize() = 0;

		// �X�V
		virtual void Update(float elapsedTime) = 0;

		// �`��
		virtual void Render() = 0;

		// �I������
		virtual void Finalize() = 0;

		// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
		virtual void CreateDeviceDependentResources() {}

		// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
		virtual void CreateWindowSizeDependentResources() {}

		// �f�o�C�X���X�g�������ɌĂяo�����֐�
		virtual void OnDeviceLost() {}

	public:

		// �V�[���}�l�[�W���[�ݒ�֐�
		void SetSceneManager(SceneManager<T>* sceneManager) { m_sceneManager = sceneManager; }

		// �V�[���̐؂�ւ��֐�
		template <class U>
		void ChangeScene();

		// ���[�U�[���ݒ肵�����\�[�X�擾�֐�
		T* GetUserResources();

	};

	// �V�[���}�l�[�W���[�N���X
	template <class T>
	class SceneManager
	{
	private:

		// ���ʂŃA�N�Z�X�������I�u�W�F�N�g�ւ̃|�C���^
		T* m_userResources;

		// ���s���̃V�[���ւ̃|�C���^
		Scene<T>* m_scene;

		// �V�[���폜�֐�
		void DeleteScene();

	public:

		// �R���X�g���N�^
		SceneManager(T* userResources)
			: m_userResources(userResources)
			, m_scene(nullptr)
		{
		};

		// �f�X�g���N�^
		virtual ~SceneManager() { DeleteScene(); };

		// �X�V
		void Update(float elapsedTime);

		// �`��
		void Render();

		// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
		void CreateDeviceDependentResources();
		
		// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
		void CreateWindowSizeDependentResources();

		// �f�o�C�X���X�g�������ɌĂяo�����֐�
		virtual void OnDeviceLost();

		// �V�[���̐ݒ�֐�
		template <class U>
		void SetScene();

		// ���[�U�[���\�[�X�擾�֐�
		T* GetUseResources() { return m_userResources; }

	};

	// �V�[���̐؂�ւ��֐�
	template <class T>
	template <class U>
	void Scene<T>::ChangeScene()
	{
		m_sceneManager->SetScene<U>();
	}

	// ���[�U�[���ݒ肵�����\�[�X�擾�֐�
	template <class T>
	T* Scene<T>::GetUserResources()
	{
		assert(m_sceneManager);

		return m_sceneManager->GetUseResources();
	}

	// �V�[���̐ݒ�֐�
	template <class T>
	template <class U>
	void SceneManager<T>::SetScene()
	{
		// �V�[�����폜
		DeleteScene();

		assert(m_scene == nullptr);

		// �V�[���𐶐�
		m_scene = new U;

		// �V�[���ɃV�[���}�l�[�W���[�ւ̃|�C���^��ݒ�
		m_scene->SetSceneManager(this);

		// �V�[���̏���������
		m_scene->Initialize();
	}

	// �X�V�֐�
	template <class T>
	void SceneManager<T>::Update(float elapsedTime)
	{
#ifdef ESC_QUIT_ENABLE
		// ESC�L�[�ŏI��
		auto kb = DirectX::Keyboard::Get().GetState();
		if (kb.Escape) PostQuitMessage(0);
#endif

		if (m_scene) m_scene->Update(elapsedTime);
	}

	// �`��֐�
	template <class T>
	void SceneManager<T>::Render()
	{
		if (m_scene) m_scene->Render();
	}

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	template <class T>
	void SceneManager<T>::CreateDeviceDependentResources()
	{
		if (m_scene) m_scene->CreateDeviceDependentResources();
	}

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	template <class T>
	void SceneManager<T>::CreateWindowSizeDependentResources()
	{
		if (m_scene) m_scene->CreateWindowSizeDependentResources();
	}

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	template <class T>
	void SceneManager<T>::OnDeviceLost()
	{
		if (m_scene) m_scene->OnDeviceLost();
	}

	// �V�[���̍폜�֐�
	template <class T>
	void SceneManager<T>::DeleteScene()
	{
		if (m_scene)
		{
			m_scene->Finalize();

			delete m_scene;

			m_scene = nullptr;
		}
	}

}

