// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 MESSERVICE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// MESSERVICE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef MESSERVICE_EXPORTS
#define MESSERVICE_API __declspec(dllexport)
#else
#define MESSERVICE_API __declspec(dllimport)
#endif

// 此类是从 MesService.dll 导出的
class MESSERVICE_API CMesService {
public:
	CMesService(void);
	// TODO: 在此添加您的方法。
};

extern MESSERVICE_API int nMesService;

MESSERVICE_API int fnMesService(void);

//检查用户、密码、资源代码是否正确
extern "C" MESSERVICE_API BOOL CheckUserAndResourcePassed(char *iUserCode, char *iResCode,char *iPassword,char *oErrMessage);
//检查SN当前能否进入当前站点（途程检查）
extern "C" MESSERVICE_API BOOL CheckRoutePassed(char *iSN, char *iResCode,char *oErrMessage) ;
//SN过站，当测试结果为NG时传入的字段iResult值要为NG,正常则为OK
extern "C" MESSERVICE_API BOOL SetMobileData(char *iSN, char *iResCode, char *iOperator, char *iResult, char *iErrCode, char *oErrMessage);
//SN过站，当测试结果为NG时传入的字段iResult值要为NG,正常则为OK，多了iTSMemo参数
extern "C" MESSERVICE_API BOOL SetMobileData2(char *iSN, char *iResCode, char *iOperator, char *iResult, char *iErrCode, char *iTSMemo, char *oErrMessage);


//保存测试信息 
extern "C" MESSERVICE_API BOOL SetTestDetail(char *iSN,char *iResCode,char *iClass,char *iSubClass1,char *iSubClass2,char *iSubClass3,
	char *iMaxValue,char *iMinValue,char *iActualValue,char *iValue1, char *iValue2,char *iValue3,char *iTestResult,char *oErrMessage);

/*	根据SN从MES获取MO下对应的Mac或BT地址，MO上未维护为空值时则传出空值
GetAddressRangerByMo (string Sn,Out string wifi ,Out string bt,Out string code1 ,Out string code2,Out string code3)
参数说明：
		SN:  产品序列号
		Wifi: 获取WIFI地址
		Bt：获取蓝牙地址
		Code1：获取扩装栏位1
		code2：获取扩装栏位2
		code3：获取扩装栏位3
*/
extern "C" MESSERVICE_API BOOL GetAddressRangerByMo(char *SN,char *oWIFI,char *oBT,char *oCode1,char *oCode2,char *oCode3,char *oErrMSG);  


/*
1、判断传入的IMEI和NetCode号为空，若为空则根据SN的工单分配一个未使用IMEI号，系统回传IMEI1、IMEI2、MEID、NetCode、PSN、ID1、ID2、ID3、ID4、ID5，设备接收分配的所需信息
2、判断传入的IMEI或NetCode不未空，则IMEI或NetCode转化为判断IMEI是否存在SN所在工单的IMEI工艺中，并且判断IMEI号是否被使用，被使用返回False；若返回True,系统回传IMEI1、IMEI2、MEID、NetCode、PSN、ID1、ID2、ID3、ID4、ID5，设备接收分配的所需信息
3、若传入IMEI和NetCode，需要比对是否IMEI和NetCode和SN所在MO信息中一一对应不是对应则返回False,针对这返回True系统回传IMEI1、IMEI2、MEID、NetCode、PSN、ID1、ID2、ID3、ID4、ID5，设备接收分配的所需信息
GetMEIOrNetCodeRange (String SN，String IMEI，String NetCode, OUT String IMEI1, OUT String IMEI2,OUT String MEID，OUT String ONETCODE ，OUT String OPSN )
参数说明：
SN：产品序列号(DLL转化为TSN）
		IMEI：imei1
		NetCode:网标或称入网许可证
         IMEI1：系统回传IMEI1
         IMEI2:系统回传IMEI2
         MEID：系统回传meid
         NETCODE0:系统回传网标
         PSN0：系统回传机身标签
         ID1  系统回传扩站栏位默认为IMEI3
         ID2  系统回传扩站栏位2
         ID3  系统回传扩站栏位3
         ID4  系统回传扩站栏位4
         ID5  系统回传扩站栏位5
		 ERRMSG 错误信息

*/
extern "C" MESSERVICE_API BOOL GetMEIOrNetCodeRange(char *SN,char *IMEI, char * NetCode, char * IMEI1,char * IMEI2,char * MEID,char *NETCODE0,char *PSN0,char *ID1,char *ID2,char *ID3,char *ID4,char *ID5,char *oErrMSG);




