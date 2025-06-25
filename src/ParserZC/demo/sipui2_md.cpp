#include "sipui2_md.hpp"
#include <utility>

sipui2MD *sipui2MD::sip = nullptr;

sipui2MD::sipui2MD(std::string name) : MDBase(std::move(name))
{
    if (sip == nullptr)
    {
        sip = this;
        requestManager = new RequestManager("req", this);

        bool err = false;
        if (this->getCfg("serverIP", this->m_ip) == false)
        {
            this->getLog()->critical("cannot find serverIP cfg");
            err = true;
        }
        if (this->getCfg("serverPort", this->m_port) == false)
        {
            this->getLog()->critical("cannot find serverPort cfg");
            err = true;
        }
        if (this->getCfg("account", this->m_account) == false)
        {
            this->getLog()->critical("cannot find account cfg");
            err = true;
        }
        if (this->getCfg("passwd", this->m_passwd) == false)
        {
            this->getLog()->critical("cannot find password cfg");
            err = true;
        }
        if (this->getCfg("use_L1", this->m_L1) == false)
        {
            m_L1 = true;
        }
        if (this->getCfg("use_L2", this->m_L2) == false)
        {
            m_L2 = false;
        }
        if (this->getCfg("use_ZK", this->m_ZK) == false)
        {
            m_ZK = false;
        }
        if (this->getCfg("use_ZC", this->m_ZC) == false)
        {
            m_ZC = false;
        }
        if (this->getCfg("use_ZW", this->m_ZW) == false)
        {
            m_ZW = false;
        }
        if (this->getCfg("use_WD", this->m_WD) == false)
        {
            m_WD = false;
        }
        if (this->getCfg("use_JC", this->m_JC) == false)
        {
            m_JC = false;
        }
        if (this->getCfg("use_CJ", this->m_CJ) == false)
        {
            m_CJ = false;
        }
        if (this->getCfg("use_FK", this->m_FK) == false)
        {
            m_FK = false;
        }
        if (this->getCfg("use_HL", this->m_HL) == false)
        {
            m_HL = false;
        }
        if (this->getCfg("use_XJ", this->m_XJ) == false)
        {
            m_XJ = false;
        }
        if (this->getCfg("use_VM", this->m_VM) == false)
        {
            m_VM = false;
        }
        if (this->getCfg("use_LF", this->m_LF) == false)
        {
            m_LF = false;
        }
        if (this->getCfg("use_MC", this->m_MC) == false)
        {
            m_MC = false;
        }


        if (err)
        {
            exit(-1);
        }

        m_uihandler_ = UI_Open(OnNotifyMsg, nullptr);
        if (m_uihandler_ == INVALID_SIPHANDLE)
        {
            this->getLog()->critical("UI_Open Error!");
            exit(0);
        }
        if (!connect())
        {
            this->getLog()->critical("connect fail ");
            exit(0);
        }
    }
    else
    {
        this->getLog()->critical("Already have MD, only one MD");
    }
}

void sipui2MD::handle_start()
{
    MDBase::handle_start();
    this->setStatus(ServerComponentStatus::SRVCOMP_STATUS_READY);
}

void sipui2MD::handle_stop()
{
    this->setStatus(ServerComponentStatus::SRVCOMP_STATUS_NOTREADY);
    MDBase::handle_stop();
}

void __stdcall sipui2MD::OnNotifyMsg(TPKG_SIP *pPkg, CBPARAM pParam)
{
    // PKG错误
    if (CPKG_LOCAL_ERR == pPkg->PkgCode)
    {
        auto *p = (TPKG_SIP_SST *)pPkg;
        if (p->ErrCode == SIPE_DISCONNECT)
        {
            sip->getLog()->error(" Error! OnNotify:{},{}", GetErrInfo(p->ErrCode), p->Des);
            sip->connect();
            sip->subAll();
        }
        else if (p->ErrCode == SIPE_ASYNCONNECTERR)
        {
            sip->getLog()->error("error: SIPE_ASYNCONNECTERR");
        }
        else if (p->ErrCode == SIPE_ASYNCONNECTOK)
        {
            sip->getLog()->info("Success OnNotify: SIPE_ASYNCONNECTOK");
        }
        else if (p->ErrCode == SIPE_CONSVRFAIL)
        {
            sip->getLog()->info("error: SIPE_CONSVRFAIL");
            sip->connect();
            sip->subAll();
        }
        else
        {
            sip->getLog()->error("error:{},{}", GetErrInfo(p->ErrCode), p->Des);
        }
    }
    else if (CPKG_SVRPUTMSG == pPkg->PkgCode) // 消息推送
    {
        UI_ParseTagMsgs((TPKG_SIP_TAGMSGS *)pPkg, DoMsg, nullptr);
    }
    else if (CPKG_SSCTAGERRNOTIFY == pPkg->PkgCode) // 错误消息标签
    {
        auto *p = (TPKG_SIP_TAGERR *)pPkg;
        T_U16 i;
        for (i = 0; i < p->TagNum; i++)
            sip->getLog()->error("Tag = {} ,errcode =  {}, errdes = {} ", p->TagErr[i].TagCode, p->TagErr[i].Errcode,
                                 GetErrInfo(p->TagErr[i].Errcode));
    }
    else
        sip->getLog()->warn("OnNotify PkgCode = {},PkgSize = {}\n", pPkg->PkgCode, pPkg->PkgSize);
}

void _cdecl sipui2MD::DoMsg(T_SIPTAGMSG *ptag, void *pParam)
{
    sip->getLog()->trace("{}:{} Code:{}, MsgType:{}", __FILE__, __LINE__, ptag->Code, ptag->MsgType);
    if (0 != strcmp(ptag->Code, "MSG.PUBLIC.T"))
    {
        switch (ptag->MsgType)
        {
        case msg_type::SZ_STOCK_MARKET_L1:
        case msg_type::SH_STOCK_MARKET_L1:
            {
                sip->GetStockDataL1(ptag);
                break;
            }
        case msg_type::SH_STOCK_MARKET_L2:
        case msg_type::SZ_STOCK_MARKET_L2:
            {
                sip->GetStockDataL2(ptag);
                break;
            }
        case msg_type::SH_ORDER_QUEUE:
            {
                sip->GetOrderQueueData(ptag);
                break;
            }
        case msg_type::SZ_STOCK_STEP_TRADE:
            {
                sip->GetSZTransData(ptag);
                break;
            }
        case msg_type::SH_STOCK_STEP_TRADE:
            {
                sip->GetSHTransData(ptag);
                break;
            }
        case msg_type::SZ_STEP_ORDER:
            {
                sip->GetOrderData(ptag);
                break;
            }
        case msg_type::SH_STOCK_INDEX: // 上证指数
        case msg_type::SZ_STOCK_INDEX: // 深证指数
            {
                sip->GetIndexData(ptag);
                break;
            }
        /**
         * 这些交易所期货和期权是公用的
         */
        case msg_type::CFFEX_STOCK_BASE:
        case msg_type::CZCE_STOCK_BASE:
        case msg_type::DCE_STOCK_BASE:
        case msg_type::SHFE_STOCK_BASE:
            sip->GetFutureBaseData(ptag);
            break;
        case msg_type::CZCE_STOCK_MARKET:
        case msg_type::DCE_STOCK_MARKET:
        case msg_type::SHFE_STOCK_MARKET:
        case msg_type::CFFEX_STOCK_MARKET:
            sip->GetFutureData(ptag);
            break;
        /**
         * 上交所和深交所期权是独立的
         */
        case msg_type::SHOP_STOCK_BASE:
            sip->GetSHOptionBaseData(ptag);
            break;
        case msg_type::SHOP_STOCK_MARKET_L1:
            sip->GetSHOptionData(ptag);
            break;
        case msg_type::SZOP_STOCK_BASE:
            sip->GetSZOptionBaseData(ptag);
            break;
        case msg_type::SZOP_STOCK_MARKETL1:
            sip->GetSZOptionData(ptag);
            break;
        default:
            break;
        }
    }
}

