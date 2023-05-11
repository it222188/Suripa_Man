//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "ImaseLib/DebugFont.h"
#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "ImaseLib/DebugCamera.h"
#include "TitoLib/Floor_Model.h"
#include "TitoLib/Grass.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

    std::unique_ptr<Imase::DebugCamera> m_debugCamera;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;



    // Rendering loop timer.
    DX::StepTimer                           m_timer;

private:

    // �ǉ�

    // �L�[�{�[�h�X�e�[�g�g���b�J�[
    DirectX::Keyboard::KeyboardStateTracker m_tracker;

    // ���ʃX�e�[�g�I�u�W�F�N�g�ւ̃|�C���^
    std::unique_ptr<DirectX::CommonStates> m_states;

    // �f�o�b�O�p������\���I�u�W�F�N�g�ւ̃|�C���^
    std::unique_ptr<Imase::DebugFont> m_font;

    // ���[�U�[���\�[�X�ւ̃|�C���^
    std::unique_ptr<UserResources> m_userResources;

    // �V�[���}�l�[�W���[�ւ̃|�C���^
    std::unique_ptr<Imase::SceneManager<UserResources>> m_sceneManager;

    std::unique_ptr<tito::Floor_Model> m_floor_Model;

    std::unique_ptr<tito::Grass> m_grass;
};
