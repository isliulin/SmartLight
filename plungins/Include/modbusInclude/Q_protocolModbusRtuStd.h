//*
//*
//* Q_protocolModbusTcpServerStandard.h
//*
//*

#ifndef __Q_PROTOCOL_MODBUS_RTU_STD_H_INCLUDED__
#define __Q_PROTOCOL_MODBUS_RTU_STD_H_INCLUDED__
#ifdef WINDOWS_ENV
#pragma warning(disable:4251)
#endif
#include "Q_frameInclude.h"
#include "Q_ModbusRtuStdDef.h"
#include "Q_ModbusDefine.h"
#include "Q_runingUnitDefine.h"
#include <vector>
using namespace std;
class Q_protocolModbusRtuStdCommand : public Q_protocolCommandBase
{
public:
	Q_protocolModbusRtuStdCommand(void);
	virtual ~Q_protocolModbusRtuStdCommand(void);

public:
	//设备地址
	inline void					setDestinationId(unsigned char nId) { m_nDestinationId = nId;}
	inline unsigned char		getDestinationId() { return m_nDestinationId;}
	//命令类型
	inline void					setCommandModbusType(Q_Modbus_CommandType eType) { m_commandCDTType = eType;}
	inline Q_Modbus_CommandType    getCommandModbusType() { return m_commandCDTType;}

	inline void					setCommandModbusStatus(Q_Modbus_CommandStatus eStatus) { m_commandCDTStatus = eStatus;}
	inline Q_Modbus_CommandStatus	getCommandModbusStatus() { return m_commandCDTStatus;}

	//寄存器地址
	inline void					setObjectIndex(int nIndex) { m_nObjectIndex = nIndex;}
	inline int		getObjectIndex() { return m_nObjectIndex;}
	//值信息
	inline void					setSwitchValue(bool bVal) { m_bOpen = bVal;}
	inline bool					getSwitchValue() { return m_bOpen;}
	inline void					setAnalogValue(float fValue) { m_fValue = fValue;}
	inline float				getAnalogValue() { return m_fValue;}
	inline void					setIntValue(int nValue) { m_nValue = nValue;}
	inline int				    getIntValue() { return m_nValue;}
	//设置最大处理次数有时信息不反馈， 程序要根据这些内容来删除命令
	inline void				    setMaxTryCount(int nMaxTryCount) { m_nMaxTryCount=nMaxTryCount;}
	inline int				    getMaxTryCount() { return m_nMaxTryCount;}
	inline void				    setCurTryNum(int nCurTryNum) { m_nCurTryNum=nCurTryNum;}
	inline int				    getCurTryNum() { return m_nCurTryNum;}
	int m_curIdx;
protected:
	unsigned char				m_nDestinationId; //站编号
	Q_Modbus_CommandType			m_commandCDTType;//命令类型
	Q_Modbus_CommandStatus			m_commandCDTStatus;//状态默认设定选择
	int				m_nObjectIndex;//站里面的设备编号
	bool						m_bOpen;/// 数字量
	float						m_fValue;//模拟量
	int                         m_nValue;//数字量
	int                         m_nMaxTryCount;//最大试验数
	int                         m_nCurTryNum;//当前实验数
};





/** 
* @interface Q_protocolModbusTcpServerStandardCommandManager
* @brief modbus tcp server通讯规约命令管理
* @author yangxi
* @date 2012-5-23
* @see 
* @bug No know bugs so far.
*/
class Q_ModbusRtuStdCmdMgr : public Q_protocolCommandManagerBase
{
public:
	Q_ModbusRtuStdCmdMgr(void);
	virtual ~Q_ModbusRtuStdCmdMgr(void);

public:
	virtual bool				addCommand(Q_protocolCommandBase* pCommand);
	virtual bool	addCommand(Q_CommandVal *v_val);
	Q_protocolModbusRtuStdCommand*		findCommand(Q_Modbus_CommandType eType,Q_Modbus_CommandStatus eStatus,int nObjIndex);
	bool						removeCommand(Q_Modbus_CommandType eType,Q_Modbus_CommandStatus eStatus,int nObjIndex);
	bool						removeCommand(Q_protocolCommandBase* pCommand);


};






