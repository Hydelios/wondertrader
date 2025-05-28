#ifndef STP_MSG_TYPE_H_
#define STP_MSG_TYPE_H_

#include <iostream>

namespace msg_type{

//const uint32_t kErrorMessage = 100000;

//心跳功能-请求
const uint32_t ReqHeartBeatF = 1000001; 


/*users begin */
const uint32_t MSG_TYPE_USER_BEGIN = 101020000;
//STP操作员登录-请求
const uint32_t ReqOperatorLoginF = 101020001;
//STP操作员登录-应答
const uint32_t RspOperatorLoginF = 101020002;

//获取所有登录账号信息-请求
const uint32_t ReqGetAllAccountF = 101020011;
//获取所有登录账号信息-应答
const uint32_t RspGetAllAccountF = 101020012;

//STP操作员登出
const uint32_t ReqOperatorLogoutF = 101020021;
//STP操作员登出应答
const uint32_t RsqOperatorLogoutF = 101020022;

//查合约-请求
const uint32_t ReqQryInstrumentF = 101020031;
//查合约-应答
const uint32_t RspQryInstrumentF = 101020032;

//STP操作员密码修改-请求
const uint32_t ReqPasswordChangeF = 101020041;
//STP操作员密码修改-应答
const uint32_t RspPasswordChangeF = 101020042;

//获取用户中心Token-请求
const uint32_t ReqGetUserTokenF = 101020051;
//获取用户中心Token-应答
const uint32_t RspGetUserTokenF = 101020052;
//账号锁定
const uint32_t ReqLockOpaccountF = 101020053;
const uint32_t RsqLockOpaccountF = 101020054;
//通知账号禁用
const uint32_t ReqNotifyLockOpaccountSpF = 101020055;
//操作员获取菜单权限
const uint32_t ReqGetMenuAuthF = 101020071;
const uint32_t RspGetMenuAuthF = 101020072;

const uint32_t MSG_TYPE_USER_END = 101029999;



/*users end */

/* 主推类 功能 begin */
const uint32_t MSG_TYPE_PUSH_BEGIN = 101000000;
//成交通知
const uint32_t OnRtnTradeSpF = 101000000;

//报单通知
const uint32_t OnRtnOrderSpF = 101000010;

//高级订单回报
const uint32_t OnRtnSeniorOrderSpF = 101000020;

//通用数据推送
const uint32_t OnRtnCommonPushSpF = 101000030;

//期权组合报单通知
const uint32_t OnRtnOptCombOrderSpF = 101000040;

//DMA指令报单通知
const uint32_t OnRtnContractOrderSpF = 101000050;

const uint32_t MSG_TYPE_PUSH_END = 101009999;
/* 主推类 功能 end */

/* OMS 功能 begin */
const uint32_t MSG_TYPE_OMS_BEGIN = 101030000;
//委托-请求
const uint32_t ReqInsertOrderF = 101030001;
//委托错误应答
const uint32_t OnRspErrInsertOrderF = 101030002;  //结构详见 ReqInsertOrder

//撤单-请求
const uint32_t ReqCancelOrderF = 101030011;
//撤单错误应答
const uint32_t OnRspErrCancelOrderF = 101030012;  //结构详见 ReqCancelOrder

//查委托-请求
const uint32_t ReqQryOrderF = 101030021;
//查委托-应答
const uint32_t RspQryOrderF = 101030022;

//查成交-请求
const uint32_t ReqQryTradeF = 101030031;
//查成交-应答
const uint32_t RspQryTradeF = 101030032;

//查资金-请求
const uint32_t ReqQryAccountAssetF = 101030041;
//查资金-应答
const uint32_t RspQryAccountAssetF = 101030042;

//查持仓-请求
const uint32_t ReqQryPositionF = 101030051;
//查持仓-应答
const uint32_t RspQryPositionF = 101030052;

//查合约-请求
//const uint32_t ReqQryInstrumentF = 101030061;

//查合约-应答
//const uint32_t RspQryInstrumentF = 101030062;

//批量报单录入-请求
const uint32_t ReqInsertOrderBatchF = 101030071;

//批量报单录入-应答
const uint32_t RspInsertOrderBatchF = 101030072;

//批量撤单录入-请求
const uint32_t ReqCancelOrderBatchF = 101030081;

//查持仓明细-请求,期货
const uint32_t ReqQryPositionDetailF = 101030091;

//查持仓明细-应答，期货
const uint32_t RspQryPositionDetailF = 101030092;

//现金还款-请求
const uint32_t ReqCreditCashRtnF = 101030101;

//现金还款-应答
const uint32_t RspCreditCashRtnF = 101030102;

//查资金流水-请求
const uint32_t ReqQryAssetSerialF = 101030111;

//查资金流水-应答
const uint32_t RspQryAssetSerialF = 101030112;

//查最大交易数量-请求
const uint32_t ReqQryCrdtMaxBuyF = 101030121;
//查最大交易数量-应答
const uint32_t RspQryCrdtMaxBuyF = 101030122;

//查客户担保证券-请求
const uint32_t ReqQryCrdtStkInfoF = 101030131;
//查客户担保证券-应答
const uint32_t RspQryCrdtStkInfoF = 101030132;

//查标的券-请求
const uint32_t ReqQryTarStkInfoF = 101030141;
//查标的券-应答
const uint32_t RspQryTarStkInfoF = 101030142;

//查可融券-请求
const uint32_t ReqQryEnsloSecuF = 101030151;
//查可融券-应答
const uint32_t RspQryEnsloSecuF = 101030152;

//查信用资产-请求
const uint32_t ReqQryCreditAssetF = 101030161;
//查信用资产-响应
const uint32_t RspQryCreditAssetF = 101030162;

//查两融合约-请求
const uint32_t ReqQryCreditCompactF = 101030171;
//查两融合约-应答
const uint32_t RspQryCreditCompactF = 101030172;

// 期权组合委托-请求
const uint32_t ReqInsertOptCombOrderF = 101030181;

// 期权组合委托-错误应答
const uint32_t OnRspErrInsertOptCombOrderF = 101030182;

// 期权组合委托查询-请求
const uint32_t ReqQryOptCombOrderF = 101030191;

// 期权组合委托查询-应答
const uint32_t RspQryOptCombOrderF = 101030192;

// 账户锁定解锁
const uint32_t ReqActLockOrUnLockF = 101030201;

//期权组合报单通知
const uint32_t OnRtnOptCombOrderF = 101039970;

//报单通知
const uint32_t OnRtnOrderF = 101039980;

//成交通知
const uint32_t OnRtnTradeF = 101039990;

const uint32_t MSG_TYPE_OMS_END = 101039999;
/* OMS 功能 end */

/* 适配器(O32,UFT,UF20等) 功能 begin */
const uint32_t MSG_TYPE_ADAPTER_BEGIN = 101040000;
//委托-请求
const uint32_t ReqInsertOrderSpF = 101040001;
//委托错误应答
const uint32_t OnRspErrInsertOrderSpF = 101040002;  //结构详见 ReqInsertOrder 
 
//撤单-请求
const uint32_t ReqCancelOrderSpF = 101040011;
//撤单错误应答
const uint32_t OnRspErrCancelOrderSpF = 101040012;  //结构详见 ReqCancelOrder

//查委托-请求
const uint32_t ReqQryOrderSpF = 101040021;
//查委托-应答
const uint32_t RspQryOrderSpF = 101040022;

//查成交-请求
const uint32_t ReqQryTradeSpF = 101040031;
//查成交-应答
const uint32_t RspQryTradeSpF = 101040032;

//查资金-请求
const uint32_t ReqQryAccountAssetSpF = 101040041;
//查资金-应答
const uint32_t RspQryAccountAssetSpF = 101040042;

//查持仓-请求
const uint32_t ReqQryPositionSpF = 101040051;
//查持仓-应答
const uint32_t RspQryPositionSpF = 101040052;

//查合约-请求
const uint32_t ReqQryInstrumentSpF = 101040061;
//查合约-应答
const uint32_t RspQryInstrumentSpF = 101040062;

//批量报单录入-请求
const uint32_t ReqInsertOrderBatchSpF = 101040071;
//批量报单录入-应答
const uint32_t RspInsertOrderBatchSpF = 101040072;
//批量撤单录入-请求
const uint32_t ReqCancelOrderBatchSpF = 101040081;

//查持仓明细-请求，期货
const uint32_t ReqQryPositionDetailSpF = 101040091;
//查持仓明细-应答，期货
const uint32_t RspQryPositionDetailSpF = 101040092;

//查资金流水-请求
const uint32_t ReqQryAssetSerialSpF = 101040101;
//查资金流水-应答
const uint32_t RspQryAssetSerialSpF = 101040102;

//非交易过户-请求
const uint32_t ReqQryFjyAmountSpF = 101040111;
//非交易过户-应答
const uint32_t RspQryFjyAmountSpF = 101040112;

//现券还券-请求
const uint32_t ReqCreditSecuRtnSpF = 101040121;
//现券还券-应答
const uint32_t RspCreditSecuRtnSpF = 101040122;

//现金还款-请求
const uint32_t ReqCreditCashRtnSpF = 101040131;
//现金还款-应答
const uint32_t RspCreditCashRtnSpF = 101040132;

//信用资产信息查询-请求
const uint32_t ReqQryCreditAssetSpF = 101040141;
//信用资产信息查询-应答
const uint32_t RspQryCreditAssetSpF = 101040142;

//标的券查询-请求
const uint32_t ReqQryTargetStockinfoSpF = 101040151;
//标的券查询-应答
const uint32_t RspQryTargetStockinfoSpF = 101040152;

//可融券查询-请求
const uint32_t ReqQryEnsloSecuSpF = 101040161;
//可融券查询-应答
const uint32_t RspQryEnsloSecuSpF = 101040162;

//两融合约查询-请求
const uint32_t ReqQryCreditCompactSpF = 101040171;
//两融合约查询-应答
const uint32_t RspQryCreditCompactSpF = 101040172;

//交易账户登录请求-请求
const uint32_t ReqAccountLoginSpF = 101040181;
//交易账户登录请求-应答
const uint32_t RspAccountLoginSpF = 101040182;

//最大交易数量获取-请求
const uint32_t ReqQryCrdtMaxBuySpF = 101040191;
//最大交易数量获取-应答
const uint32_t RspQryCrdtMaxBuySpF = 101040192;

//担保证券查询-请求
const uint32_t ReqQryCrdtStkInfoSpF = 101040201;
//担保证券查询-应答
const uint32_t RspQryCrdtStkInfoSpF = 101040202;

//期权组合委托-请求
const uint32_t ReqInsertOptCombOrderSpF = 101040211;
//期权组合委托错误应答
const uint32_t OnRspErrInsertOptCombOrderSpF = 101040212;

//期权组合委托查询-请求
const uint32_t ReqQryOptCombOrderSpF = 101040221;
//期权组合委托查询-应答
const uint32_t RspQryOptCombOrderSpF = 101040222;

//期权组合持仓查询-请求
const uint32_t ReqQryOptCombPositionSpF = 101040231;
//期权组合持仓查询-应答
const uint32_t RspQryOptCombPositionSpF = 101040232;

const uint32_t MSG_TYPE_ADAPTER_END = 101049999;
//成交通知
//const uint32_t OnRtnTradeSpF = 101049990;
//报单通知
//const uint32_t OnRtnOrderSpF = 101049980;

/* 适配器(O32,UFT,UF20等) 功能 end */


/* senior 功能 begin */

//以下目前用于固收↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
const uint32_t MSG_TYPE_SENIOR_BEGIN = 101070000;
//高级订单录入-请求
const uint32_t ReqInsertSeniorOrderF = 101070001;
//高级订单录入-错误应答
const uint32_t OnRspErrInsertSeniorOrderF = 101070002;

//高级订单操作-请求
const uint32_t ReqOperateSeniorOrderF = 101070011;
//高级订单操作-错误应答
const uint32_t OnRspErrOperateSeniorOrderF = 101070012;

//高级订单查询-请求
const uint32_t ReqQrySeniorOrderF = 101070021;
//高级订单查询-应答
const uint32_t RspQrySeniorOrderF = 101070022;

//算法模板操作-请求
const uint32_t ReqOperateAlgorithmTemplateF = 101070031;
//算法模板操作-应答
const uint32_t RspOperateAlgorithmTemplateF = 101070032;

//算法模板查询-请求
const uint32_t ReqQryAlgorithmTemplateF = 101070041;
//算法模板查询-应答
const uint32_t RspQryAlgorithmTemplateF = 101070042;

//批量高级订单新增-请求
const uint32_t ReqInsertSeniorOrderBatchF = 101070051;
//批量高级订单新增-应答
const uint32_t RspInsertSeniorOrderBatchF = 101070052;

//期权指标查询-请求
const uint32_t ReqQryOptIndexF = 101070061;
//期权指标查询-应答
const uint32_t RspQryOptIndexF = 101070062;

//期权指标计算-请求
const uint32_t ReqCalcOptIndexF = 101070071;
//期权指标计算-应答
const uint32_t RspCalcOptIndexF = 101070072;

//期权指标订阅-请求
const uint32_t ReqSubscribeOptIndexF = 101070081;
//期权指标订阅-应答
const uint32_t RspSubscribeOptIndexF = 101070082;

//期权指标取消订阅-请求
const uint32_t ReqCancelSubOptIndexF = 101070091;
//期权指标取消订阅-应答
const uint32_t RspCancelSubOptIndexF = 101070092;


const uint32_t MSG_TYPE_SENIOR_END = 101079999;

//以上目前用于固收↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

//两融篮子指令下单-请求
const uint32_t ReqInsertCreditComboOrderF = 101070501;
//两融篮子指令下单-应答
const uint32_t RspInsertCreditComboOrderF = 101070502;

//两融直接还款-请求
const uint32_t ReqReturnCreditFundF = 101070511;
//两融直接还款-应答
const uint32_t RspReturnCreditFundF = 101070512;

//两融组合现券还券-请求
const uint32_t ReqReturnCreditStock = 101070521;
//两融组合现券还券-应答
const uint32_t RspReturnCreditStock = 101070522;

//两融篮子客户资产查询-请求
const uint32_t ReqQryCreditComboAssetF = 101070531;
//两融篮子客户资产查询-应答
const uint32_t RspQryCreditComboAssetF = 101070532;

//两融篮子组合持仓查询-请求
const uint32_t ReqQryCreditComboHoldListF = 101070541;
//两融篮子组合持仓查询-应答
const uint32_t RspQryCreditComboHoldListF = 101070542;

//两融篮子执行列表查询-请求
const uint32_t ReqQryOrderProcessListF = 101070551;
//两融篮子执行列表查询-应答
const uint32_t RspQryOrderProcessListF = 101070552;

/* senior 功能 end */

/* http_service 功能 begin */
//查询合约-请求
const uint32_t ReqInnerQryInstrumentSpF = 101080001;
//查询合约-应答
const uint32_t RspInnerQryInstrumentSpF = 101080002;
//查询账户-请求
const uint32_t ReqInnerGetAllAccountSpF = 101080011;
//查询账户-应答
const uint32_t RspInnerGetAllAccountSpF = 101080012;
//查询操作员-请求
const uint32_t ReqInnerGetAllOperatorSpF = 101080021;
//查询操作员-应答
const uint32_t RspInnerGetAllOperatorSpF = 101080022;
//查询菜单权限-请求
const uint32_t ReqGetAllMenuAuthSpF = 101080023;
//查询菜单权限-应答
const uint32_t RspGetAllMenuAuthSpF = 101080024;
//获取用户中心Token-请求
const uint32_t ReqGetUserTokenSpF = 101080031;
//获取用户中心Token-应答
const uint32_t RspGetUserTokenSpF = 101080032;
//操作员密码修改-请求
const uint32_t ReqPasswordChangeSpF = 101080041;
//操作员密码修改-应答
const uint32_t RspPasswordChangeSpF = 101080042;
//账号禁用
const uint32_t ReqLockOpaccountSpF= 101080043;
const uint32_t RsqLockOpaccountSpF = 101080044;
//查询国债收益率-请求
const uint32_t ReqQryYieldOfGovBondSpF = 101080051;
//查询国债收益率-应答
const uint32_t RspQryYieldOfGovBondSpF = 101080052;
/* http_service 功能 end */

/* hq_service 功能 begin */
////查询实时行情-请求
//const uint32_t ReqInnerQryStkMarketSpF = 101090001;
////查询实时行情-应答
//const uint32_t RspInnerQryStkMarketSpF = 101090002;
////查询历史行情-请求
//const uint32_t ReqInnerQryHisStkMarketSpF = 101090011;
////查询历史行情-应答
//const uint32_t RspInnerQryHisStkMarketSpF = 101090012;
////通用查询-请求 应答
//const uint32_t ReqInnerQryInfoSpF = 101090021;
//const uint32_t RspInnerQryInfoSpF = 101090022;

/*宽邦 10109开头*/
const uint32_t MSG_TYPE_BIGQUANT_BEGIN = 101090000;
//插入宽邦策略-请求
const uint32_t ReqInsertBigQuantStrategyF = 101090001;
//插入宽邦策略-应答
const uint32_t RspInsertBigQuantStrategyF = 101090002;
//插入宽邦策略详情-请求
const uint32_t ReqInsertBigQuantStrategyDetailF = 101090011;
//插入宽邦策略详情-应答
const uint32_t RspInsertBigQuantStrategyDetailF = 101090012;
//查询宽邦策略-请求
const uint32_t ReqQryBigQuantStrategyF = 101090021;
//查询宽邦策略-应答
const uint32_t RspQryBigQuantStrategyF = 101090022;
//查询宽邦策略详情-请求
const uint32_t ReqQryBigQuantStrategyDetailF = 101090031;
//查询宽邦策略详情-应答
const uint32_t RspQryBigQuantStrategyDetailF = 101090032;
//查询宽邦策略日志-请求
const uint32_t ReqQryBigQuantLogDetailF = 101090041;
//查询宽邦策略日志-应答
const uint32_t RspQryBigQuantLogDetailF = 101090042;
//修改宽邦策略-请求
const uint32_t ReqUpdateBigQuantStrategyF = 101090051;
//修改宽邦策略-应答
const uint32_t RspUpdateBigQuantStrategyF = 101090052;
const uint32_t MSG_TYPE_BIGQUANT_END = 101099999;
/*BCT 10110开头*/
//查询BCT可交易标的(白名单)-请求
const uint32_t MSG_TYPE_DMA_BEGIN = 101100000;

const uint32_t ReqQryBctTradableInstrumentsF = 101100001;
//查询BCT可交易标的(白名单)-应答
const uint32_t RspQryBctTradableInstrumentsF = 101100002;
//查询合约名义本金接口-请求
const uint32_t ReqQryContractUsableNotionAmtF = 101100011;
//查询合约名义本金接口-应答
const uint32_t RspQryContractUsableNotionAmtF = 101100012;
//查询合约持仓-请求
const uint32_t ReqQryContractPositionF = 101100021;
//查询合约持仓-应答
const uint32_t RspQryContractPositionF = 101100022;
//合约委托记录-请求
const uint32_t ReqInsertContractOrderF = 101100031;
//合约委托记录-应答
const uint32_t OnRspInsertContractOrderF = 101100032;
//查询合约委托记录-请求
const uint32_t ReqQryContractOrdersF = 101100041;
//查询合约委托记录-应答
const uint32_t RspQryContractOrdersF = 101100042;
//撤销指令-请求
const uint32_t ReqCancelContractOrderF = 101100051;
//撤销指令-应答
const uint32_t OnRspCancelContractOrderF = 101100052;
//审核指令-请求
const uint32_t ReqAuditContractOrderF = 101100061;
//审核指令-应答
const uint32_t RspAuditContractOrderF = 101100062;
//查询合约成交-请求
const uint32_t ReqQryContractDealF = 101100071;
//查询合约成交-应答
const uint32_t RspQryContractDealF = 101100072;
//批量委托-请求
const uint32_t ReqInsertContractOrderBatchF = 101100081;
//批量委托-应答
const uint32_t OnRspInsertContractOrderBatchF = 101100082;
//批量撤单-请求
const uint32_t ReqCancelContractOrderBatchF = 101100091;
//批量撤单-应答
const uint32_t OnRspCancelContractOrderBatchF = 101100092;
//查询合约指令-请求
const uint32_t ReqQryContractCommandsF = 101100101;
//查询合约指令-应答
const uint32_t RspQryContractCommandsF = 101100102;
//查询风险数据-请求
const uint32_t ReqQryDmaRiskDataF = 101100111;
//查询风险数据-应答
const uint32_t RspQryDmaRiskDataF = 101100112;
//计算多空相关性-请求
const uint32_t ReqCalcLongShortCorrelationF = 101100121;
//查询多空相关性-应答
const uint32_t RspCalcLongShortCorrelationF = 101100122;
//同步数据-请求
const uint32_t ReqSyncBctDataF = 101100131;
//同步数据-应答
const uint32_t RspSyncBctDataF = 101100132;
//查询风控参数-请求
const uint32_t ReqQryDmaRiskParamF = 101100141;
//查询风控参数-应答
const uint32_t RspQryDmaRiskParamF = 101100142;
//设置风控参数-请求
const uint32_t ReqSetDmaRiskParamF = 101100151;
//设置风控参数-应答
const uint32_t RspSetDmaRiskParamF = 101100152;
//dma系统运维-请求
const uint32_t ReqDmaSystemMaintenanceOpF = 101100161;
//dma系统运维-应答
const uint32_t RspDmaSystemMaintenanceOpF = 101100162;
//dma系统状态查询-请求
const uint32_t ReqQryDmaSystemStatusF = 101100171;
//dma系统状态查询-应答
const uint32_t RspQryDmaSystemStatusF = 101100172;
//撤销dma委托-请求
const uint32_t ReqCancelDmaOrderF = 101100181;
//撤销dma委托-错误应答
const uint32_t OnRspErrCancelDmaOrderF = 101100182;

const uint32_t DMA_MSG_END = 101109992;
const uint32_t MSG_TYPE_DMA_END = 101109999;
}
#endif // !STP_MSG_TYPE_H_
