#include <stdio.h>
#include <string.h>
#include "AcsDevice.h"

using namespace std;

AcsDevice::AcsDevice()
{
	m_bResource = TRUE;
}


void AcsDevice::Usage(void)
{
	printf("Select Acs Capacity:\r\n");
	PRINTF(CUSTOM_PRINT_MENU);
	PRINTF(CUSTOM_GET_SDK_VERSION);
	PRINTF(CUSTOM_USB_INIT);
	PRINTF(CUSTOM_SET_LOGTOFILE);
	PRINTF(CUSTOM_GET_DEVICE_COUNT);
	PRINTF(CUSTOM_ENUM_DEVICE);
	PRINTF(CUSTOM_LOGIN_DEVICE);
	PRINTF(CUSTOM_DEVICE_LOGOUT);
	PRINTF(CUSTOM_CLEANUP);
	PRINTF(ACS_SET_BEEP_AND_FLICKER);
	PRINTF(ACS_GET_CARD_ISSUE_VERSION);
	PRINTF(ACS_CTRL_RESET_RFC);
	PRINTF(ACS_SET_CARD_PROTO);
	PRINTF(ACS_GET_ACTIVATE_CARD);
	PRINTF(ACS_CTRL_STOP_CARD_OPER);
	PRINTF(ACS_SET_M1_PWD_VERIFY);
	PRINTF(ACS_GET_M1_READ_BLOCK);
	PRINTF(ACS_SET_M1_WRITE_BLOCK);
	PRINTF(ACS_SET_M1_MODIFY_SCB);
	PRINTF(ACS_SET_M1_BLOCK_ADD_VALUE);
	PRINTF(ACS_SET_M1_BLOCK_MINUS_VALUE);
	PRINTF(ACS_CTRL_M1_BLOCK_TO_REG);
	PRINTF(ACS_CTRL_M1_REG_TO_BLOCK);
	PRINTF(ACS_SET_M1_MIFARE_PACK);
	PRINTF(ACS_SET_CARD_PARAM);
	PRINTF(ACS_GET_CPU_CARD_RESET);
	PRINTF(ACS_SET_CPU_CARD_PACK);
	PRINTF(ACS_GET_CERTIFICATE_INFO);
	PRINTF(ACS_GET_CERTIFICATE_ADD_ADDR_INFO);
	PRINTF(ACS_GET_CERTIFICATE_MAC);
	PRINTF(ACS_GET_IC_CARD_NO);
	PRINTF(ACS_DETECT_CARD);
	PRINTF(ACS_SET_IDENTITY_INFO);
	PRINTF(ACS_GET_EXTERNAL_DEV_INFO);
	PRINTF(ACS_SET_FINGER_PRINT_OPER_PARAM);
	PRINTF(ACS_CAPTURE_FINGER_PRINT);
	PRINTF(ACS_GET_FINGER_PRINT_CONTRAST_RESULT);
	PRINTF(ACS_CPU_CARD_ENCRYPT_CFG);
	PRINTF(ACS_SET_M1_SECTION_ENCRYPT);
	PRINTF(ACS_SET_SYSTEM_UPDATE_FIRMWARE);
	PRINTF(ACS_GET_DEVICE_UPGRADE_STATE);
	PRINTF(ACS_CLOSE_UPGRADE);
	PRINTF(ACS_TRANS_CONFIG);
	PRINTF(ACS_ACTIVE_DEVICE);
	printf("\t Press q to quit...\r\n");
}

void AcsDevice::UsbImplement()
{
	while (TRUE)
	{
		int iIn = CheckBoardInput();
		DoBusiness(iIn);
    }
}

