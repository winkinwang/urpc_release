
#ifndef  _TRPC_ENGINE_INTERFACE_H_
#define  _TRPC_ENGINE_INTERFACE_H_

#define URPC_TEST_MSG_MAGIC_NUM 0xAA5555AA

typedef struct
{
	int32_t synByte;
	int32_t msgType;
	int32_t msgLen;
	int32_t seq;
	char data[0];
}URPC_TEST_MSG_PAYLOAD_T;


#define URPC_TEST_LOGI(fmt, ...) {printf(TAG"[%s]%s(%d) "fmt"\n", __FILE__,__func__,__LINE__, ##__VA_ARGS__);}
#define URPC_TEST_LOGW(fmt, ...) {printf(TAG"[%s]%s(%d) "fmt"\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}
#define URPC_TEST_LOGE(fmt, ...) {printf(TAG"[%s]%s(%d) "fmt"\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}
#define URPC_TEST_LOGT(fmt, ...) {printf(TAG"[%s]%s(%d) "fmt"\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}

#endif

