#ifndef _CAMERA_DEVICE_H_
#define _CAMERA_DEVICE_H_

#include "DeviceBase.h"
#include "GetStream.h"


//前端命令码
#define CAMERA_BASE 								8
#define CAMERA_GET_VIDEO_CAP           				(CAMERA_BASE+1)		// 获取视频能力集
#define CAMERA_GET_AUDIO_CAP           				(CAMERA_BASE+2)  	// 获取音频能力集
#define CAMERA_GET_VIDEO_PARAM         				(CAMERA_BASE+3)  	// 获取视频参数
#define CAMERA_SET_VIDEO_PARAM         				(CAMERA_BASE+4)  	// 设置视频参数
#define CAMERA_SET_AUDIO_PARAM         				(CAMERA_BASE+5)  	// 设置音频参数
#define CAMERA_SET_SRC_STREAM_TYPE     				(CAMERA_BASE+6)  	// 设置原始码流类型
#define CAMERA_SET_EVENT_CALLBACK      				(CAMERA_BASE+7)  	// 设置事件回调参数
#define CAMERA_SET_ROTATE_ANGLE        				(CAMERA_BASE+8) 	// 设置预览画面旋转角度
#define CAMERA_GET_IRFRAME             				(CAMERA_BASE+9) 	// 获取IR帧
#define CAMERA_INIT_LIVE_DETECT        				(CAMERA_BASE+10) 	// 创建活体算法资源
#define CAMERA_GET_LIVEDETECT          				(CAMERA_BASE+11) 	// 活体检测
#define CAMERA_GET_VIDEO_PROPERTY_CAP				(CAMERA_BASE+12)	// 获取视频属性能力集
#define CAMERA_GET_VIDEO_BRIGHTNESS					(CAMERA_BASE+13)	// 获取视频亮度
#define CAMERA_SET_VIDEO_BRIGHTNESS					(CAMERA_BASE+14)	// 设置视频亮度
#define CAMERA_GET_VIDEO_CONTRAST					(CAMERA_BASE+15)	// 获取视频对比度
#define CAMERA_SET_VIDEO_CONTRAST					(CAMERA_BASE+16)	// 设置视频对比度
#define CAMERA_GET_VIDEO_HUE						(CAMERA_BASE+17)	// 获取视频色调
#define CAMERA_SET_VIDEO_HUE						(CAMERA_BASE+18)	// 设置视频色调
#define CAMERA_GET_VIDEO_SATURATION					(CAMERA_BASE+19)	// 获取视频饱和度
#define CAMERA_SET_VIDEO_SATURATION					(CAMERA_BASE+20)	// 设置视频饱和度
#define CAMERA_GET_VIDEO_SHARPNESS					(CAMERA_BASE+21)	// 获取视频清晰度
#define CAMERA_SET_VIDEO_SHARPNESS					(CAMERA_BASE+22)	// 设置视频清晰度
#define CAMERA_GET_VIDEO_GAMMA						(CAMERA_BASE+23)	// 获取视频伽玛
#define CAMERA_SET_VIDEO_GAMMA						(CAMERA_BASE+24)	// 设置视频伽玛
#define CAMERA_GET_VIDEO_COLORENABLE				(CAMERA_BASE+25)	// 获取视频启用颜色
#define CAMERA_SET_VIDEO_COLORENABLE				(CAMERA_BASE+26)	// 设置视频启用颜色
#define CAMERA_GET_VIDEO_WHITEBALANCE				(CAMERA_BASE+27)	// 获取视频白平衡
#define CAMERA_SET_VIDEO_WHITEBALANCE				(CAMERA_BASE+28)	// 设置视频白平衡
#define CAMERA_GET_VIDEO_BACKLIGHTCOMPENSATION		(CAMERA_BASE+29)	// 获取视频逆光对比
#define CAMERA_SET_VIDEO_BACKLIGHTCOMPENSATION		(CAMERA_BASE+30)	// 设置视频逆光对比
#define CAMERA_GET_VIDEO_GAIN						(CAMERA_BASE+31)	// 获取视频增益
#define CAMERA_SET_VIDEO_GAIN						(CAMERA_BASE+32)	// 设置视频增益
#define CAMERA_GET_VIDEO_POWERLINEFREQUENCY			(CAMERA_BASE+33)	// 获取视频电力线频率
#define CAMERA_SET_VIDEO_POWERLINEFREQUENCY			(CAMERA_BASE+34)	// 设置视频电力线频率
#define CAMERA_GET_VIDEO_PAN						(CAMERA_BASE+35)	// 获取视频全景
#define CAMERA_SET_VIDEO_PAN						(CAMERA_BASE+36)	// 设置视频全景
#define CAMERA_GET_VIDEO_TILT						(CAMERA_BASE+37)	// 获取视频倾斜
#define CAMERA_SET_VIDEO_TILT						(CAMERA_BASE+38)	// 设置视频倾斜
#define CAMERA_GET_VIDEO_ROLL						(CAMERA_BASE+39)	// 获取视频滚动
#define CAMERA_SET_VIDEO_ROLL						(CAMERA_BASE+40)	// 设置视频滚动
#define CAMERA_GET_VIDEO_ZOOM						(CAMERA_BASE+41)	// 获取视频缩放
#define CAMERA_SET_VIDEO_ZOOM						(CAMERA_BASE+42)	// 设置视频缩放
#define CAMERA_GET_VIDEO_EXPOSURE					(CAMERA_BASE+43)	// 获取视频曝光
#define CAMERA_SET_VIDEO_EXPOSURE					(CAMERA_BASE+44)	// 设置视频曝光
#define CAMERA_GET_VIDEO_IRIS						(CAMERA_BASE+45)	// 获取视频光圈
#define CAMERA_SET_VIDEO_IRIS						(CAMERA_BASE+46)	// 设置视频光圈
#define CAMERA_GET_VIDEO_FOCUS						(CAMERA_BASE+47)	// 获取视频焦点
#define CAMERA_SET_VIDEO_FOCUS						(CAMERA_BASE+48)	// 设置视频焦点
#define CAMERA_GET_VIDEO_LOWBRIGHTNESSCOMPENSATION	(CAMERA_BASE+49)	// 获取视频低亮度补偿
#define CAMERA_SET_VIDEO_LOWBRIGHTNESSCOMPENSATION	(CAMERA_BASE+50)	// 设置视频低亮度补偿
#define CAMERA_GET_VIDEO_VOLUME						(CAMERA_BASE+51)	// 获取设备音量
#define CAMERA_SET_VIDEO_VOLUME						(CAMERA_BASE+52)	// 设置设备音量
#define CAMERA_SET_OSD				            	(CAMERA_BASE+53)	// 设置OSD


class CameraDevice : public DeviceBase
{
public:
	CameraDevice();
	virtual void Usage(void);
	virtual void UsbImplement();
    virtual void DoBusiness(int iType, int iDevIndex = 0);

private:
    void GetCamVideoCap();
    void GetCamAudioCap();
    void UsbGetVideoParam();
    void UsbSetVideoParam();
    void UsbSetSrcStreamType();
    void UsbSetAudioParam();
    void UsbSetOSD();
    void GetVideoProperty();

private:
	CGetStream *m_pGetStream;
	int m_nVideoCapCount;
	int m_nAudioCapCount;
	bool m_bPreviewAudio;
	bool m_bCaptureAudio;
	USB_VIDEO_CAPACITY m_CamVideoCap[100];
    USB_AUDIO_PARAM    m_CamAudioCap[100];

};

#endif