void AcsDevice::DoBusiness(int iType, int iDevIndex)
{
	switch (iType)
	{
		case KEYBOARD_INPUT_FAILED:
		{
			printf("Acs Device Exit...\r\n");
			return;
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
			break;
		}
		case CUSTOM_DEVICE_LOGOUT:
		{
			DeviceLogout();
			break;
		}
		case CUSTOM_CLEANUP: //反初始化
		{	
			FuncSdkCleanup();
			break;
		}
		case ACS_SET_BEEP_AND_FLICKER:
		{
			SetBeepAndFlicker();
			break;
		}
		case ACS_GET_CARD_ISSUE_VERSION:
		{
			GetCardIssueVersion();
			break;
		}
		case ACS_CTRL_RESET_RFC:
		{
			CtrlResetRfc();
			break;
		}
		case ACS_SET_CARD_PROTO:
		{
			SetCardProto();
			break;
		}
		case ACS_GET_ACTIVATE_CARD:
		{
			GetActivateCard();
			break;
		}
		case ACS_CTRL_STOP_CARD_OPER:
		{
			CtrlStopCardOper();
			break;
		}
		case ACS_SET_M1_PWD_VERIFY:
		{
			SetM1PwdVerify();
			break;
		}
		case ACS_GET_M1_READ_BLOCK:
		{
			GetM1ReadBlock();
			break;
		}
		case ACS_SET_M1_WRITE_BLOCK:
		{
			SetM1WriteBlock();
			break;
		}
		case ACS_SET_M1_MODIFY_SCB:
		{
			SetM1ModifyScb();
			break;
		}
		case ACS_SET_M1_BLOCK_ADD_VALUE:
		{
			SetM1BlockAddValue();
			break;
		}
		case ACS_SET_M1_BLOCK_MINUS_VALUE:
		{
			SetM1BlockMinusValue();
			break;
		}
		case ACS_CTRL_M1_BLOCK_TO_REG:
		{
			CtrlM1BlockToReg();
			break;
		}
		case ACS_CTRL_M1_REG_TO_BLOCK:
		{
			CtrlM1RegToBlock();
			break;
		}
		case ACS_SET_M1_MIFARE_PACK:
		{
			SetM1MifarePack();
			break;
		}
		case ACS_SET_CARD_PARAM:
		{
			SetCardParam();
			break;
		}
		case ACS_GET_CPU_CARD_RESET:
		{
			GetCpuCardReset();
			break;
		}
		case ACS_SET_CPU_CARD_PACK:
		{
			SetCpuCardPack();
			break;
		}
		case ACS_GET_CERTIFICATE_INFO:
		{
			GetCertificateInfo();
			break;
		}
		case ACS_GET_CERTIFICATE_ADD_ADDR_INFO:
		{
			GetCertificateAddAddrInfo();
			break;
		}
		case ACS_GET_CERTIFICATE_MAC:
		{
			GetCertificateMac();
			break;
		}
		case ACS_GET_IC_CARD_NO:
		{
			GetICCardNo();
			break;
		}
		case ACS_DETECT_CARD:
		{
			DetectCard();
			break;
		}
		case ACS_SET_IDENTITY_INFO:
		{
			SetIdentityInfo();
			break;
		}
		case ACS_GET_EXTERNAL_DEV_INFO:
		{
			GetExternalDevInfo();
			break;
		}
		case ACS_SET_FINGER_PRINT_OPER_PARAM:
		{
			SetFingerPrintOperParam();
			break;
		}
		case ACS_CAPTURE_FINGER_PRINT:
		{
			CaptureFingerPrint();
			break;
		}
		case ACS_GET_FINGER_PRINT_CONTRAST_RESULT:
		{
			GetFingerPrintContrastResult();
			break;
		}
		case ACS_CPU_CARD_ENCRYPT_CFG:
		{
			CpuCardEncryptCfg();
			break;
		}
		case ACS_SET_M1_SECTION_ENCRYPT:
		{
			SetM1SectionEncrypt();
			break;
		}
		case ACS_SET_SYSTEM_UPDATE_FIRMWARE: // 设备升级
		{
			SetSystemUpdateFirmware();
			GetDeviceUpgradeState();
			break;
		}
		case ACS_GET_DEVICE_UPGRADE_STATE:  // 获取设备升级状态
		{
			GetDeviceUpgradeState();
			break;
		}
		case ACS_CLOSE_UPGRADE: //关闭升级 
		{
			CloseUpgradeHandle();
			break;
		}
		case ACS_TRANS_CONFIG:
		{
			TransConfigIn();	//下发图片
			TransConfigOut();	//接收图片
			break;
		}
		case ACS_ACTIVE_DEVICE:
		{
			ActiveDevice();
			break;
		}
		default:
		{
			printf("FAILED Unsupported\r\n");
			break;
		}
	}
}

void AcsDevice::SetBeepAndFlicker()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_BEEP_AND_FLICKER struBeepAndFlicker = { 0 };

	struBeepAndFlicker.dwSize = sizeof(struBeepAndFlicker);
	struBeepAndFlicker.byBeepType = 2;
	struBeepAndFlicker.byBeepCount = 3;
	struBeepAndFlicker.byFlickerType = 2;
	struBeepAndFlicker.byFlickerCount = 3;

	struConfigInputInfo.lpInBuffer = &struBeepAndFlicker;
	struConfigInputInfo.dwInBufferSize = sizeof(struBeepAndFlicker);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_BEEP_AND_FLICKER, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_BEEP_AND_FLICKER ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_BEEP_AND_FLICKER\r\n");
	}
}

