#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "CameraDevice.h"
#include "AcsDevice.h"
#include "ThermalDevice.h"
#include <pthread.h>

typedef struct _thread_data_
{
	DeviceBase* pDevice;
	int iCommand;
}thread_param;


void Usage(void)
{
	printf("Select Device:\r\n");
	PRINTF(CUSTOM_PRINT_MENU);
	PRINTF(CAMERA_DEVICE);
	PRINTF(ACS_DEVICE);
	PRINTF(THERMAL_DEVICE);
	PRINTF(CAMERA_RECORD_THERMAL_PREVIEW);
	PRINTF(THERMAL_PREVIEW_CAMERA_RECORD);
	PRINTF(THERMAL_SET_CAMERA_CALLBACK);
	printf("\t Press q to quit...\r\n");
}

void *ProcCommandThread(void* param)
{
	thread_param* threadParam = (thread_param*)param;
	if (threadParam == NULL) return NULL;

	while (TRUE)
	{
		threadParam->pDevice->DoBusiness(threadParam->iCommand);
		sleep(3);
	}
	
}

int main(int argc, char* argv[])
{
	CameraDevice camera;
	ThermalDevice thermal;
	AcsDevice acs;

	pthread_t tids[2];
	thread_param threadParam[2];
	while (TRUE)
	{
		Usage();
		int iIn = CheckBoardInput();
		switch (iIn)
		{
			case KEYBOARD_INPUT_FAILED:
			{
				printf("KeyBoard Input Invalid Parameters or Exit...\r\n");
				return 0;
			}	
			case CUSTOM_PRINT_MENU:
			{
				break;
			}
			case CAMERA_DEVICE:
			{
				if (!camera.Start())
				{
					return -1;
				}
				break;
			}
			case ACS_DEVICE:
			{
				if (!acs.Start())
				{
					return -1;
				}
				break;
			}
			case THERMAL_DEVICE:
			{
				if (!thermal.Start())
				{
					return -1;
				}
				break;
			}
			case CAMERA_RECORD_THERMAL_PREVIEW:
			{
				camera.DoBusiness(CUSTOM_GET_SDK_VERSION);
				camera.DoBusiness(CUSTOM_USB_INIT);
				camera.DoBusiness(CUSTOM_SET_LOGTOFILE);
				camera.DoBusiness(CUSTOM_GET_DEVICE_COUNT);
				camera.DoBusiness(CUSTOM_ENUM_DEVICE);
				camera.DoBusiness(CUSTOM_LOGIN_DEVICE, 0);

				int iDevNum;
				USB_DEVICE_INFO pDevInfo[MAX_USB_DEV_LEN];
				camera.GetDevInfo(iDevNum, pDevInfo);

				thermal.SetDevInfo(iDevNum, pDevInfo);
				thermal.DoBusiness(CUSTOM_LOGIN_DEVICE, 1);
				
				/*while (TRUE)
				{
					camera.DoBusiness(CUSTOM_STREAM_RECORD);
					thermal.DoBusiness(CUSTOM_STREAM_PREVIEW);
				}*/

				threadParam[0].pDevice = &camera;
				threadParam[0].iCommand = CUSTOM_STREAM_RECORD;
				pthread_create(&tids[0], NULL, ProcCommandThread, &threadParam[0]);
				pthread_detach(tids[0]); 

				threadParam[1].pDevice = &thermal;
				threadParam[1].iCommand = CUSTOM_STREAM_PREVIEW;
				pthread_create(&tids[1], NULL, ProcCommandThread, &threadParam[1]);
				pthread_detach(tids[1]);
				break;
			}
			case THERMAL_PREVIEW_CAMERA_RECORD:
			{
				camera.DoBusiness(CUSTOM_GET_SDK_VERSION);
				camera.DoBusiness(CUSTOM_USB_INIT);
				camera.DoBusiness(CUSTOM_SET_LOGTOFILE);
				camera.DoBusiness(CUSTOM_GET_DEVICE_COUNT);
				camera.DoBusiness(CUSTOM_ENUM_DEVICE);
				camera.DoBusiness(CUSTOM_LOGIN_DEVICE, 1);

				int iDevNum;
				USB_DEVICE_INFO pDevInfo[MAX_USB_DEV_LEN];
				camera.GetDevInfo(iDevNum, pDevInfo);

				thermal.SetDevInfo(iDevNum, pDevInfo);
				thermal.DoBusiness(CUSTOM_LOGIN_DEVICE, 0);

				/*while (TRUE)
				{
					camera.DoBusiness(CUSTOM_STREAM_RECORD);
					thermal.DoBusiness(CUSTOM_STREAM_PREVIEW);
				}*/
				
				threadParam[0].pDevice = &camera;
				threadParam[0].iCommand = CUSTOM_STREAM_RECORD;
				pthread_create(&tids[0], NULL, ProcCommandThread, &threadParam[0]);
				pthread_detach(tids[0]); 

				threadParam[1].pDevice = &thermal;
				threadParam[1].iCommand = CUSTOM_STREAM_PREVIEW;
				pthread_create(&tids[1], NULL, ProcCommandThread, &threadParam[1]);
				pthread_detach(tids[1]);
				break;
			}
			case THERMAL_SET_CAMERA_CALLBACK:
			{
				camera.DoBusiness(CUSTOM_GET_SDK_VERSION);
				camera.DoBusiness(CUSTOM_USB_INIT);
				camera.DoBusiness(CUSTOM_SET_LOGTOFILE);
				camera.DoBusiness(CUSTOM_GET_DEVICE_COUNT);
				camera.DoBusiness(CUSTOM_ENUM_DEVICE);
				camera.DoBusiness(CUSTOM_LOGIN_DEVICE, 1);

				int iDevNum;
				USB_DEVICE_INFO pDevInfo[MAX_USB_DEV_LEN];
				camera.GetDevInfo(iDevNum, pDevInfo);

				thermal.SetDevInfo(iDevNum, pDevInfo);
				thermal.DoBusiness(CUSTOM_LOGIN_DEVICE, 0);
				
				threadParam[0].pDevice = &camera;
				threadParam[0].iCommand = CUSTOM_STREAM_CALLBACK;
				pthread_create(&tids[0], NULL, ProcCommandThread, &threadParam[0]);
				pthread_detach(tids[0]); 

				threadParam[1].pDevice = &thermal;
				threadParam[1].iCommand = THERMAL_GET_SYSTEM_LOCALTIME;
				pthread_create(&tids[1], NULL, ProcCommandThread, &threadParam[1]);
				pthread_detach(tids[1]);
				break;
			}
            default:
            {
                printf("FAILED Unsupported\r\n");
                break;
            }
        }
    }
	return -1;
}
