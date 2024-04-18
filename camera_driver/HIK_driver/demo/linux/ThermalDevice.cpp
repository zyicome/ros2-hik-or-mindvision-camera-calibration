#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ThermalDevice.h"

using namespace std;

ThermalDevice::ThermalDevice()
	: fd(NULL)
{
	m_pGetStream = new CGetStream(THERMAL_DEVICE);
	m_bResource = (m_pGetStream != NULL);
}


void ThermalDevice::Usage(void)
{
	printf("Select Thermal Capacity:\r\n");
	PRINTF(CUSTOM_PRINT_MENU);
	PRINTF(CUSTOM_GET_SDK_VERSION);
	PRINTF(CUSTOM_USB_INIT);
	PRINTF(CUSTOM_SET_LOGTOFILE);
	PRINTF(CUSTOM_GET_DEVICE_COUNT);
	PRINTF(CUSTOM_ENUM_DEVICE);
	PRINTF(CUSTOM_LOGIN_DEVICE);
	PRINTF(CUSTOM_DEVICE_LOGOUT);
	PRINTF(CUSTOM_CLEANUP);
	PRINTF(THERMAL_GET_SYSTEM_DEVICE_INFO);
	PRINTF(THERMAL_SET_SYSTEM_REBOOT);
	PRINTF(THERMAL_SET_SYSTEM_RESET);
	PRINTF(THERMAL_GET_SYSTEM_HARDWARE_SERVER);
	PRINTF(THERMAL_SET_SYSTEM_HARDWARE_SERVER);
	PRINTF(THERMAL_GET_SYSTEM_LOCALTIME);
	PRINTF(THERMAL_SET_SYSTEM_LOCALTIME);
	PRINTF(THERMAL_GET_IMAGE_BRIGHTNESS);
	PRINTF(THERMAL_SET_IMAGE_BRIGHTNESS);
	PRINTF(THERMAL_GET_IMAGE_CONTRAST);
	PRINTF(THERMAL_SET_IMAGE_CONTRAST);
	PRINTF(THERMAL_SET_SYSTEM_UPDATE_FIRMWARE);
	PRINTF(THERMAL_SET_IMAGE_BACKGROUND_CORRECT);
	PRINTF(THERMAL_GET_SYSTEM_DIAGNOSED_DATA);
	PRINTF(THERMAL_SET_IMAGE_MANUAL_CORRECT);
	PRINTF(THERMAL_GET_IMAGE_ENHANCEMENT);
	PRINTF(THERMAL_SET_IMAGE_ENHANCEMENT);
	PRINTF(THERMAL_GET_IMAGE_VIDEO_ADJUST);
	PRINTF(THERMAL_SET_IMAGE_VIDEO_ADJUST);
	PRINTF(THERMAL_GET_THERMOMETRY_BASIC_PARAM);
	PRINTF(THERMAL_SET_THERMOMETRY_BASIC_PARAM);
	PRINTF(THERMAL_GET_THERMOMETRY_MODE);
	PRINTF(THERMAL_SET_THERMOMETRY_MODE);
	PRINTF(THERMAL_GET_THERMOMETRY_REGIONS);
	PRINTF(THERMAL_SET_THERMOMETRY_REGIONS);
	PRINTF(THERMAL_GET_THERMAL_ALG_VERSION);
	PRINTF(THERMAL_GET_THERMAL_STREAM_PARAM);
	PRINTF(THERMAL_SET_THERMAL_STREAM_PARAM);
	PRINTF(THERMAL_GET_TEMPERATURE_CORRECT);
	PRINTF(THERMAL_SET_TEMPERATURE_CORRECT);
	PRINTF(THERMAL_GET_BLACK_BODY);
	PRINTF(THERMAL_SET_BLACK_BODY);
	PRINTF(THERMAL_GET_BODYTEMP_COMPENSATION);
	PRINTF(THERMAL_SET_BODYTEMP_COMPENSATION);
	PRINTF(THERMAL_GET_JPEGPIC_WITH_APPENDDATA);
	PRINTF(THERMAL_GET_ROI_MAX_TEMPERATURE_SEARCH);
	PRINTF(THERMAL_GET_P2P_PARAM);
	PRINTF(THERMAL_SET_P2P_PARAM);
	PRINTF(THERMAL_POST_DOUBLE_LIGHTS_CORRECT);
	PRINTF(THERMAL_GET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL);
	PRINTF(THERMAL_SET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL);
	PRINTF(THERMAL_GET_THERMOMETRY_CALIBRATION_FILE);
	PRINTF(THERMAL_SET_THERMOMETRY_CALIBRATION_FILE);
	PRINTF(THERMAL_GET_DEVICE_UPGRADE_STATE);
	PRINTF(THERMAL_CLOSE_UPGRADE);
	PRINTF(THERMAL_GET_COMMAND_STATE);
	PRINTF(CUSTOM_STREAM_CALLBACK);
	PRINTF(CUSTOM_STREAM_RECORD);
	PRINTF(CUSTOM_STREAM_PREVIEW);
	printf("\t Press q to quit...\r\n");
}

void ThermalDevice::UsbImplement()
{
	while (!m_bExit)
	{
		int iIn = CheckBoardInput();
		DoBusiness(iIn);
    }
	delete m_pGetStream;
	m_pGetStream = NULL;
}