/*
根据IMEI，获取系统内相关数据
*/
//extern "C" MESSERVICE_API BOOL GetIMEIRange(char *imei,char *IMEI1,char *IMEI2,char *MEID,char *NETCODE0,char *PSN0,char *TSN0,char *SN0,char *ID1,char *ID2,char *ID3,char *ID4,char *ID5,char *oErrMSG);

/*写SN、WIFI、BT成功后，回返WIFI、BT给MES
SetAddressInfo (string Sn,stringwifi ,string BT, string code1 ,string code2, string code3)	*/
extern "C" MESSERVICE_API BOOL SetAddressInfo(char *SN,char *wifi,char *bt,char *code1,char *code2,char *code3,char *oErrMSG);


/*
 通过SN获取MES记录信息（WIFI、BT、IMEI1、IMEI2、NETCODE、PSN）
GetIMobileAllinfo(string Sn,out string wifi , out  string BT,  out string code1 ,out  string code2,Out string code3,out string IMEI1、 out string IMEI2、out string MEID、out string NETCODE、out string PSN，out string id1,out string id2,out string id3,out string id4,out string id5)
通过系统传入的SN，去追溯出手机的所有信息，若无信息则返回空值；
 	参数说明：			
		SN: PCBA编号	
		wifi: 系统回传MAC地址
		BT:系统回传蓝牙地址
		code1：扩展栏位1（MO和蓝牙、WIFI地址关系）
		code2：扩展栏位2（MO和蓝牙、WIFI地址关系）
		code3：扩展栏位3（MO和蓝牙、WIFI地址关系）
		IMEI1：系统回传IMEI1
         IMEI2:系统回传IMEI2
         MEID：系统回传meid
         NETCODE0:系统回传网标
         PSN0：系统回传机身标签
         ID1  系统回传扩站栏位默认为IMEI3
         ID2  系统回传扩站栏位2
         ID3  系统回传扩站栏位3
         ID4  系统回传扩站栏位4
         ID5  系统回传扩站栏位5
 */
extern "C" MESSERVICE_API BOOL GetIMobileAllinfo(char *SN,char *wifi,char *BT,char *code1,char *code2,char *code3,char *IMEI1,char *IMEI2,char *MEID,char *NETCODE0,char *PSN0,char *ID1,char *ID2,char *ID3,char *ID4,char *ID5,char *oErrMSG);
 /*
 写IMEI号成功后回传IMEI号给MES
 SetImeiInfo (string Sn,string IMEI)
 参数说明：
			SN: 产品序列号（DLL转化为TSN）	
			IMEI：imei1	
			ERRMSG 错误信息
*/
extern "C" MESSERVICE_API BOOL SetImeiInfo(char *SN,char *IMEI,char *oErrMSG);


/*
 写IMEI号成功后回传IMEI号给MES
 SetImeiInfo (string Sn,string IMEI)
 参数说明：
			SN: 产品序列号（DLL转化为TSN）	
			IMEI：imei1	
			Psn: 整机sn
			ERRMSG 错误信息
*/
extern "C" MESSERVICE_API BOOL SetImeiInfo2(char *SN,char *IMEI,char *Psn,char *oErrMSG);

