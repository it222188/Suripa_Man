#pragma once

#include "ImaseLib/TaskManager.h"
#include "ImaseLib/DebugFont.h"

class SampleTask : public Imase::Task
{
private:

	// �f�o�b�O������\���I�u�W�F�N�g�ւ̃|�C���^
	Imase::DebugFont* m_font;

public:

	// �R���X�g���N�^
	SampleTask(Imase::DebugFont* font);

	// �f�X�g���N�^
	~SampleTask();

	// �X�V
	bool Update(float elapsedTime) override;

	// �`��
	void Render() override;

};