void ThermalDevice::DoBusiness(int iType, int iDevIndex)
{
	switch (iType)
	{
		case KEYBOARD_INPUT_FAILED:
		{
			printf("Thermal Device Exit...\r\n");
			m_bExit = TRUE;
			break;
		}
		case THERMAL_CLOSE_UPGRADE: //关闭升级 
		{
			CloseUpgradeHandle();
			break;
		}
		case CUSTOM_CLEANUP: //反初始化
		{	
			FuncSdkCleanup();
			break;
		}
		case CUSTOM_PRINT_MENU:
		{
			Usage();
			break;
		}
		case CUSTOM_GET_SDK_VERSION: //打印SDK版本号
		{
			FuncGetSdkVersion();
			break;
		}
		case CUSTOM_USB_INIT: //SDK初始化
		{
			FuncSdkInit();
			break;
		}
		case CUSTOM_SET_LOGTOFILE: //开启SDK日志
		{
			SetLogFile();
			break;
		}
		case CUSTOM_GET_DEVICE_COUNT: //获取设备数量
		{
			FuncGetDeviceCount();
			break;
		}
		case CUSTOM_ENUM_DEVICE: //枚举设备信息
		{
			FuncEnumDevices();
			break;
		}
		case CUSTOM_LOGIN_DEVICE: //登陆设备
		{
			FuncLoginDevices(iDevIndex);
			m_pGetStream->SetUserID(m_lUserID);
			break;
		}
		case THERMAL_GET_SYSTEM_DEVICE_INFO: //获取设备信息
		{
			GetSystemDeviceInfo();
			break;
		}
		case THERMAL_SET_SYSTEM_REBOOT: //设备重启
		{
			SetSystemReboot();
			break;
		}
		case THERMAL_SET_SYSTEM_RESET: //恢复默认
		{
			SetSystemReset();
			break;
		}
		case THERMAL_GET_SYSTEM_HARDWARE_SERVER: // 获取硬件服务参数
		{
			GetSystemHardwareServer();
			break;
		}
		case THERMAL_SET_SYSTEM_HARDWARE_SERVER: // 设置硬件服务参数
		{
			SetSystemHardwareServer();
			break;
		}
		case THERMAL_GET_SYSTEM_LOCALTIME: //获取系统本地时间
		{
			GetSystemLocalTime();
			break;
		}
		case THERMAL_SET_SYSTEM_LOCALTIME: //设置系统本地时间
		{
			SetSystemLocalTime();
			break;
		}
		case THERMAL_GET_IMAGE_BRIGHTNESS: //获取图像亮度参数
		{
			GetImageBrightness();
			break;
		}
		case THERMAL_SET_IMAGE_BRIGHTNESS: //设置图像亮度参数
		{
			SetImageBrightness();
			break;
		}
		case THERMAL_GET_IMAGE_CONTRAST: //获取图像对比度参数
		{
			GetImageContrast();
			break;
		}
		case THERMAL_SET_IMAGE_CONTRAST: //设置图像对比度参数
		{
			SetImageContrast();
			break;
		}
		case THERMAL_SET_SYSTEM_UPDATE_FIRMWARE: // 设备升级
		{
			SetSystemUpdateFirmware();
			GetDeviceUpgradeState();
			break;
		}
		case THERMAL_SET_IMAGE_BACKGROUND_CORRECT: //一键背景校正
		{
			SetImageBackgroundCorrect();
			break;
		}
		case THERMAL_GET_SYSTEM_DIAGNOSED_DATA: //诊断信息导出
		{
			GetSystemDiagnoseData();
			break;
		}
		case THERMAL_SET_IMAGE_MANUAL_CORRECT: //一键手动校正
		{
			SetImageManualCorrect();
			break;
		}
		case THERMAL_GET_IMAGE_ENHANCEMENT: // 获取图像增强参数
		{
			GetImageEnhance();
			break;
		}
		case THERMAL_SET_IMAGE_ENHANCEMENT: //设置图像增强参数
		{
			SetImageEnhancement();
			break;
		}
		case THERMAL_GET_IMAGE_VIDEO_ADJUST: //获取视频调整参数
		{
			GetImageVideoAdjust();
			break;
		}
		case THERMAL_SET_IMAGE_VIDEO_ADJUST: //设置视频调整参数
		{
			SetImageVideoAdjust();
			break;
		}
		case THERMAL_GET_THERMOMETRY_BASIC_PARAM: // 获取测温基本参数
		{
			GetThermometryBasicParam();
			break;
		}
		case THERMAL_SET_THERMOMETRY_BASIC_PARAM: // 设置测温基本参数
		{
			SetThermometryBasicParam();
			break;
		}
		case THERMAL_GET_THERMOMETRY_MODE: //获取测温模式
		{
			GetThermometryMode();
			break;
		}
		case THERMAL_SET_THERMOMETRY_MODE: //设置测温模式
		{
			SetThermometryMode();
			break;
		}
		case THERMAL_GET_THERMOMETRY_REGIONS: // 获取测温规则参数
		{
			GetThermometryRegions();
			break;
		}
		case THERMAL_SET_THERMOMETRY_REGIONS: //设置测温规则参数
		{
			SetThermometryRegions();
			break;
		}
		case THERMAL_GET_THERMAL_ALG_VERSION: //获取热成像相关算法版本信息
		{
			GetThermalAlgVersion();
			break;
		}
		case THERMAL_GET_THERMAL_STREAM_PARAM: // 获取热成像码流参数
		{
			GetThermalStreamParam();
			break;
		}
		case THERMAL_SET_THERMAL_STREAM_PARAM: // 设置热成像码流参数
		{
			SetThermalStreamParam();
			break;
		}
		case THERMAL_GET_TEMPERATURE_CORRECT: //获取测温修正参数
		{
			GetTemperatureCorrect();
			break;
		}
		case THERMAL_SET_TEMPERATURE_CORRECT: //设置测温修正参数
		{
			SetTemperatureCorrect();
			break;
		}
		case THERMAL_GET_BLACK_BODY: //获取黑体参数
		{
			GetBlackBody();
			break;
		}
		case THERMAL_SET_BLACK_BODY: //设置黑体参数
		{
			SetBlackBody();
			break;
		}
		case THERMAL_GET_BODYTEMP_COMPENSATION: // 获取体温补偿参数
		{
			GetBodytempCompensation();
			break;
		}
		case THERMAL_SET_BODYTEMP_COMPENSATION: //设置体温补偿参数
		{
			SetBodytempCompensation();
			break;
		}
		case THERMAL_GET_JPEGPIC_WITH_APPENDDATA: // 获取热图
		{
			GetJpegpicWithAppenddata();
			break;
		}
		case THERMAL_GET_ROI_MAX_TEMPERATURE_SEARCH: //roi最高温信息查询
		{
			GetRoiMaxTemperatureSearch();
			break;
		}
		case THERMAL_GET_P2P_PARAM: //获取全屏测温参数
		{
			GetP2PParam();
			break;
		}
		case THERMAL_SET_P2P_PARAM: //设置全屏测温参数
		{
			SetP2PParam();
			break;
		}
		case THERMAL_POST_DOUBLE_LIGHTS_CORRECT: //双光校准
		{
			PostDoubleLightsCorrect();
			break;
		}
		case THERMAL_GET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL: //获取双光校准坐标控制参数
		{
			GetDoubleLightsCorrectPointsCtrl();
			break;
		}
		case THERMAL_SET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL: //设置双光校准坐标控制参数
		{
			SetDoubleLightsCorrectPointCtrl();
			break;
		}
		case THERMAL_GET_THERMOMETRY_CALIBRATION_FILE: //测温标定文件导出
		{
			GetThermometryCalibrationFile();
			break;
		}
		case THERMAL_SET_THERMOMETRY_CALIBRATION_FILE: //测温标定文件导入
		{
			SetThermometryCalibrationFile();
			break;
		}
		case THERMAL_GET_DEVICE_UPGRADE_STATE:  // 获取设备升级状态
		{
			GetDeviceUpgradeState();
			break;
		}
		case CUSTOM_STREAM_CALLBACK:	//码流回调
		{
			m_pGetStream->StartStreamCallback();
			break;
		}
		case CUSTOM_DEVICE_LOGOUT:	//登出
		{
			DeviceLogout();
			break;
		}
		case CUSTOM_STREAM_RECORD:	//录像
		{
			m_pGetStream->StartStreamRecord();
			break;
		}
		case CUSTOM_STREAM_PREVIEW:	//预览
		{
			m_pGetStream->StartStreamPreview();
			break;
		}
		case THERMAL_GET_COMMAND_STATE:	//获取命令状态
		{
			GetCommandState();
			break;
		}
		default:
		{
			printf("FAILED Unsupported\r\n");
			break;
		}
	}
}