//上传iOSVersion,  iHW,  iTzKey,  iCPUID,  iEMMC,  iUFSId,  iFPUId,  iFido_Data,  iIFAA_Data
//bool UpdateMapSource(string iSN, string iOSVersion, string iHW, string iTzKey, string iCPUID, string iEMMC, string iUFSId
//            , string iFPUId, string iFido_Data, string iIFAA_Data, out string oErrMessage)
extern "C" MESSERVICE_API BOOL UpdateMapSource(char *iSN,char *iOSVersion,char *iHW,char *iTzKey,char *iCPUID,char *iEMMC
	,char *iUFSId,char *iFPUId,char *iFido_Data,char *iIFAA_Data,char *oErrMSG);

//获取oIMEIProtectionKey, oFidoKey,  oIFAAKey,  oAttestationKeyPath
// bool GetInfo(string iSN, out string oIMEIProtectionKey, out string oFidoKey, out string oIFAAKey, out string oAttestationKeyPath, out string oErrMessage);
extern "C" MESSERVICE_API BOOL GetInfo(char *iSN,char *oIMEIProtectionKey,char *oFidoKey,char *oIFAAKey,char *oAttestationKeyPath,char *oErrMSG);
//按文件夹序号获取oIMEIProtectionKey, oFidoKey,  oIFAAKey,  oAttestationKeyPath
extern "C" MESSERVICE_API BOOL GetInfo_2(char *iNO,char *iSN,char *oIMEIProtectionKey,char *oFidoKey,char *oIFAAKey,char *oAttestationKeyPath,char *oErrMSG);

//获取机型条码规则信息
extern "C" MESSERVICE_API BOOL GetModel_LeiDiao(char *oModel,char *oPRE_STR,char *oSN_GuiZe,char *oMotherSN_GuiZe,char *oErrMSG);

//雷雕机获取SN；iMachine_NO:雷雕机编号,iModel 产品机型,iPRE_STR 前缀,iQty 单板条码数量,iLineNo 线体编号,
extern "C" MESSERVICE_API BOOL GetSN_LeiDiao(char *iMachine_NO,char *iModel,char *iPRE_STR,char *iQty,char *iLineNo,char *oMother_SN
,char *oSN,char *oErrMSG);

//上传测试LOG文件
//TestLog(string iLogFile, string iErrorCode, out string oErrMessage)
extern "C" MESSERVICE_API BOOL TestLog(char *iLogFile,char *iErrorCode,char *oErrMSG);
//上传电池条码  bool SetBatteryID(string iSN, string iBatteryID, out string oErrMessage);
extern "C" MESSERVICE_API BOOL SetBatteryID(char *iSN,char *iBatteryID,char *oErrMSG);
//获取电池条码 bool GetBatteryID(string iSN, out string oBatteryID, out string oErrMessage);
extern "C" MESSERVICE_API BOOL GetBatteryID(char *iSN,char *iBatteryID,char *oErrMSG);
 //打印条码2  bool PrintBarCode2(string iSN,int _PrintQty, out string oErrMessage);
extern "C" MESSERVICE_API BOOL PrintBarCode2(char *iSN,char *iPrintQty,char *oErrMSG);
//PrintBarCode3(iPath, iParmName, iParmValue,_PrintQty, out  oErrMessage))
extern "C" MESSERVICE_API BOOL PrintBarCode3(char *iPath,char *iParmName,char *iParmValue,char *iPrintQty,char *oErrMSG);

