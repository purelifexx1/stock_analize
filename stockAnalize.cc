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

using namespace std;

vector<ticker> HSX_data;
vector<ticker> HNX_data;
vector<ticker> UPCOM_data;

vector<float> basedata;
vector<pair<float, string>> result;

int main(int args, char** params)
{
    vector<string> Args;
    for(int i = 0; i < args; i++){
        Args.push_back(params[i]);
    }
    ArgsInputTypeDef m_Args;
    CommandParams* m_CommandParams = CommandParams::getInstance();
    m_CommandParams->argumentsHandle(Args, m_Args);
    StockData* m_StockData = StockData::getInstance();
    StockDataAlg* m_StockDataAlg = StockDataAlg::getInstance();
    if(m_Args.m_Flag == GRAPH_MATCH)
    {
        m_StockData->load_standard(m_Args.m_GraphMatch.basefilename, basedata);
        int selected_nums = m_Args.output_nums; //28
        int num_of_day = basedata.size() + 2;
        m_StockData->load_stockData("stock_data/HSX.csv", HSX_data, num_of_day);
        m_StockDataAlg->cal_derivative(HSX_data);
        m_StockDataAlg->cal_similar(HSX_data, basedata, result);
        sort(result.begin(), result.end());
        for(int i = 0; i < selected_nums; i++)
        {
            cout << result[i].second << ": " 
            << m_StockData->display_ticker_data(result[i].second, HSX_data, 0) << endl;
        }
    }
    else if(m_Args.m_Flag == VOLUME_SORTING)
    {
        
    }
    exit(0);
}