void ThermalDevice::GetSystemDeviceInfo()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_SYSTEM_DEVICE_INFO struSysDevInfo = { 0 };

	struSysDevInfo.dwSize = sizeof(struSysDevInfo);
	struConfigOutputInfo.lpOutBuffer = &struSysDevInfo;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struSysDevInfo);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_SYSTEM_DEVICE_INFO, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_SYSTEM_DEVICE_INFO ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_SYSTEM_DEVICE_INFO byDeviceType[%s] byEncoderVersion[%s]  byFirmwareVersion[%s] byHardwareVersion[%s] byProtocolVersion[%s]\r\n",
			struSysDevInfo.byDeviceType, struSysDevInfo.byEncoderVersion, struSysDevInfo.byFirmwareVersion, struSysDevInfo.byHardwareVersion, struSysDevInfo.byProtocolVersion);
	}
}

void ThermalDevice::SetSystemReboot()
{
	if (!USB_Control(m_lUserID, USB_SET_SYSTEM_REBOOT, NULL))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_SYSTEM_REBOOT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_SYSTEM_REBOOT\r\n");
	}
}

void ThermalDevice::SetSystemReset()
{
	if (!USB_Control(m_lUserID, USB_SET_SYSTEM_RESET, NULL))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_SYSTEM_RESET ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_SYSTEM_RESET\r\n");
	}
}

void ThermalDevice::GetSystemHardwareServer()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_SYSTEM_HARDWARE_SERVER struHardware = { 0 };

	struHardware.dwSize = sizeof(struHardware);
	struConfigOutputInfo.lpOutBuffer = &struHardware;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struHardware);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_SYSTEM_HARDWARE_SERVER, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_SYSTEM_HARDWARE_SERVER ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_SYSTEM_HARDWARE_SERVER byUsbMode[%d]\r\n", struHardware.byUsbMode);
	}
}

void ThermalDevice::SetSystemHardwareServer()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_SYSTEM_HARDWARE_SERVER struHardware = { 0 };

	struHardware.dwSize = sizeof(struHardware);
	struHardware.byUsbMode = 1; //设置为uvc模式
	struConfigInputInfo.lpInBuffer = &struHardware;
	struConfigInputInfo.dwInBufferSize = sizeof(struHardware);
	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_SYSTEM_HARDWARE_SERVER, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_SYSTEM_HARDWARE_SERVER ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_SYSTEM_HARDWARE_SERVER byUsbMode[%d]\r\n", struHardware.byUsbMode);
	}
}

void ThermalDevice::GetSystemLocalTime()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_SYSTEM_LOCALTIME struSysTime = { 0 };

	struSysTime.dwSize = sizeof(struSysTime);
	struConfigOutputInfo.lpOutBuffer = &struSysTime;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struSysTime);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_SYSTEM_LOCALTIME, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_SYSTEM_LOCALTIME ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_SYSTEM_LOCALTIME time[%d-%d-%d %d:%d:%d.%d]\r\n",
			struSysTime.wYear, struSysTime.byMonth, struSysTime.byDay, struSysTime.byHour, struSysTime.byMinute, struSysTime.bySecond, struSysTime.wMillisecond);
	}
	struConfigInputInfo.lpInBuffer = &struSysTime;
	struConfigInputInfo.dwInBufferSize = sizeof(struSysTime);
	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_SYSTEM_LOCALTIME, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_SYSTEM_LOCALTIME ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_SYSTEM_LOCALTIME time[%d-%d-%d %d:%d:%d.%d]\r\n",
			struSysTime.wYear, struSysTime.byMonth, struSysTime.byDay, struSysTime.byHour, struSysTime.byMinute, struSysTime.bySecond, struSysTime.wMillisecond);
	}
}

void ThermalDevice::SetSystemLocalTime()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_SYSTEM_LOCALTIME struSysTime = { 0 };

	//GetLocalTime(&sys);
	//linux下wMillisecond为0； 
	time_t tNow = time(NULL);
	struct tm *pLocalTime = NULL;
	pLocalTime = localtime(&tNow);
	struSysTime.wYear = pLocalTime->tm_year + 1900;
	struSysTime.byMonth = pLocalTime->tm_mon + 1;
	struSysTime.byDay = pLocalTime->tm_wday;
	struSysTime.byHour = pLocalTime->tm_hour;
	struSysTime.byMinute = pLocalTime->tm_min;
	struSysTime.bySecond = pLocalTime->tm_sec;
	struSysTime.wMillisecond = 0;
	struSysTime.byExternalTimeSourceEnabled = 0; //关闭外部校时
	struSysTime.dwSize = sizeof(struSysTime);
	struConfigInputInfo.lpInBuffer = &struSysTime;
	struConfigInputInfo.dwInBufferSize = sizeof(struSysTime);
	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_SYSTEM_LOCALTIME, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_SYSTEM_LOCALTIME ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_SYSTEM_LOCALTIME time[%d-%d-%d %d:%d:%d.%d]\r\n",
			struSysTime.wYear, struSysTime.byMonth, struSysTime.byDay, struSysTime.byHour, struSysTime.byMinute, struSysTime.bySecond, struSysTime.wMillisecond);
	}
}

void ThermalDevice::GetImageBrightness()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_BRIGHTNESS struImageBrightness = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);
	struConfigOutputInfo.lpOutBuffer = &struImageBrightness;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struImageBrightness);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_IMAGE_BRIGHTNESS, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_IMAGE_BRIGHTNESS ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_IMAGE_BRIGETNESS dwBrightness[%d]\r\n", struImageBrightness.dwBrightness);
	}
}

