#pragma once

#include "Render.h"
#include "UIValue.h"
#include "imgui.h"

namespace RenderApp
{
	// Main UI
	void RenderUI(UIValue::UIValue& MainUIValue);
	
	void RenderSetting(UIValue::UIValue& MainUIValue);
	// Render View Port
	void RenderSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);
}