void AcsDevice::GetCardIssueVersion()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CARD_ISSUE_VERSION struCardIssueVersion = { 0 };

	struCardIssueVersion.dwSize = sizeof(struCardIssueVersion);

	struConfigOutputInfo.lpOutBuffer = &struCardIssueVersion;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struCardIssueVersion);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_CARD_ISSUE_VERSION, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_CARD_ISSUE_VERSION ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_CARD_ISSUE_VERSION szDeviceName[%s], szSerialNumber[%s], dwSoftwareVersion[0x%X], wYear[%d], byMonth[%d], byDay[%d], byLanguage[%d]\r\n", 
				struCardIssueVersion.szDeviceName, struCardIssueVersion.szSerialNumber, struCardIssueVersion.dwSoftwareVersion, 
				struCardIssueVersion.wYear, struCardIssueVersion.byMonth, struCardIssueVersion.byDay, struCardIssueVersion.byLanguage);
	}
}

void AcsDevice::CtrlResetRfc()
{
	if (!USB_Control(m_lUserID, USB_CTRL_RESET_RFC, NULL))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_CTRL_RESET_RFC ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_CTRL_RESET_RFC\r\n");
	}
}

void AcsDevice::SetCardProto()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CARD_PROTO struCardProto = { 0 };

	struCardProto.dwSize = sizeof(struCardProto);
	struCardProto.byProto = 1;

	struConfigInputInfo.lpInBuffer = &struCardProto;
	struConfigInputInfo.dwInBufferSize = sizeof(struCardProto);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_CARD_PROTO, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_CARD_PROTO ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_CARD_PROTO\r\n");
	}
}

void AcsDevice::GetActivateCard()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_WAIT_SECOND struWaitSecond = { 0 };
	USB_ACTIVATE_CARD_RES struActivateCardRes= { 0 };

	struWaitSecond.dwSize = sizeof(struWaitSecond);
	struWaitSecond.byWait = 5;

	struConfigInputInfo.lpInBuffer = &struWaitSecond;
	struConfigInputInfo.dwInBufferSize = sizeof(struWaitSecond);

	struActivateCardRes.dwSize = sizeof(struActivateCardRes);

	struConfigOutputInfo.lpOutBuffer = &struActivateCardRes;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struActivateCardRes);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_ACTIVATE_CARD, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_ACTIVATE_CARD ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_ACTIVATE_CARD byCardType[%d], bySerialLen[%d], bySerial[%s], bySelectVerifyLen[%d], bySelectVerify[%s]\r\n", 
				struActivateCardRes.byCardType, struActivateCardRes.bySerialLen, (char*)struActivateCardRes.bySerial, 
				struActivateCardRes.bySelectVerifyLen, (char*)struActivateCardRes.bySelectVerify);
	}
}

void AcsDevice::CtrlStopCardOper()
{
	if (!USB_Control(m_lUserID, USB_CTRL_STOP_CARD_OPER, NULL))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_CTRL_STOP_CARD_OPER ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_CTRL_STOP_CARD_OPER\r\n");
	}
}

void AcsDevice::SetM1PwdVerify()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_PWD_VERIFY_INFO struM1PwdVerifyInfo = { 0 };

	struM1PwdVerifyInfo.dwSize = sizeof(struM1PwdVerifyInfo);
	struM1PwdVerifyInfo.byPasswordType = 1;
	struM1PwdVerifyInfo.bySectionNum = 1;
	struM1PwdVerifyInfo.byPassword[0] = 0xff;
	struM1PwdVerifyInfo.byPassword[1] = 0xff;
	struM1PwdVerifyInfo.byPassword[2] = 0xff;
	struM1PwdVerifyInfo.byPassword[3] = 0xff;
	struM1PwdVerifyInfo.byPassword[4] = 0xff;
	struM1PwdVerifyInfo.byPassword[5] = 0xff;

	struConfigInputInfo.lpInBuffer = &struM1PwdVerifyInfo;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1PwdVerifyInfo);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_M1_PWD_VERIFY, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_M1_PWD_VERIFY ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_M1_PWD_VERIFY\r\n");
	}
}

void AcsDevice::GetM1ReadBlock()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_BLOCK_ADDR struM1BlockAddr = { 0 };
	USB_M1_BLOCK_DATA struM1BlockData = { 0 };

	struM1BlockAddr.dwSize = sizeof(struM1BlockAddr);
	struM1BlockAddr.wAddr = 4;

	struConfigInputInfo.lpInBuffer = &struM1BlockAddr;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1BlockAddr);

	struM1BlockData.dwSize = sizeof(struM1BlockData);

	struConfigOutputInfo.lpOutBuffer = &struM1BlockData;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struM1BlockData);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_M1_READ_BLOCK, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_M1_READ_BLOCK ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_M1_READ_BLOCK byData[%s]\r\n", (char*)struM1BlockData.byData);
	}
}