void ThermalDevice::SetImageBrightness()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_BRIGHTNESS struImageBrightness = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struImageBrightness.dwBrightness = 50; //亮度50
	struConfigInputInfo.lpInBuffer = &struImageBrightness;
	struConfigInputInfo.dwInBufferSize = sizeof(struImageBrightness);
	if (!USB_GetDeviceConfig(m_lUserID, USB_SET_IMAGE_BRIGHTNESS, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_IMAGE_BRIGHTNESS ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_IMAGE_BRIGHTNESS dwBrightness[%d]\r\n", struImageBrightness.dwBrightness);
	}
}

void ThermalDevice::GetImageContrast()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_CONTRAST struImageContrast = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);
	struConfigOutputInfo.lpOutBuffer = &struImageContrast;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struImageContrast);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_IMAGE_CONTRAST, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_IMAGE_CONTRAST ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_IMAGE_CONTRAST dwContrast[%d]\r\n", struImageContrast.dwContrast);
	}
}

void ThermalDevice::SetImageContrast()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_CONTRAST struImageContrast = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struImageContrast.dwContrast = 50; //对比度50
	struConfigInputInfo.lpInBuffer = &struImageContrast;
	struConfigInputInfo.dwInBufferSize = sizeof(struImageContrast);
	if (!USB_GetDeviceConfig(m_lUserID, USB_SET_IMAGE_CONTRAST, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_IMAGE_CONTRAST ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_IMAGE_CONTRAST dwContrast[%d]\r\n", struImageContrast.dwContrast);
	}
}

void ThermalDevice::SetImageBackgroundCorrect()
{
	USB_COMMON_COND struCond = { 0 };
	USB_CONTROL_INPUT_INFO struControlInputInfo = { 0 };

	struCond.byChannelID = 1;
	struControlInputInfo.lpCondBuffer = &struCond;
	struControlInputInfo.dwCondBufferSize = sizeof(struCond);
	if (!USB_Control(m_lUserID, USB_SET_IMAGE_BACKGROUND_CORRECT, &struControlInputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_IMAGE_BACKGROUND_CORRECT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_IMAGE_BACKGROUND_CORRECT\r\n");
	}
}

void ThermalDevice::GetSystemDiagnoseData()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_SYSTEM_DIAGNOSED_DATA struSysDiagnosedData = { 0 };
	BYTE *pData = new BYTE[BUFFER_LEN];
	if (NULL == pData)
	{
		return;
	}
	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struSysDiagnosedData;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struSysDiagnosedData);

	struSysDiagnosedData.pDiagnosedData = pData;
	struSysDiagnosedData.dwDataLenth = BUFFER_LEN;
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_SYSTEM_DIAGNOSED_DATA, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_SYSTEM_DIAGNOSED_DATA ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		if (struSysDiagnosedData.dwDataLenth > 0)
		{
			FILE *fd = NULL;
			fd = fopen("./USBSDKLog/diagnoseinformation.txt", "w");
			fwrite((void *)struSysDiagnosedData.pDiagnosedData, 1, struSysDiagnosedData.dwDataLenth, fd);
			fclose(fd);
			fd = NULL;
		}
		printf("SUCCESS  USB_GET_SYSTEM_DIAGNOSED_DATA dwDataLenth[%d]\r\n", struSysDiagnosedData.dwDataLenth);
	}
	delete[] pData;
	pData = NULL;
}

void ThermalDevice::SetImageManualCorrect()
{
	USB_COMMON_COND struCond = { 0 };
	USB_CONTROL_INPUT_INFO struControlInputInfo = { 0 };

	struCond.byChannelID = 1;
	struControlInputInfo.lpCondBuffer = &struCond;
	struControlInputInfo.dwCondBufferSize = sizeof(struCond);
	if (!USB_Control(m_lUserID, USB_SET_IMAGE_MANUAL_CORRECT, &struControlInputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_IMAGE_MANUAL_CORRECT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_IMAGE_MANUAL_CORRECT\r\n");

	}
}

void ThermalDevice::GetImageEnhance()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_ENHANCEMENT struImageEnhancement = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struImageEnhancement;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struImageEnhancement);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_IMAGE_ENHANCEMENT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_IMAGE_ENHANCEMENT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_IMAGE_ENHANCEMENT byNoiseReduceMode[%d] dwGeneralLevel[%d] dwFrameNoiseReduceLevel[%d] dwInterFrameNoiseReduceLevel[%d] byPaletteMode[%d] byLSEDetailEnabled[%d] dwLSEDetailLevel[%d]\r\n",
			struImageEnhancement.byNoiseReduceMode, struImageEnhancement.dwGeneralLevel, struImageEnhancement.dwFrameNoiseReduceLevel, struImageEnhancement.dwInterFrameNoiseReduceLevel, struImageEnhancement.byPaletteMode, struImageEnhancement.byLSEDetailEnabled, struImageEnhancement.dwLSEDetailLevel);
	}
}

void ThermalDevice::SetImageEnhancement()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_ENHANCEMENT struImageEnhancement = { 0 };
	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);


	struImageEnhancement.byNoiseReduceMode = 2; // 专家模式
	struImageEnhancement.dwGeneralLevel = 50;
	struImageEnhancement.dwFrameNoiseReduceLevel = 50;
	struImageEnhancement.dwInterFrameNoiseReduceLevel = 50;
	struImageEnhancement.byPaletteMode = 1;
	struImageEnhancement.byLSEDetailEnabled = 1;
	struImageEnhancement.dwLSEDetailLevel = 50;
	struConfigInputInfo.lpInBuffer = &struImageEnhancement;
	struConfigInputInfo.dwInBufferSize = sizeof(struImageEnhancement);
	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_IMAGE_ENHANCEMENT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_IMAGE_ENHANCEMENT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_SET_IMAGE_ENHANCEMENT byNoiseReduceMode[%d] dwGeneralLevel[%d] dwFrameNoiseReduceLevel[%d] dwInterFrameNoiseReduceLevel[%d] byPaletteMode[%d] byLSEDetailEnabled[%d] dwLSEDetailLevel[%d]\r\n",
			struImageEnhancement.byNoiseReduceMode, struImageEnhancement.dwGeneralLevel, struImageEnhancement.dwFrameNoiseReduceLevel, struImageEnhancement.dwInterFrameNoiseReduceLevel, struImageEnhancement.byPaletteMode, struImageEnhancement.byLSEDetailEnabled, struImageEnhancement.dwLSEDetailLevel);
	}
}

