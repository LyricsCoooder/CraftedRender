# CraftedRender

CraftedRender是一个主要基于DearImGui，手写渲染管线的练习项目，用于渲染管线，计算机图形学的学习与理解。

![Main Structure](Doc\Main Structure.png)

**模块：**

- Application
  - 用于渲染GUI和渲染场景视口，使用OpenGL作为渲染。

- Render
  - 手写渲染管线的主类，大部分渲染逻辑在这里实现。
- CommonStructure
  - 项目中经常使用的自建类型，包括 `Model` 和 `Shader`的定义。
- UIValue
  - 从UI面板获取数据流的主类，Render的数据上游，用于Application与Render之间的数据传递。