void AcsDevice::SetM1WriteBlock()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_BLOCK_WRITE_DATA struM1BlockWriteData = { 0 };

	struM1BlockWriteData.dwSize = sizeof(struM1BlockWriteData);
	struM1BlockWriteData.wAddr = 5;
	struM1BlockWriteData.byDataLen = 3;
	struM1BlockWriteData.byData[0] = '1';
	struM1BlockWriteData.byData[1] = '2';
	struM1BlockWriteData.byData[2] = '3';

	struConfigInputInfo.lpInBuffer = &struM1BlockWriteData;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1BlockWriteData);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_M1_WRITE_BLOCK, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_M1_WRITE_BLOCK ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_M1_WRITE_BLOCK\r\n");
	}
}

void AcsDevice::SetM1ModifyScb()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_MODIFY_SCB struM1ModifyScb = { 0 };

	struM1ModifyScb.dwSize = sizeof(struM1ModifyScb);
	struM1ModifyScb.bySectionNum = 1;
	struM1ModifyScb.byPasswordA[0] = 0x00;
	struM1ModifyScb.byPasswordA[1] = 0x00;
	struM1ModifyScb.byPasswordA[2] = 0x00;
	struM1ModifyScb.byPasswordA[3] = 0x00;
	struM1ModifyScb.byPasswordA[4] = 0x00;
	struM1ModifyScb.byPasswordA[5] = 0x00;
	struM1ModifyScb.byCtrlBits[0] = 0x00;
	struM1ModifyScb.byCtrlBits[1] = 0x00;
	struM1ModifyScb.byCtrlBits[2] = 0x00;
	struM1ModifyScb.byCtrlBits[3] = 0x00;
	struM1ModifyScb.byPasswordB[0] = 0xff;
	struM1ModifyScb.byPasswordB[1] = 0xff;
	struM1ModifyScb.byPasswordB[2] = 0xff;
	struM1ModifyScb.byPasswordB[3] = 0xff;
	struM1ModifyScb.byPasswordB[4] = 0xff;
	struM1ModifyScb.byPasswordB[5] = 0xff;

	struConfigInputInfo.lpInBuffer = &struM1ModifyScb;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1ModifyScb);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_M1_MODIFY_SCB, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_M1_MODIFY_SCB ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_M1_MODIFY_SCB\r\n");
	}
}

void AcsDevice::SetM1BlockAddValue()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_BLOCK_OPER struM1BlockOper = { 0 };
	USB_M1_BLOCK_OPER_RES struM1BlockOperRes = { 0 };

	struM1BlockOper.dwSize = sizeof(struM1BlockOper);
	struM1BlockOper.wAddr = 1;
	struM1BlockOper.wValue = 1;

	struConfigInputInfo.lpInBuffer = &struM1BlockOper;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1BlockOper);

	struM1BlockOperRes.dwSize = sizeof(struM1BlockOperRes);

	struConfigOutputInfo.lpOutBuffer = &struM1BlockOperRes;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struM1BlockOperRes);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_M1_BLOCK_ADD_VALUE, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_M1_BLOCK_ADD_VALUE ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_M1_BLOCK_ADD_VALUE\r\n");
	}
}

void AcsDevice::SetM1BlockMinusValue()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_BLOCK_OPER struM1BlockOper = { 0 };
	USB_M1_BLOCK_OPER_RES struM1BlockOperRes = { 0 };

	struM1BlockOper.dwSize = sizeof(struM1BlockOper);
	struM1BlockOper.wAddr = 1;
	struM1BlockOper.wValue = 1;

	struConfigInputInfo.lpInBuffer = &struM1BlockOper;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1BlockOper);

	struM1BlockOperRes.dwSize = sizeof(struM1BlockOperRes);

	struConfigOutputInfo.lpOutBuffer = &struM1BlockOperRes;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struM1BlockOperRes);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_M1_BLOCK_MINUS_VALUE, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_M1_BLOCK_MINUS_VALUE ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_M1_BLOCK_MINUS_VALUE\r\n");
	}
}

void AcsDevice::CtrlM1BlockToReg()
{
	USB_CONTROL_INPUT_INFO struConfigInputInfo = { 0 };
	USB_M1_BLOCK_ADDR struM1BlockAddr = { 0 };

	struM1BlockAddr.dwSize = sizeof(struM1BlockAddr);
	struM1BlockAddr.wAddr = 1;

	struConfigInputInfo.lpInBuffer = &struM1BlockAddr;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1BlockAddr);

	if (!USB_Control(m_lUserID, USB_CTRL_M1_BLOCK_TO_REG, &struConfigInputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_CTRL_M1_BLOCK_TO_REG ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_CTRL_M1_BLOCK_TO_REG\r\n");
	}
}

