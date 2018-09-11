
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include  <sys/resource.h> /*setrlimit */

#include "../interface/urpc_test_interface.h"
#include "urpc_engine.h"

#define TAG "TEST_S:"

void *_urpc_server_test_event_callback(URPCHandle handle, int32_t cliHandle, URPC_SOCK_EVT_TYPE_E evtType)
{
    //URPC_TEST_LOGI("client Handle:%d, event:%d",cliHandle, evtType);
    char outIp[32];
    int32_t outPort = 0;
    URPC_RESULT_TYPE_E ret = urpc_server_get_client_info(handle, cliHandle, outIp, sizeof(outIp), &outPort);
    if (ret != EN_URPC_OK)
    {
        URPC_TEST_LOGE("urpc_server_get_client_info FAILED");
        return NULL;
    }
    
	switch(evtType)
	{
		case EN_URPC_SOCK_EVT_TYPE_REGISTER:
			URPC_TEST_LOGT("EN_URPC_SOCK_EVT_TYPE_REGISTER (cliHandle=[%d] [%s:%d])", cliHandle, outIp, outPort);
			break;
		case EN_URPC_SOCK_EVT_TYPE_UNREGISTER:
			URPC_TEST_LOGT("EN_URPC_SOCK_EVT_TYPE_UNREGISTER (cliHandle[%d] [%s:%d])", cliHandle, outIp, outPort);
			break;
		default:
			URPC_TEST_LOGT("evt invalid(handle=%d)", handle);
			break;
	}

	return NULL;
}
  
int _urpc_server_test_process_msg(URPCHandle handle, int cliHandle,int msgType, int32_t seq, char *msg, int msgLen, char *outBuff, int32_t *outBuffLen)
{
    int retMsgLen;
    
	if ((NULL == msg)||(msgLen <= 0))
	{
		URPC_TEST_LOGE("para invalid");
		return -1;
	}

	URPC_TEST_LOGE("handle=%d msgType[%d] len=%d",cliHandle, msgType, msgLen);
	
	switch(msgType)
	{
		case 11:
        {
            URPC_TEST_LOGE("msg=%s", msg);
            //memset(buff, 0, sizeof(buff));
    		URPC_TEST_MSG_PAYLOAD_T *pMsgHeader = (URPC_TEST_MSG_PAYLOAD_T *)outBuff;
    		pMsgHeader->synByte = URPC_TEST_MSG_MAGIC_NUM;
    		pMsgHeader->msgType = 12;
    		pMsgHeader->seq = seq;
            //sprintf(pMsgHeader->data, "%s===user:%d",msg, cliHandle); 
            strcpy(pMsgHeader->data, "HELLO");
    		pMsgHeader->msgLen = strlen(pMsgHeader->data);
            //pMsgHeader->msgLen = 960;
    		
            retMsgLen = sizeof(URPC_TEST_MSG_PAYLOAD_T)+pMsgHeader->msgLen;
            *outBuffLen = retMsgLen;
            URPC_TEST_LOGI("retMsgLen:%d", *outBuffLen);
            break;
        }
        case 13:
        {
            URPC_TEST_LOGE("msg=%s", msg+60000);
    		URPC_TEST_MSG_PAYLOAD_T *pMsgHeader = (URPC_TEST_MSG_PAYLOAD_T *)outBuff;
    		pMsgHeader->synByte = URPC_TEST_MSG_MAGIC_NUM;
    		pMsgHeader->msgType = 14;
    		pMsgHeader->seq = seq;
            strcpy(pMsgHeader->data+60000, "HELLO");
    		pMsgHeader->msgLen = 60000+5;    		
            retMsgLen = sizeof(URPC_TEST_MSG_PAYLOAD_T)+pMsgHeader->msgLen;
            *outBuffLen = retMsgLen;
            URPC_TEST_LOGI("retMsgLen:%d", *outBuffLen);
            break;
        }
        
        
        default:
            URPC_TEST_LOGE("type=%d invalid",msgType);
	}
	
	return 0;
}

void *_urpc_server_test_recv_msg_callback(URPCHandle handle, int32_t cliHandle, uint8_t *inBuff, int32_t inBuffLen, char *outBuff, int32_t *outBuffLen)
{
	if ((NULL == inBuff)||(inBuffLen <= 0))
	{
		URPC_TEST_LOGE("para invalid");
		return NULL;
	}
	
    //URPC_TEST_LOGE("cliHandle:%d, inBuffLen=%d",cliHandle, inBuffLen);
    
	URPC_TEST_MSG_PAYLOAD_T *pMsgHeader = (URPC_TEST_MSG_PAYLOAD_T *)inBuff;


	if (URPC_TEST_MSG_MAGIC_NUM != pMsgHeader->synByte)
	{
		URPC_TEST_LOGE("msg synbyte(0x%x) != 0x%x", pMsgHeader->synByte, URPC_TEST_MSG_MAGIC_NUM);
		return NULL;
	}

	_urpc_server_test_process_msg(handle,cliHandle, pMsgHeader->msgType, pMsgHeader->seq, pMsgHeader->data, pMsgHeader->msgLen, outBuff, outBuffLen);

	//snprintf(outBuff, "[SVR RECV]:%s", pMsgHeader->data, pMsgHeader->msgLen);
	//*outBuffLen = strlen(outBuff);

	return NULL;
}


int main(int argc, char **argv)
{
	URPC_RESULT_TYPE_E ret;
	int svrPort = 7895;
    URPCHandle handle=NULL;

    //signal(SIGILL, SIG_IGN);
    //signal(SIGPIPE, SIG_IGN);

    struct rlimit rt;
 
    /* 设置每个进程允许打开的最大文件数 */
    rt.rlim_max = rt.rlim_cur = 4096;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1)
    {
        printf("setrlimit error\n");
        return -1;
    }

	ret = urpc_server_init(&handle, svrPort);
	if (ret != EN_URPC_OK)
	{
		URPC_TEST_LOGE("urpc_server_init failed");
		return -1;
	}
    
	ret = urpc_server_set_callback(handle, (URPC_FUNC_EVT_CB)_urpc_server_test_event_callback,(URPC_FUNC_MSG_CB)_urpc_server_test_recv_msg_callback);
	if (ret != EN_URPC_OK)
	{
		URPC_TEST_LOGE("urpc_server_set_callback failed");
		return -1;
	}

	URPC_TEST_LOGE("loop.....");
	while(1)
	{
		sleep(5);
	}

	urpc_server_deinit(&handle);
	
	return 0;
}