void ThermalDevice::GetImageVideoAdjust()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_VIDEO_ADJUST struImageVideoAdjuse = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struImageVideoAdjuse;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struImageVideoAdjuse);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_IMAGE_VIDEO_ADJUST, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_IMAGE_VIDEO_ADJUST ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_IMAGE_VIDEO_ADJUST byImageFlipStyle[%d] byPowerLineFrequencyMode[%d] byCorridor[%d]\r\n",
			struImageVideoAdjuse.byImageFlipStyle, struImageVideoAdjuse.byPowerLineFrequencyMode, struImageVideoAdjuse.byCorridor);
	}
}

void ThermalDevice::SetImageVideoAdjust()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_IMAGE_VIDEO_ADJUST struImageVideoAdjuse = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struImageVideoAdjuse.byImageFlipStyle = 1;
	struImageVideoAdjuse.byPowerLineFrequencyMode = 1;
	struImageVideoAdjuse.byCorridor = 1;
	struConfigInputInfo.lpInBuffer = &struImageVideoAdjuse;
	struConfigInputInfo.dwInBufferSize = sizeof(struImageVideoAdjuse);
	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_IMAGE_VIDEO_ADJUST, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_IMAGE_VIDEO_ADJUST ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_SET_IMAGE_VIDEO_ADJUST byImageFlipStyle[%d] byPowerLineFrequencyMode[%d] byCorridor[%d]\r\n",
			struImageVideoAdjuse.byImageFlipStyle, struImageVideoAdjuse.byPowerLineFrequencyMode, struImageVideoAdjuse.byCorridor);
	}
}

void ThermalDevice::GetThermometryBasicParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_BASIC_PARAM struThermometryBasicParam = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struThermometryBasicParam;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermometryBasicParam);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMOMETRY_BASIC_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMOMETRY_BASIC_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_THERMOMETRY_BASIC_PARAM byImageFlipStyle[%d] byDisplayMaxTemperatureEnabled[%d] byDisplayMinTemperatureEnabled[%d]\r\n",
			struThermometryBasicParam.byEnabled, struThermometryBasicParam.byDisplayMaxTemperatureEnabled, struThermometryBasicParam.byDisplayMinTemperatureEnabled);
	}
}

void ThermalDevice::SetThermometryBasicParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_BASIC_PARAM struThermometryBasicParam = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struThermometryBasicParam;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermometryBasicParam);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMOMETRY_BASIC_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMOMETRY_BASIC_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		struConfigInputInfo.lpInBuffer = &struThermometryBasicParam;
		struConfigInputInfo.dwInBufferSize = sizeof(struThermometryBasicParam);
		if (!USB_GetDeviceConfig(m_lUserID, USB_SET_THERMOMETRY_BASIC_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
		{
			DWORD dwError = USB_GetLastError();
			printf("FAILED USB_SET_THERMOMETRY_BASIC_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
		}
		else
		{
			printf("SUCCESS  USB_SET_THERMOMETRY_BASIC_PARAM byImageFlipStyle[%d] byDisplayMaxTemperatureEnabled[%d] byDisplayMinTemperatureEnabled[%d]\r\n",
				struThermometryBasicParam.byEnabled, struThermometryBasicParam.byDisplayMaxTemperatureEnabled, struThermometryBasicParam.byDisplayMinTemperatureEnabled);
		}
	}
}

void ThermalDevice::GetThermometryMode()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_MODE struThermometryMode = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struThermometryMode;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermometryMode);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMOMETRY_MODE, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMOMETRY_MODE ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_THERMOMETRY_MODE byThermometryMode[%d] byThermometryROIEnabled[%d]\r\n",
			struThermometryMode.byThermometryMode, struThermometryMode.byThermometryROIEnabled);
	}
}

void ThermalDevice::SetThermometryMode()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_MODE struThermometryMode = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struThermometryMode.byThermometryMode = 1;//专家
	struThermometryMode.byThermometryROIEnabled = 2;
	struConfigInputInfo.lpInBuffer = &struThermometryMode;
	struConfigInputInfo.dwInBufferSize = sizeof(struThermometryMode);
	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_THERMOMETRY_MODE, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_THERMOMETRY_MODE ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_SET_THERMOMETRY_MODE byThermometryMode[%d] byThermometryROIEnabled[%d]\r\n",
			struThermometryMode.byThermometryMode, struThermometryMode.byThermometryROIEnabled);
	}
}

void ThermalDevice::GetThermometryRegions()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_REGIONS struThermometryRegions = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struThermometryRegions;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermometryRegions);
	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMOMETRY_REGIONS, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMOMETRY_REGIONS ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_THERMOMETRY_REGIONS byRegionNum[%d]\r\n",
			struThermometryRegions.byRegionNum);
	}
}

void ThermalDevice::SetThermometryRegions()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_REGIONS struThermometryRegions = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struThermometryRegions;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermometryRegions);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMOMETRY_REGIONS, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMOMETRY_REGIONS ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		struConfigInputInfo.lpInBuffer = &struThermometryRegions;
		struConfigInputInfo.dwInBufferSize = sizeof(struThermometryRegions);

		if (!USB_SetDeviceConfig(m_lUserID, USB_SET_THERMOMETRY_REGIONS, &struConfigInputInfo, &struConfigOutputInfo))
		{
			DWORD dwError = USB_GetLastError();
			printf("FAILED USB_SET_THERMOMETRY_REGIONS ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
		}
		else
		{
			printf("SUCCESS  USB_SET_THERMOMETRY_REGIONS byRegionNum[%d]\r\n",
				struThermometryRegions.byRegionNum);
		}
	}
}

void ThermalDevice::GetThermalStreamParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMAL_STREAM_PARAM struThermalStreamParam = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struThermalStreamParam;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermalStreamParam);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMAL_STREAM_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMAL_STREAM_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_THERMAL_STREAM_PARAM dwSize[%d] byVideoCodingType[%d]\r\n",
			struThermalStreamParam.dwSize, struThermalStreamParam.byVideoCodingType);
	}
}

void ThermalDevice::GetThermalAlgVersion()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMAL_ALG_VERSION struThermalAlgVersion = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struThermalAlgVersion;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermalAlgVersion);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMAL_ALG_VERSION, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMAL_ALG_VERSION ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_THERMOMETRY_REGIONS dwSize[%d] byThermometryAlgName[%s]\r\n",
			struThermalAlgVersion.dwSize, struThermalAlgVersion.byThermometryAlgName);
	}
}

