#include <iostream>
#include <string.h>
#include <vector>
#include <utility>
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "stockDataAlg.h"
#include "stockData.h"
#include "commonTypeDef.h"
#include "command.h"

using namespace std;

vector<ticker> HSX_data;
vector<ticker> HNX_data;
vector<ticker> UPCOM_data;

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
        vector<float> basedata;
        vector<pair<float, string>> result;
        if(STOCKDATA_OK != m_StockData->load_standard(m_Args.m_GraphMatch.basefilename, basedata))
        {
            sstr("No basefile, please check the path again");
            exit(1);
        }
        int selected_nums = m_Args.output_nums; //28
        int num_of_day = basedata.size() + 2;
        if(STOCKDATA_OK != m_StockData->load_stockData("stock_data/HSX.csv", HSX_data, num_of_day))
        {
            sstr("No database file, please check the path again");
            exit(1);
        }
        m_StockDataAlg->cal_derivative(HSX_data);
        m_StockDataAlg->cal_similar(HSX_data, basedata, result);
        sort(result.begin(), result.end());
        for(int i = 0; i < selected_nums; i++)
        {
            sstr(result[i].second, ": ", m_StockData->display_ticker_data(result[i].second, HSX_data, 0));
        }
    }
    else if(m_Args.m_Flag == VOLUME_SORTING)
    {
        if(STOCKDATA_OK != m_StockData->load_stockData("stock_data/HSX.csv", HSX_data, m_Args.m_VolumeSorting.spans))
        {
            sstr("No database file, please check the path again");
            exit(1);
        }
        vector<ticker> result;
        for(ticker& i : HSX_data)
        {
            m_StockDataAlg->cal_largest_green_cluster(i);
            result.push_back(i);
        }
        sort(result.begin(), result.end(), [](ticker a, ticker b){
            return a.greenCluster.percentDiff < b.greenCluster.percentDiff;
        });
        for(int i = 0; i < m_Args.output_nums; i++)
        {
            sstr(result[i].name, ": ", m_StockData->display_ticker_data(result[i], 0));
            int tt = 0;
        }
    }
    exit(0);
}

