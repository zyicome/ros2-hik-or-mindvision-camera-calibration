#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "DeviceBase.h"


const int CheckBoardInput()
{
	int iInput = KEYBOARD_INPUT_FAILED;
	char ch = ' ';
	if (scanf("%d", &iInput) != EOF)
	{
		while ((ch = getchar()) != '\n' && ch != EOF)
		{
			if ('q' == ch)
			{
				return KEYBOARD_INPUT_FAILED;
			}
		}
	}
	return iInput;
}

DeviceBase::DeviceBase()
	: m_iDevNum(0)
	, m_lUserID(USB_INVALID_USERID)
	, m_nTimeout(60)
	, m_bUpgrade(FALSE)
	, m_bResource(FALSE)
	, m_lUpgradeHandle(USB_INVALID_UPGRADE_HANDLE)
    , m_tid(0)
	, m_bExit(FALSE)
{
	memset(m_aDevInfo, 0, MAX_USB_DEV_LEN);
	memset(&m_struCurUsbLoginInfo, 0, sizeof(m_struCurUsbLoginInfo));
	memset(&m_struUpgradeState, 0, sizeof(m_struUpgradeState));
}

BOOL DeviceBase::Start()
{
	if(m_bResource)
	{
		m_bExit = FALSE;
		Usage();
		UsbImplement();
	}
	return m_bResource;
}


void DeviceBase::Usage(void)
{
}

void DeviceBase::UsbImplement()
{
}

void DeviceBase::FuncGetSdkVersion()
{
	unsigned int dwVersion = USB_GetSDKVersion();
	printf("HCUSBSDK V%d.%d.%d.%d\r\n", 
			(0xff000000 & dwVersion) >> 24, 
			(0x00ff0000 & dwVersion) >> 16, 
			(0x0000ff00 & dwVersion) >> 8, 
			(0x000000ff & dwVersion));//%.d,0x0000ff & dwVersion,build NO. do not expose
}

void DeviceBase::FuncSdkInit()
{
	if (!USB_Init())
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_Init() ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_Init()\r\n");
	}
}

void DeviceBase::FuncGetDeviceCount()
{
	m_iDevNum = USB_GetDeviceCount();
	printf("DeviceCount %d\r\n", m_iDevNum);
}

void DeviceBase::FuncEnumDevices()
{
    if (0 == m_iDevNum)
    {
        printf("FAILED USB_EnumDevices()  DeviceCount %d\r\n", m_iDevNum);
        return;
    }
    if (USB_EnumDevices(m_iDevNum, &m_aDevInfo[0]))
    {
        printf("SUCCESS USB_EnumDevices()\r\n");
        printf("dwVID [%x] dwPID [%x]\r\n", m_aDevInfo[0].dwVID, m_aDevInfo[0].dwPID);
    }
    else
    {
        printf("failed USB_EnumDevices()  err[%d]\r\n", USB_GetLastError());
    }
}

void DeviceBase::FuncLoginDevices(int iDevIndex)
{
	USB_DEVICE_INFO struUsbDeviceInfo = { 0 };
	USB_DEVICE_REG_RES struDeviceRegRes = { 0 };

	struUsbDeviceInfo.dwSize = sizeof(USB_DEVICE_INFO);
	memcpy(&struUsbDeviceInfo, &m_aDevInfo[iDevIndex], sizeof(USB_DEVICE_INFO));

	memset(&m_struCurUsbLoginInfo, 0, sizeof(m_struCurUsbLoginInfo));
	m_struCurUsbLoginInfo.dwSize = sizeof(USB_USER_LOGIN_INFO);
	m_struCurUsbLoginInfo.dwTimeout = 5000;
	m_struCurUsbLoginInfo.dwVID = struUsbDeviceInfo.dwVID;
	m_struCurUsbLoginInfo.dwPID = struUsbDeviceInfo.dwPID;

	memcpy(m_struCurUsbLoginInfo.szSerialNumber, struUsbDeviceInfo.szSerialNumber, MAX_SERIAL_NUMBER_LEN);
	memcpy(m_struCurUsbLoginInfo.szUserName, "admin", strlen("admin"));
	memcpy(m_struCurUsbLoginInfo.szPassword, "12345", strlen("12345"));
	m_struCurUsbLoginInfo.byLoginMode = 1;

	struDeviceRegRes.dwSize = sizeof(struDeviceRegRes);

	m_lUserID = USB_Login(&m_struCurUsbLoginInfo, &struDeviceRegRes);
	printf("Login m_lUserID = [%d]\r\n", m_lUserID);
	if (USB_INVALID_USERID == m_lUserID)
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_Login() ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_Login() \r\nDevice Register Information:\r\n Deviec Name:%s\r\n Device Serial Number:%s\r\n", struDeviceRegRes.szDeviceName, struDeviceRegRes.szSerialNumber);
		printf("error code [%d]\r\n", USB_GetLastError()); //缺陷测试
	}
}

void DeviceBase::DeviceLogout()
{
	if (!USB_Logout(m_lUserID))
    {
        DWORD dwError = USB_GetLastError();
        printf("FAILED USB_Logout() ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
    }
    else
    {
    	printf("SUCCESS USB_Logout()\r\n[%d]", m_lUserID);
    }
}

void DeviceBase::SetLogFile()
{
	const char* szLogPath = "./USBSDKLog";
	if (!USB_SetLogToFile(3, szLogPath, TRUE))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SetLogToFile() ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SetLogToFile()\r\n");
	}
}

