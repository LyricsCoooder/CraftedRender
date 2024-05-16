#include "Application.h"

void RenderApp::RenderUI(UIValue::UIValue& MainUIValue)
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
            if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
            if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
            if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    Render::Renderer ViewportRender;

    RenderSetting(MainUIValue);
    
    RenderSense(MainUIValue, ViewportRender);

    // Show Demo Window
    ImGui::ShowDemoWindow();
    ImGui::End();
}

struct Point {
    float Pos[2] = { 0.0f };
    float Color[4] = { 0.0f };
};
int PointNum = 0;
std::vector<Point> Points(10);

void RenderApp::RenderSetting(UIValue::UIValue& MainUIValue)
{
    ImGui::Begin("Settings");

    // Add Points 
    ImGui::Text("Points");

    ImGui::SameLine();
    if (ImGui::Button("Add Point"))
    {
        MainUIValue.PointTreeSize++;
        MainUIValue.PointTree.push_back(UIValue::Point());
    }

    for (int i = 0; i < MainUIValue.PointTreeSize; i++)
    {
        ImGui::PushID(i);
        if (ImGui::TreeNode("", "Point%d", i))
        {
            ImGui::InputFloat2("Position", MainUIValue.PointTree[i].Pos);

            ImGui::ColorEdit4("Color", MainUIValue.PointTree[i].Color);

            if (ImGui::Button("Remove"))
            {
                MainUIValue.PointTree.erase(MainUIValue.PointTree.begin() + i);
                MainUIValue.PointTreeSize--;
                i--;
            }

            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    ImGui::End();
}

void RenderApp::RenderSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    ImGui::Begin("Sence");

    // PointTree Render
    for (UIValue::Point Point : MainUIValue.PointTree)
    {
        Common::PixelColor TempPixelColor = Common::PixelColor((int)Point.Pos[0], (int)Point.Pos[1],
                                                    Common::Color(Point.Color[0], Point.Color[1], Point.Color[2], Point.Color[3]));
        ViewportRender.AddToFrameBuffer(TempPixelColor);
    }


    ViewportRender.FinalRender();

    ImGui::End();
}
