#ifndef _STOCK_DATA_ALG
#define _STOCK_DATA_ALG

#include <iostream>
#include <string.h>
#include <vector>
#include <utility>
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "stockData.h"
#include <sstream>
#include "commonTypeDef.h"
using namespace std;

class StockDataAlg
{
public:
    StockDataAlg() {}
    static StockDataAlg* getInstance();
    void cal_derivative(vector<ticker>& stock_data);
    void cal_similar(vector<ticker>& stock_data, vector<float>& base, vector<pair<float, string>>& output);
    float cal_rms(vector<float>& base, vector<float>& target);
    void cal_largest_green_cluster(ticker& m_ticker);
};

#endif