void ThermalDevice::SetThermalStreamParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMAL_STREAM_PARAM struThermalStreamParam = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struThermalStreamParam.byVideoCodingType = 2;//全屏测温数据
	struConfigInputInfo.lpInBuffer = &struThermalStreamParam;
	struConfigInputInfo.dwInBufferSize = sizeof(struThermalStreamParam);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_THERMAL_STREAM_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_THERMAL_STREAM_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_SET_THERMAL_STREAM_PARAM dwSize[%d] byVideoCodingType[%d]\r\n",
			struThermalStreamParam.dwSize, struThermalStreamParam.byVideoCodingType);
	}
}

void ThermalDevice::GetTemperatureCorrect()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_TEMPERATURE_CORRECT struTemperatureCorrect = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struTemperatureCorrect;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struTemperatureCorrect);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_TEMPERATURE_CORRECT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_TEMPERATURE_CORRECT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_TEMPERATURE_CORRECT dwSize[%d] byEnabled[%d]\r\n",
			struTemperatureCorrect.dwSize, struTemperatureCorrect.byEnabled);
	}
}

void ThermalDevice::SetTemperatureCorrect()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_TEMPERATURE_CORRECT struTemperatureCorrect = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struTemperatureCorrect;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struTemperatureCorrect);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_TEMPERATURE_CORRECT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_TEMPERATURE_CORRECT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		struConfigInputInfo.lpInBuffer = &struTemperatureCorrect;
		struConfigInputInfo.dwInBufferSize = sizeof(struTemperatureCorrect);

		if (!USB_SetDeviceConfig(m_lUserID, USB_SET_TEMPERATURE_CORRECT, &struConfigInputInfo, &struConfigOutputInfo))
		{
			DWORD dwError = USB_GetLastError();
			printf("FAILED USB_SET_TEMPERATURE_CORRECT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
		}
		else
		{
			printf("SUCCESS  USB_SET_TEMPERATURE_CORRECT dwSize[%d] byEnabled[%d]\r\n",
				struTemperatureCorrect.dwSize, struTemperatureCorrect.byEnabled);
		}
	}
}

void ThermalDevice::GetBlackBody()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_BLACK_BODY struBlackBody = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struBlackBody;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struBlackBody);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_BLACK_BODY, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_BLACK_BODY ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_BLACK_BODY dwSize[%d] byEnabled[%d]\r\n",
			struBlackBody.dwSize, struBlackBody.byEnabled);
	}
}

void ThermalDevice::SetBlackBody()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_BLACK_BODY struBlackBody = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struBlackBody;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struBlackBody);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_BLACK_BODY, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_BLACK_BODY ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		struConfigInputInfo.lpInBuffer = &struBlackBody;
		struConfigInputInfo.dwInBufferSize = sizeof(struBlackBody);

		if (!USB_SetDeviceConfig(m_lUserID, USB_SET_BLACK_BODY, &struConfigInputInfo, &struConfigOutputInfo))
		{
			DWORD dwError = USB_GetLastError();
			printf("FAILED USB_SET_BLACK_BODY ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
		}
		else
		{
			printf("SUCCESS  USB_SET_BLACK_BODY dwSize[%d] byEnabled[%d]\r\n",
				struBlackBody.dwSize, struBlackBody.byEnabled);
		}
	}
}

void ThermalDevice::GetBodytempCompensation()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_BODYTEMP_COMPENSATION struBodytempCompensation = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struBodytempCompensation;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struBodytempCompensation);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_BODYTEMP_COMPENSATION, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_BODYTEMP_COMPENSATION ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_BODYTEMP_COMPENSATION dwSize[%d] byEnabled[%d]\r\n",
			struBodytempCompensation.dwSize, struBodytempCompensation.byEnabled);
	}
}

void ThermalDevice::SetBodytempCompensation()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_BODYTEMP_COMPENSATION struBodytempCompensation = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struConfigOutputInfo.lpOutBuffer = &struBodytempCompensation;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struBodytempCompensation);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_BODYTEMP_COMPENSATION, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_BODYTEMP_COMPENSATION ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		struConfigInputInfo.lpInBuffer = &struBodytempCompensation;
		struConfigInputInfo.dwInBufferSize = sizeof(struBodytempCompensation);

		if (!USB_SetDeviceConfig(m_lUserID, USB_SET_BODYTEMP_COMPENSATION, &struConfigInputInfo, &struConfigOutputInfo))
		{
			DWORD dwError = USB_GetLastError();
			printf("FAILED USB_SET_BODYTEMP_COMPENSATION ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
		}
		else
		{
			printf("SUCCESS  USB_SET_BODYTEMP_COMPENSATION dwSize[%d] byEnabled[%d]\r\n",
				struBodytempCompensation.dwSize, struBodytempCompensation.byEnabled);
		}
	}
}