void DeviceBase::FuncSdkCleanup()
{
	if (!USB_Cleanup())
	{
		printf("usb_cleanup failed. Error code [%d]\r\n", USB_GetLastError());
	}
	else
	{
		printf("usb_cleanup success.\r\n");
	}
}

void DeviceBase::SetSystemUpdateFirmware()
{
	if (m_bUpgrade)
	{
		printf("Device Upgrading......\r\n");
		printf("Press 50 to check Update states...\r\n");
		return;
	}
	if (m_nTimeout < 15 || m_nTimeout > 255)
	{
		printf("Timeout time range should between 15(include) and 255(include)\r\n");
		return;
	}

	USB_UPGRADE_COND struUpgradeCond = { 0 };
	struUpgradeCond.dwSize = sizeof(struUpgradeCond);
	struUpgradeCond.byTimeout = m_nTimeout;
	char szFilePatch[256] = "./USBSDKLog/digicap.dav";
	DWORD dwError = 0;
	m_lUpgradeHandle = USB_Upgrade(m_lUserID, 0, szFilePatch, &struUpgradeCond, sizeof(struUpgradeCond));
	if (-1 == m_lUpgradeHandle)
	{
		dwError = USB_GetLastError();
		printf("FAILED USB_Upgrade ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		m_bUpgrade = TRUE;
		printf("SUCCESS USB_Upgrade() upgrading...\r\n");
		printf("Press 50 to check Update states...\r\n");
	}
}

void DeviceBase::CloseUpgradeHandle()
{
	if (m_bUpgrade)
	{
		if (!USB_CloseUpgradeHandle(m_lUpgradeHandle))
		{
			printf("FAILED USB_CloseUpgradeHandle, errorcode [%d]\r\n", USB_GetLastError());
		}
		else
		{
			m_bUpgrade = FALSE;	
			sleep(2);
			pthread_join(m_tid, NULL);	
			printf("success USB_CloseUpgradeHandle\r\n");				
		}
	}
    m_lUpgradeHandle = USB_INVALID_UPGRADE_HANDLE;
}

void DeviceBase::GetDeviceUpgradeState()
{
	if (!m_bUpgrade)
	{
		printf("Not upgrading...\r\n");
	}

	//TODO：开启线程关闭升级  //其他功能需判断升级状态
	if (!USB_GetUpgradeState(m_lUpgradeHandle, &m_struUpgradeState))
	{
		m_bUpgrade = FALSE;
		printf("FAILED USB_SDK_GetUpgradeState\r\n");
		DWORD dwError = USB_GetLastError();
		printf("m_lUpgradeHandle = [%ld] byState = [%d], byProgress = [%d]\r\n", m_lUpgradeHandle, m_struUpgradeState.byState, m_struUpgradeState.byProgress);
		
		printf("ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("m_lUpgradeHandle = [%ld] byState = [%d], byProgress = [%d]\r\n", m_lUpgradeHandle, m_struUpgradeState.byState, m_struUpgradeState.byProgress);
		switch (m_struUpgradeState.byState)
		{
		case USB_UPGRADE_FAILED:
		{
			printf("Upgrade failed\r\n");
			DWORD dwError = USB_GetLastError();
			printf("ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
			m_bUpgrade = FALSE;
			break;
		}
		case USB_UPGRADE_SUCCESS:
		{
			m_bUpgrade = FALSE;
			printf("SUCCESS Upgrade\r\n");
			printf("Before operate this device,please enum and login device again\r\n");
			break;
		}
		case USB_UPGRADE_TRANS:
		{
			printf("Upgrade packet transferring...\r\n");
			//sleep(1);
			break;
		}
		case USB_UPGRADE_FLASH_FAILED:
		{
			m_bUpgrade = FALSE;
			printf("Upgrade write flash failed\r\n");
			DWORD dwError = USB_GetLastError();
			printf("ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
			break;
		}
		case USB_UPGRADE_TYPE_UNMATCH:
		{
			m_bUpgrade = FALSE;
			printf("Upgrade type unmatch\r\n");
			DWORD dwError = USB_GetLastError();
			printf("ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
			break;
		}
		default:
		{
			m_bUpgrade = FALSE;
			printf("Error Unknown upgrade status\r\n");
			DWORD dwError = USB_GetLastError();
			printf("ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
			break;
		}
		}
	}
}

void DeviceBase::GetDevInfo(int& iDevNum, LPUSB_DEVICE_INFO pDevInfo)
{
	iDevNum = m_iDevNum;
	memcpy(pDevInfo, m_aDevInfo, sizeof(USB_DEVICE_INFO) * MAX_USB_DEV_LEN);
}

void DeviceBase::SetDevInfo(int iDevNum, LPUSB_DEVICE_INFO pDevInfo)
{
	m_iDevNum = iDevNum;
	memcpy(m_aDevInfo, pDevInfo, sizeof(USB_DEVICE_INFO) * MAX_USB_DEV_LEN);
}
