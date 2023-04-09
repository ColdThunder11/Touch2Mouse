# Touch2Mouse
Convert windows touch tap message to mouse left click  
将触摸形式的鼠标时间转换为鼠标左键点击
## Introduction
It seems that the behavior of touch tap to WM_LBUTTONUP and WM_LBUTTONDOWN has a lot of different to normal mouse click, it may make some old games unhappy and not work as expected.  
## Usage
Download it from Release, run it and put console in backstage, it will still work until you close the console window. Install [Microsoft Visual C++ Redistributable for Visual Studio 2015, 2017, 2019, and 2022 x64](https://aka.ms/vs/17/release/vc_redist.x64.exe) if missing dll on start up.  
***
## 介绍
部分老游戏对触摸形式输入处理有问题导致win板无法正常进行游戏（影响我推gal了），所以写了个小玩具处理这种情况
## Usage
从Release下载程序，打开后最小化在后台就行，不关掉都一直有效。如果打开时报缺少DLL，请下载[VC++运行库](https://aka.ms/vs/17/release/vc_redist.x64.exe)。