void sipui2MD::GetStockDataL1(T_SIPTAGMSG *msg)
{
    const auto *market_data = reinterpret_cast<T_SZ_StockMarketDataL1 *>(msg->MsgData);
    auto code = std::string(msg->Code).substr(3, 6);

    MarketDataField res{};
    auto &res_stock = MarketDataStockL1::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);

    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", market_data->nTime / 10000000,
             market_data->nTime / 100000 % 100, market_data->nTime / 1000 % 100);
    res.UpdateMillisec = market_data->nTime % 1000;
    res.type = MARKET_DATA_TYPE_STOCK_L1;

    res_stock.payload().nTime = market_data->nTime;
    res_stock.payload().nNumTrades = market_data->uNumTrades;
    res_stock.payload().nVolume = market_data->iVolume;
    res_stock.payload().dbTurnover = static_cast<double>(market_data->iTurnover) / 10000;
    res_stock.payload().dbMatch = static_cast<double>(market_data->uMatch) / 10000;
    res_stock.payload().dbHighLimited = static_cast<double>(market_data->uHighLimited) / 10000;
    res_stock.payload().dbLowLimited = static_cast<double>(market_data->uLowLimited) / 10000;
    res_stock.payload().dbOpen = static_cast<double>(market_data->uOpen) / 10000;
    res_stock.payload().dbHigh = static_cast<double>(market_data->uHigh) / 10000;
    res_stock.payload().dbLow = static_cast<double>(market_data->uLow) / 10000;
    res_stock.payload().nStatus = market_data->nStatus; // 状态
    res_stock.payload().nPreIOPV = market_data->nPreIOPV; // 基金 T-1 日收盘时刻 IOPV 仅标的为基金时有效
    res_stock.payload().nIOPV = market_data->nIOPV; // 基金 IOPV 仅标的为基金时有效
    res_stock.payload().dbPreClose = static_cast<double>(market_data->uPreClose) / 10000; // 前收盘价
    for (int i = 0; i < 5; i++)
    {
        res_stock.payload().stAskSide[i].price = static_cast<float>(market_data->uAskPrice[i]) / 10000;
        res_stock.payload().stAskSide[i].volume = market_data->uAskVol[i];
        res_stock.payload().stBidSide[i].price = static_cast<float>(market_data->uBidPrice[i]) / 10000;
        res_stock.payload().stBidSide[i].volume = market_data->uBidVol[i];
    }

    this->forwardMarketData(res);
    if (!this->InfoIsIn(code))
    {
        staticInfo info{};
        info.lowerLimitPrice = res_stock.payload().dbLowLimited;
        info.upperLimitPrice = res_stock.payload().dbHighLimited;
        info.openPrice = res_stock.payload().dbOpen;
        info.preSettlementPrice = static_cast<double>(market_data->uPreClose) / 10000;
        putInfo(code, info);
    }
    this->getLog()->trace(
        "{}:{}, TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}] Cumtrade[{}] "
        "Cumvol[{}] Cumamount[{}] Last[{}]"
        "\nD0[{} {} {} {}] "
        "\nD1[{} {} {} {}] "
        "\nD2[{} {} {} {}] "
        "\nD3[{} {} {} {}] "
        "\nD4[{} {} {} {}] ",
        __FILE__, __LINE__, res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
        res_stock.payload().nNumTrades, res_stock.payload().nVolume, res_stock.payload().dbTurnover,
        res_stock.payload().dbMatch, res_stock.payload().stAskSide[0].price, res_stock.payload().stAskSide[0].volume,
        res_stock.payload().stBidSide[0].price, res_stock.payload().stBidSide[0].volume,
        res_stock.payload().stAskSide[1].price, res_stock.payload().stAskSide[1].volume,
        res_stock.payload().stBidSide[1].price, res_stock.payload().stBidSide[1].volume,
        res_stock.payload().stAskSide[2].price, res_stock.payload().stAskSide[2].volume,
        res_stock.payload().stBidSide[2].price, res_stock.payload().stBidSide[2].volume,
        res_stock.payload().stAskSide[3].price, res_stock.payload().stAskSide[3].volume,
        res_stock.payload().stBidSide[3].price, res_stock.payload().stBidSide[3].volume,
        res_stock.payload().stAskSide[4].price, res_stock.payload().stAskSide[4].volume,
        res_stock.payload().stBidSide[4].price, res_stock.payload().stBidSide[4].volume);
};

void sipui2MD::GetStockDataL2(T_SIPTAGMSG *msg)
{

    const auto market_data = reinterpret_cast<T_SZ_StockMarketDataL2 *>(msg->MsgData);
    auto code = std::string(msg->Code).substr(3, 6);
    MarketDataField res{};
    auto &res_stock = MarketDataStockL2::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);

    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", market_data->nTime / 10000000,
             market_data->nTime / 100000 % 100, market_data->nTime / 1000 % 100);
    res.UpdateMillisec = market_data->nTime % 1000;
    res.type = MARKET_DATA_TYPE_STOCK_L2;

    res_stock.payload().nTime = market_data->nTime;
    res_stock.payload().nNumTrades = market_data->uNumTrades;
    res_stock.payload().nVolume = market_data->iVolume;
    res_stock.payload().dbTurnover = static_cast<double>(market_data->iTurnover) / 10000;
    res_stock.payload().dbMatch = static_cast<double>(market_data->uMatch) / 10000;
    res_stock.payload().dbHighLimited = static_cast<double>(market_data->uHighLimited) / 10000;
    res_stock.payload().dbLowLimited = static_cast<double>(market_data->uLowLimited) / 10000;
    res_stock.payload().dbOpen = static_cast<double>(market_data->uOpen) / 10000;
    res_stock.payload().dbHigh = static_cast<double>(market_data->uHigh) / 10000;
    res_stock.payload().dbLow = static_cast<double>(market_data->uLow) / 10000;
    res_stock.payload().nTotalBidVol = market_data->iTotalBidVol;
    res_stock.payload().nTotalAskVol = market_data->iTotalAskVol;
    res_stock.payload().dbWeightedAvgBidPrice = static_cast<double>(market_data->uWeightedAvgBidPrice) / 10000;
    res_stock.payload().dbWeightedAvgAskPrice = static_cast<double>(market_data->uWeightedAvgAskPrice) / 10000;

    res_stock.payload().nStatus = market_data->nStatus; // 状态
    res_stock.payload().nPreIOPV = market_data->nPreIOPV; // 基金 T-1 日收盘时刻 IOPV 仅标的为基金时有效
    res_stock.payload().nIOPV = market_data->nIOPV; // 基金 IOPV 仅标的为基金时有效
    res_stock.payload().dbPreClose = static_cast<double>(market_data->uPreClose) / 10000; // 前收盘价

    for (int i = 0; i < 10; i++)
    {
        res_stock.payload().stAskSide[i].price = static_cast<float>(market_data->uAskPrice[i]) / 10000;
        res_stock.payload().stAskSide[i].volume = market_data->uAskVol[i];
        res_stock.payload().stBidSide[i].price = static_cast<float>(market_data->uBidPrice[i]) / 10000;
        res_stock.payload().stBidSide[i].volume = market_data->uBidVol[i];
    }

    this->forwardMarketData(res);
    if (!this->InfoIsIn(code))
    {
        staticInfo info{};
        info.lowerLimitPrice = res_stock.payload().dbLowLimited;
        info.upperLimitPrice = res_stock.payload().dbHighLimited;
        info.openPrice = res_stock.payload().dbOpen;
        info.preSettlementPrice = static_cast<double>(market_data->uPreClose) / 10000;

        putInfo(code, info);
    }
    this->getLog()->trace(
        "TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}] Cumtrade[{}] Cumvol[{}] "
        "Cumamount[{}] Last[{}] "
        "\nD0[{} {} {} {}] "
        "\nD1[{} {} {} {}] "
        "\nD2[{} {} {} {}] "
        "\nD3[{} {} {} {}] "
        "\nD4[{} {} {} {}] "
        "\nD5[{} {} {} {}] "
        "\nD6[{} {} {} {}] "
        "\nD7[{} {} {} {}] "
        "\nD8[{} {} {} {}] "
        "\nD9[{} {} {} {}] ",
        res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
        res_stock.payload().nNumTrades, res_stock.payload().nVolume, res_stock.payload().dbTurnover,
        res_stock.payload().dbMatch, res_stock.payload().stAskSide[0].price, res_stock.payload().stAskSide[0].volume,
        res_stock.payload().stBidSide[0].price, res_stock.payload().stBidSide[0].volume,
        res_stock.payload().stAskSide[1].price, res_stock.payload().stAskSide[1].volume,
        res_stock.payload().stBidSide[1].price, res_stock.payload().stBidSide[1].volume,
        res_stock.payload().stAskSide[2].price, res_stock.payload().stAskSide[2].volume,
        res_stock.payload().stBidSide[2].price, res_stock.payload().stBidSide[2].volume,
        res_stock.payload().stAskSide[3].price, res_stock.payload().stAskSide[3].volume,
        res_stock.payload().stBidSide[3].price, res_stock.payload().stBidSide[3].volume,
        res_stock.payload().stAskSide[4].price, res_stock.payload().stAskSide[4].volume,
        res_stock.payload().stBidSide[4].price, res_stock.payload().stBidSide[4].volume,
        res_stock.payload().stAskSide[5].price, res_stock.payload().stAskSide[5].volume,
        res_stock.payload().stBidSide[5].price, res_stock.payload().stBidSide[5].volume,
        res_stock.payload().stAskSide[6].price, res_stock.payload().stAskSide[6].volume,
        res_stock.payload().stBidSide[6].price, res_stock.payload().stBidSide[6].volume,
        res_stock.payload().stAskSide[7].price, res_stock.payload().stAskSide[7].volume,
        res_stock.payload().stBidSide[7].price, res_stock.payload().stBidSide[7].volume,
        res_stock.payload().stAskSide[8].price, res_stock.payload().stAskSide[8].volume,
        res_stock.payload().stBidSide[8].price, res_stock.payload().stBidSide[8].volume,
        res_stock.payload().stAskSide[9].price, res_stock.payload().stAskSide[9].volume,
        res_stock.payload().stBidSide[9].price, res_stock.payload().stBidSide[9].volume);
};

