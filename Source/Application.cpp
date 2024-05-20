#include "Application.h"
#include "ImGuiFileDialog.h"
#include "iostream"

void RenderApp::RenderUI(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{   
    RenderDocking();

    // Render Settings
    RenderSetting(MainUIValue, ViewportRender);

    // Render Sense
    RenderSense(MainUIValue, ViewportRender);

    // Show Demo Window
    ImGui::ShowDemoWindow();
}

void RenderApp::RenderDocking()
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

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

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
    ImGui::End();
}

void RenderApp::RenderSetting(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    ImGui::Begin("Settings");

    RenderCameraUI(MainUIValue, ViewportRender);
    // RenderPointTreeUI    
    RenderPointTreeUI(MainUIValue);
    // RenderTreeUI
    RenderLineTreeUI(MainUIValue);
    
    RenderTriangleTreeUI(MainUIValue);

    RenderModelTreeUI(MainUIValue, ViewportRender);


    ImGui::End();
}

void RenderApp::RenderPointTreeUI(UIValue::UIValue& MainUIValue)
{
    // Add Points 
    ImGui::SeparatorText("Points");

    if (ImGui::Button("Add Point"))
    {
        MainUIValue.PointTreeSize++;
        MainUIValue.PointTree.push_back(Common::Point());
    }

    for (int i = 0; i < MainUIValue.PointTreeSize; i++)
    {
        ImGui::PushID(i);
        if (ImGui::TreeNode("", "Point%d", i))
        {
            bool RemoveButton = ImGui::Button("Remove");
            ImGui::InputFloat2("Position", MainUIValue.PointTree[i].Pos);
            ImGui::ColorEdit4("Color", MainUIValue.PointTree[i].Color);

            if (RemoveButton)
            {
                MainUIValue.PointTree.erase(MainUIValue.PointTree.begin() + i);
                MainUIValue.PointTreeSize--;
                i--;
            }

            ImGui::TreePop();
        }
        ImGui::PopID();
    }
}

void RenderApp::RenderPointTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    // PointTree Render
    for (Common::Point& Point : MainUIValue.PointTree)
    {
        ViewportRender.AddToFrameBuffer(Common::PixelColor(Point.Pos, Point.Color));
    }
}

void RenderApp::RenderLineTreeUI(UIValue::UIValue& MainUIValue)
{
    ImGui::SeparatorText("Lines");

    if (ImGui::Button("Add Line"))
    {
        MainUIValue.LineTreeSize++;
        MainUIValue.LineTree.push_back(Common::Line());
    }

    for (int i = 0; i < MainUIValue.LineTreeSize; i++)
    {
        ImGui::PushID(MainUIValue.PointTreeSize + i);
        if (ImGui::TreeNode("", "Line%d", i))
        {
            bool RemoveButton = ImGui::Button("Remove");
            ImGui::InputFloat2("Start Pos", MainUIValue.LineTree[i].StartPos);
            ImGui::InputFloat2("End Pos", MainUIValue.LineTree[i].EndPos);
            ImGui::ColorEdit4("Color", MainUIValue.LineTree[i].Color);

            if (RemoveButton)
            {
                MainUIValue.LineTree.erase(MainUIValue.LineTree.begin() + i);
                MainUIValue.LineTreeSize--;
                i--;
            }

            ImGui::TreePop();
        }
        ImGui::PopID();
    }
}

void RenderApp::RenderLineTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    // LineTree Render
    for (Common::Line& Line : MainUIValue.LineTree)
    {
        ViewportRender.RenderLine(Line.StartPos, Line.EndPos, Line.Color);
    }
}

void RenderApp::RenderTriangleTreeUI(UIValue::UIValue& MainUIValue)
{
    ImGui::SeparatorText("Triangles");

    if (ImGui::Button("Add Triangle"))
    {
        MainUIValue.TriangleTreeSize++;
        MainUIValue.TriangleTree.push_back(Common::Triangle());
    }

    for (int i = 0; i < MainUIValue.TriangleTreeSize; i++)
    {
        ImGui::PushID(MainUIValue.TriangleTreeSize + i);
        if (ImGui::TreeNode("", "Triangle%d", i))
        {
            bool RemoveButton = ImGui::Button("Remove");
            ImGui::InputFloat2("Pos0", MainUIValue.TriangleTree[i].Pos0);
            ImGui::InputFloat2("Pos1", MainUIValue.TriangleTree[i].Pos1);
            ImGui::InputFloat2("Pos3", MainUIValue.TriangleTree[i].Pos2);
            ImGui::ColorEdit4("Color", MainUIValue.TriangleTree[i].Color);

            if (RemoveButton)
            {
                MainUIValue.TriangleTree.erase(MainUIValue.TriangleTree.begin() + i);
                MainUIValue.TriangleTreeSize--;
                i--;
            }

            ImGui::TreePop();
        }
        ImGui::PopID();
    }
}

