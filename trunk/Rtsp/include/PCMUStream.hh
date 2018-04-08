/******************************************************************************

                  ��Ȩ���� (C), 2012-2022, Goscam

 ******************************************************************************
  �� �� ��   : 
  �� �� ��   : ����
  ��    ��   : chenjx
  ��������   : 2014��10��10��
  ����޸�   :
  ��������   : 
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��6��5��
    ��    ��   : chenjx
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef _PCMU_STREAM_HH
#define _PCMU_STREAM_HH
#include "FramedSource.hh"
#include "OnDemandServerMediaSubsession.hh"
#include "SimpleRTPSink.hh"
#include "stream_manager.h"

class PCMUStream: public FramedSource {
public:
	static PCMUStream* createNew(UsageEnvironment& env, int sub);
	unsigned samplingFrequency() const { return fSamplingFrequency; }
	unsigned numChannels() const { return fNumChannels; }
	char const* configStr() const { return fConfigStr; }
	// returns the 'AudioSpecificConfig' for this stream (in ASCII form)

private:
	PCMUStream(UsageEnvironment& env, int sub, u_int8_t profile,u_int8_t samplingFrequencyIndex, u_int8_t channelConfiguration);
	// called only by createNew()
	virtual ~PCMUStream();

	static void incomingDataHandler(PCMUStream* source);
	void incomingDataHandler1();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();

private:
	unsigned fSamplingFrequency;
	unsigned fNumChannels;
	unsigned fuSecsPerFrame;
	char fConfigStr[5];

	shm_stream_t* 		   m_StreamList;
	unsigned int m_ref;
};



class PCMUServerMediaSubsession: public OnDemandServerMediaSubsession{
public:
	static PCMUServerMediaSubsession* createNew(UsageEnvironment& env, int sub, Boolean reuseFirstSource);
protected:
	PCMUServerMediaSubsession(UsageEnvironment& env, int sub, Boolean reuseFirstSource);
	// called only by createNew();
	virtual ~ PCMUServerMediaSubsession();

protected: // redefined virtual functions
	virtual FramedSource* createNewStreamSource(unsigned clientSessionId,unsigned& estBitrate);
	virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                		unsigned char rtpPayloadTypeIfDynamic,
				       	FramedSource* inputSource);
	int sub;
};

#endif
