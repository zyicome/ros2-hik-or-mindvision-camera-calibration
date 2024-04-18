#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "GetStream.h"

using namespace std;

CGetStream::CGetStream(int nDeviceType)
    : m_iCallBackChannel(-1)
	, m_iRecordChannel(-1)
	, fd_1(NULL)
    , fd_2(NULL)
	, m_lUserID(-1)
    , m_nDeviceType(nDeviceType)
{
}

void CGetStream::StartStreamCallback()
{
    if (!SetVideoParam())
    {
        return;
    }

    //启动码流回调
    USB_STREAM_CALLBACK_PARAM struDecCbInfo = { 0 };
    struDecCbInfo.dwStreamType = USB_STREAM_PS_H264;
    struDecCbInfo.pUser = this;
    struDecCbInfo.funcStreamCallBack = fnStreamCallBack(DeviceCallBack);
    struDecCbInfo.dwSize = sizeof(struDecCbInfo);
    m_iCallBackChannel = USB_StartStreamCallback(m_lUserID, &struDecCbInfo);
    printf("m_iCallBackChannel1[%d].\r\n", m_iCallBackChannel);

    if (m_iCallBackChannel < 0)
    {
    	printf("Set Device Stream Callback Parameters Failed, errorcode [%d]\r\n", USB_GetLastError());
    	return;
    }
    printf("USB_StartStreamCallback()\r\n");


    //取流5秒
    sleep(2);

    if (!USB_StopChannel(m_lUserID, m_iCallBackChannel))
    {
        printf("USB_StopChannel Failed, errorcode [%d]\r\n", USB_GetLastError());
    }

    if (fd_1 != NULL)
    {
        fclose(fd_1);
		fd_1 = NULL;
    }
    if (fd_2 != NULL)
    {
        fclose(fd_2);
		fd_2 = NULL;
    }
}

void __stdcall CGetStream::DeviceCallBack(LONG handle, USB_FRAME_INFO *pFrameInfo, void* pUser)
{
	CGetStream *pThis = (CGetStream*)pUser;
	if (pThis != NULL)
	{
		pThis->DeviceCallBackLocal(handle, pFrameInfo, pUser);
	}
}

void CGetStream::DeviceCallBackLocal(LONG handle, USB_FRAME_INFO *pFrameInfo, void* pUser)
{
    printf("DeviceCallBackLocal:handle[%d], StreamType[%d], FrameLen[%d], RealFrameRate[%d]\n",
        handle, pFrameInfo->dwStreamType, pFrameInfo->dwBufSize, pFrameInfo->dwFrameRate);
    return;

    if (pFrameInfo->dwStreamType == USB_STREAM_PS_H264)
    {
        if (fd_1 == NULL)
        {
            if (m_nDeviceType == CAMERA_DEVICE)
            {
                fd_1 = fopen("./CallBack/Camera_ps_h264.ps", "wb+");
            }
            else if (m_nDeviceType == THERMAL_DEVICE)
            {
                fd_1 = fopen("./CallBack/Thermal_ps_h264.ps", "wb+");
            }
            else
            {
                fd_1 = fopen("./CallBack/ps_h264.ps", "wb+");
            }
        }
	    fwrite(pFrameInfo->pBuf, 1, pFrameInfo->dwBufSize, fd_1);
    }
    else if (pFrameInfo->dwStreamType == USB_STREAM_PS_NV12)
    {
        if (fd_2 == NULL)
        {
            if (m_nDeviceType == CAMERA_DEVICE)
            {
                fd_2 = fopen("./CallBack/Camera_ps_nv12.ps", "wb+");
            }
            else if (m_nDeviceType == THERMAL_DEVICE)
            {
                fd_2 = fopen("./CallBack/Thermal_ps_nv12.ps", "wb+");
            }
            else
            {
                fd_2 = fopen("./CallBack/ps_nv12.ps", "wb+");
            }
        }
        fwrite(pFrameInfo->pBuf, 1, pFrameInfo->dwBufSize, fd_2);
    }
    else
    {
        printf("DeviceCallBackLocal invalid FrameType[%d]\r\n", pFrameInfo->dwStreamType);
    }
}

