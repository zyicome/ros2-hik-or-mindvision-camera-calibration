#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "CameraDevice.h"

using namespace std;

CameraDevice::CameraDevice()
	: m_nVideoCapCount(0)
	, m_nAudioCapCount(0)
    , m_bPreviewAudio(FALSE)
	, m_bCaptureAudio(FALSE)
{
	memset(m_CamVideoCap, 0, sizeof(m_CamVideoCap));
	memset(m_CamAudioCap, 0, sizeof(m_CamAudioCap));
	m_pGetStream = new CGetStream(CAMERA_DEVICE);
	m_bResource = (m_pGetStream != NULL);
}


void CameraDevice::Usage(void)
{
	printf("Select Camera Capacity:\r\n");
	PRINTF(CUSTOM_PRINT_MENU);
	PRINTF(CUSTOM_GET_SDK_VERSION);
	PRINTF(CUSTOM_USB_INIT);
	PRINTF(CUSTOM_SET_LOGTOFILE);
	PRINTF(CUSTOM_GET_DEVICE_COUNT);
	PRINTF(CUSTOM_ENUM_DEVICE);
	PRINTF(CUSTOM_LOGIN_DEVICE);
	PRINTF(CUSTOM_DEVICE_LOGOUT);
	PRINTF(CUSTOM_CLEANUP);
	PRINTF(CAMERA_GET_VIDEO_CAP);
	PRINTF(CAMERA_GET_AUDIO_CAP);
	PRINTF(CAMERA_GET_VIDEO_PARAM);
	PRINTF(CAMERA_SET_VIDEO_PARAM);
	PRINTF(CAMERA_SET_AUDIO_PARAM);
	PRINTF(CAMERA_SET_SRC_STREAM_TYPE);
	PRINTF(CAMERA_SET_EVENT_CALLBACK);
	PRINTF(CAMERA_SET_ROTATE_ANGLE);
	PRINTF(CAMERA_GET_IRFRAME);
	PRINTF(CAMERA_INIT_LIVE_DETECT);
	PRINTF(CAMERA_GET_LIVEDETECT);
	PRINTF(CAMERA_GET_VIDEO_PROPERTY_CAP);
	PRINTF(CAMERA_GET_VIDEO_BRIGHTNESS);
	PRINTF(CAMERA_SET_VIDEO_BRIGHTNESS);
	PRINTF(CAMERA_GET_VIDEO_CONTRAST);
	PRINTF(CAMERA_SET_VIDEO_CONTRAST);
	PRINTF(CAMERA_GET_VIDEO_HUE);
	PRINTF(CAMERA_SET_VIDEO_HUE);
	PRINTF(CAMERA_GET_VIDEO_SATURATION);
	PRINTF(CAMERA_SET_VIDEO_SATURATION);
	PRINTF(CAMERA_GET_VIDEO_SHARPNESS);
	PRINTF(CAMERA_SET_VIDEO_SHARPNESS);
	PRINTF(CAMERA_GET_VIDEO_GAMMA);
	PRINTF(CAMERA_SET_VIDEO_GAMMA);
	PRINTF(CAMERA_GET_VIDEO_COLORENABLE);
	PRINTF(CAMERA_SET_VIDEO_COLORENABLE);
	PRINTF(CAMERA_GET_VIDEO_WHITEBALANCE);
	PRINTF(CAMERA_SET_VIDEO_WHITEBALANCE);
	PRINTF(CAMERA_GET_VIDEO_BACKLIGHTCOMPENSATION);
	PRINTF(CAMERA_SET_VIDEO_BACKLIGHTCOMPENSATION);
	PRINTF(CAMERA_GET_VIDEO_GAIN);
	PRINTF(CAMERA_SET_VIDEO_GAIN);
	PRINTF(CAMERA_GET_VIDEO_POWERLINEFREQUENCY);
	PRINTF(CAMERA_SET_VIDEO_POWERLINEFREQUENCY);
	PRINTF(CAMERA_GET_VIDEO_PAN);
	PRINTF(CAMERA_SET_VIDEO_PAN);
	PRINTF(CAMERA_GET_VIDEO_TILT);
	PRINTF(CAMERA_SET_VIDEO_TILT);
	PRINTF(CAMERA_GET_VIDEO_ROLL);
	PRINTF(CAMERA_SET_VIDEO_ROLL);
	PRINTF(CAMERA_GET_VIDEO_ZOOM);
	PRINTF(CAMERA_SET_VIDEO_ZOOM);
	PRINTF(CAMERA_GET_VIDEO_EXPOSURE);
	PRINTF(CAMERA_SET_VIDEO_EXPOSURE);
	PRINTF(CAMERA_GET_VIDEO_IRIS);
	PRINTF(CAMERA_SET_VIDEO_IRIS);
	PRINTF(CAMERA_GET_VIDEO_FOCUS);
	PRINTF(CAMERA_SET_VIDEO_FOCUS);
	PRINTF(CAMERA_GET_VIDEO_LOWBRIGHTNESSCOMPENSATION);
	PRINTF(CAMERA_SET_VIDEO_LOWBRIGHTNESSCOMPENSATION);
	PRINTF(CAMERA_GET_VIDEO_VOLUME);
	PRINTF(CAMERA_SET_VIDEO_VOLUME);
	PRINTF(CAMERA_SET_OSD);
	PRINTF(CUSTOM_STREAM_CALLBACK);
	PRINTF(CUSTOM_STREAM_RECORD);
	PRINTF(CUSTOM_STREAM_PREVIEW);
	printf("\t Press q to quit...\r\n");
}