/** 
* @interface Q_protocolModbusTcpServerStandardSetting 
* @brief modbus tcp 服务端通讯规约配置
* @author yangxi
* @date 2012-5-23
* @see 
* @bug No know bugs so far.
*/
class Q_protcolModbusRtuStdSetting : public Q_protocolSettingBase
{
public:
	Q_protcolModbusRtuStdSetting(void);
	virtual ~Q_protcolModbusRtuStdSetting(void);
	void setFilePath(char *);
	bool initSetting();
	char *getContentID(const int &v_idx,const int &v_grp=1);
	//设定遥测的地址范围及有效的遥信个数
	void               setAnalogScope(int nAddrBegin,int nAddrEnd,int nVaildCount);
	//设定遥信的地址范围及有效的遥信个数
	void               setDigitalScope(int nAddrBegin,int nAddrEnd,int nVaildCount);
	//设定计划曲线遥测的地址范转及有效的信息个数
	void               setPlanScope(int nAddrBegin,int nAddrEnd,int nVaildCount);
	//遥测开始地址
	int                 getAnalogBegin();
	int                 getAnalogEnd();
	//遥信开始地址
	int                 getPointBegin();
	int                 getPointEnd();
	//遥测个数
	int                 getAnalogCount();
	//遥信个数
	int                 getPointCount();
	//计划曲线开始地址
	int                 getPlanAddrBegin();
	//计划曲线结束地址
	int                 getPlanAddrEnd();
	//计划曲线信息个数
	int                 getPlanInfoCount();

	//遥测起始寄存器地址
	int                 getRegisterBegin();
	//遥信起始线圈地址
	int                 getRelayBegin();
	int                 getReadRegisterCode();//遥测读寄存器功能码
	int                 getReadYXRegisterCode();//遥信读寄存器功能码
	int                 getYTCode();//遥调
	int                 getYKCode();//遥控
	bool                getPrintPacket();//得到打印信息
	bool                getPrintPrompt();//打印提示信息
	bool                getPrintError();//打印错误信息
	bool                getPrintTranslate();//打印规约解释信息
	virtual bool reloadLog();


	int getDeviceId();//读设备地址
	int getPerTime();//发送遥测、遥信间隔时间
	int getSleepPerTimes();//寄存器最大数
	ModbusFloatUpSeq getFloatUpSeq();
	ModbusCheckCodSeq getCheckCodeSeq();
	ModbusIntUpSeq getIntUpSeq();
	int getCRCErrorHandle();
	NewModbusYTMethod   getYTMethod();
	int getAlgCmdCount();
	int getPntCmdCount();
	vector<ST_ModCmdCfg> m_vCommand;// 命令
	vector<ST_ModCmdYXCfg> m_vYXCommand;// 命令
protected:
	vector<ST_ModCfgT > m_vContent;//内容
	vector<ST_ModCfgT > m_vGroup;//分组名

private:
	char m_sFilePath[MAX_PATH];//文件路径
	char LastError[Q_FRAME_CONST1024];         //错误信息
	bool init();
private:
	int m_alg_count;//遥测个数
	int m_alg_begin;//遥测起始地址
	int m_alg_end;//遥测结束地址
	int m_pnt_count;//遥信息个数
	int m_pnt_begin;//遥信起始地址
	int m_pnt_end;//遥信结束地址
	int m_plan_addr_begin;//计划曲线开始地址
	int m_plan_addr_end;//计划曲线结束地址
	int m_plan_count;//计划曲线信息个数
	int m_alg_cmd_count;//遥测命令个数
	int m_pnt_cmd_count;//遥信命令个数

};


/** 
* @interface Q_protocolModbusTcpServerStandard
* @brief Modbus tcp服务侧通讯规约
* @author yangxi
* @date 2012-5-23
* @see 
* @bug No know bugs so far.
*/
//class __Q_MODBUS_RTU_STD_EXPORT Q_protocolModbusRtuStd : public Q_protocolBase
class Q_protocolModbusRtuStd : public Q_protocolBase
{
public:
	Q_protocolModbusRtuStd(void);
	virtual ~Q_protocolModbusRtuStd(void);

public:
	virtual bool				initializeProtocol();
	virtual bool				explainData();
	virtual bool				makeFrame();
	virtual bool				terminateProtocol();
	virtual bool				startProcess();
	virtual bool				stopProcess();