void CGetStream::StartStreamRecord()
{
    if (!SetVideoParam())
    {
        return;
    }
    USB_RECORD_PARAM struRecordParam = { 0 };
    if (m_nDeviceType == CAMERA_DEVICE)
    {
        struRecordParam.dwRecordType = USB_RECORDTYPE_PS_MJPEG;
        strcpy((char*)struRecordParam.szFilePath, "./Record/camera_record.ps");
    }
    else if (m_nDeviceType == THERMAL_DEVICE)
    {
        struRecordParam.dwRecordType = USB_RECORDTYPE_PS_MJPEG;
        strcpy((char*)struRecordParam.szFilePath, "./Record/thermal_ps_mjpeg.ps");
    }
    else
    {
        struRecordParam.dwRecordType = USB_RECORDTYPE_PS_MJPEG;
        strcpy((char*)struRecordParam.szFilePath, "./Record/record_ps_mjpeg.ps");
    }
    struRecordParam.dwSize = sizeof(struRecordParam);
    struRecordParam.bRecordAudio = 0;
    m_iRecordChannel = USB_StartRecord(m_lUserID, &struRecordParam);
    if (m_iRecordChannel < 0)
    {
        DWORD dwError = USB_GetLastError();
        printf("FAILED USBStreamRecord ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
    }
    printf("success USBStreamRecord");

	//取流5秒
    sleep(2);

    if (!USB_StopChannel(m_lUserID, m_iRecordChannel))
    {
        printf("USB_StopChannel Failed, errorcode [%d]\r\n", USB_GetLastError());
    }
}

void CGetStream::StartStreamPreview()
{
    if (!SetVideoParam())
    {
        return;
    }
    USB_PREVIEW_PARAM struPreviewParam = { 0 };
    struPreviewParam.dwStreamType = USB_STREAM_PS_MJPEG;
    struPreviewParam.bUseAudio = 0;
    struPreviewParam.dwSize = sizeof(USB_PREVIEW_PARAM);
    m_iRecordChannel = USB_StartPreview(m_lUserID, &struPreviewParam);
    if (m_iRecordChannel < 0)
    {
        DWORD dwError = USB_GetLastError();
        printf("FAILED StartStreamPreview ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
        return;
    }
    printf("success StartStreamPreview");

	//取流5秒
    sleep(2);

    if (!USB_StopChannel(m_lUserID, m_iRecordChannel))
    {
        printf("USB_StopChannel Failed, errorcode [%d]\r\n", USB_GetLastError());
    }
}

BOOL CGetStream::SetVideoParam()
{
    USB_CONFIG_INPUT_INFO struConfigInputInfo2 = { 0 };
    USB_CONFIG_OUTPUT_INFO struConfigOutputInfo2 = { 0 };
    USB_VIDEO_PARAM struVideoParam = { 0 };

    struVideoParam.dwFramerate = 30;
    if (m_nDeviceType == CAMERA_DEVICE)
    {
        struVideoParam.dwWidth = 1920;   //前端参数配置
        struVideoParam.dwHeight = 1080;
        struVideoParam.dwVideoFormat = USB_STREAM_MJPEG;
    }
    else if (m_nDeviceType == THERMAL_DEVICE)
    {
        struVideoParam.dwWidth = 240;   //热成像参数配置
        struVideoParam.dwHeight = 320;
        struVideoParam.dwVideoFormat = USB_STREAM_MJPEG;
    }
    else
    {
        printf("failed SetVideoParam invalid device type[%d]\r\n", m_nDeviceType);
        return FALSE;
    }

    memset(&struConfigInputInfo2, 0, sizeof(struConfigInputInfo2));
    memset(&struConfigOutputInfo2, 0, sizeof(struConfigOutputInfo2));
    struConfigInputInfo2.lpInBuffer = &struVideoParam;
    struConfigInputInfo2.dwInBufferSize = sizeof(struVideoParam);

    if (USB_SetDeviceConfig(m_lUserID, USB_SET_VIDEO_PARAM, &struConfigInputInfo2, &struConfigOutputInfo2))
    {
        printf("SUCCESS USB_SetDeviceConfig()  USB_SET_VIDEO_PARAM\r\n");
        return TRUE;
    }
    printf("failed USB_SetDeviceConfig() USB_SET_VIDEO_PARAM err[%d]\r\n", USB_GetLastError());
    return FALSE;
}