void CameraDevice::UsbImplement()
{
	while (!m_bExit)
	{
		int iIn = CheckBoardInput();
		DoBusiness(iIn, 0);
    }
	delete m_pGetStream;
	m_pGetStream = NULL;
}

void CameraDevice::DoBusiness(int iType, int iDevIndex)
{
	switch (iType)
	{
		case KEYBOARD_INPUT_FAILED:
		{
			printf("Camera Device Exit...\r\n");
			m_bExit = TRUE;
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
		case CUSTOM_DEVICE_LOGOUT:
		{
			DeviceLogout();
			break;
		}
		case CAMERA_GET_VIDEO_CAP:
		{
			GetCamVideoCap();
			break;
		}
		case CAMERA_GET_VIDEO_PARAM:
		{
			UsbGetVideoParam();
			break;
		}
		case CAMERA_SET_VIDEO_PARAM:
		{
			UsbSetVideoParam();
			break;
		}
		case CUSTOM_STREAM_CALLBACK:
		{
			m_pGetStream->StartStreamCallback();
			break;
		}
		case CUSTOM_STREAM_RECORD:
		{
			m_pGetStream->StartStreamRecord();
			break;
		}
		case CUSTOM_STREAM_PREVIEW:
		{
			m_pGetStream->StartStreamPreview();
			break;
		}
		default:
		{
			printf("FAILED Unsupported\r\n");
			break;
		}
	}
}

void CameraDevice::GetCamVideoCap()
{
    USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };

	if (USB_INVALID_USERID == m_lUserID)
	{
		printf("Please Login Device.\r\n");
		return;
	}
	memset(&m_CamVideoCap, 0, sizeof(m_CamVideoCap));
    struConfigOutputInfo.lpOutBuffer = m_CamVideoCap;
    struConfigOutputInfo.dwOutBufferSize = sizeof(m_CamVideoCap);
	m_nVideoCapCount = 0;
	//获取设备支持的视频格式
    if (!USB_GetDeviceConfig(m_lUserID, USB_GET_VIDEO_CAP, &struConfigInputInfo, &struConfigOutputInfo))
	{
        DWORD dwError = USB_GetLastError();
        printf("FAILED USB_GET_VIDEO_CAP, ErrorCode[%d] ErrorMsg[%s]", dwError, USB_GetErrorMsg(dwError));
        return;
	}
	printf("SUCCESS USB_GET_VIDEO_CAP\r\n");
	//设备支持的视频格式的个数
	for (int i = 0; m_CamVideoCap[i].lListSize != 0; i++)
	{
		m_nVideoCapCount++;
	}
	printf("m_nVideoCapCount [%d]\r\n", m_nVideoCapCount);
}

