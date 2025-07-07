# SlayTheShrike

## 项目介绍

本项目基于 Qt 6.9.1 (win_mingw64) 完成，属于 Qt Widget 应用

浙江大学 短学期课程 课程综合实践 II （C++ 项目管理与工程实践） 袁昕老师 课程大作业

2025年7月8日

## 编译与运行

本项目的编译和运行仅在 ` Windows ` 下经过测试

- 使用 ` QT Creator ` 打开项目的 ` CmakeList.txt ` 文件，并借助 ` QT Creator ` 提供的图形界面完成编译

- 完全使用命令行进行编译，流程如下 (以下命令需要在 ` powershell ` 中运行)：

    - ` mkdir build; cd build `

    - ` cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="/path/to/Qt" -DCMAKE_CXX_COMPILER="/path/to/Qt/Tools/mingw1310_64/bin/g++.exe" .. `
      - 如：` D:\QT\Tools\CMake_64\bin\cmake.exe -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="D:/QT/6.9.1/mingw_64" -DCMAKE_CXX_COMPILER="D:/QT/Tools/mingw1310_64/bin/g++.exe" .. `

    - ` cmake --build . -j `

    - ` $env:Path += ";/path/to/Qt" ` (添加文件运行所需的动态链接库)
      - 如：` $env:Path += ";D:\QT\6.9.1\mingw_64\bin\" `

    - ` mkdir run `

    - ` Start-Process -WorkingDirectory ".\run" .\SlayTheShrike.exe ` (由于 Debug 代码的文件打开地址问题，需要调整文件的工作目录)

- 注意：请不要尝试使用其他版本的编译器，可能会带来意外错误
