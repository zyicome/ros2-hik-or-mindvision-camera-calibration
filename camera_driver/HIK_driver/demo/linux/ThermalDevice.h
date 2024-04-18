#ifndef _THERMAL_DEVICE_H_
#define _THERMAL_DEVICE_H_

#include "DeviceBase.h"
#include "GetStream.h"


//热成像命令码
#define THERMAL_BASE 									8
#define THERMAL_GET_SYSTEM_DEVICE_INFO     				(THERMAL_BASE + 1)	//获取设备信息
#define THERMAL_SET_SYSTEM_REBOOT     					(THERMAL_BASE + 2)  //设备重启
#define THERMAL_SET_SYSTEM_RESET     					(THERMAL_BASE + 3)  //恢复默认
#define THERMAL_GET_SYSTEM_HARDWARE_SERVER     			(THERMAL_BASE + 4)  //获取硬件服务参数
#define THERMAL_SET_SYSTEM_HARDWARE_SERVER     			(THERMAL_BASE + 5)  //设置硬件服务参数
#define THERMAL_GET_SYSTEM_LOCALTIME     				(THERMAL_BASE + 6)  //获取系统本地时间
#define THERMAL_SET_SYSTEM_LOCALTIME     				(THERMAL_BASE + 7)  //设置系统本地时间
#define THERMAL_GET_IMAGE_BRIGHTNESS    				(THERMAL_BASE + 8)  //获取图像亮度参数
#define THERMAL_SET_IMAGE_BRIGHTNESS     				(THERMAL_BASE + 9)  //设置图像亮度参数
#define THERMAL_GET_IMAGE_CONTRAST     					(THERMAL_BASE + 10) //获取图像对比度参数
#define THERMAL_SET_IMAGE_CONTRAST     					(THERMAL_BASE + 11) //设置图像对比度参数
#define THERMAL_SET_SYSTEM_UPDATE_FIRMWARE     			(THERMAL_BASE + 12) //设备升级
#define THERMAL_SET_IMAGE_BACKGROUND_CORRECT     		(THERMAL_BASE + 13) //一键背景校正
#define THERMAL_GET_SYSTEM_DIAGNOSED_DATA     			(THERMAL_BASE + 14) //诊断信息导出
#define THERMAL_SET_IMAGE_MANUAL_CORRECT     			(THERMAL_BASE + 15) //一键手动校正
#define THERMAL_GET_IMAGE_ENHANCEMENT     				(THERMAL_BASE + 16)	//获取图像增强参数
#define THERMAL_SET_IMAGE_ENHANCEMENT     				(THERMAL_BASE + 17) //设置图像增强参数
#define THERMAL_GET_IMAGE_VIDEO_ADJUST     				(THERMAL_BASE + 18) //获取视频调整参数
#define THERMAL_SET_IMAGE_VIDEO_ADJUST     				(THERMAL_BASE + 19) //设置视频调整参数
#define THERMAL_GET_THERMOMETRY_BASIC_PARAM     		(THERMAL_BASE + 20) //获取测温基本参数
#define THERMAL_SET_THERMOMETRY_BASIC_PARAM     		(THERMAL_BASE + 21) //设置测温基本参数
#define THERMAL_GET_THERMOMETRY_MODE                    (THERMAL_BASE + 22) //获取测温模式
#define THERMAL_SET_THERMOMETRY_MODE                    (THERMAL_BASE + 23) //设置测温模式
#define THERMAL_GET_THERMOMETRY_REGIONS         		(THERMAL_BASE + 24) //获取测温规则参数
#define THERMAL_SET_THERMOMETRY_REGIONS         		(THERMAL_BASE + 25) //设置测温规则参数
#define THERMAL_GET_THERMAL_ALG_VERSION                 (THERMAL_BASE + 26) //获取热成像相关算法版本信息
#define THERMAL_GET_THERMAL_STREAM_PARAM                (THERMAL_BASE + 27) //获取热成像码流参数
#define THERMAL_SET_THERMAL_STREAM_PARAM                (THERMAL_BASE + 28) //设置热成像码流参数
#define THERMAL_GET_TEMPERATURE_CORRECT         		(THERMAL_BASE + 29) //获取测温修正参数
#define THERMAL_SET_TEMPERATURE_CORRECT         		(THERMAL_BASE + 30) //设置测温修正参数
#define THERMAL_GET_BLACK_BODY                  		(THERMAL_BASE + 31) //获取黑体参数
#define THERMAL_SET_BLACK_BODY                  		(THERMAL_BASE + 32) //设置黑体参数
#define THERMAL_GET_BODYTEMP_COMPENSATION       		(THERMAL_BASE + 33) //获取体温补偿参数
#define THERMAL_SET_BODYTEMP_COMPENSATION       		(THERMAL_BASE + 34) //设置体温补偿参数
#define THERMAL_GET_JPEGPIC_WITH_APPENDDATA     		(THERMAL_BASE + 35) //获取热图
#define THERMAL_GET_ROI_MAX_TEMPERATURE_SEARCH  		(THERMAL_BASE + 36) //ROI最高温信息查询
#define THERMAL_GET_P2P_PARAM                   		(THERMAL_BASE + 37) //获取全屏测温参数
#define THERMAL_SET_P2P_PARAM                   		(THERMAL_BASE + 38) //设置全屏测温参数
#define THERMAL_POST_DOUBLE_LIGHTS_CORRECT       		(THERMAL_BASE + 39) //双光校准
#define THERMAL_GET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL	(THERMAL_BASE + 40) //获取双光校准坐标控制参数
#define THERMAL_SET_DOUBLE_LIGHTS_CORRECT_POINTS_CTRL   (THERMAL_BASE + 41) //设置双光校准坐标控制参数
#define THERMAL_GET_THERMOMETRY_CALIBRATION_FILE      	(THERMAL_BASE + 42) //测温标定文件导出
#define THERMAL_SET_THERMOMETRY_CALIBRATION_FILE       	(THERMAL_BASE + 43) //测温标定文件导入
#define THERMAL_GET_DEVICE_UPGRADE_STATE				(THERMAL_BASE + 44) //获取设备升级状态
#define THERMAL_CLOSE_UPGRADE							(THERMAL_BASE + 45) //关闭升级
#define THERMAL_GET_COMMAND_STATE						(THERMAL_BASE + 46)	//获取命令状态