void sipui2MD::GetOrderData(T_SIPTAGMSG *msg)
{
    const auto step_order = reinterpret_cast<Stock_StepOrder_SZ *>(msg->MsgData);

    MarketDataField res = {};
    OrderData &res_stock = OrderData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", step_order->nActionDay);

    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(step_order->i64TransactTime / 10000000),
             (int)(step_order->i64TransactTime / 100000 % 100), (int)(step_order->i64TransactTime / 1000 % 100));
    res.UpdateMillisec = step_order->i64TransactTime % 1000;
    res.type = MARKET_DATA_TYPE_ORDER_DATA;

    res_stock.payload().price = static_cast<float>(step_order->i64Price) / 10000;
    res_stock.payload().volume = step_order->i64OrderQty;

    // @todo 为什么提示代码不可到达
    if (step_order->cSide == '1')
    {
        res_stock.payload().directory = Buy;
    }
    else if (step_order->cSide == '2')
    {
        res_stock.payload().directory = Sell;
    }
    else
    {
        this->getLog()->error("code:{} time:{} prc:{} vol:{} order side {} is error", msg->Code,
                              step_order->i64TransactTime, step_order->i64Price, step_order->i64OrderQty,
                              step_order->cSide);
        return;
    }

    if (step_order->sExtendFields[0] == '1')
        res_stock.payload().type = AnyPrice;
    else if (step_order->sExtendFields[0] == '2')
        res_stock.payload().type = LimitPrice;
    else if (step_order->sExtendFields[0] == 'U')
        res_stock.payload().type = BestPrice;
    else
    {
        this->getLog()->error("code:{} time:{} prc:{} vol:{} order type {} is error", msg->Code,
                              step_order->i64TransactTime, step_order->i64Price, step_order->i64OrderQty,
                              step_order->sExtendFields);
        return;
    }
    res_stock.payload().orderId = step_order->i64ApplSeqNum;

    this->forwardMarketData(res);
    this->getLog()->trace("TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
                         "price[{}] volume[{}] directory[{}] type[{}] orderId[{}]",
                         res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
                         res_stock.payload().price, res_stock.payload().volume, res_stock.payload().directory,
                         res_stock.payload().type, res_stock.payload().orderId);
}

void sipui2MD::GetOrderQueueData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<PSH_StockOrderQueue>(msg->MsgData);
    auto stHeadInfo = market_data->tHead;
    auto stOrderQueue = market_data->tItem;
    getLog()->info("{}:{} Day:{}, ItemNum:{}", __FILE__, __LINE__, stHeadInfo.nActionDay, stHeadInfo.nItem);
    MarketDataField res = {};
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", stHeadInfo.nActionDay);

    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", stOrderQueue->nTime / 10000000,
             stOrderQueue->nTime / 100000 % 100, stOrderQueue->nTime / 1000 % 100);
    res.UpdateMillisec = stOrderQueue->nTime % 1000;
    res.type = MARKET_DATA_TYPE_ORDER_QUEUE;
    auto &orderQueueData = OrderQueueData::doCast(res);
    orderQueueData.payload().stHead.nActionDay = stHeadInfo.nActionDay;
    orderQueueData.payload().stHead.nItem = stHeadInfo.nItem;
    for (int i = 0; i < stHeadInfo.nItem; i++)
    {
        getLog()->trace("{}:{} OrderNum:{}, Price:{}, Side:{}, Time:{}", __FILE__, __LINE__, stOrderQueue[i].nOrders,
                       stOrderQueue[i].nPrice, stOrderQueue[i].nSide, stOrderQueue[i].nTime);
        orderQueueData.payload().stItem[i].nOrders = stOrderQueue[i].nOrders;
        orderQueueData.payload().stItem[i].dbPrice = static_cast<double>(stOrderQueue[i].nPrice) / 10000;
        if (stOrderQueue[i].nSide == 'B')
            orderQueueData.payload().stItem[i].emDirection = Buy;
        else
            orderQueueData.payload().stItem[i].emDirection = Sell;
        orderQueueData.payload().stItem[i].nTime = stOrderQueue[i].nTime;
        orderQueueData.payload().stItem[i].nABItems = stOrderQueue[i].nABItems;
        auto itemNum = stOrderQueue[i].nABItems;
        for (int j = 0; j < itemNum; j++)
        {
            getLog()->trace("{}:{} ABItems:{}, ABVolume:{}", __FILE__, __LINE__, stOrderQueue[i].nABItems,
                           stOrderQueue[i].nABVolume[j]);
            orderQueueData.payload().stItem[i].nABVolume[j] = stOrderQueue[i].nABVolume[j];
        }
    }
    this->forwardMarketData(res);
}

void sipui2MD::GetSZTransData(T_SIPTAGMSG *msg)
{
    const auto step_trade = reinterpret_cast<Stock_Transaction_SZ *>(msg->MsgData);

    MarketDataField res = {};
    TransactionData &res_stock = TransactionData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", step_trade->nActionDay);

    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(step_trade->i64TransactTime / 10000000),
             (int)(step_trade->i64TransactTime / 100000 % 100), (int)(step_trade->i64TransactTime / 1000 % 100));
    res.UpdateMillisec = step_trade->i64TransactTime % 1000;
    res.type = MARKET_DATA_TYPE_TRANSACTION;

    res_stock.payload().transid = step_trade->i64ApplSeqNum;
    res_stock.payload().price = static_cast<float>(step_trade->i64LastPx) / 10000;
    res_stock.payload().volume = step_trade->i64LastQty;
    res_stock.payload().askId = step_trade->i64OfferApplSeqNum;
    res_stock.payload().bidId = step_trade->i64BidApplSeqNum;
    if (res_stock.payload().price == 0)
        res_stock.payload().type = 'C';
    else
        res_stock.payload().type = '0';
    if (res_stock.payload().askId > res_stock.payload().bidId)
    {
        res_stock.payload().directory = Sell;
    }
    else
    {
        res_stock.payload().directory = Buy;
    }

    this->forwardMarketData(res);
    this->getLog()->trace("TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
                         "transid[{}] price[{}] volume[{}] askid[{}] bidid[{}] type[{}] directory[{}]",
                         res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
                         res_stock.payload().transid, res_stock.payload().price, res_stock.payload().volume,
                         res_stock.payload().askId, res_stock.payload().bidId, res_stock.payload().type,
                         res_stock.payload().directory);
}

void sipui2MD::GetSHTransData(T_SIPTAGMSG *msg)
{
    const auto *step_trade = reinterpret_cast<Stock_Transaction_SH *>(msg->MsgData);

    MarketDataField res{};
    TransactionData &res_stock = TransactionData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", step_trade->nActionDay);

    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(step_trade->nTradeTime / 10000000),
             (int)(step_trade->nTradeTime / 100000 % 100), (int)(step_trade->nTradeTime / 1000 % 100));
    res.UpdateMillisec = step_trade->nTradeTime % 1000;
    res.type = MARKET_DATA_TYPE_TRANSACTION;

    res_stock.payload().transid = step_trade->nTradeIndex;
    res_stock.payload().price = static_cast<float>(step_trade->nTradePrice) / 10000;
    res_stock.payload().volume = step_trade->iTradeQty;
    res_stock.payload().askId = step_trade->iTradeSellNo;
    res_stock.payload().bidId = step_trade->iTradeBuyNo;
    if (res_stock.payload().price == 0)
        res_stock.payload().type = 'C';
    else
        res_stock.payload().type = '0';
    if (res_stock.payload().askId > res_stock.payload().bidId)
    {
        res_stock.payload().directory = Sell;
    }
    else
    {
        res_stock.payload().directory = Buy;
    }

    this->forwardMarketData(res);
    this->getLog()->trace("TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
                         "transid[{}] price[{}] volume[{}] askid[{}] bidid[{}] type[{}] directory[{}]",
                         res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
                         res_stock.payload().transid, res_stock.payload().price, res_stock.payload().volume,
                         res_stock.payload().askId, res_stock.payload().bidId, res_stock.payload().type,
                         res_stock.payload().directory);
}

