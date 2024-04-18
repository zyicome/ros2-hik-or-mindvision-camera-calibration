#ifndef _DEVICE_BASE_H_
#define _DEVICE_BASE_H_

#include <pthread.h>
#include "../../include/HCUsbSDK.h"

#define PRINTF(value) printf("\t %d.%s.\r\n", value, (#value))

#define MAX_USB_DEV_LEN 64
#define BUFFER_LEN 1024 * 1024 
#define USB_UPGRADE_FAILED     0
#define USB_UPGRADE_SUCCESS    1
#define USB_UPGRADE_TRANS      2
#define USB_UPGRADE_FLASH_FAILED 4
#define USB_UPGRADE_TYPE_UNMATCH 5

//通用命令码
#define CUSTOM_PRINT_MENU				0
#define CUSTOM_GET_SDK_VERSION		  	(CUSTOM_PRINT_MENU+1)			//打印SDK版本号
#define CUSTOM_USB_INIT				  	(CUSTOM_PRINT_MENU+2)			//SDK初始化
#define CUSTOM_SET_LOGTOFILE		  	(CUSTOM_PRINT_MENU+3)			//开启SDK日志
#define CUSTOM_GET_DEVICE_COUNT		  	(CUSTOM_PRINT_MENU+4)			//获取设备数量
#define CUSTOM_ENUM_DEVICE			  	(CUSTOM_PRINT_MENU+5)			//枚举设备信息
#define CUSTOM_LOGIN_DEVICE			  	(CUSTOM_PRINT_MENU+6)			//登陆设备
#define CUSTOM_DEVICE_LOGOUT		  	(CUSTOM_PRINT_MENU+7)   		//注销
#define CUSTOM_CLEANUP 					(CUSTOM_PRINT_MENU+8)   		//反初始化

#define KEYBOARD_INPUT_FAILED   -1  //键盘输入失败或退出

//设备类型
#define CAMERA_DEVICE		1
#define ACS_DEVICE			2
#define THERMAL_DEVICE		3
// 稳定性场景
#define CAMERA_RECORD_THERMAL_PREVIEW 4	//前端录像+热成像预览
#define THERMAL_PREVIEW_CAMERA_RECORD 5	//热成像预览+前端录像
#define THERMAL_SET_CAMERA_CALLBACK	  6	//热成像参数配置+前端码流回调

const int CheckBoardInput();

class DeviceBase
{
public:
	DeviceBase();
	BOOL Start();
	virtual void Usage(void) = 0;
	virtual void UsbImplement() = 0;
	virtual void DoBusiness(int iType, int iDevIndex = 0) = 0;

	void GetDevInfo(int& iDevNum, LPUSB_DEVICE_INFO pDevInfo);
	void SetDevInfo(int iDevNum, LPUSB_DEVICE_INFO pDevInfo);

protected:
	void FuncGetSdkVersion();
	void FuncSdkInit();
    void SetLogFile();
	void FuncGetDeviceCount();
	void FuncEnumDevices();
	void FuncLoginDevices(int iDevIndex);
	void DeviceLogout();
	void FuncSdkCleanup();
	void SetSystemUpdateFirmware();
	void GetDeviceUpgradeState();
    void CloseUpgradeHandle();

protected:
	int m_iDevNum; //设备个数
	int m_lUserID;
	int m_nTimeout;
	bool m_bUpgrade;
	bool m_bResource;
	long m_lUpgradeHandle;
	pthread_t m_tid;
	bool m_bExit;	//子类退出标记
	USB_DEVICE_INFO m_aDevInfo[MAX_USB_DEV_LEN];
	USB_USER_LOGIN_INFO m_struCurUsbLoginInfo;
	USB_UPGRADE_STATE_INFO m_struUpgradeState;
};


#endif

