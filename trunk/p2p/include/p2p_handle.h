#ifndef _P2P_HANDLE_H_
#define _P2P_HANDLE_H_

#include <stdio.h>
#include "p2p_define.h"
#include "p2p_transport.h" 
#include "p2p_dispatch.h"
#include "cqueue.h"
#include "cmap.h"
#include "lock_utils.h"

enum HANDLE_TYPE_E
{
	HANDLE_TYPE_NONE		= -1,
	HANDLE_TYPE_TCP 		= 0,
	HANDLE_TYPE_P2P			= 1,
	HANDLE_TYPE_TCP_PUSH 	= 2,
	HANDLE_TYPE_TCP_RTMP 	= 3,
};

typedef struct clnt_node_s{
	int id;
}clnt_node;

typedef struct p2p_handle_t
{
	int					m_type;
	
	char				m_CfgServer[64];
	char				m_CfgUser[64];
	char				m_CfgPwd[64];
	unsigned short		m_CfgServerPort;
	int					m_Iwait;
}p2p_handle;

/*
	����uid���ַ�������
����ֵ: int 
			HANDLE_TYPE_P2P	��p2pģʽ
			HANDLE_TYPE_TCP ��TCP turnģʽ
����: char* uid Ψһ��ʶUID����NULL
�û���ʹ�ô˽ӿ�ѡ���Ӧ�����dispathce server�� turn server ���� port
*/
int p2p_handle_uid_type(char* uid);
/*
	����������
����ֵ: ���ָ��
����:	char* uid 	Ψһ��ʶUID����NULL
*/
p2p_handle* p2p_handle_create(char* uid);

/*
	���ٷ���
����ֵ: ��
����:	p2p_handle* handle	���ָ��
*/
void p2p_handle_destory(p2p_handle* handle);

/*
	��ʼ������
����ֵ: int
			0	�ɹ�
			��0	ʧ��
����:	p2p_handle* handle		���ָ��
		char* dispathce_server	���ɷ�������ַ(��ʽ:IP:port)����NULL����Ϊ""�ַ���ʱ��������ǿ��ʹ��TURN����
		char* server			Turn����IP����NULL
		unsigned short port		Turn����˿�
		char* uid				Ψһ��ʶUID����NULL
		char* pwd				Turn��������
		int tcp					P2p Turn���ӷ������Ƿ�ʹ��TCP���ӷ�ʽ�����ҽ���ʹ��P2Pģʽʱ��Ч
��ʼ���󣬽��Զ����ӷ����������������ڲ������˶�����������
*/
int p2p_handle_init(p2p_handle* handle, char* dispathce_server, char* server, unsigned short port, char* uid, char* pwd, int tcp);

/*
	���񷴳�ʼ��
����ֵ: int
			0	�ɹ�
			��0	ʧ��
����:	p2p_handle* handle		���ָ��
*/
int p2p_handle_uninit(p2p_handle* handle);
/*
	�������������(��Ϣ/ý������)
����ֵ: int
			0	�ɹ�
			��0	ʧ��
����:	p2p_handle* handle		���ָ��
		unsigned char* data		����
		unsigned int len		���ݳ���
		int type				�������ͣ�ͬp2p_handle_av_swtich�Ĳ���type
		unsigned int time_stamp	ý������ʱ���
		char is_key				ý�������Ƿ�ؼ�֡
*/
int p2p_handle_write(p2p_handle* handle, unsigned char* data, unsigned int len, int type, unsigned int time_stamp, char is_key);

/*
	��ȡ����Ƶ�Ƿ�������
����ֵ: int
			0	�ɹ�
			��0	ʧ��
����:	p2p_handle* handle		���ָ��
		int type
				SND_AUDIO		��Ƶ
				SND_VIDEO_HD	������Ƶ
				SND_VIDEO_LD	������Ƶ
*/
int p2p_handle_av_swtich(p2p_handle* handle, int type);

/*
	��������
����ֵ: int
			0	�ɹ�
			��0	ʧ��
����:	p2p_handle* handle		���ָ��
		int type
				ENABLE_AUDIO		��Ƶ
				ENABLE_VIDEO		��Ƶ
		int val
				��type=ENABLE_AUDIO	0��ʾ��ֹ��Ƶ 1��ʾ������Ƶ
				��type=ENABLE_VIDEO	0��ʾ��ֹ��Ƶ 1��ʾ������Ƶ
				������ο�PARAMS_SET_E
*/
int p2p_handle_param_set(p2p_handle* handle, int type, char* val);

#endif