void RenderApp::RenderTriangleTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    for (Common::Triangle& Triangle : MainUIValue.TriangleTree)
    {
        ViewportRender.RenderTriangle(Triangle.Pos0, Triangle.Pos1, Triangle.Pos2, Triangle.Color);
    }
}

void RenderApp::RenderModelTreeUI(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    ImGui::SeparatorText("Models");

    if (ImGui::Button("Import Model"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose Model", ".obj");
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::cout << filePathName << std::endl;
            MainUIValue.ModelTree.push_back(Common::Model::readObj(filePathName));
            MainUIValue.ModelTreeSize++;
        }

        ImGuiFileDialog::Instance()->Close();
    }


    for (int i = 0; i < MainUIValue.ModelTreeSize; i++)
    {
        ImGui::PushID(MainUIValue.TriangleTreeSize + i);
        if (ImGui::TreeNode("", "Model%d", i))
        {
            if (ImGui::Button("Log Model"))
            {
                MainUIValue.ModelTree[i].LogModel();
            }
            ImGui::SameLine();
            bool RemoveButton = ImGui::Button("Remove");
            
            const char* items[] = { "None", "WireFrameShader" };
            static int item_current = 0;
            ImGui::Combo("Shader Type", &item_current, items, IM_ARRAYSIZE(items));

            if (item_current == 0)
            {
                MainUIValue.ModelTree[i].ModelShader = nullptr;
            }
            else if (item_current == 1)
            {
                MainUIValue.ModelTree[i].ModelShader = &ViewportRender.WireFrameShader;
            }
            ImGui::Checkbox("Show Axis", &MainUIValue.ModelTree[i].AxisIsShow);

            ImGui::InputFloat3("Translation", MainUIValue.ModelTree[i].Transform.Translation);
 
            ImGui::SliderFloat3("Rotation", MainUIValue.ModelTree[i].Transform.Rotation, -360, 360);

            ImGui::InputFloat3("Scale", MainUIValue.ModelTree[i].Transform.Scale);
            MainUIValue.ModelTree[i].ModelMatrix = MainUIValue.ModelTree[i].Transform.toMatrix();

            ImGui::Text("TexCoords Size: %d", MainUIValue.ModelTree[i].TexCoords.size());
            ImGui::Text("Normals Size: %d", MainUIValue.ModelTree[i].Normals.size());
            ImGui::Text("Vertices Size: %d", MainUIValue.ModelTree[i].Vertices.size());

            if (RemoveButton)
            {
                MainUIValue.ModelTree.erase(MainUIValue.ModelTree.begin() + i);
                MainUIValue.ModelTreeSize--;
                i--;
            }

            ImGui::TreePop();
        }
        ImGui::PopID();
    }
}

void RenderApp::RenderModelTreeToSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    // ModelTree Render
    for (Common::Model& Model : MainUIValue.ModelTree)
    {
        ViewportRender.RenderModel(Model);
    }
}

void RenderApp::RenderCameraUI(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    ImGui::SeparatorText("Camera Setting");

    ImGui::InputFloat3("Translation", ViewportRender.RenderCamera.Transform.Translation);
    ImGui::SliderFloat3("Rotation", ViewportRender.RenderCamera.Transform.Rotation, -360, 360);
    ImGui::InputFloat3("Scale", ViewportRender.RenderCamera.Transform.Scale);
    
    ImGui::Text("Fov: %f", ViewportRender.RenderCamera.Fov);
    ImGui::Text("Ratio: %f", ViewportRender.RenderCamera.Ratio);
    ImGui::Text("F: %f", ViewportRender.RenderCamera.F);
    ImGui::Text("N: %f", ViewportRender.RenderCamera.N);
}

void RenderApp::RenderSense(UIValue::UIValue& MainUIValue, Render::Renderer& ViewportRender)
{
    ImGui::Begin("Sence");

    ViewportRender.ClearFrameBuffer();

    // RenderPointTreeToSense
    RenderPointTreeToSense(MainUIValue, ViewportRender);
    
    // RenderLineTreeToSense
    RenderLineTreeToSense(MainUIValue, ViewportRender);
    
    // RenderTriangleTreeToSense
    RenderTriangleTreeToSense(MainUIValue, ViewportRender);
    
    // RenderModelTreeToSense
    RenderModelTreeToSense(MainUIValue, ViewportRender);

    ImVec2 WindowSize = ImGui::GetWindowSize();
    const int width = WindowSize.x - 15;
    const int height = WindowSize.y - 42;
    ViewportRender.RenderCamera.Ratio = (float)width / (float)height;
    ViewportRender.RenderCamera.UpdateCamera();

    // FinalRender From FrameBuffer
    ViewportRender.FinalRender();

    ImGui::End();
}