void sipui2MD::GetIndexData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<t_SH_StockIndex *>(msg->MsgData);

    MarketDataField res{};
    IndexData &res_stock = IndexData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);
    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(market_data->nTime / 10000000),
             (int)(market_data->nTime / 100000 % 100), (int)(market_data->nTime / 1000 % 100));
    res.UpdateMillisec = market_data->nTime % 1000;
    res.type = MARKET_DATA_TYPE_INDEX_DATA;

    res_stock.payload().Open = static_cast<double>(market_data->nOpenIndex) / 10000;
    res_stock.payload().Last = static_cast<double>(market_data->nLastIndex) / 10000;
    res_stock.payload().High = static_cast<double>(market_data->nHighIndex) / 10000;
    res_stock.payload().Low = static_cast<double>(market_data->nLowIndex) / 10000;
    res_stock.payload().Cumvol = market_data->iTotalVolume / 100;
    res_stock.payload().Cumamount = market_data->iTurnover;

    this->forwardMarketData(res);
    this->getLog()->trace(
        "TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}] Cumvol[{}] Cumamount[{}]"
        "Last[{}] open[{}] High[{}] Low[{}]",
        res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
        res_stock.payload().Cumvol, res_stock.payload().Cumamount, res_stock.payload().Last, res_stock.payload().Open,
        res_stock.payload().High, res_stock.payload().Low);
}

void sipui2MD::GetFutureData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<Futures_MarketData *>(msg->MsgData);
    MarketDataField res{};
    auto &res_stock = FutureData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);
    const auto result = sipui2MD::splitString(msg->Code, '.');
    const auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(market_data->nTime / 10000000),
             (int)(market_data->nTime / 100000 % 100), (int)(market_data->nTime / 1000 % 100));
    res.UpdateMillisec = market_data->nTime % 1000;
    res.type = MARKET_DATA_TYPE_FUTURE_DATA;

    res_stock.payload().nTime = market_data->nTime;
    res_stock.payload().nPreOpenInterest = market_data->iPreOpenInterest;
    res_stock.payload().dbPreClose = static_cast<double>(market_data->uPreClose) / 10000;
    res_stock.payload().dbPreSettlePrice = static_cast<double>(market_data->uPreSettlePrice) / 10000;
    res_stock.payload().dbOpen = static_cast<double>(market_data->uOpen) / 10000;
    res_stock.payload().dbHigh = static_cast<double>(market_data->uHigh) / 10000;
    res_stock.payload().dbLow = static_cast<double>(market_data->uLow) / 10000;
    res_stock.payload().dbMatch = static_cast<double>(market_data->uMatch) / 10000;
    res_stock.payload().nVolume = market_data->iVolume;
    res_stock.payload().dbTurnover = static_cast<double>(market_data->iTurnover) / 10000;
    res_stock.payload().nOpenInterest = market_data->iOpenInterest;
    res_stock.payload().dbClose = static_cast<double>(market_data->uClose) / 10000;
    res_stock.payload().dbSettlePrice = static_cast<double>(market_data->uSettlePrice) / 10000;
    res_stock.payload().dbHighLimited = static_cast<double>(market_data->uHighLimited) / 10000;
    res_stock.payload().dbLowLimited = static_cast<double>(market_data->uLowLimited) / 10000;
    res_stock.payload().nCurrDelta = market_data->nCurrDelta;
    res_stock.payload().nStatus = market_data->nStatus;
    res_stock.payload().nPreDelta = market_data->nPreDelta;

    for (int i = 0; i < 5; i++)
    {
        res_stock.payload().stAskSide[i].price = static_cast<float>(market_data->uAskPrice[i]) / 10000;
        res_stock.payload().stAskSide[i].volume = market_data->uAskVol[i];
        res_stock.payload().stBidSide[i].price = static_cast<float>(market_data->uBidPrice[i]) / 10000;
        res_stock.payload().stBidSide[i].volume = market_data->uBidVol[i];
    }

    this->forwardMarketData(res);
    this->getLog()->trace(
        "{}:{} TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
        "\n nPreOpenInterest[{}] dbPreClose[{}] dbPreSettlePrice[{}] dbOpen[{}] dbHigh[{}] dbLow[{}]"
        "\n dbMatch[{}] nVolume[{}] dbTurnover[{}] nOpenInterest[{}] dbClose[{}] dbSettlePrice[{}]"
        "\n dbHighLimited[{}] dbLowLimited[{}] nCurrDelta[{}] nStatus[{}] nPreDelta[{}]"
        "\n D0[{} {} {} {}] "
        "\n D1[{} {} {} {}] "
        "\n D2[{} {} {} {}] "
        "\n D3[{} {} {} {}] "
        "\n D4[{} {} {} {}]",
        __FILE__, __LINE__, res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
        res_stock.payload().nPreOpenInterest, res_stock.payload().dbPreClose, res_stock.payload().dbPreSettlePrice,
        res_stock.payload().dbOpen, res_stock.payload().dbHigh, res_stock.payload().dbLow, res_stock.payload().dbMatch,
        res_stock.payload().nVolume, res_stock.payload().dbTurnover, res_stock.payload().nOpenInterest,
        res_stock.payload().dbClose, res_stock.payload().dbSettlePrice, res_stock.payload().dbHighLimited,
        res_stock.payload().dbLowLimited, res_stock.payload().nCurrDelta, res_stock.payload().nStatus,
        res_stock.payload().nPreDelta, res_stock.payload().stAskSide[0].price, res_stock.payload().stAskSide[0].volume,
        res_stock.payload().stBidSide[0].price, res_stock.payload().stBidSide[0].volume,
        res_stock.payload().stAskSide[1].price, res_stock.payload().stAskSide[1].volume,
        res_stock.payload().stBidSide[1].price, res_stock.payload().stBidSide[1].volume,
        res_stock.payload().stAskSide[2].price, res_stock.payload().stAskSide[2].volume,
        res_stock.payload().stBidSide[2].price, res_stock.payload().stBidSide[2].volume,
        res_stock.payload().stAskSide[3].price, res_stock.payload().stAskSide[3].volume,
        res_stock.payload().stBidSide[3].price, res_stock.payload().stBidSide[3].volume,
        res_stock.payload().stBidSide[4].price, res_stock.payload().stBidSide[4].volume,
        res_stock.payload().stAskSide[4].price, res_stock.payload().stAskSide[4].volume);
}
void sipui2MD::GetFutureBaseData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<PCFFEX_BaseInfo>(msg->MsgData);
    MarketDataField res{};
    auto &res_stock = FutureBaseData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);
    const auto result = sipui2MD::splitString(msg->Code, '.');
    const auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(market_data->nActionDay / 10000000),
             (int)(market_data->nActionDay / 100000 % 100), (int)(market_data->nActionDay / 1000 % 100));
    res.UpdateMillisec = market_data->nActionDay % 1000;
    res.type = MARKET_DATA_TYPE_FUTURE_BASE;

    strcpy(res_stock.payload().pszInstrumentID, market_data->sInstrumentID);
    strcpy(res_stock.payload().pszExchangeID, market_data->sExchangeID);
    strcpy(res_stock.payload().pszInstrumentName, market_data->sInstrumentName);
    strcpy(res_stock.payload().pszExchangeInstID, market_data->sExchangeInstID);
    strcpy(res_stock.payload().pszProductID, market_data->sProductID);
    res_stock.payload().chProductClass = market_data->cProductClass;
    res_stock.payload().nDeliveryYear = market_data->nDeliveryYear;
    res_stock.payload().nDeliveryMonth = market_data->nDeliveryMonth;
    res_stock.payload().nMaxMarketOrderVolume = market_data->nMaxMarketOrderVolume;
    res_stock.payload().nMinLimitOrderVolume = market_data->nMinLimitOrderVolume;
    res_stock.payload().nMaxLimitOrderVolume = market_data->nMaxLimitOrderVolume;
    res_stock.payload().nMinLimitOrderVolume = market_data->nMinLimitOrderVolume;
    res_stock.payload().nPriceTick = market_data->i64PriceTick;
    res_stock.payload().nCreateDate = market_data->nCreateDate;
    res_stock.payload().nOpenDate = market_data->nOpenDate;
    res_stock.payload().nExpireDate = market_data->nExpireDate;
    res_stock.payload().nStartDelivDate = market_data->nStartDelivDate;
    res_stock.payload().nEndDelivDate = market_data->nEndDelivDate;
    res_stock.payload().chInstLifePhase = market_data->cInstLifePhase;
    res_stock.payload().nIsTrading = market_data->nIsTrading;
    res_stock.payload().chPositionType = market_data->cPositionType;
    res_stock.payload().chPositionDateType = market_data->cPositionDateType;
    res_stock.payload().nLongMarginRatio = market_data->i64LongMarginRatio;
    res_stock.payload().nShortMarginRatio = market_data->i64ShortMarginRatio;
    res_stock.payload().chMaxMarginSideAlgorithm = market_data->cMaxMarginSideAlgorithm;
    strcpy(res_stock.payload().pszUnderlyingInstrID, market_data->sUnderlyingInstrID);
    res_stock.payload().nStrikePrice = market_data->i64StrikePrice;
    res_stock.payload().chOptionsType = market_data->cOptionsType;
    res_stock.payload().nUnderlyingMultiple = market_data->i64UnderlyingMultiple;
    res_stock.payload().chCombinationType = market_data->cCombinationType;

    this->forwardMarketData(res);
    this->getLog()->trace(
        "{}:{} TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
        "\n pszInstrumentID[{}] pszExchangeID[{}] pszInstrumentName[{}] pszExchangeInstID[{}] pszProductID[{}]"
        "\n chProductClass[{}] nDeliveryYear[{}] nDeliveryMonth[{}] nMaxMarketOrderVolume[{}] nMinLimitOrderVolume[{}]"
        "\n nMaxLimitOrderVolume[{}] nMinLimitOrderVolume[{}] nPriceTick[{}] nCreateDate[{}] nOpenDate[{}] "
        "nExpireDate[{}]"
        "\n nStartDelivDate[{}] nEndDelivDate[{}] chInstLifePhase[{}] nIsTrading[{}] chPositionType[{}] "
        "chPositionDateType[{}]"
        "\n nLongMarginRatio[{}] nShortMarginRatio[{}] chMaxMarginSideAlgorithm[{}] pszUnderlyingInstrID[{}] "
        "nStrikePrice[{}]"
        "\n chOptionsType[{}] nUnderlyingMultiple[{}] chCombinationType[{}]",
        __FILE__, __LINE__, res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
        res_stock.payload().pszInstrumentID, res_stock.payload().pszExchangeID, res_stock.payload().pszInstrumentName,
        res_stock.payload().pszExchangeInstID, res_stock.payload().pszProductID, res_stock.payload().chProductClass,
        res_stock.payload().nDeliveryYear, res_stock.payload().nDeliveryMonth,
        res_stock.payload().nMaxMarketOrderVolume, res_stock.payload().nMinLimitOrderVolume,
        res_stock.payload().nMaxLimitOrderVolume, res_stock.payload().nMinLimitOrderVolume,
        res_stock.payload().nPriceTick, res_stock.payload().nCreateDate, res_stock.payload().nOpenDate,
        res_stock.payload().nExpireDate, res_stock.payload().nStartDelivDate, res_stock.payload().nEndDelivDate,
        res_stock.payload().chInstLifePhase, res_stock.payload().nIsTrading, res_stock.payload().chPositionType,
        res_stock.payload().chPositionDateType, res_stock.payload().nLongMarginRatio,
        res_stock.payload().nShortMarginRatio, res_stock.payload().chMaxMarginSideAlgorithm,
        res_stock.payload().pszUnderlyingInstrID, res_stock.payload().nStrikePrice, res_stock.payload().chOptionsType,
        res_stock.payload().nUnderlyingMultiple, res_stock.payload().chCombinationType);
}