void ThermalDevice::GetRoiMaxTemperatureSearch()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_ROI_MAX_TEMPERATURE_SEARCH struRoiMaxTemperatureSearch = { 0 };
	USB_ROI_MAX_TEMPERATURE_SEARCH_RESULT struRoiMaxTemperatureSearchResult = { 0 };

	char *pData = new char[BUFFER_LEN];
	if (NULL == pData)
	{
		return;
	}
	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struRoiMaxTemperatureSearch.byJpegPicEnabled = 1;
	struRoiMaxTemperatureSearch.byMaxTemperatureOverlay = 1;
	struRoiMaxTemperatureSearch.byRegionsOverlay = 1;
	struRoiMaxTemperatureSearch.byROIRegionNum = 2;
	struRoiMaxTemperatureSearch.struThermalROIRegion[0].byROIRegionID = 1;
	struRoiMaxTemperatureSearch.struThermalROIRegion[0].byROIRegionEnabled = 1;
	struRoiMaxTemperatureSearch.struThermalROIRegion[0].dwROIRegionX = 0;
	struRoiMaxTemperatureSearch.struThermalROIRegion[0].dwROIRegionY = 0;
	struRoiMaxTemperatureSearch.struThermalROIRegion[0].dwROIRegionHeight = 50;
	struRoiMaxTemperatureSearch.struThermalROIRegion[0].dwROIRegionWidth = 150;
	struRoiMaxTemperatureSearch.struThermalROIRegion[0].dwDistance = 50;

	struRoiMaxTemperatureSearch.struThermalROIRegion[1].byROIRegionID = 2;
	struRoiMaxTemperatureSearch.struThermalROIRegion[1].byROIRegionEnabled = 1;
	struRoiMaxTemperatureSearch.struThermalROIRegion[1].dwROIRegionX = 70;
	struRoiMaxTemperatureSearch.struThermalROIRegion[1].dwROIRegionY = 110;
	struRoiMaxTemperatureSearch.struThermalROIRegion[1].dwROIRegionHeight = 10;
	struRoiMaxTemperatureSearch.struThermalROIRegion[1].dwROIRegionWidth = 10;
	struRoiMaxTemperatureSearch.struThermalROIRegion[1].dwDistance = 100;

	//查询参数
	struConfigInputInfo.lpInBuffer = &struRoiMaxTemperatureSearch;
	struConfigInputInfo.dwInBufferSize = sizeof(struRoiMaxTemperatureSearch);


	struRoiMaxTemperatureSearchResult.pJpegPic = (BYTE*)pData;
	struRoiMaxTemperatureSearchResult.dwJpegPicLen = BUFFER_LEN;
	//查询结果
	struConfigOutputInfo.lpOutBuffer = &struRoiMaxTemperatureSearchResult;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struRoiMaxTemperatureSearchResult);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_ROI_MAX_TEMPERATURE_SEARCH, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_ROI_MAX_TEMPERATURE_SEARCH ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		if (struRoiMaxTemperatureSearchResult.dwJpegPicLen > 0)
		{
			FILE *fd = NULL;
			fd = fopen("./USBSDKLog/roimax.jpg", "wb");
			fwrite((void *)struRoiMaxTemperatureSearchResult.pJpegPic, 1, struRoiMaxTemperatureSearchResult.dwJpegPicLen, fd);
			fclose(fd);
			fd = NULL;
		}
		printf("SUCCESS  USB_GET_ROI_MAX_TEMPERATURE_SEARCH dwSize[%d] dwJpegPicLen[%d]\r\n",
			struRoiMaxTemperatureSearchResult.dwSize, struRoiMaxTemperatureSearchResult.dwJpegPicLen);
	}
	delete[] pData;
	pData = NULL;
}

void ThermalDevice::GetJpegpicWithAppenddata()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_JPEGPIC_WITH_APPENDDATA struJpegpicWithAppendData = { 0 };
	char *pData = new char[BUFFER_LEN];
	if (NULL == pData)
	{
		return;
	}
	char *pData2 = new char[BUFFER_LEN];
	if (NULL == pData2)
	{
		return;
	}
	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struJpegpicWithAppendData.pP2pData = (BYTE*)pData;
	struJpegpicWithAppendData.dwP2pDataLen = BUFFER_LEN;
	struJpegpicWithAppendData.pJpegPic = (BYTE*)pData2;
	struJpegpicWithAppendData.dwJpegPicLen = BUFFER_LEN;
	struConfigOutputInfo.lpOutBuffer = &struJpegpicWithAppendData;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struJpegpicWithAppendData);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_JPEGPIC_WITH_APPENDDATA, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_JPEGPIC_WITH_APPENDDATA ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		if (struJpegpicWithAppendData.dwJpegPicLen > 0)
		{
			FILE *fd = NULL;
			fd = fopen("./USBSDKLog/append.jpg", "wb");
			fwrite((void *)struJpegpicWithAppendData.pJpegPic, 1, struJpegpicWithAppendData.dwJpegPicLen, fd);
			fclose(fd);
			fd = NULL;
		}
		printf("SUCCESS  USB_GET_JPEGPIC_WITH_APPENDDATA dwSize[%d] dwJpegPicLen[%d]\r\n",
			struJpegpicWithAppendData.dwSize, struJpegpicWithAppendData.dwJpegPicLen);
	}
	delete[] pData;
	pData = NULL;
	delete[] pData2;
	pData2 = NULL;
}

void ThermalDevice::GetP2PParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_P2P_PARAM struP2pParam = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);
	struConfigOutputInfo.lpOutBuffer = &struP2pParam;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struP2pParam);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_P2P_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_P2P_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_P2P_PARAM dwSize[%d] byJpegPicEnabled[%d]\r\n",
			struP2pParam.dwSize, struP2pParam.byJpegPicEnabled);
	}
}

void ThermalDevice::SetP2PParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_P2P_PARAM struP2pParam = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struP2pParam.byJpegPicEnabled = 1;
	struConfigInputInfo.lpInBuffer = &struP2pParam;
	struConfigInputInfo.dwInBufferSize = sizeof(struP2pParam);
	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_P2P_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_P2P_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_SET_P2P_PARAM dwSize[%d] byJpegPicEnabled[%d]\r\n",
			struP2pParam.dwSize, struP2pParam.byJpegPicEnabled);
	}
}

void ThermalDevice::PostDoubleLightsCorrect()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_DOUBLE_LIGHTS_CORRECT struDoubleLightsCorrect = { 0 };
	USB_DOUBLE_LIGHTS_CORRECT_RESULT struDoubleLightsCorrectResult = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	//可见光图片
	FILE *fd = NULL;
	int iReadSize = 0;
	BYTE *pData = new BYTE[BUFFER_LEN];
	if (NULL == pData)
	{
		return;
	}
	fd = fopen("./USBSDKLog/1080p.jpg", "rb");
	fseek(fd, 0, SEEK_END);
	iReadSize = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	fread(pData, 1, iReadSize, fd);

	struDoubleLightsCorrect.pVisiblePic = pData;
	struDoubleLightsCorrect.dwVisiblePicLen = iReadSize;

	fclose(fd);
	fd = NULL;
	struDoubleLightsCorrect.byVisiblePicHorizontalScale = 20;
	struDoubleLightsCorrect.byVisiblePicVerticalScale = 118;
	struDoubleLightsCorrect.wHorizontalCalibrationOffset = 1;
	struDoubleLightsCorrect.wVerticalCalibrationOffset = 1;
	struDoubleLightsCorrect.dwVisibleFocusDistance = 4;
	struDoubleLightsCorrect.dwVisiblePixelInterval = 2;
	struDoubleLightsCorrect.dwHorizontalCenterDistance = 50;
	struDoubleLightsCorrect.dwVerticalCenterDistance = 15;
	struDoubleLightsCorrect.dwCalibrationDistance = 100;

	struConfigInputInfo.lpInBuffer = &struDoubleLightsCorrect;
	struConfigInputInfo.dwInBufferSize = sizeof(struDoubleLightsCorrect);

	struConfigOutputInfo.lpOutBuffer = &struDoubleLightsCorrectResult;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struDoubleLightsCorrectResult);
	struDoubleLightsCorrectResult.pJpegPic = pData;
	struDoubleLightsCorrectResult.dwJpegPicLen = BUFFER_LEN;


	if (!USB_GetDeviceConfig(m_lUserID, USB_POST_DOUBLE_LIGHTS_CORRECT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_POST_DOUBLE_LIGHTS_CORRECT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		if (struDoubleLightsCorrectResult.dwJpegPicLen > 0)
		{
			FILE *fd = NULL;
			fd = fopen("./USBSDKLog/double.jpg", "wb");
			fwrite((void *)struDoubleLightsCorrectResult.pJpegPic, 1, struDoubleLightsCorrectResult.dwJpegPicLen, fd);
			fclose(fd);
			fd = NULL;
		}
		printf("SUCCESS  USB_POST_DOUBLE_LIGHTS_CORRECT dwSize[%d] dwJpegPicLen[%d]\r\n",
			struDoubleLightsCorrectResult.dwSize, struDoubleLightsCorrectResult.dwJpegPicLen);
	}
	delete[] pData;
	pData = NULL;
}

