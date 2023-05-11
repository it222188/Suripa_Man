#pragma once

#include "ImaseLib/TaskManager.h"
#include "ImaseLib/DebugFont.h"

class SampleTask : public Imase::Task
{
private:

	// デバッグ文字列表示オブジェクトへのポインタ
	Imase::DebugFont* m_font;

public:

	// コンストラクタ
	SampleTask(Imase::DebugFont* font);

	// デストラクタ
	~SampleTask();

	// 更新
	bool Update(float elapsedTime) override;

	// 描画
	void Render() override;

};

