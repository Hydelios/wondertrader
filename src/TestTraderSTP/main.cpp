// 测试STP交易模块的主程序
#include "../TraderSTP/TraderSTP.h"
#include <iostream>

extern "C" {
    ITraderApi* createTrader();
    void deleteTrader(ITraderApi*& trader);
}

// 测试登录
void test_login(ITraderApi* trader) {
    std::cout << "[测试] 登录接口..." << std::endl;
    // trader->login(...); // TODO: 填写实际参数
}

// 测试下单
void test_send_order(ITraderApi* trader) {
    std::cout << "[测试] 下单接口..." << std::endl;
    // trader->sendOrder(...); // TODO: 填写实际参数
}

// 测试撤单
void test_cancel_order(ITraderApi* trader) {
    std::cout << "[测试] 撤单接口..." << std::endl;
    // trader->cancelOrder(...); // TODO: 填写实际参数
}

// 测试查询资金
void test_query_account(ITraderApi* trader) {
    std::cout << "[测试] 查询资金接口..." << std::endl;
    // trader->queryAccount(...); // TODO: 填写实际参数
}

// 测试查询持仓
void test_query_position(ITraderApi* trader) {
    std::cout << "[测试] 查询持仓接口..." << std::endl;
    // trader->queryPosition(...); // TODO: 填写实际参数
}

// 测试查询委托
void test_query_order(ITraderApi* trader) {
    std::cout << "[测试] 查询委托接口..." << std::endl;
    // trader->queryOrder(...); // TODO: 填写实际参数
}

// 测试查询成交
void test_query_trade(ITraderApi* trader) {
    std::cout << "[测试] 查询成交接口..." << std::endl;
    // trader->queryTrade(...); // TODO: 填写实际参数
}

int main() {
    std::cout << "TestTraderSTP 启动，准备测试 TraderSTP..." << std::endl;
    ITraderApi* trader = createTrader();

    int choice = 0;
    while (true) {
        std::cout << "\n请选择要测试的接口：" << std::endl;
        std::cout << "1. 登录" << std::endl;
        std::cout << "2. 下单" << std::endl;
        std::cout << "3. 撤单" << std::endl;
        std::cout << "4. 查询资金" << std::endl;
        std::cout << "5. 查询持仓" << std::endl;
        std::cout << "6. 查询委托" << std::endl;
        std::cout << "7. 查询成交" << std::endl;
        std::cout << "0. 退出" << std::endl;
        std::cout << "输入编号: ";
        std::cin >> choice;

        if (choice == 0) break;
        switch (choice) {
            case 1: test_login(trader); break;
            case 2: test_send_order(trader); break;
            case 3: test_cancel_order(trader); break;
            case 4: test_query_account(trader); break;
            case 5: test_query_position(trader); break;
            case 6: test_query_order(trader); break;
            case 7: test_query_trade(trader); break;
            default: std::cout << "无效选择，请重试。" << std::endl; break;
        }
    }

    deleteTrader(trader);
    std::cout << "TraderSTP 测试完成。" << std::endl;
    return 0;
}