void sipui2MD::GetSHOptionData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<PSHOP_MarketData>(msg->MsgData);
    MarketDataField res{};
    auto &res_stock = SHOptionData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);
    const auto result = sipui2MD::splitString(msg->Code, '.');
    const auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(market_data->nActionDay / 10000000),
             (int)(market_data->nActionDay / 100000 % 100), (int)(market_data->nActionDay / 1000 % 100));
    res.UpdateMillisec = market_data->nActionDay % 1000;
    res.type = MARKET_DATA_TYPE_SHOPTION_DATA;

    auto &payload = res_stock.payload();

    payload.nDataTimestamp = market_data->nDataTimestamp;
    payload.dbPreSettlPrice = static_cast<double>(market_data->iPreSettlPrice) / 10000;
    payload.dbSettlPrice = static_cast<double>(market_data->iSettlPrice) / 10000;
    payload.dbOpenPx = static_cast<double>(market_data->iOpenPx) / 10000;
    payload.dbHighPx = static_cast<double>(market_data->iHighPx) / 10000;
    payload.dbLowPx = static_cast<double>(market_data->iLowPx) / 10000;
    payload.dbLastPx = static_cast<double>(market_data->iLastPx) / 10000;
    payload.dbAuctionPrice = static_cast<double>(market_data->iAuctionPrice) / 10000;
    payload.nAuctionQty = market_data->iAuctionQty;
    payload.nTotalLongPosition = market_data->iTotalLongPosition;
    for (int i = 0; i < 5; i++)
    {
        payload.stAskSide[i].price = static_cast<float>(market_data->iOfferPx[i]) / 10000;
        payload.stAskSide[i].volume = market_data->iOfferSize[i];
        payload.stBidSide[i].price = static_cast<float>(market_data->iBidPx[i]) / 10000;
        payload.stBidSide[i].volume = market_data->iBidSize[i];
    }
    payload.dbTotalValueTrade = static_cast<double>(market_data->iTotalValueTrade) / 10000;
    payload.nTotalVolumeTrade = market_data->iTotalVolumeTrade;
    strcpy(payload.pszTradingPhaseCode, market_data->sTradingPhaseCode);
    strcpy(payload.pszTransactTimeOnly, market_data->sTransactTimeOnly);
    this->forwardMarketData(res);
    this->getLog()->trace("{}:{} TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
                         "\n nDataTimestamp[{}] dbPreSettlPrice[{}] dbSettlPrice[{}] dbOpenPx[{}] dbHighPx[{}] dbLowPx[{}]"
                         "\n dbLastPx[{}] dbAuctionPrice[{}] nAuctionQty[{}] nTotalLongPosition[{}]"
                         "\n dbTotalValueTrade[{}] nTotalVolumeTrade[{}] pszTradingPhaseCode[{}] pszTransactTimeOnly[{}]"
                         "\n D0[{} {} {} {}] "
                         "\n D1[{} {} {} {}] "
                         "\n D2[{} {} {} {}] "
                         "\n D3[{} {} {} {}] "
                         "\n D4[{} {} {} {}]",
                         __FILE__, __LINE__, res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID,
                         res.UpdateMillisec, payload.nDataTimestamp, payload.dbPreSettlPrice, payload.dbSettlPrice,
                         payload.dbOpenPx, payload.dbHighPx, payload.dbLowPx, payload.dbLastPx, payload.dbAuctionPrice,
                         payload.nAuctionQty, payload.nTotalLongPosition, payload.dbTotalValueTrade,
                         payload.nTotalVolumeTrade, payload.pszTradingPhaseCode, payload.pszTransactTimeOnly,
                         payload.stAskSide[0].price, payload.stAskSide[0].volume, payload.stBidSide[0].price,
                         payload.stBidSide[0].volume, payload.stAskSide[1].price, payload.stAskSide[1].volume,
                         payload.stBidSide[1].price, payload.stBidSide[1].volume, payload.stAskSide[2].price,
                         payload.stAskSide[2].volume, payload.stBidSide[2].price, payload.stBidSide[2].volume,
                         payload.stAskSide[3].price, payload.stAskSide[3].volume, payload.stBidSide[3].price,
                         payload.stBidSide[3].volume, payload.stBidSide[4].price, payload.stBidSide[4].volume,
                         payload.stAskSide[4].price, payload.stAskSide[4].volume);
}

