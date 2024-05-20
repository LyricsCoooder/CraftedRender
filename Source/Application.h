#pragma once

#include "Render.h"
#include "UIValue.h"
#include "imgui.h"

namespace RenderApp
{
	/*
		Render main UI, include RenderDocking RenderSetting RenderSense
	*/
	void RenderUI(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);
	
	// Render Doking
	void RenderDocking();
	
	// Setting 
	void RenderSetting(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);
	
	// Render PointTree UI to Setting
	void RenderPointTreeUI(UIValue::UIValue& MainUIValue);
	
	// Render PointTree To Sense
	void RenderPointTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);

	// Render RenderLineTreeUI to Setting
	void RenderLineTreeUI(UIValue::UIValue& MainUIValue);
	
	// Render LineTree To Sense
	void RenderLineTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);

	// Render RenderTriangleTreeUI to Setting
	void RenderTriangleTreeUI(UIValue::UIValue& MainUIValue);
	
	// Render TriangleTree To Sense
	void RenderTriangleTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);

	// Render RenderModelTreeUI to Setting
	void RenderModelTreeUI(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);
	
	// Render RenderModelTreeUI to Sense
	void RenderModelTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);

	// Render CameraUI to Setting
	void RenderCameraUI(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);

	// Render View Port
	void RenderSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender);
}