void AcsDevice::CtrlM1RegToBlock()
{
	USB_CONTROL_INPUT_INFO struConfigInputInfo = { 0 };
	USB_M1_BLOCK_ADDR struM1BlockAddr = { 0 };

	struM1BlockAddr.dwSize = sizeof(struM1BlockAddr);
	struM1BlockAddr.wAddr = 1;

	struConfigInputInfo.lpInBuffer = &struM1BlockAddr;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1BlockAddr);

	if (!USB_Control(m_lUserID, USB_CTRL_M1_REG_TO_BLOCK, &struConfigInputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_CTRL_M1_REG_TO_BLOCK ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_CTRL_M1_REG_TO_BLOCK\r\n");
	}
}

void AcsDevice::SetM1MifarePack()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_MF_PACK struM1MifarePackIn = { 0 };
	USB_M1_MF_PACK struM1MifarePackOut = { 0 };

	struM1MifarePackIn.dwSize = sizeof(struM1MifarePackIn);
	struM1MifarePackIn.byBufLen = 10;
	memcpy(struM1MifarePackIn.byBuf, "0123456789", 10);
	struM1MifarePackIn.byDelay = 0;

	struConfigInputInfo.lpInBuffer = &struM1MifarePackIn;
	struConfigInputInfo.dwInBufferSize = sizeof(struM1MifarePackIn);

	struM1MifarePackOut.dwSize = sizeof(struM1MifarePackOut);

	struConfigOutputInfo.lpOutBuffer = &struM1MifarePackOut;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struM1MifarePackOut);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_M1_MF_PACK, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_M1_MIFARE_PACK ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_M1_MIFARE_PACK\r\n");
	}
}

void AcsDevice::SetCardParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CARD_PARAM struCardParam = { 0 };

	struCardParam.dwSize = sizeof(struCardParam);
	struCardParam.byCardType = 1;
	struCardParam.byCardProto = 1;

	struConfigInputInfo.lpInBuffer = &struCardParam;
	struConfigInputInfo.dwInBufferSize = sizeof(struCardParam);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_CARD_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_CARD_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_CARD_PARAM\r\n");
	}
}

void AcsDevice::GetCpuCardReset()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CPU_CARD_RESET_RES struCpuCardResetRes = { 0 };

	struCpuCardResetRes.dwSize = sizeof(struCpuCardResetRes);

	struConfigOutputInfo.lpOutBuffer = &struCpuCardResetRes;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struCpuCardResetRes);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_CPU_CARD_RESET, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_CPU_CARD_RESET ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_CPU_CARD_RESET byBufLen[%d], byBuf[%s]\r\n", struCpuCardResetRes.byBufLen, (char*)struCpuCardResetRes.byBuf);
	}
}

void AcsDevice::SetCpuCardPack()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CPU_CARD_PACK struCpuCardPackIn = { 0 };
	USB_CPU_CARD_PACK struCpuCardPackOut = { 0 };

	struCpuCardPackIn.dwSize = sizeof(struCpuCardPackIn);
	struCpuCardPackIn.byBufLen = 10;
	memcpy(struCpuCardPackIn.byBuf, "0123456789", 10);
	struCpuCardPackIn.byDelay = 0;

	struConfigInputInfo.lpInBuffer = &struCpuCardPackIn;
	struConfigInputInfo.dwInBufferSize = sizeof(struCpuCardPackIn);

	struCpuCardPackOut.dwSize = sizeof(struCpuCardPackOut);

	struConfigOutputInfo.lpOutBuffer = &struCpuCardPackOut;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struCpuCardPackOut);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_CPU_CARD_PACK, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_CPU_CARD_PACK ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_CPU_CARD_PACK\r\n");
	}
}

void AcsDevice::GetCertificateInfo()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CERTIFICATE_INFO struCertificateInfo = { 0 };

	struCertificateInfo.dwSize = sizeof(struCertificateInfo);

	struConfigOutputInfo.lpOutBuffer = &struCertificateInfo;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struCertificateInfo);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_CERTIFICATE_INFO, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_CERTIFICATE_INFO ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_CERTIFICATE_INFO wWordInfoSize[%d], wPicInfoSize[%d], wFingerPrintInfoSize[%d], byCertificateType[%d], byWordInfo[%s], byPicInfo[%s], byFingerPrintInfo[%s]\r\n", 
				struCertificateInfo.wWordInfoSize, struCertificateInfo.wPicInfoSize, struCertificateInfo.wFingerPrintInfoSize, 
				struCertificateInfo.byCertificateType, (char*)struCertificateInfo.byWordInfo,
				(char*)struCertificateInfo.byPicInfo, (char*)struCertificateInfo.byFingerPrintInfo);
	}
}

