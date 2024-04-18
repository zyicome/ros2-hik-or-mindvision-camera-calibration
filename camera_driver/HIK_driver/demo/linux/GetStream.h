#ifndef _GET_STREAM_H_
#define _GET_STREAM_H_

#include "DeviceBase.h"

#define CUSTOM_STREAM_Base			100
#define CUSTOM_STREAM_CALLBACK		(CUSTOM_STREAM_Base+1)	// 开启码流回调
#define CUSTOM_STREAM_RECORD		(CUSTOM_STREAM_Base+2)	// 开启录像
#define CUSTOM_STREAM_PREVIEW		(CUSTOM_STREAM_Base+3)	// 开启预览


class CGetStream
{
public:
	CGetStream(int nDeviceType);
	void SetUserID(int lUserID) { m_lUserID = lUserID; }

public:
	void StartStreamCallback();
    void StartStreamRecord();
	void StartStreamPreview();

private:
	BOOL SetVideoParam(); 

private:
    int m_iCallBackChannel; //码流回调句柄
	int m_iRecordChannel;	//录像句柄
	FILE *fd_1;
	FILE *fd_2;
	int m_lUserID;
	int m_nDeviceType;
	static void __stdcall DeviceCallBack(LONG handle, USB_FRAME_INFO *pFrameInfo, void* pUser);
	void DeviceCallBackLocal(LONG handle, USB_FRAME_INFO *pFrameInfo, void* pUser);

};

#endif