	/**************************************************************************************************
	@Function: SetWndInfo
	@Description: 设置窗口句柄
	@Calls:
	@Called By:
	@Input: wnd 窗体句柄,msgID打印消息的ID
	@Output:
	@Return:
	@Update:
	@Others:
	**************************************************************************************************/
	void SetWndInfo(HWND wnd,int MsgID);
protected:
	bool makeFrameEx(Q_protocolModbusRtuStdCommand* pCommand);
	Q_ComCpuEndian m_cpuEndian;//cpu对齐方式;
	//读遥测数据 
	//data去掉前两个字节Address与Function,当包括CRC校验码在内
	//len 是数据区的长度,也即是去掉adddress+function，又加上crc两个字节，所以打平
	virtual bool explainFrameYC(Q_MODBUS_ASDU_RTU *asdu,BYTE *data);
	//读遥信
	virtual bool explainFrameYX(Q_MODBUS_ASDU_RTU *asdu,BYTE *data);
	//遥控
	virtual bool explainFrameYK(Q_MODBUS_ASDU_RTU *asdu,BYTE *data);
	//处理返回的遥调命令
	virtual bool explainFrameYT(Q_MODBUS_ASDU_RTU *asdu,BYTE *data);
	//处理4字节int遥调
	virtual bool explainFrameYT_Int4(Q_MODBUS_ASDU_RTU *asdu,BYTE *data);
	//写多个寄存器内容，遥调
	virtual bool explainFrameYT_M(Q_MODBUS_ASDU_RTU *asdu,BYTE *data);
	//处理遥调命令
	virtual bool handleFrameYT(Q_protocolModbusRtuStdCommand* pCommand);
	//处理遥调命令
	virtual bool handleFrameYT_Int4(Q_protocolModbusRtuStdCommand* pCommand);
	//处理遥测命令
	virtual bool handleFrameYC(Q_protocolModbusRtuStdCommand* pCommand);
	//处理遥信命令
	virtual bool handleFrameYX(Q_protocolModbusRtuStdCommand* pCommand);
	virtual bool handleFrameYT_M(Q_protocolModbusRtuStdCommand* pCommand);
	//处理遥控命令
	virtual bool handelFrameYK(Q_protocolModbusRtuStdCommand* pCommand);
	//在数据库中查询数据
	bool fillTagInformation(LPQ_RECORDDATATAG pData,int nAdr,int nDevID);
	//len 是asdu 中从addr开始的报文区的长度
	virtual bool sendData(Q_MODBUS_ASDU_RTU *asdu,int len);
	virtual bool explainDataEx(char* buff,int nCount,int& nCurrentPos);
	//发送错误码
	bool sendErroCode(Q_MODBUS_ASDU_RTU *header,BYTE code);
	char chInfo[Q_FRAME_CONST128];
	char m_LastMsg[Q_FRAME_CONST1024];
	virtual void onRxMsg(BYTE *msgbuf, unsigned int len);
	void onTxMsg(BYTE *msgbuf, unsigned int len);
	virtual void OnErrorMsg(char *msg,unsigned int len);
	virtual void OnShowMsg(char *msg,unsigned int len);
	WORD CRC16(BYTE* data, WORD len);
	void SendMsgPrint(int nchannelid,int nmsgtype,BYTE* mse,int nlen);
	
private:
	Q_protocolModbusRtuStdCommand* m_LastCmd;
	Q_protocolModbusRtuStdCommand* m_LastCmdForCmd;
	vector<Q_protocolModbusRtuStdCommand*>m_vecCmd;
	ModbusFloatUpSeq m_FloatUpSeq;
	ModbusIntUpSeq m_IntUpSeq;
	ModbusCheckCodSeq m_CheckCodeSeq;
	NewModbusYTMethod   m_YtMethod;
	int m_CRCErroHandle; //连续10帧数据CRC校验错误是否判定为通道断开0否1是
	int m_CRCErroCount;
	HWND					m_wnd;
	int m_nMsgID;//消息编号;
	Q_protcolModbusRtuStdSetting* m_PrintSetting;

	void setNextAnalog(Q_protocolModbusRtuStdCommand* cmd);
	void setNextDigital(Q_protocolModbusRtuStdCommand* cmd);
	time_t m_ReciveTime;
};



#endif