void AcsDevice::GetCertificateAddAddrInfo()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CERTIFICATE_ADD_ADDR_INFO struCertificateAddAddrInfo = { 0 };

	struCertificateAddAddrInfo.dwSize = sizeof(struCertificateAddAddrInfo);

	struConfigOutputInfo.lpOutBuffer = &struCertificateAddAddrInfo;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struCertificateAddAddrInfo);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_CERTIFICATE_ADD_ADDR_INFO, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_CERTIFICATE_ADD_ADDR_INFO ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_CERTIFICATE_ADD_ADDR_INFO wAddrInfoSize[%d], byAddAddrInfo[%s]\r\n", 
				struCertificateAddAddrInfo.wAddrInfoSize, (char*)struCertificateAddAddrInfo.byAddAddrInfo);
	}
}

void AcsDevice::GetCertificateMac()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CERTIFICATE_MAC struCertificateMac = { 0 };

	struCertificateMac.dwSize = sizeof(struCertificateMac);

	struConfigOutputInfo.lpOutBuffer = &struCertificateMac;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struCertificateMac);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_CERTIFICATE_MAC, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_CERTIFICATE_MAC ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_CERTIFICATE_MAC byMac[%s]\r\n", (char*)struCertificateMac.byMac);
	}
}

void AcsDevice::GetICCardNo()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_IC_CARD_NO struICCardNo = { 0 };

	struICCardNo.dwSize = sizeof(struICCardNo);

	struConfigOutputInfo.lpOutBuffer = &struICCardNo;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struICCardNo);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_IC_CARD_NO, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_IC_CARD_NO ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_IC_CARD_NO byCardNo[%s]\r\n", struICCardNo.byCardNo);
	}
}

void AcsDevice::DetectCard()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_DETECT_CARD_COND struDetectCardCond = { 0 };
	USB_DETECT_CARD_CFG struDetectCardCfg = { 0 };

	struDetectCardCond.dwSize = sizeof(struDetectCardCond);
	struDetectCardCond.byWait = 10;

	struConfigInputInfo.lpInBuffer = &struDetectCardCond;
	struConfigInputInfo.dwInBufferSize = sizeof(struDetectCardCond);

	struDetectCardCfg.dwSize = sizeof(struDetectCardCfg);

	struConfigOutputInfo.lpOutBuffer = &struDetectCardCfg;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struDetectCardCfg);

	if (!USB_SetDeviceConfig(m_lUserID, USB_DETECT_CARD, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_DETECT_CARD ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_DETECT_CARD byCardStatus[%d]\r\n", struDetectCardCfg.byCardStatus);
	}
}

void AcsDevice::SetIdentityInfo()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_IDENTITY_INFO_CFG struIdentifyInfoCfg = { 0 };

	struIdentifyInfoCfg.dwSize = sizeof(struIdentifyInfoCfg);
	struIdentifyInfoCfg.wPicInfoSize = 10;
	struIdentifyInfoCfg.wFingerPrintInfoSize = 10;
	memcpy(struIdentifyInfoCfg.byPicInfo, "0123456789", 10);
	memcpy(struIdentifyInfoCfg.byFingerPrintInfo, "0123456789", 10);

	struConfigInputInfo.lpInBuffer = &struIdentifyInfoCfg;
	struConfigInputInfo.dwInBufferSize = sizeof(struIdentifyInfoCfg);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_IDENTITY_INFO, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_IDENTITY_INFO ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_IDENTITY_INFO\r\n");
	}
}

void AcsDevice::GetExternalDevInfo()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_EXTERNAL_DEV_INFO struExternalDevInfo = { 0 };

	struExternalDevInfo.dwSize = sizeof(struExternalDevInfo);

	struConfigOutputInfo.lpOutBuffer = &struExternalDevInfo;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struExternalDevInfo);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_EXTERNAL_DEV_INFO, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_EXTERNAL_DEV_INFO ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_EXTERNAL_DEV_INFO szFPModuleSoftVersion[%s], szFPModuleSerialNumber[%s], szSecurityModuleSerialNumber[%s]\r\n", 
				struExternalDevInfo.szFPModuleSoftVersion, struExternalDevInfo.szFPModuleSerialNumber, struExternalDevInfo.szSecurityModuleSerialNumber);
	}
}

void AcsDevice::SetFingerPrintOperParam()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_FINGER_PRINT_OPER_PARAM struFingerPrintOperParam = { 0 };

	struFingerPrintOperParam.dwSize = sizeof(struFingerPrintOperParam);
	struFingerPrintOperParam.byFPCompareType = 1;
	struFingerPrintOperParam.byFPCaptureType = 1;
	struFingerPrintOperParam.byFPCompareTimeout = 1;
	struFingerPrintOperParam.byFPCompareMatchLevel = 1;

	struConfigOutputInfo.lpOutBuffer = &struFingerPrintOperParam;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struFingerPrintOperParam);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_FINGER_PRINT_OPER_PARAM, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_FINGER_PRINT_OPER_PARAM ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_FINGER_PRINT_OPER_PARAM\r\n");
	}
}