void sipui2MD::GetSZOptionData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<PSZOP_MARKETDATA>(msg->MsgData);
    MarketDataField res{};
    auto &res_stock = SZOptionData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);
    const auto result = sipui2MD::splitString(msg->Code, '.');
    const auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(market_data->nActionDay / 10000000),
             (int)(market_data->nActionDay / 100000 % 100), (int)(market_data->nActionDay / 1000 % 100));
    res.UpdateMillisec = market_data->nActionDay % 1000;
    res.type = MARKET_DATA_TYPE_SZOPTION_DATA;

    auto &payload = res_stock.payload();

    payload.nTime = market_data->nTime;
    payload.nChannelNo = market_data->usChannelNo;
    strcpy(payload.pszMDStreamID, market_data->sMDStreamID);
    strcpy(payload.pszSecrityID, market_data->sSecrityID);
    strcpy(payload.pszSecurityIDSource, market_data->sSecurityIDSource);
    strcpy(payload.pszTradingPhaseCode, market_data->sTradingPhaseCode);
    payload.dbPrevClosePx = static_cast<double>(market_data->i64PrevClosePx) / 10000;
    payload.nNumTrades = market_data->i64NumTrades;
    payload.nTotalVolumeTrade = market_data->i64TotalVolumeTrade;
    payload.dbTotalValueTrade = static_cast<double>(market_data->i64TotalValueTrade) / 10000;
    payload.dbLastPrice = static_cast<double>(market_data->i64LastPrice) / 10000;
    payload.dbOpenPrice = static_cast<double>(market_data->i64OpenPrice) / 10000;
    payload.dbHighPrice = static_cast<double>(market_data->i64HighPrice) / 10000;
    payload.dbLowPrice = static_cast<double>(market_data->i64LowPrice) / 10000;
    payload.dbBuyAvgPrice = static_cast<double>(market_data->i64BuyAvgPrice) / 10000;
    payload.dbSellAvgPrice = static_cast<double>(market_data->i64SellAvgPrice) / 10000;
    payload.nBuyVolumeTrade = market_data->i64BuyVolumeTrade;
    payload.nSellVolumeTrade = market_data->i64SellVolumeTrade;
    for (int i = 0; i < 10; i++)
    {
        payload.stOfferSide[i].price = static_cast<float>(market_data->i64OfferPrice[i]) / 10000;
        payload.stOfferSide[i].volume = market_data->i64OfferQty[i];
        payload.stBidSide[i].price = static_cast<float>(market_data->i64BidPrice[i]) / 10000;
        payload.stBidSide[i].volume = market_data->i64BidQty[i];
    }
    payload.dbPriceUpperLimit = static_cast<double>(market_data->i64PriceUpperLimit) / 10000;
    payload.dbPriceLowerLimit = static_cast<double>(market_data->i64PriceLowerLimit) / 10000;
    payload.nContractPosition = market_data->i64ContractPosition;

    this->forwardMarketData(res);
    this->getLog()->trace(
        "{}:{} TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
        "\n nTime[{}] nChannelNo[{}] pszMDStreamID[{}] pszSecrityID[{}] pszSecurityIDSource[{}]"
        "\n pszTradingPhaseCode[{}] dbPrevClosePx[{}] nNumTrades[{}] nTotalVolumeTrade[{}]"
        "\n dbTotalValueTrade[{}] dbLastPrice[{}] dbOpenPrice[{}] dbHighPrice[{}] dbLowPrice[{}]"
        "\n dbBuyAvgPrice[{}] dbSellAvgPrice[{}] nBuyVolumeTrade[{}] nSellVolumeTrade[{}]"
        "\n dbPriceUpperLimit[{}] dbPriceLowerLimit[{}] nContractPosition[{}]"
        "\n D0[{} {} {} {}] "
        "\n D1[{} {} {} {}] "
        "\n D2[{} {} {} {}] "
        "\n D3[{} {} {} {}] "
        "\n D4[{} {} {} {}] "
        "\n D5[{} {} {} {}] "
        "\n D6[{} {} {} {}] "
        "\n D7[{} {} {} {}] "
        "\n D8[{} {} {} {}] "
        "\n D9[{} {} {} {}] ",
        __FILE__, __LINE__, res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
        payload.nTime, payload.nChannelNo, payload.pszMDStreamID, payload.pszSecrityID, payload.pszSecurityIDSource,
        payload.pszTradingPhaseCode, payload.dbPrevClosePx, payload.nNumTrades, payload.nTotalVolumeTrade,
        payload.dbTotalValueTrade, payload.dbLastPrice, payload.dbOpenPrice, payload.dbHighPrice, payload.dbLowPrice,
        payload.dbBuyAvgPrice, payload.dbSellAvgPrice, payload.nBuyVolumeTrade, payload.nSellVolumeTrade,
        payload.dbPriceUpperLimit, payload.dbPriceLowerLimit, payload.nContractPosition, payload.stOfferSide[0].price,
        payload.stOfferSide[0].volume, payload.stBidSide[0].price, payload.stBidSide[0].volume,
        payload.stOfferSide[1].price, payload.stOfferSide[1].volume, payload.stBidSide[1].price,
        payload.stBidSide[1].volume, payload.stOfferSide[2].price, payload.stOfferSide[2].volume,
        payload.stBidSide[2].price, payload.stBidSide[2].volume, payload.stOfferSide[3].price,
        payload.stOfferSide[3].volume, payload.stBidSide[3].price, payload.stBidSide[3].volume,
        payload.stBidSide[4].price, payload.stBidSide[4].volume, payload.stOfferSide[4].price,
        payload.stOfferSide[4].volume, payload.stBidSide[5].price, payload.stBidSide[5].volume,
        payload.stOfferSide[5].price, payload.stOfferSide[5].volume, payload.stBidSide[6].price,
        payload.stBidSide[6].volume, payload.stOfferSide[6].price, payload.stOfferSide[6].volume,
        payload.stBidSide[7].price, payload.stBidSide[7].volume, payload.stOfferSide[7].price,
        payload.stOfferSide[7].volume, payload.stBidSide[8].price, payload.stBidSide[8].volume,
        payload.stOfferSide[8].price, payload.stOfferSide[8].volume, payload.stBidSide[9].price,
        payload.stBidSide[9].volume, payload.stOfferSide[9].price, payload.stOfferSide[9].volume);
}

void sipui2MD::GetSHOptionBaseData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<PSHOP_BaseInfo>(msg->MsgData);
    MarketDataField res{};
    auto &res_stock = SHOptionBaseData::doCast(res);
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", market_data->nActionDay);
    const auto result = sipui2MD::splitString(msg->Code, '.');
    const auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(market_data->nActionDay / 10000000),
             (int)(market_data->nActionDay / 100000 % 100), (int)(market_data->nActionDay / 1000 % 100));
    res.UpdateMillisec = market_data->nActionDay % 1000;
    res.type = MARKET_DATA_TYPE_SHOPTION_BASE;

    auto &payload = res_stock.payload();
    strcpy(payload.pszSecurityID, market_data->sSecurityID);
    strcpy(payload.pszContractID, market_data->sContractID);
    strcpy(payload.pszContractSymbol, market_data->sContractSymbol);
    strcpy(payload.pszUnderlyingSecurityID, market_data->sUnderlyingSecurityID);
    strcpy(payload.pszUnderlyingSymbol, market_data->sUnderlyingSymbol);
    strcpy(payload.pszUnderlyingType, market_data->sUnderlyingType);
    payload.chOptionType = market_data->cOptionType;
    payload.chCallOrPut = market_data->cCallOrPut;
    payload.nContractMultiplierUnit = market_data->uContractMultiplierUnit;
    payload.nExercisePrice = market_data->uExercisePrice;
    strcpy(payload.pszStartDate, market_data->sStartDate);
    strcpy(payload.pszEndDate, market_data->sEndDate);
    strcpy(payload.pszExerciseDate, market_data->sExerciseDate);
    strcpy(payload.pszDeliveryDate, market_data->sDeliveryDate);
    strcpy(payload.pszExpireDate, market_data->sExpireDate);
    payload.chUpdateVersion = market_data->cUpdateVersion;
    payload.nTotalLongPosition = market_data->iTotalLongPosition;
    payload.dbSecurityClosePx = static_cast<double>(market_data->uSecurityClosePx) / 10000;
    payload.dbSettlPrice = static_cast<double>(market_data->uSettlPrice) / 10000;
    payload.dbUnderlyingClosePx = static_cast<double>(market_data->uUnderlyingClosePx) / 10000;
    payload.chPriceLimitType = market_data->cPriceLimitType;
    payload.dbDailyPriceUpLimit = static_cast<double>(market_data->uDailyPriceUpLimit) / 10000;
    payload.dbDailyPriceDownLimit = static_cast<double>(market_data->uDailyPriceDownLimit) / 10000;
    payload.dbMarginUnit = static_cast<double>(market_data->uMarginUnit) / 10000;
    payload.dbMarginRatioParam1 = static_cast<double>(market_data->nMarginRatioParam1) / 10000;
    payload.dbMarginRatioParam2 = static_cast<double>(market_data->nMarginRatioParam2) / 10000;
    payload.nRoundLot = market_data->uRoundLot;
    payload.nLmtOrdMinFloor = market_data->uLmtOrdMinFloor;
    payload.nLmtOrdMaxFloor = market_data->uLmtOrdMaxFloor;
    payload.nMktOrdMinFloor = market_data->uMktOrdMinFloor;
    payload.nMktOrdMaxFloor = market_data->uMktOrdMaxFloor;
    payload.dbTickSize = static_cast<double>(market_data->uTickSize) / 10000;
    strcpy(payload.pszSecurityStatusFlag, market_data->sSecurityStatusFlag);

    this->forwardMarketData(res);
    this->getLog()->trace(
        " {}:{} TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
        "\n pszSecurityID[{}] pszContractID[{}] pszContractSymbol[{}] pszUnderlyingSecurityID[{}]"
        "\n pszUnderlyingSymbol[{}] pszUnderlyingType[{}] chOptionType[{}] chCallOrPut[{}]"
        "\n nContractMultiplierUnit[{}] nExercisePrice[{}] pszStartDate[{}] pszEndDate[{}]"
        "\n pszExerciseDate[{}] pszDeliveryDate[{}] pszExpireDate[{}] chUpdateVersion[{}]"
        "\n nTotalLongPosition[{}] dbSecurityClosePx[{}] dbSettlPrice[{}] dbUnderlyingClosePx[{}]"
        "\n chPriceLimitType[{}] dbDailyPriceUpLimit[{}] dbDailyPriceDownLimit[{}] dbMarginUnit[{}]"
        "\n dbMarginRatioParam1[{}] dbMarginRatioParam2[{}] nRoundLot[{}] nLmtOrdMinFloor[{}]"
        "\n nLmtOrdMaxFloor[{}] nMktOrdMinFloor[{}] nMktOrdMaxFloor[{}] dbTickSize[{}] pszSecurityStatusFlag[{}]",
        __FILE__, __LINE__, res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID, res.UpdateMillisec,
        payload.pszSecurityID, payload.pszContractID, payload.pszContractSymbol, payload.pszUnderlyingSecurityID,
        payload.pszUnderlyingSymbol, payload.pszUnderlyingType, payload.chOptionType, payload.chCallOrPut,
        payload.nContractMultiplierUnit, payload.nExercisePrice, payload.pszStartDate, payload.pszEndDate,
        payload.pszExerciseDate, payload.pszDeliveryDate, payload.pszExpireDate, payload.chUpdateVersion,
        payload.nTotalLongPosition, payload.dbSecurityClosePx, payload.dbSettlPrice, payload.dbUnderlyingClosePx,
        payload.chPriceLimitType, payload.dbDailyPriceUpLimit, payload.dbDailyPriceDownLimit, payload.dbMarginUnit,
        payload.dbMarginRatioParam1, payload.dbMarginRatioParam2, payload.nRoundLot, payload.nLmtOrdMinFloor,
        payload.nLmtOrdMaxFloor, payload.nMktOrdMinFloor, payload.nMktOrdMaxFloor, payload.dbTickSize,
        payload.pszSecurityStatusFlag);
}

