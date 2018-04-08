#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#define LIST_BUFFER
#define MAX_SPEAK_BUF_SIZE	100*1024
#define MAX_CMD_SIZE		150			//������б������
#define MAX_RESP_SIZE		256			//����ָ�����ݰ���С

enum{
	STATUS_START = 1,
	STATUS_STOP  = 0,
};

enum{
	VIDEO_STATUS  		= 0,
	VIDEO_QUALITY 		= 1,
	AUDIO_STATUS  		= 2,
	SPEAK_STATUS  		= 3,
	REC_VIDEO_STATUS  	= 4,
	REC_AUDIO_STATUS  	= 5,
};

enum{
	SND_VIDEO_LD		= 0x00F0,
	SND_VIDEO_HD		= 0x00F1,
	SND_VIDEO			= 0x00F2,
	SND_AUDIO			= 0x00F3,
	SND_NOTIC	    	= 0x00F4,
	SND_FILE	    	= 0x00F5,
};

enum PARAMS_SET_E{
	ENABLE_VIDEO		= 0x00F1,
	ENABLE_AUDIO		= 0x00F2,
	ENABLE_VQUALITY		= 0x00F3,
	ENABLE_1VN			= 0x00F4,
	SET_1VN_RTMP_RUL	= 0x00F6,
};

typedef struct Conn_t{
	int id; 		//connection_id
	int vstatus;	//ͼ��״̬
	int vquality;	//ͼ��������
	int astatus;	//��Ƶ״̬
	int pstatus;	//�Խ�״̬
	unsigned char* m_pRevcBuf;
	int m_curPos;
}Conn;

#pragma   pack(1)
typedef struct P2pHead_t
{
	int  			flag;		//��Ϣ��ʼ��ʶ
	unsigned int 	size;		//���շ�����Ϣ��С(��������Ϣͷ)
	char 			type;		//Э������1 json 2 json ����
	char			protoType;	//��Ϣ����1 ����2Ӧ��3֪ͨ
	int 			msgType;	//IOTYPE��Ϣ����
	char 			reserve[6];	//����
}P2pHead;
#pragma   pack()

typedef struct RemoteCmd_t{
	int id;
	int len;
	unsigned char* body;
}RemoteCmd;

typedef struct MassData_t{
	int type;
	int len;
	unsigned char* body;
}MassData;

typedef struct CmdRespInfo_t{
	int 	len;		//�������ݳ���
	int 	enable;		//�Ƿ񷵻�
}CmdRespInfo;

#endif