void CameraDevice::GetCamAudioCap()
{
    USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	if (USB_INVALID_USERID == m_lUserID)
	{
		printf("Please Login Device.\r\n");
		return;
	}
	
	memset(&m_CamAudioCap, 0, sizeof(m_CamAudioCap));
    struConfigOutputInfo.lpOutBuffer = m_CamAudioCap;
    struConfigOutputInfo.dwOutBufferSize = sizeof(m_CamAudioCap);
	//获取设备支持的音频格式
	printf("m_lUserID = [%d]\r\n", m_lUserID);

    if (!USB_GetDeviceConfig(m_lUserID, USB_GET_AUDIO_CAP, &struConfigInputInfo, &struConfigOutputInfo))
	{
        DWORD dwError = USB_GetLastError();
        printf("FAILED USB_GET_AUDIO_CAP, ErrorCode[%d] ErrorMsg[%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
	}
	printf("SUCCESS USB_GET_AUDIO_CAP\r\n");

	//设备支持的音频格式的个数
	m_nAudioCapCount = 0;
    for (int i = 0; (m_CamAudioCap[i].nAvgBytesPerSec && m_CamAudioCap[i].nChannels); i++)
    {
        m_nAudioCapCount++;
    }
	printf("m_nAudioCapCount [%d]\r\n", m_nAudioCapCount);	
}


void CameraDevice::UsbGetVideoParam()
{
	if (USB_INVALID_USERID == m_lUserID)
	{
		printf("Please Login Device.\r\n");
		return;
	}	 
    USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };       
	USB_VIDEO_PARAM struVideoParam = { 0 };
    struConfigOutputInfo.lpOutBuffer = &struVideoParam;
    struConfigOutputInfo.dwOutBufferSize = sizeof(struVideoParam);
    //获取设备视频参数
	printf("m_lUserID = [%d]\r\n", m_lUserID);

    if (!USB_GetDeviceConfig(m_lUserID, USB_GET_VIDEO_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
    {
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_VIDEO_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
    }
    printf("SUCCESS USB_GET_VIDEO_PARAM \r\n");
    printf("dwVideoFormat[%d] dwWidth[%d] dwHeight[%d] dwFramerate[%d]\r\n", 
    	struVideoParam.dwVideoFormat, struVideoParam.dwWidth, struVideoParam.dwHeight, struVideoParam.dwFramerate);
}

void CameraDevice::UsbSetVideoParam()
{
	if (USB_INVALID_USERID == m_lUserID)
	{
		printf("Please Login Device.\r\n");
		return;
	}	
    //更新需要设置的参数
	        //参数配置
    USB_CONFIG_INPUT_INFO struConfigInputInfo1 = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo1 = { 0 };
    memset(&struConfigInputInfo1, 0, sizeof(struConfigInputInfo1));
    memset(&struConfigOutputInfo1, 0, sizeof(struConfigOutputInfo1));
    USB_VIDEO_CAPACITY m_CamVideo1Cap[100];
    memset(&m_CamVideo1Cap, 0, sizeof(m_CamVideo1Cap));
    struConfigOutputInfo1.lpOutBuffer = &m_CamVideo1Cap;
    struConfigOutputInfo1.dwOutBufferSize = sizeof(m_CamVideo1Cap);
    if (USB_GetDeviceConfig(m_lUserID, USB_GET_VIDEO_CAP, &struConfigInputInfo1, &struConfigOutputInfo1))
    {
        printf("SUCCESS USB_GetDeviceConfig()  USB_GET_VIDEO_CAP\r\n");
    }
    else
    {
        printf("failed USB_GetDeviceConfig() USB_GET_VIDEO_CAP err[%d]\r\n", USB_GetLastError());
        USB_Logout(m_lUserID);
        USB_Cleanup();
        sleep(1);
        return;
    }
    USB_CONFIG_INPUT_INFO struConfigInputInfo2 = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo2 = { 0 };
    USB_VIDEO_PARAM struVideoParam = { 0 };
    struVideoParam.dwFramerate = m_CamVideo1Cap[0].lFrameRates[0];
    struVideoParam.dwWidth = m_CamVideo1Cap[0].dwWidth;
    struVideoParam.dwHeight = m_CamVideo1Cap[0].dwHeight;
    struVideoParam.dwParamType = m_CamVideo1Cap[0].nType;
    struVideoParam.dwVideoFormat = 101;
    struConfigInputInfo2.lpInBuffer = &struVideoParam;
    struConfigInputInfo2.dwInBufferSize = sizeof(struVideoParam);
    if (USB_SetDeviceConfig(m_lUserID, USB_SET_VIDEO_PARAM, &struConfigInputInfo2, &struConfigOutputInfo2))
    {
        printf("SUCCESS USB_SetDeviceConfig()  USB_SET_VIDEO_PARAM\r\n");
    }
    else
    {
        printf("failed USB_SetDeviceConfig() USB_SET_VIDEO_PARAM err[%d]\r\n", USB_GetLastError());
        USB_Logout(m_lUserID);
        USB_Cleanup();
        sleep(1);
        return;
    }
    printf("SUCCESS USB_SET_VIDEO_PARAM\r\n");
    printf("dwVideoFormat[%d] dwWidth[%d] dwHeight[%d] dwFramerate[%d]\r\n", 
	struVideoParam.dwVideoFormat, struVideoParam.dwWidth, struVideoParam.dwHeight, struVideoParam.dwFramerate);
}

void CameraDevice::UsbSetSrcStreamType()
{
	if (USB_INVALID_USERID == m_lUserID)
	{
		printf("Please Login Device.\r\n");
		return;
	}
	char ch = ' ';
	printf("PbPreviewAudio || bCaptureAudio, y or n?\r\n");
	while ((ch = getchar()) != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
	{
		printf("Please Input a Valid Value, y or n?.\r\n");
	}
	if ('y' == ch || 'Y' == ch)
	{
		m_bPreviewAudio = TRUE;
		m_bCaptureAudio = TRUE;
	}
	else
	{
		m_bPreviewAudio = FALSE;
		m_bCaptureAudio = FALSE;
	}
    //更新需要设置的参数
	//int dwSrcStreamType = m_CamVideoCap[0].nType;   //固定值
    
    USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
    USB_SRC_STREAM_CFG struSrcStreamCfg = { 0 };
    struSrcStreamCfg.dwStreamType = USB_STREAM_MJPEG; //固定值 USB_STREAM_MJPEG
    struSrcStreamCfg.bUseAudio = (m_bPreviewAudio || m_bCaptureAudio);

    memset(&struConfigInputInfo, 0, sizeof(struConfigInputInfo));
    memset(&struConfigOutputInfo, 0, sizeof(struConfigOutputInfo));

    struConfigInputInfo.lpInBuffer = &struSrcStreamCfg;
    struConfigInputInfo.dwInBufferSize = sizeof(struSrcStreamCfg);

    //设置设备视频参数
   	printf("m_lUserID = [%d]\r\n", m_lUserID);
  
    if (!USB_SetDeviceConfig(m_lUserID, USB_SET_SRC_STREAM_TYPE, &struConfigInputInfo, &struConfigOutputInfo))
    {
		m_bPreviewAudio = FALSE;
		m_bCaptureAudio = FALSE;
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_SRC_STREAM_TYPE ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
    }
    printf("SUCCESS USB_SET_SRC_STREAM_TYPE\r\n");
    printf("dwStreamType[%d] bUseAudio[%d]\r\n", struSrcStreamCfg.dwStreamType, struSrcStreamCfg.bUseAudio);
}

void CameraDevice::UsbSetAudioParam()
{
	if (!m_bPreviewAudio && !m_bCaptureAudio)
	{
		printf("Please Open Audio Stream.\r\n");
		return;
	}
	if (USB_INVALID_USERID == m_lUserID)
	{
		printf("Please Login Device.\r\n");
		return;
	}	

    USB_AUDIO_PARAM struWF = { 0 };
    USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
    //选择音频格式
    //GetAudioFormat(1, &struWF); 
    struWF = m_CamAudioCap[0];   //选择音频能力，固定值
    memcpy(&struWF, &m_CamAudioCap[0], sizeof(m_CamAudioCap[0]));   //固定值
    memset(&struConfigInputInfo, 0, sizeof(struConfigInputInfo));
    memset(&struConfigOutputInfo, 0, sizeof(struConfigOutputInfo));

    struConfigInputInfo.lpInBuffer = &struWF;
    struConfigInputInfo.dwInBufferSize = sizeof(struWF);

	printf("m_lUserID = [%d]\r\n", m_lUserID);

    if (!USB_SetDeviceConfig(m_lUserID, USB_SET_AUDIO_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
    {
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_AUDIO_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
    }
    printf("SUCCESS USB_SET_AUDIO_PARAM\r\nPreviewAudio or CaptureAudio\r\n");
}

void CameraDevice::UsbSetOSD()
{
    USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
    memset(&struConfigInputInfo, 0, sizeof(struConfigInputInfo));
    memset(&struConfigOutputInfo, 0, sizeof(struConfigOutputInfo));

    USB_OSD struOsd = { 0 };
    struOsd.byEnabled = 1; //开启osd

    struOsd.struOsdInfo.wLineNums = 2;  //Osd 行数
    struOsd.struOsdInfo.uiWinWidth = 704;
    struOsd.struOsdInfo.uiWinHeight = 576;


    //第一行osd信息
    sprintf((char*)struOsd.struOsdLineList[0].szOsdString, "aaaaaaaaaaaaaaaa");
    struOsd.struOsdLineList[0].uiOffsetx = 0;
    struOsd.struOsdLineList[0].uiOffsety = 0;

    ////第二行osd信息
    sprintf((char*)struOsd.struOsdLineList[1].szOsdString, "bbbbbbbbbbbbbbbb");
    struOsd.struOsdLineList[1].uiOffsetx = 100;
    struOsd.struOsdLineList[1].uiOffsety = 100;

    struConfigInputInfo.lpInBuffer = &struOsd;
    struConfigInputInfo.dwInBufferSize = sizeof(struOsd);

    if (!USB_SetDeviceConfig(m_lUserID, USB_SET_OSD, &struConfigInputInfo, &struConfigOutputInfo))
    {
        DWORD dwError = USB_GetLastError();
        printf("FAILED UsbSetOSD ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
    }
    printf("success UsbSetOSD");
}

void CameraDevice::GetVideoProperty()
{
    USB_VIDEO_PROPERTY struPropertyValue = { 0 };
    USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };

    struConfigOutputInfo.lpOutBuffer = &struPropertyValue;
    struConfigOutputInfo.dwOutBufferSize = sizeof(USB_VIDEO_PROPERTY);

    //设置设备视频属性
    if (!USB_GetDeviceConfig(m_lUserID, USB_GET_VIDEO_BRIGHTNESS, &struConfigInputInfo, &struConfigOutputInfo))
    {
        DWORD dwError = USB_GetLastError();
        printf("FAILED USB_GET_VIDEO_BRIGHTNESS ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
    }
    printf("success USB_GET_VIDEO_BRIGHTNESS");
}

