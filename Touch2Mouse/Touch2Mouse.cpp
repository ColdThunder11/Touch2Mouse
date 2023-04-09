// Touch2Mouse.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <shellscalingapi.h>
#include <TlHelp32.h>
#include <stdlib.h>

const LONG_PTR c_SIGNATURE_MASK = 0xFFFFFF00;
const LONG_PTR c_MOUSEEVENTF_FROMTOUCH = 0xFF515700;

static HHOOK hook;

DWORD WINAPI SendLBClick(LPVOID lpParameter) {
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lpParameter; // WH_MOUSE_LL struct
	SetCursorPos(pMouseStruct->pt.x, pMouseStruct->pt.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(30);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	//pMouseStruct->dwExtraInfo = 0;

	//INPUT inputs[1] = {};
	//ZeroMemory(inputs, sizeof(inputs));
	//inputs[0].type = INPUT_MOUSE;
	//inputs[0].mi.dx = pMouseStruct->pt.x;
	//inputs[0].mi.dy = pMouseStruct->pt.y;
	//inputs[0].mi.mouseData = 0;
	//inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
	//UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

	//if (uSent != ARRAYSIZE(inputs))
	//{
	//	std::cout << "SendInput failed: 0x" << HRESULT_FROM_WIN32(GetLastError()) << std::endl;;
	//}
	//else
	//{
	//	std::cout << "Success" << std::endl;
	//}
	return 0;
}


LRESULT WINAPI MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam; // WH_MOUSE_LL struct
	if (nCode == 0) { // we have information in wParam/lParam ? If yes, let's check it:
		if(pMouseStruct == NULL) return CallNextHookEx(hook, nCode, wParam, lParam);

		bool isTouch = (pMouseStruct->dwExtraInfo & c_SIGNATURE_MASK) == c_MOUSEEVENTF_FROMTOUCH;

		//if (pMouseStruct != NULL) { // Mouse struct contain information?			
		//	std::cout << "Mouse Coordinates: x = " << pMouseStruct->pt.x << " | y = " << pMouseStruct->pt.y <<" \n";
		//}

		switch (wParam) {

		case WM_LBUTTONUP: {
			if (isTouch) {
				std::cout << "Touch event ";
			}
			std::cout << "LEFT CLICK UP\n";
			std::cout << "Mouse Coordinates: x = " << pMouseStruct->pt.x << " | y = " << pMouseStruct->pt.y << " \n";
			if (isTouch) return 1;			
		}break;
		case WM_LBUTTONDOWN: {
			if (isTouch) {
				std::cout << "Touch event ";
			}
			std::cout << "LEFT CLICK DOWN\n";
			std::cout << "Mouse Coordinates: x = " << pMouseStruct->pt.x << " | y = " << pMouseStruct->pt.y << " \n";
			if (isTouch) {
				CreateThread(NULL, NULL, SendLBClick, pMouseStruct, 0, NULL);
				return 1;
			}
		}break;
		case WM_RBUTTONUP: {
			std::cout << "RIGHT CLICK UP\n";
		}break;
		case WM_RBUTTONDOWN: {
			std::cout << "RIGHT CLICK DOWN\n";
		}break;
		case WM_CHAR: {
			std::cout << wParam;
		}break;

		}

	}

	/*
	Every time that the nCode is less than 0 we need to CallNextHookEx:
	-> Pass to the next hook
	MSDN: Calling CallNextHookEx is optional, but it is highly recommended;
	otherwise, other applications that have installed hooks will not receive hook notifications and may behave incorrectly as a result.
	*/
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
int main(int argc, char* argv[])
{
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);//禁用系统高dpi缩放使设置鼠标指针位置正确
	if (!(hook = SetWindowsHookEx(WH_MOUSE_LL, MyMouseCallback, GetModuleHandle(NULL), 0))) {
		std::cout << "Error: " << GetLastError() << std::endl;
		return -1;
	}
    //std::cout << "Hello World!\n";
	MSG msg{};
	while (msg.message != WM_QUIT) { //while we do not close our application
		if (GetMessage(&msg, NULL, 0, 0)) {
			//TranslateMessage(&msg);
			//DispatchMessage(&msg);
		}
		//Sleep(1);
	}
	UnhookWindowsHookEx(hook);
	return (int)msg.wParam; //return the messages
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