void AcsDevice::CaptureFingerPrint()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_FINGER_PRINT_COND struFingerPrintCond = { 0 };
	USB_FINGER_PRINT struFingerPrint = { 0 };

	struFingerPrintCond.dwSize = sizeof(struFingerPrintCond);
	struFingerPrintCond.byWait = 10;
	struFingerPrintCond.byFPType = 1;

	struConfigInputInfo.lpInBuffer = &struFingerPrintCond;
	struConfigInputInfo.dwInBufferSize = sizeof(struFingerPrintCond);

	struFingerPrint.dwSize = sizeof(struFingerPrint);

	struConfigOutputInfo.lpOutBuffer = &struFingerPrint;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struFingerPrint);

	if (!USB_GetDeviceConfig(m_lUserID, USB_CAPTURE_FINGER_PRINT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_CAPTURE_FINGER_PRINT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_CAPTURE_FINGER_PRINT dwFPBufferSize[%d], pFPBuffer[%s], dwFPSize[%d], byFPType[%d], byResult[%d], byFPTemplateQuality[%d]\r\n", 
				struFingerPrint.dwFPBufferSize, struFingerPrint.pFPBuffer, struFingerPrint.dwFPSize, 
				struFingerPrint.byFPType, struFingerPrint.byResult, struFingerPrint.byFPTemplateQuality);
	}
}

void AcsDevice::GetFingerPrintContrastResult()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_FINGER_PRINT_CONTRAST_RESULT struFingerPrintContrastResult = { 0 };

	struFingerPrintContrastResult.dwSize = sizeof(struFingerPrintContrastResult);

	struConfigOutputInfo.lpOutBuffer = &struFingerPrintContrastResult;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struFingerPrintContrastResult);

	if (!USB_GetDeviceConfig(m_lUserID, USB_GET_FINGER_PRINT_CONTRAST_RESULT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_GET_FINGER_PRINT_CONTRAST_RESULT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_GET_FINGER_PRINT_CONTRAST_RESULT byResult[%d], byFPTemplateQuality[%d]\r\n", 
				struFingerPrintContrastResult.byResult, struFingerPrintContrastResult.byFPTemplateQuality);
	}
}

void AcsDevice::CpuCardEncryptCfg()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_CPU_CARD_ENCRYPT struCardEncrypt = { 0 };
	USB_CPU_CARD_ENCRYPT_RES struCardEncryptRes = { 0 };

	struCardEncrypt.dwSize = sizeof(struCardEncrypt);
	struCardEncrypt.byCardType = 2;

	struConfigInputInfo.lpInBuffer = &struCardEncrypt;
	struConfigInputInfo.dwInBufferSize = sizeof(struCardEncrypt);

	struCardEncryptRes.dwSize = sizeof(struCardEncryptRes);

	struConfigOutputInfo.lpOutBuffer = &struCardEncryptRes;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struCardEncryptRes);

	if (!USB_SetDeviceConfig(m_lUserID, USB_CPU_CARD_ENCRYPT_CFG, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_CPU_CARD_ENCRYPT_CFG ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_CPU_CARD_ENCRYPT_CFG byTryTimes[%d]\r\n", struCardEncryptRes.byTryTimes);
	}
}