void sipui2MD::GetSZOptionBaseData(T_SIPTAGMSG *msg)
{
    const auto market_data = reinterpret_cast<PSZOP_BASEINFO>(msg->MsgData);
    MarketDataField res{};
    auto &res_stock = SZOptionBaseData::doCast(res);
    // const auto& base_info = market_data->tBase;
    // const auto& op_params = market_data->tOpParams;
    // const auto& dev_params = market_data->tDeParmas;
    const auto& [base_info, op_params, dev_params] = *market_data;
    snprintf(res.TradingDay, sizeof(res.TradingDay), "%d", base_info.nActionDay);
    auto result = sipui2MD::splitString(msg->Code, '.');
    auto InstrumentID = result[0] + '.' + result[1];
    memccpy(res.ExchangeID, result[0].c_str(), 0, result[0].size());
    memcpy(res.InstrumentID, InstrumentID.c_str(), InstrumentID.size());
    res.setinstrumentId(res.InstrumentID);
    res.InstrumentIDHash = gEnv->hash(res.InstrumentID);
    snprintf(res.UpdateTime, sizeof(res.UpdateTime), "%02d:%02d:%02d", (int)(base_info.nActionDay / 10000000),
             (int)(base_info.nActionDay / 100000 % 100), (int)(base_info.nActionDay / 1000 % 100));
    res.UpdateMillisec = base_info.nActionDay % 1000;
    res.type = MARKET_DATA_TYPE_SZOPTION_BASE;

    auto & [p_base, p_op_params, p_dev_params] = res_stock.payload();
    {
        strcpy(p_base.pszSecurityID, base_info.sSecurityID);
        strcpy(p_base.pszSymbol, base_info.sSymbol);
        strcpy(p_base.pszEnglishName, base_info.sEnglishName);
        strcpy(p_base.pszISIN, base_info.sISIN);
        strcpy(p_base.pszSecurityIDSource, base_info.sSecurityIDSource);
        strcpy(p_base.pszUnderlyingSecurityID, base_info.sUnderlyingSecurityID);
        p_base.nListDate = base_info.uListDate;
        p_base.nSecurityType = base_info.usSecurityType;
        strcpy(p_base.pszCurrency, base_info.sCurrency);
        p_base.nQtyUnit = base_info.i64QtyUnit;
        p_base.chDayTrading = base_info.cDayTrading;
        p_base.dbPrevClosePx = static_cast<double>(base_info.i64PrevClosePx) / 10000;
        strcpy(p_base.pszSecurityStatus, base_info.sSecurityStatus);
        p_base.nOutstandingShare = base_info.i64OutstandingShare;
        p_base.nPublicFloatShareQuantity = base_info.i64PublicFloatShareQuantity;
        p_base.nParValue = base_info.i64ParValue;
        p_base.chGageFlag = base_info.cGageFlag;
        p_base.dbGageRatio = static_cast<double>(base_info.nGageRatio) / 10000;
        p_base.chCrdBuyUnderlying = base_info.cCrdBuyUnderlying;
        p_base.chCrdSellUnderlying = base_info.cCrdSellUnderlying;
        p_base.chPledgeFlag = base_info.cPledgeFlag;
        p_base.nContractMultiplier = base_info.nContractMultiplier;
        strcpy(p_base.pszRegularShare, base_info.sRegularShare);
    }
    {
        p_op_params.chCallOrPut = op_params.cCallOrPut;
        p_op_params.nDeliveryDay = op_params.nDeliveryDay;
        p_op_params.chDeliveryType = op_params.cDeliveryType;
        p_op_params.nExerciseBeginDate = op_params.nExerciseBeginDate;
        p_op_params.nExerciseEndDate = op_params.nExerciseEndDate;
        p_op_params.dbExercisePrice = static_cast<double>(op_params.i64ContractPosition) / 10000;
        p_op_params.chExerciseType = op_params.cExerciseType;
        p_op_params.nLastTradeDay = op_params.nLastTradeDay;
        p_op_params.nAdjustTimes = op_params.usAdjustTimes;
        p_op_params.nContractUnit = op_params.i64ContractUnit;
        p_op_params.dbPrevClearingPrice = static_cast<double>(op_params.i64PrevClearingPrice) / 10000;
        p_op_params.nContractPosition = op_params.i64ContractPosition;
    }
    {
        strcpy(p_dev_params.pszSecurityID, dev_params.sSecurityID);
        p_dev_params.nBuyQtyUpperLimit = dev_params.i64BuyQtyUpperLimit;
        p_dev_params.nSellQtyUpperLimit = dev_params.i64SellQtyUpperLimit;
        p_dev_params.nBuyQtyUnit = dev_params.i64BuyQtyUnit;
        p_dev_params.nSellQtyUnit = dev_params.i64SellQtyUnit;
        p_dev_params.nPriceTick = dev_params.i64PriceTick;
        p_dev_params.dbPriceUpperLimit = static_cast<double>(dev_params.i64PriceUpperLimit) / 10000;
        p_dev_params.dbPriceLowerLimit = static_cast<double>(dev_params.i64PriceLowerLimit) / 10000;
        p_dev_params.dbLastSellMargin = static_cast<double>(dev_params.i64LastSellMargin) / 10000;
        p_dev_params.dbSellMargin = static_cast<double>(dev_params.i64SellMargin) / 10000;
        p_dev_params.dbMarginRatioParam1 = static_cast<double>(dev_params.nMarginRatioParam1) / 10000;
        p_dev_params.dbMarginRatioParam2 = static_cast<double>(dev_params.nMarginRatioParam2) / 10000;
        p_dev_params.chMarketMakerFlag = dev_params.cMarketMakerFlag;
    }
    this->forwardMarketData(res);
    this->getLog()->trace("{}:{} TradingDay[{}] InstrumentID[{}] UpdateTime[{}] ExchangeID[{}] UpdateMillisec[{}]"
                         "\n pszSecurityID[{}] pszSymbol[{}] pszEnglishName[{}] pszISIN[{}]"
                         "\n pszSecurityIDSource[{}] pszUnderlyingSecurityID[{}] nListDate[{}] nSecurityType[{}]"
                         "\n pszCurrency[{}] nQtyUnit[{}] chDayTrading[{}] dbPrevClosePx[{}] pszSecurityStatus[{}]"
                         "\n nOutstandingShare[{}] nPublicFloatShareQuantity[{}] nParValue[{}] chGageFlag[{}]"
                         "\n dbGageRatio[{}] chCrdBuyUnderlying[{}] chCrdSellUnderlying[{}] chPledgeFlag[{}]"
                         "\n nContractMultiplier[{}] pszRegularShare[{}]",
                         __FILE__, __LINE__, res.TradingDay, res.InstrumentID, res.UpdateTime, res.ExchangeID,
                         res.UpdateMillisec, p_base.pszSecurityID, p_base.pszSymbol, p_base.pszEnglishName,
                         p_base.pszISIN, p_base.pszSecurityIDSource, p_base.pszUnderlyingSecurityID, p_base.nListDate,
                         p_base.nSecurityType, p_base.pszCurrency, p_base.nQtyUnit, p_base.chDayTrading,
                         p_base.dbPrevClosePx, p_base.pszSecurityStatus, p_base.nOutstandingShare,
                         p_base.nPublicFloatShareQuantity, p_base.nParValue, p_base.chGageFlag, p_base.dbGageRatio,
                         p_base.chCrdBuyUnderlying, p_base.chCrdSellUnderlying, p_base.chPledgeFlag,
                         p_base.nContractMultiplier, p_base.pszRegularShare);
    this->getLog()->trace("{}:{} chCallOrPut[{}] nDeliveryDay[{}] chDeliveryType[{}] nExerciseBeginDate[{}]"
                         "\n nExerciseEndDate[{}] dbExercisePrice[{}] chExerciseType[{}] nLastTradeDay[{}]"
                         "\n nAdjustTimes[{}] nContractUnit[{}] dbPrevClearingPrice[{}] nContractPosition[{}]",
                         __FILE__, __LINE__, p_op_params.chCallOrPut, p_op_params.nDeliveryDay,
                         p_op_params.chDeliveryType, p_op_params.nExerciseBeginDate, p_op_params.nExerciseEndDate,
                         p_op_params.dbExercisePrice, p_op_params.chExerciseType, p_op_params.nLastTradeDay,
                         p_op_params.nAdjustTimes, p_op_params.nContractUnit, p_op_params.dbPrevClearingPrice,
                         p_op_params.nContractPosition);
    this->getLog()->trace("{}:{} pszSecurityID[{}] nBuyQtyUpperLimit[{}] nSellQtyUpperLimit[{}] nBuyQtyUnit[{}]"
                         "\n nSellQtyUnit[{}] nPriceTick[{}] dbPriceUpperLimit[{}] dbPriceLowerLimit[{}]"
                         "\n dbLastSellMargin[{}] dbSellMargin[{}] dbMarginRatioParam1[{}] dbMarginRatioParam2[{}]"
                         "\n chMarketMakerFlag[{}]",
                         __FILE__, __LINE__, p_dev_params.pszSecurityID, p_dev_params.nBuyQtyUpperLimit,
                         p_dev_params.nSellQtyUpperLimit, p_dev_params.nBuyQtyUnit, p_dev_params.nSellQtyUnit,
                         p_dev_params.nPriceTick, p_dev_params.dbPriceUpperLimit, p_dev_params.dbPriceLowerLimit,
                         p_dev_params.dbLastSellMargin, p_dev_params.dbSellMargin, p_dev_params.dbMarginRatioParam1,
                         p_dev_params.dbMarginRatioParam2, p_dev_params.chMarketMakerFlag);
}