void ThermalDevice::GetDoubleLightsCorrectPointsCtrl()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL struDoubleLightsCorrectPointsCtrl = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);
	struConfigOutputInfo.lpOutBuffer = &struDoubleLightsCorrectPointsCtrl;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struDoubleLightsCorrectPointsCtrl);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_GET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL dwSize[%d] byDoubleLightsCorrectPointsEnabled[%d]\r\n",
			struDoubleLightsCorrectPointsCtrl.dwSize, struDoubleLightsCorrectPointsCtrl.byDoubleLightsCorrectPointsEnabled);
	}
}

void ThermalDevice::SetDoubleLightsCorrectPointCtrl()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL struDoubleLightsCorrectPointsCtrl = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	struDoubleLightsCorrectPointsCtrl.byDoubleLightsCorrectPointsEnabled = 1;
	struConfigInputInfo.lpInBuffer = &struDoubleLightsCorrectPointsCtrl;
	struConfigInputInfo.dwInBufferSize = sizeof(struDoubleLightsCorrectPointsCtrl);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_SET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL dwSize[%d] byDoubleLightsCorrectPointsEnabled[%d]\r\n",
			struDoubleLightsCorrectPointsCtrl.dwSize, struDoubleLightsCorrectPointsCtrl.byDoubleLightsCorrectPointsEnabled);
	}
}

void ThermalDevice::GetThermometryCalibrationFile()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_CALIBRATION_FILE struThermometryCalibrationFile = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	//struConfigInputInfo.lpInBuffer = &struThermometryCalibrationFile;
	//struConfigInputInfo.dwInBufferSize = sizeof(struThermometryCalibrationFile);

	struConfigOutputInfo.lpOutBuffer = &struThermometryCalibrationFile;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struThermometryCalibrationFile);
	BYTE *pData = new BYTE[BUFFER_LEN];
	if (NULL == pData)
	{
		return;
	}
	struThermometryCalibrationFile.pCalibrationFile = pData;
	struThermometryCalibrationFile.dwFileLenth = BUFFER_LEN;

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_THERMOMETRY_CALIBRATION_FILE, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_THERMOMETRY_CALIBRATION_FILE ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		if (struThermometryCalibrationFile.dwFileLenth > 0)
		{
			FILE *fd = NULL;
			fd = fopen("./USBSDKLog/MT_DS-2TM01-3XFTB20200529CACH415127250.dat", "wb");
			fwrite((void *)struThermometryCalibrationFile.pCalibrationFile, 1, struThermometryCalibrationFile.dwFileLenth, fd);
			fclose(fd);
			fd = NULL;
		}
		printf("SUCCESS  USB_GET_THERMOMETRY_CALIBRATION_FILE dwSize[%d] dwFileLenth[%d]\r\n",
			struThermometryCalibrationFile.dwSize, struThermometryCalibrationFile.dwFileLenth);
	}
	delete[] pData;
	pData = NULL;
}

void ThermalDevice::SetThermometryCalibrationFile()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_COMMON_COND struCond = { 0 };
	USB_THERMOMETRY_CALIBRATION_FILE struThermometryCalibrationFile = { 0 };

	struCond.byChannelID = 1;
	struConfigInputInfo.lpCondBuffer = &struCond;
	struConfigInputInfo.dwCondBufferSize = sizeof(struCond);

	//可见光图片   ?????
	FILE *fd = NULL;
	int iReadSize = 0;
	char *pData = new char[BUFFER_LEN];
	if (NULL == pData)
	{
		return;
	}
	fd = fopen("./USBSDKLog/MT_DS-2TM01-3XFTB20200529CACH415127250.dat", "rb");
	fseek(fd, 0, SEEK_END);
	iReadSize = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	fread(pData, 1, iReadSize, fd);
	fclose(fd);
	fd = NULL;
	struThermometryCalibrationFile.pCalibrationFile = (BYTE*)pData;
	struThermometryCalibrationFile.dwFileLenth = iReadSize;
	sprintf((char *)struThermometryCalibrationFile.byFileName, "MT_DS-2TM01-3XFTB20200529CACH415127250.dat");
	struConfigInputInfo.lpInBuffer = &struThermometryCalibrationFile;
	struConfigInputInfo.dwInBufferSize = sizeof(struThermometryCalibrationFile);

	//struConfigOutputInfo.lpOutBuffer = &struThermometryCalibrationFile;
	//struConfigOutputInfo.dwOutBufferSize = sizeof(struThermometryCalibrationFile);

	if (!USB_GetDeviceConfig(m_lUserID, USB_SET_THERMOMETRY_CALIBRATION_FILE, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_THERMOMETRY_CALIBRATION_FILE ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS  USB_SET_THERMOMETRY_CALIBRATION_FILE dwSize[%d] dwFileLenth[%d]\r\n",
			struThermometryCalibrationFile.dwSize, struThermometryCalibrationFile.dwFileLenth);
	}
	delete[] pData;
	pData = NULL;
}

void ThermalDevice::GetCommandState()
{
	USB_COMMAND_STATE struCommandState = { 0 };
	struCommandState.dwSize = sizeof(struCommandState);

	if (!USB_GetCommandState(m_lUserID, &struCommandState))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GetCommandState ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GetCommandState byState[%d]\r\n", struCommandState.byState);
	}
}

