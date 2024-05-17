#pragma once

#include "Render.h"
#include "UIValue.h"
#include "imgui.h"

namespace RenderApp
{
	// Main UI
	void RenderUI(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);
	// Render Doking
	void RenderDocking();
	// Setting 
	void RenderSetting(UIValue::UIValue& MainUIValue);
	// Render PointTree UI
	void RenderPointTreeUI(UIValue::UIValue& MainUIValue);
	// Render PointTree To Sense
	void RenderPointTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);

	void RenderLineTreeUI(UIValue::UIValue& MainUIValue);
	void RenderLineTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);

	void RenderModelTreeUI(UIValue::UIValue& MainUIValue);
	// Render View Port
	void RenderSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);
}