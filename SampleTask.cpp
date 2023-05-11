#include "pch.h"
#include "SampleTask.h"
#include <sstream>

using namespace DirectX;

SampleTask::SampleTask(Imase::DebugFont* font)
	: m_font(font)
{
}

SampleTask::~SampleTask()
{
}

bool SampleTask::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// タスク名を表示
	std::wostringstream oss;
	oss << "TaskName:" << this->GetName().c_str();
	m_font->AddString(oss.str().c_str(), SimpleMath::Vector2(0.0f, m_font->GetFontHeight() * 2.0f));

	return true;
}

void SampleTask::Render()
{
}