std::vector<std::string> sipui2MD::splitString(const std::string &input, char delimiter)
{
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

int sipui2MD::subscribeMarketData(const std::string &instrument)
{
    auto result = splitString(instrument, '.');
    if (result.size() != 2)
    {
        this->getLog()->error("instrument {} is error", instrument);
        return -1;
    }

    std::string exchange = result[0];
    const auto &code = result[1];

    this->getLog()->info("exchange:{}, code: {}", exchange, code);
    if (exchange == SIPUI_MARKET_EXCHANGE_ID_SH || exchange == SIPUI_MARKET_EXCHANGE_ID_SZ)
    {
        if (m_L1)
        {
            sub(exchange, code, MarketDataBitType::L1);
        }
        if (m_L2)
        {
            sub(exchange, code, MarketDataBitType::L2);
        }
        if (m_ZK)
        {
            sub(exchange, code, MarketDataBitType::ZK);
        }
        if (m_ZC)
        {
            sub(exchange, code, MarketDataBitType::ZC);
        }
        if (m_WD)
        {
            sub(exchange, code, MarketDataBitType::WD);
        }
        if (m_ZW && exchange == SIPUI_MARKET_EXCHANGE_ID_SZ)
        {
            sub(exchange, code, MarketDataBitType::ZW);
        }
    }
    else if (exchange == SIPUI_MARKET_EXCHANGE_ID_CZCE || exchange == SIPUI_MARKET_EXCHANGE_ID_CFFEX ||
             exchange == SIPUI_MARKET_EXCHANGE_ID_DCE || exchange == SIPUI_MARKET_EXCHANGE_ID_SHFE ||
             exchange == SIPUI_MARKET_EXCHANGE_ID_SHOP || exchange == SIPUI_MARKET_EXCHANGE_ID_SZOP ||
             exchange == SIPUI_MARKET_EXCHANGE_ID_CFFEX_OP || exchange == SIPUI_MARKET_EXCHANGE_ID_DCE_OP ||
             exchange == SIPUI_MARKET_EXCHANGE_ID_CZCE_OP || exchange == SIPUI_MARKET_EXCHANGE_ID_SHFE_OP)
    {
        if (m_L1)
        {
            sub(exchange, code, MarketDataBitType::L1);
        }
        if (m_JC)
        {
            sub(exchange, code, MarketDataBitType::JC);
        }
    }
    else if (exchange == SIPUI_MARKET_EXCHANGE_ID_HK)
    {
        if (m_L1)
        {
            sub(exchange, code, MarketDataBitType::L1);
        }
        if (m_L2)
        {
            sub(exchange, code, MarketDataBitType::L2);
        }
        if (m_JC)
        {
            sub(exchange, code, MarketDataBitType::JC);
        }
        if (m_HL)
        {
            sub(exchange, code, MarketDataBitType::HL);
        }
        if (m_ZK)
        {
            sub(exchange, code, MarketDataBitType::ZK);
        }
    }
    else
    {
        this->getLog()->error("instrument {} is error", instrument);
        return -1;
    }
    instruments_set.insert(instrument);
    return 0;
}

int sipui2MD::sub(std::string &martket, const std::string &code, int type)
{
    this->getLog()->warn("subscribe martket:{} codename:{} type:{}", martket, code, type);
    std::string types;
    switch (type)
    {
    // L1 快照
    case MarketDataBitType::L1:
        types = SIPUI_DATATYPE_L1;
        break;
    // L2 快照
    case MarketDataBitType::L2:
        types = SIPUI_DATATYPE_L2;
        break;
    // 委托队列
    case MarketDataBitType::WD:
        types = SIPUI_DATATYPE_WD;
        break;
    // 逐笔成交
    case MarketDataBitType::ZC:
        types = SIPUI_DATATYPE_ZC;
        break;
    // 指数快照
    case MarketDataBitType::ZK:
        types = SIPUI_DATATYPE_ZK;
        break;
    // 逐笔委托
    case MarketDataBitType::ZW:
        types = SIPUI_DATATYPE_ZW;
        break;
    case MarketDataBitType::LF:
        types = SIPUI_DATATYPE_LF;
        break;
    case MarketDataBitType::JC:
        types = SIPUI_DATATYPE_JC;
        break;
    case MarketDataBitType::CJ:
        types = SIPUI_DATATYPE_CJ;
        break;
    case MarketDataBitType::FK:
        types = SIPUI_DATATYPE_FK;
        break;
    case MarketDataBitType::HL:
        types = SIPUI_DATATYPE_HL;
        break;
    case MarketDataBitType::XJ:
        types = SIPUI_DATATYPE_XJ;
        break;
    case MarketDataBitType::MC:
        types = SIPUI_DATATYPE_MC;
        break;
    case MarketDataBitType::JY:
        types = SIPUI_DATATYPE_JY;
        break;
    case MarketDataBitType::VM:
        types = SIPUI_DATATYPE_VM;
        break;
    default:
        break;
    }

    T_SSCTAG tag{};
    memset(&tag, 0, sizeof(T_SSCTAG));
    strcpy(tag.sTag, (martket + '.' + code + '.' + types).c_str());
    //    tag.sTag = (martket + InstrumentID + types).c_str();
    tag.cMode = SSC_MODE_INC;
    tag.uSeqNo = -1;

    int nRet = UI_SubscribeTags(m_uihandler_, &tag, 1);
    if (nRet)
    {
        this->getLog()->error("UI_Subscribed {} failure :{} ", tag.sTag, GetErrInfo(nRet));
        return nRet;
    }
    else
    {
        this->getLog()->info("sub {}  success ", tag.sTag);
        return nRet;
    }
}

// int sipui2MD::code2list(int code, int type) {
//    if (this->codelist.count(code))
//        this->codelist[code] = this->codelist[code] | type;
//    else
//        this->codelist[code] = type;
//
//    return 0;
// };
//
// bool sipui2MD::codeinlist(int code, int type)
//{
//    if (codelist.count(code))
//    {
//        if (codelist[code] & type)
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }
//    else
//    {
//        return false;
//    }
// }

bool sipui2MD::connect()
{
    int iRet = 0;
    iRet = UI_Connect(m_uihandler_, m_ip.c_str(), m_port, m_account.c_str(), m_passwd.c_str(), LOGIN_NR, false);
    if (iRet != SIPE_OK)
    {
        this->getLog()->error("UI_Connect ERROR: {}", GetErrInfo(iRet));
        return false;
    }
    if (!UI_IsConnect(m_uihandler_))
    {
        this->getLog()->error("UI_IsConnect is not connect");
        return false;
    }
    return true;
}

int sipui2MD::subAll()
{
    for (const auto & it : instruments_set)
    {
        subscribeMarketData(it);
    }
    return 0;
}

int sipui2MD::reqInstrumentInfo(std::string instrument, std::function<void(InstrumentField &instrumentInfo)> callback)
{
    int ret = this->reqStaticInfo(instrument, callback);
    if (ret == 1)
    {
        this->getLog()->error(" no OpenPrice!");
        return -1;
    }
    return ret;
}