//2019/01/11增加以下---------
//IMEI获取SN  bool GetSnByImei(string iIMEI1, out string oSN, out string oErrMessage);
extern "C" MESSERVICE_API BOOL GetSnByImei(char *iIMEI1,char *oSN,char *oErrMSG);
// bool CheckChecksumfile(string iBarcode, string iChecksum_path, out string oErrMessage);
extern "C" MESSERVICE_API BOOL CheckChecksumfile(char *iBarcode,char *iChecksum_path,char *oErrMSG);
//Barcode:IMEI号 WeightValue：重量 bool SetProductWeight(string Barcode, double WeightValue, out string oErrMessage);
extern "C" MESSERVICE_API BOOL SetProductWeight(char *iBarcode,char *iWeightValue,char *oErrMSG);
//上传Widevine参数 bool SetWidevinePram(string iSN, string iWidevinePram, out string oErrMessage);
extern "C" MESSERVICE_API BOOL SetWidevinePram(char *iSN,char *iWidevinePram,char *oErrMSG);
//下载WidevineKey bool GetWidevineKey(string iSN,out string oWidevineKey_Path, out string oErrMessage);
extern "C" MESSERVICE_API BOOL  GetWidevineKey(char *iSN,char *oWidevineKey_Path,char *oErrMSG);
//按文件夹序号下载WidevineKey bool GetWidevineKey(string iNO,string iSN,out string oWidevineKey_Path, out string oErrMessage);
extern "C" MESSERVICE_API BOOL  GetWidevineKey_2(char *iNO,char *iSN,char *oWidevineKey_Path,char *oErrMSG);
//获取FactoryID bool getFactroy(out string oFactoryID, out string oErrMessage);
extern "C" MESSERVICE_API BOOL GetFactroy(char *oFactoryID,char *oErrMSG);
//bool readXMtxt(string iPath, out string oErrMessage);
extern "C" MESSERVICE_API BOOL ReadXMtxt(char *iPath,char *oErrMSG);
//根据IMEI获取LSN(雷雕条码)  bool GetLSNByIMEI(string iIMEI, out string oLSN, out string oErrMessage);
extern "C" MESSERVICE_API BOOL GetLSNByIMEI(char *iIMEI,char *oLSN,char *oErrMSG);
//确认LSN(雷雕条码)  bool SetLSNByIMEI(string iIMEI, string iLSN, out string oErrMessage);
extern "C" MESSERVICE_API BOOL SetLSNByIMEI(char *iIMEI,char *iLSN,char *oErrMSG);

extern "C" MESSERVICE_API BOOL SetStandardWeight(char *iBarcode,char *iMaxValue,char *iMinValue,char *iUserCode,char *iPassWord,char *iResCode,char *oErrMSG);

extern "C" MESSERVICE_API BOOL Set_ShiYuan_Mac(char *iMac,char *iPROC_ID,char *iCheckResult,char *iUserCode,char *oErrMSG);
        
        //获取单板SN所在当前工站对应的软件版本、硬件版本、BoardID、存储大小（ROMSIZE)、内存大小（RAMSIZE）、颜色信息（COLOR）

extern "C" MESSERVICE_API BOOL GetPrdInfo(char *iSN, char *iResCode,char *oJsonData,char *oErrMSG);

extern "C" MESSERVICE_API BOOL SetTestDetail2(char *iSN,char *iResCode,char *iItem,char *iData,char *oErrMSG);

extern "C" MESSERVICE_API BOOL GetTestDetail(char *iSN,char *iResCode,char *iItem,char *oData,char *oErrMSG);

extern "C" MESSERVICE_API BOOL SetKeyParts(char *iSN,char *iResCode, char *iJsondata,char *oErrMSG);

//--广和通接口
extern "C" MESSERVICE_API BOOL ConnectMes(char* szSfc, char* szMesLog);
extern "C" MESSERVICE_API BOOL CompleteMes(char* szSfc, bool bSuccess, char* szMesLog, char *szErrorCode = NULL, char *szErrorValue = NULL);
extern "C" MESSERVICE_API BOOL UploadNumber(char* szSfc, const char* szData, char* szMesLog);
extern "C" MESSERVICE_API BOOL GetNumberBySFC(char* szSfc, char* szNumberStore, char* szReturnInfo, char* szMesLog);
extern "C" MESSERVICE_API BOOL SendLog2Mes(char* szSfc, const char* szSourceFile, char* szMesLog);

//-----------------
extern "C" MESSERVICE_API BOOL Exe2(char *oErrMessage);
extern "C" MESSERVICE_API  int Execmd(char *,char *);//执行CMD命令
extern "C" MESSERVICE_API void ReadNextOutPram(char *OutPram1);
MESSERVICE_API  int Open_kzt(void);

//extern "C" MESSERVICE_API void ShowMsg(char *, char *);

