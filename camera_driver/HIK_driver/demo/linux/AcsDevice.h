#ifndef _ACS_DEVICE_H_
#define _ACS_DEVICE_H_

#include "DeviceBase.h"


//门禁命令码
#define ACS_BASE								8
#define ACS_SET_BEEP_AND_FLICKER        		(ACS_BASE + 1)	//蜂鸣器及显示灯控制
#define ACS_GET_CARD_ISSUE_VERSION      		(ACS_BASE + 2)	//发卡器版本获取
#define ACS_CTRL_RESET_RFC              		(ACS_BASE + 3)
#define ACS_SET_CARD_PROTO              		(ACS_BASE + 4)	//设置操作卡协议类型
#define ACS_GET_ACTIVATE_CARD           		(ACS_BASE + 5)	//激活卡
#define ACS_CTRL_STOP_CARD_OPER         		(ACS_BASE + 6)
#define ACS_SET_M1_PWD_VERIFY           		(ACS_BASE + 7)	//扇区带密码验证
#define ACS_GET_M1_READ_BLOCK           		(ACS_BASE + 8)	//读卡指定块数据
#define ACS_SET_M1_WRITE_BLOCK          		(ACS_BASE + 9)	//写卡指定块数据
#define ACS_SET_M1_MODIFY_SCB           		(ACS_BASE + 10)	//指定扇区控制块修改
#define ACS_SET_M1_BLOCK_ADD_VALUE      		(ACS_BASE + 11)
#define ACS_SET_M1_BLOCK_MINUS_VALUE    		(ACS_BASE + 12)
#define ACS_CTRL_M1_BLOCK_TO_REG        		(ACS_BASE + 13)
#define ACS_CTRL_M1_REG_TO_BLOCK        		(ACS_BASE + 14)
#define ACS_SET_M1_MIFARE_PACK          		(ACS_BASE + 15)
#define ACS_SET_CARD_PARAM              		(ACS_BASE + 16)
#define ACS_GET_CPU_CARD_RESET          		(ACS_BASE + 17)
#define ACS_SET_CPU_CARD_PACK           		(ACS_BASE + 18)
#define ACS_GET_CERTIFICATE_INFO           		(ACS_BASE + 19)
#define ACS_GET_CERTIFICATE_ADD_ADDR_INFO  		(ACS_BASE + 20)
#define ACS_GET_CERTIFICATE_MAC            		(ACS_BASE + 21)
#define ACS_GET_IC_CARD_NO                 		(ACS_BASE + 22)
#define ACS_DETECT_CARD                 		(ACS_BASE + 23)
#define ACS_SET_IDENTITY_INFO           		(ACS_BASE + 24)
#define ACS_GET_EXTERNAL_DEV_INFO       		(ACS_BASE + 25)
#define ACS_SET_FINGER_PRINT_OPER_PARAM 		(ACS_BASE + 26)
#define ACS_CAPTURE_FINGER_PRINT         		(ACS_BASE + 27)
#define ACS_GET_FINGER_PRINT_CONTRAST_RESULT	(ACS_BASE + 28)
#define ACS_CPU_CARD_ENCRYPT_CFG             	(ACS_BASE + 29)
#define ACS_SET_M1_SECTION_ENCRYPT           	(ACS_BASE + 30)	//M1卡指定扇区加密
#define ACS_SET_SYSTEM_UPDATE_FIRMWARE			(ACS_BASE + 31)	//升级
#define ACS_GET_DEVICE_UPGRADE_STATE			(ACS_BASE + 32)	//获取升级状态
#define ACS_CLOSE_UPGRADE						(ACS_BASE + 33)	//关闭升级
#define ACS_TRANS_CONFIG						(ACS_BASE + 34)	//ISAPI透传
#define ACS_ACTIVE_DEVICE						(ACS_BASE + 35)	//激活设备


class AcsDevice : public DeviceBase
{
public:
	AcsDevice();
	virtual void Usage(void);
	virtual void UsbImplement();
	virtual void DoBusiness(int iType, int iDevIndex = 0);

private:
	void SetBeepAndFlicker();
	void GetCardIssueVersion();
	void CtrlResetRfc();
	void SetCardProto();
	void GetActivateCard();
	void CtrlStopCardOper();
	void SetM1PwdVerify();
	void GetM1ReadBlock();
	void SetM1WriteBlock();
	void SetM1ModifyScb();
	void SetM1BlockAddValue();
	void SetM1BlockMinusValue();
	void CtrlM1BlockToReg();
	void CtrlM1RegToBlock();
	void SetM1MifarePack();
	void SetCardParam();
	void GetCpuCardReset();
	void SetCpuCardPack();
	void GetCertificateInfo();
	void GetCertificateAddAddrInfo();
	void GetCertificateMac();
	void GetICCardNo();
	void DetectCard();
	void SetIdentityInfo();
	void GetExternalDevInfo();
	void SetFingerPrintOperParam();
	void CaptureFingerPrint();
	void GetFingerPrintContrastResult();
	void CpuCardEncryptCfg();
	void SetM1SectionEncrypt();
	void TransConfigIn();
	void TransConfigOut();
	void ActiveDevice();
};


#endif