void AcsDevice::SetM1SectionEncrypt()
{
	USB_CONFIG_INPUT_INFO struConfigInputInfo = { 0 };
	USB_CONFIG_OUTPUT_INFO struConfigOutputInfo = { 0 };
	USB_M1_SECTION_ENCRYPT struSectionEncrypt = { 0 };
	USB_M1_SECTION_ENCRYPT_RES struSectionEncryptRes = { 0 };

	struSectionEncrypt.dwSize = sizeof(struSectionEncrypt);
	struSectionEncrypt.bySectionID = 15;
	struSectionEncrypt.byKeyType = 1;
	struSectionEncrypt.byKeyAContent[0] = 0xff;
	struSectionEncrypt.byKeyAContent[1] = 0xff;
	struSectionEncrypt.byKeyAContent[2] = 0xff;
	struSectionEncrypt.byKeyAContent[3] = 0xff;
	struSectionEncrypt.byKeyAContent[4] = 0xff;
	struSectionEncrypt.byKeyAContent[5] = 0xff;
	struSectionEncrypt.byNewKeyType = 0;
	struSectionEncrypt.byCtrlBits[0] = 0xff;
	struSectionEncrypt.byCtrlBits[1] = 0x07;
	struSectionEncrypt.byCtrlBits[2] = 0x80;
	struSectionEncrypt.byCtrlBits[3] = 0x69;

	struConfigInputInfo.lpInBuffer = &struSectionEncrypt;
	struConfigInputInfo.dwInBufferSize = sizeof(struSectionEncrypt);

	struSectionEncryptRes.dwSize = sizeof(struSectionEncryptRes);

	struConfigOutputInfo.lpOutBuffer = &struSectionEncryptRes;
	struConfigOutputInfo.dwOutBufferSize = sizeof(struSectionEncryptRes);

	if (!USB_SetDeviceConfig(m_lUserID, USB_SET_M1_SECTION_ENCRYPT, &struConfigInputInfo, &struConfigOutputInfo))
	{
		DWORD dwError = USB_GetLastError();
		printf("FAILED USB_SET_M1_SECTION_ENCRYPT ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
	}
	else
	{
		printf("SUCCESS USB_SET_M1_SECTION_ENCRYPT byStatus[%d]\r\n", struSectionEncryptRes.byStatus);
	}
}

void AcsDevice::TransConfigIn()
{
	char szOutBuf[10 * 1024] = { 0 };
	char szRequest[64] = "POST /ISAPI/AccessControl/addVisitorPicture?format=json";
	char szJson[1024] = "{\r\n\"filePathType\": \"binary\",\r\n\"pictureURL\": \"test\",\r\n\"uuid\": \"test\"}";

	//读取图片
	FILE *fd = NULL;
	int iReadSize = 0;
	BYTE *pData = new BYTE[BUFFER_LEN];
	if (NULL == pData)
	{
		printf("FAILED USB_TransConfig new BYTE\r\n");
		return;
	}
	fd = fopen("./USBSDKLog/AcsIn.jpg", "rb");
	fseek(fd, 0, SEEK_END);
	iReadSize = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	fread(pData, 1, iReadSize, fd);
	fclose(fd);
	fd = NULL;

	USB_MIME_UNIT struUnit[2] = { 0 };
	// 第一段数据
	struUnit[0].pContent = szJson;
	struUnit[0].dwContentLen = strlen(szJson);
	memcpy(struUnit[0].szContentType, "application/json", strlen("application/json"));
	memcpy(struUnit[0].szFilename, "test.json", strlen("test.json"));
	memcpy(struUnit[0].szName, "test", strlen("test"));

	// 第二段数据
	struUnit[1].pContent = (char*)pData;
	struUnit[1].dwContentLen = iReadSize;
	memcpy(struUnit[1].szContentType, "image/jpeg", strlen("image/jpeg"));
	memcpy(struUnit[1].szName, "test", strlen("test"));
	memcpy(struUnit[1].szFilename, "test.jepg", strlen("test.jpeg"));

    USB_PT_PARAM struPtParam = { 0 };
	struPtParam.pInBuffer = (void*)struUnit;
	struPtParam.dwInSize = 2 * sizeof(USB_MIME_UNIT);
	struPtParam.byNumOfMultiPart = 2;
    struPtParam.pRequestUrl = (void*)szRequest;        	//请求URL
    struPtParam.dwRequestUrlLen = strlen(szRequest);	//请求URL长度
    struPtParam.pOutBuffer = (void*)szOutBuf;           //输出缓冲区
    struPtParam.dwOutSize = 10 * 1024;                  //输出缓冲区大小 
	struPtParam.dwRecvTimeOut = 5000;
    if (!USB_TransConfig(m_lUserID, &struPtParam))
    {
        DWORD dwError = USB_GetLastError();
		printf("FAILED USB_TransConfig ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
    }
	else
	{
		printf("SUCCESS USB_TransConfig\r\n");
	}
}

void AcsDevice::TransConfigOut()
{

}

void AcsDevice::ActiveDevice()
{
	USB_DEVICE_INFO struUsbDeviceInfo = { 0 };
	USB_USER_LOGIN_INFO struCurUsbLoginInfo = { 0 };

	memcpy(&struUsbDeviceInfo, &m_aDevInfo[0], sizeof(USB_DEVICE_INFO));

	struCurUsbLoginInfo.dwSize = sizeof(USB_USER_LOGIN_INFO);
    struCurUsbLoginInfo.dwTimeout = 5000;//登录超时时间(5秒)
    struCurUsbLoginInfo.dwVID = struUsbDeviceInfo.dwVID;
    struCurUsbLoginInfo.dwPID = struUsbDeviceInfo.dwPID;

    memcpy(struCurUsbLoginInfo.szSerialNumber, struUsbDeviceInfo.szSerialNumber, MAX_SERIAL_NUMBER_LEN);
    memcpy(struCurUsbLoginInfo.szUserName, "admin", strlen("admin"));
    memcpy(struCurUsbLoginInfo.szPassword, "12345", strlen("12345"));

    if(!USB_Active(&struCurUsbLoginInfo))
	{
        DWORD dwError = USB_GetLastError();
		printf("FAILED USB_Active ErrorCode = [%d], ErrorMsg = [%s]\r\n", dwError, USB_GetErrorMsg(dwError));
    }
	else
	{
		printf("SUCCESS USB_Active\r\n");
	}
}
