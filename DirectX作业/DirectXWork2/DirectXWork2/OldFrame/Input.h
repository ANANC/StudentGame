#pragma once

#define DIRECTINPUT_VERSION 0x0800  

#include <dinput.h>

#define Safe_Release(object) if((object) != NULL) { (object)->Release(); (object)=NULL; }

#define ITEMS_NUM   10


static LPDIRECTINPUT8			pInput = NULL;				//DirectInput对象
BOOL CALLBACK Enum_Joystick(LPCDIDEVICEINSTANCE device_instance, LPVOID data);


class CInput
{
public:
	CInput(HINSTANCE hInstance);
public:
	~CInput(void);
private:
	bool bUseJoystick;
	HINSTANCE hInstance;

	LPDIRECTINPUTDEVICE8	pKeyboard;				//键盘设备对象
	LPDIRECTINPUTDEVICE8	pMouse;					//鼠标设备对象
	LPDIRECTINPUTDEVICE8	pJoystick;				//游戏杆设备对象

	char keyBuffer[256];							// 键盘数据缓冲 (immediate mode)
	char oldKeyBuffer[256];
	DIDEVICEOBJECTDATA mouseBuffer[ITEMS_NUM];    // 鼠标数据缓冲 (buffer mode)
	DIJOYSTATE2 joystickBuffer;                   // 游戏杆数据缓冲 (immediate mode)

	int mouseMoveX, mouseMoveY;    // mouse move coordinate
	int LClickDownX, LClickDownY;//新加上的鼠标左键点击位置
public:
	void CreateInput(HINSTANCE instance, HWND hwnd, int min = -100, int max = 100, 
		int nDeadZone = 20, bool bUseJoystick = false);

	bool ReadKeyboard();
	bool ReadMouse();
	bool ReadJoystick();
	bool IsLButtonPressed();
	bool IsRButtonPressed();    
	bool IsMButtonPressed();

	bool IsLButtonUp();
	bool IsRButtonUp();    
	bool IsMButtonUp();


	// 判断是否有按键按下
	bool IsKeyPressed(int key);
	//判断指定键是否抬起
	bool IsKeyUp(int key);

	int GetMouseX() { return mouseMoveX; }
	int GetMouseY() { return mouseMoveY; }

	// 判断游戏杆的某个按钮是否按下
	bool IsJSButtonPressed(int button)
	{
		return (joystickBuffer.rgbButtons[button] & 0x80) ? true : false;
	}
private:
	bool CreateDirectinput(HINSTANCE instance);							//创建DirectInput对象
	bool CreateKeyboard(HWND hwnd);										//创建键盘设备对象
	bool CreateMouse(HWND hwnd);										//创建鼠标设备对象
	bool CreateJoystick(HWND hwnd, int min, int max, int nDeadZone);	//创建游戏杆对象
	void ReleaseInput();												//释放所创建的对象

};
