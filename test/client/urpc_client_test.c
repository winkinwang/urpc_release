
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../interface/urpc_test_interface.h"
#include "urpc_engine.h"

#define TAG "TEST_C:"

int main(int argc, char **argv)
{
	URPC_RESULT_TYPE_E ret;	
	char *svrIp="127.0.0.1";
	int svrPort = 7895;
	char buff[MAX_URPC_ENGINE_BUFFER_LEN];
	char outBuff[1024];
    int retLen = sizeof(buff);
    URPCHandle handle;
    
    if (argc < 2)
    {
		URPC_TEST_LOGE("argc=%d <2,  ./client svrIp svrPORT [clientNum]", argc);
		return -1;
	}   

    svrIp = argv[1];
    svrPort=atoi(argv[2]);

	ret = urpc_client_init(&handle,svrIp, svrPort);
	if (ret != EN_URPC_OK)
	{
		URPC_TEST_LOGE("trpc_client_init failed");
		return -1;
	}

	ret = urpc_client_start(handle);
	if (ret != EN_URPC_OK)
	{
		URPC_TEST_LOGE("trpc_client_start failed");
		return -1;
	}

	URPC_TEST_LOGE("loop.....");
    int i=0, msgLen, n=10, times = 0;
	while(n--)
	{
		usleep(10000);//n++;continue;
        memset(buff, 0, sizeof(buff));
        #if 0
		URPC_TEST_MSG_PAYLOAD_T *pMsgHeader = (URPC_TEST_MSG_PAYLOAD_T *)buff;
		pMsgHeader->synByte = URPC_TEST_MSG_MAGIC_NUM;
		pMsgHeader->msgType = 11;
        sprintf(pMsgHeader->data, "this is test client msg(%d):%d",svrPort, i++);        
		pMsgHeader->msgLen = strlen(pMsgHeader->data);
		
        msgLen = sizeof(URPC_TEST_MSG_PAYLOAD_T)+pMsgHeader->msgLen;
        retLen=sizeof(buff);
        ret = urpc_client_send_msg(handle, buff, msgLen, outBuff, &retLen,5000);
        if (ret != 0)
        {
            URPC_TEST_LOGE("%s trpc_client_send_with_reply ret(%d)",__func__, ret);
            break;
        }
        
    	pMsgHeader = (URPC_TEST_MSG_PAYLOAD_T *)outBuff;

    	if (URPC_TEST_MSG_MAGIC_NUM+1 != pMsgHeader->synByte)
    	{
    		URPC_TEST_LOGE("msg synbyte[0x%x] != 0x%x",pMsgHeader->synByte, URPC_TEST_MSG_MAGIC_NUM);
    		continue;
    	}

        URPC_TEST_LOGE("recv return[type:%d] msg:%s, len:%d\n", pMsgHeader->msgType, pMsgHeader->data, pMsgHeader->msgLen);
        #else
        URPC_TEST_MSG_PAYLOAD_T *pMsgHeader = (URPC_TEST_MSG_PAYLOAD_T *)buff;
		pMsgHeader->synByte = URPC_TEST_MSG_MAGIC_NUM;
		pMsgHeader->msgType = 13;
		pMsgHeader->seq = times++;
        strcpy(pMsgHeader->data+60000, "I am client");
		pMsgHeader->msgLen = 60000+11; 
        
        msgLen = sizeof(URPC_TEST_MSG_PAYLOAD_T)+pMsgHeader->msgLen;
        retLen=sizeof(buff);
        ret = urpc_client_send_msg(handle, buff, msgLen, outBuff, &retLen,5000);
        if (ret != 0)
        {
            URPC_TEST_LOGE("%s urpc_client_send_msg ret(%d)",__func__, ret);
            break;
        }
        
        pMsgHeader = (URPC_TEST_MSG_PAYLOAD_T *)outBuff;

        if (URPC_TEST_MSG_MAGIC_NUM != pMsgHeader->synByte)
        {
            URPC_TEST_LOGE("msg synbyte[0x%x] != 0x%x",pMsgHeader->synByte, URPC_TEST_MSG_MAGIC_NUM);
            continue;
        }

        URPC_TEST_LOGI("recv return[seq:%d] msg:%s, len:%d\n", pMsgHeader->seq, pMsgHeader->data+60000, pMsgHeader->msgLen);
        #endif
    }

    sleep(1);
	urpc_client_deinit(&handle);
    sleep(1);

    URPC_TEST_LOGE("loop end and exit.....");
	return 0;
}



