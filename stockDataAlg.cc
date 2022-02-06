#include "stockDataAlg.h"

using namespace std;

StockDataAlg* StockDataAlg::getInstance()
{
    static StockDataAlg stockDataAlgIns;
    return &stockDataAlgIns;
}

void StockDataAlg::cal_derivative(vector<ticker>& stock_data)
{
    for(int i = 0; i < stock_data.size() - 1; i++){
        stock_data[i].derivative_data.clear();
        for(int j = 0; j < stock_data[i].data.size()-1; j++){
            stock_data[i].derivative_data.push_back( atan(stock_data[i].data[j+1].close - stock_data[i].data[j].close) );
        }
    }
}

float StockDataAlg::cal_rms(vector<float>& base, vector<float>& target)
{
    if(base.size() == target.size()){
        float sum = 0;
        for(int i = 0; i < base.size(); i++){
            sum += pow(base[i] - target[i], 2);
        }
        return sqrt(sum/(float)base.size());
    }else{
        // cout << "size un-matched" << endl;
        return -1.0;
    }
}

void StockDataAlg::cal_similar(vector<ticker>& stock_data, vector<float>& base, vector<pair<float, string>>& output)
{
    for(int j = 0; j < base.size(); j++){
        base[j] = atan(base[j]);
    }
    for(int i = 0; i < stock_data.size(); i++){
        pair<float, string> temper;
        temper.second = stock_data[i].name;
        temper.first = cal_rms(base, stock_data[i].derivative_data);
        if(temper.first > 0){
            output.push_back(temper);
        }
    }
}

void StockDataAlg::cal_largest_green_cluster(ticker& m_ticker)
{
    int tempVolume = 0;
    int stackCount = 0;
    int flushTotalValue = 0;
    m_ticker.greenCluster.totalVolume = 0;
    for(auto i = m_ticker.data.end()-1; i >= m_ticker.data.begin(); i--)
    {
        if(i->trend == PRICE_INCREASE)
        {
            stackCount++;
            tempVolume += i->volume;
        }
        else if(i->trend == PRICE_DECREASE)
        {
            if(stackCount >= 3)
            {
                if(tempVolume >= m_ticker.greenCluster.totalVolume)
                {
                    m_ticker.greenCluster.endDate = i->date;
                    m_ticker.greenCluster.totalVolume = tempVolume;
                    flushTotalValue = 0;
                }
            }
            tempVolume = 0;
            stackCount = 0;
            flushTotalValue += i->volume;
        }
    }
    m_ticker.greenCluster.percentDiff = (float)flushTotalValue / m_ticker.greenCluster.totalVolume;
}