class ThermalDevice : public DeviceBase
{
public:
	ThermalDevice();
	virtual void Usage(void);
	virtual void UsbImplement();
	virtual void DoBusiness(int iType, int iDevIndex = 0);

private:
	void GetSystemDeviceInfo();
	void SetSystemReboot();
	void SetSystemReset();
	void GetSystemHardwareServer();
	void SetSystemHardwareServer();
	void GetSystemLocalTime();
	void SetSystemLocalTime();
	void GetImageBrightness();
	void SetImageBrightness();
	void GetImageContrast();
	void SetImageContrast();
	void SetImageBackgroundCorrect();
	void GetSystemDiagnoseData();
	void SetImageManualCorrect();
	void GetImageEnhance();
	void SetImageEnhancement();
	void GetImageVideoAdjust();
	void SetImageVideoAdjust();
	void GetThermometryBasicParam();
	void SetThermometryBasicParam();
	void GetThermometryMode();
	void SetThermometryMode();
	void GetThermometryRegions();
	void SetThermometryRegions();
	void GetThermalAlgVersion();
	void GetThermalStreamParam();
	void SetThermalStreamParam();
	void GetTemperatureCorrect();
	void SetTemperatureCorrect();
	void GetBlackBody();
	void SetBlackBody();
	void GetBodytempCompensation();
	void SetBodytempCompensation();
	void GetJpegpicWithAppenddata();
	void GetRoiMaxTemperatureSearch();
	void GetP2PParam();
	void SetP2PParam();
	void PostDoubleLightsCorrect();
	void GetDoubleLightsCorrectPointsCtrl();
	void SetDoubleLightsCorrectPointCtrl();
	void GetThermometryCalibrationFile();
	void SetThermometryCalibrationFile();
	void GetCommandState();

private:
	CGetStream *m_pGetStream;
	FILE *fd;
};

#endif

