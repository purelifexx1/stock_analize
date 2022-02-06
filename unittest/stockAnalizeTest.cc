#include <iostream>
#include <string.h>
#include <vector>
#include <utility>
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "stockData.h"
#include "stockDataAlg.h"
#include "commonTypeDef.h"
#include "command.h"
#include <gtest/gtest.h>

using namespace std;

class StockAnalize
{
private:
public:
    StockAnalize(){}
    virtual ~StockAnalize(){}
};

struct StockAnalizeTest: public testing::Test
{
    // StockAnalize* m_StockAnalizeTest;
    StockData* m_StockData;
    StockDataAlg* m_StockDataAlg;
    CommandParams* m_CommandParams;
    void SetUp()
    {
        // m_StockAnalizeTest = new StockAnalize();
    }
    void TearDown()
    {
        // delete m_StockAnalizeTest;
    }
};

TEST_F(StockAnalizeTest, InputArgs_GraphAlg_Test)
{
    ArgsInputTypeDef m_Args;
    m_CommandParams = CommandParams::getInstance();
    vector<string> command_ok = {
        "command",
        "-a", "graph",
        "-f", "dummy.txt",
        "-c", "20"
    };
    vector<string> command_invalid_flag = {
        "command",
        "-x", "graph",
        "-f", "dummy.txt",
        "-c", "20"
    };
    vector<string> command_invalid_alg = {
        "command",
        "-a", "dummy",
        "-f", "dummy.txt",
        "-c", "20"
    };
    vector<string> command_invalid_output_ticker1 = {
        "command",
        "-a", "graph",
        "-f", "dummy.txt",
        "-c", "-6"
    };
    vector<string> command_invalid_output_ticker2 = {
        "command",
        "-a", "graph",
        "-f", "dummy.txt",
        "-c", "dummy"
    };
    vector<string> command_no_filename = {
        "command",
        "-a", "graph",
        "-f",
        "-c", "20"
    };
    vector<string> command_no_last_value = {
        "command",
        "-a", "graph",
        "-f", "dummy.txt",
        "-c"
    };
    EXPECT_EQ(COMMAND_INVALID_FLAG,          m_CommandParams->argumentsHandle(command_invalid_flag, m_Args));
    EXPECT_EQ(COMMAND_INVALID_ALG,           m_CommandParams->argumentsHandle(command_invalid_alg, m_Args));
    EXPECT_EQ(COMMAND_INVALID_OUTPUT_TICKER, m_CommandParams->argumentsHandle(command_invalid_output_ticker1, m_Args));
    EXPECT_EQ(COMMAND_INVALID_OUTPUT_TICKER, m_CommandParams->argumentsHandle(command_invalid_output_ticker2, m_Args));
    EXPECT_EQ(COMMAND_NO_FILENAME,           m_CommandParams->argumentsHandle(command_no_filename, m_Args));
    EXPECT_EQ(COMMAND_NO_LAST_VALUE,         m_CommandParams->argumentsHandle(command_no_last_value, m_Args));
    EXPECT_EQ(COMMAND_OK,                    m_CommandParams->argumentsHandle(command_ok, m_Args));
    EXPECT_EQ(3, m_Args.m_GraphMatch.fullfill_index);
}

TEST_F(StockAnalizeTest, StockDataAlg_CalRms_Test)
{
    m_StockDataAlg = StockDataAlg::getInstance();

    //unsize matched
    vector<float> base = {1.0f, 1.0f, 1.0f};
    vector<float> target = {1.0f, 1.0f};
    EXPECT_FLOAT_EQ(-1.0f, m_StockDataAlg->cal_rms(base, target));

    //checking sample result
    vector<float> base1 = {12.3f, -2.5f, 3.4f};
    vector<float> target1 = {24.5f, -112.3f, 34.5f};
    EXPECT_FLOAT_EQ(66.262337f, m_StockDataAlg->cal_rms(base1, target1));
}
