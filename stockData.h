#ifndef _STOCK_DATA
#define _STOCK_DATA

#include <iostream>
#include <string.h>
#include <vector>
#include <utility>
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "commonTypeDef.h"

#define TRADINGVIEW_SOURCE "https://vn.tradingview.com/chart/?symbol=HOSE%3A"

using namespace std;

typedef enum
{
    STOCKDATA_OK,
    STOCKDATA_NO_BASEFILE,
    STOCKDATA_NO_DATABASE
} StockDataDiagCodeTypeDef;
typedef enum
{
    PRICE_INCREASE,
    PRICE_DECREASE
} DateTrendTypeDef;

typedef struct {
    string date;
    float open;
    float high;
    float low;
    float close;
    int volume;
    DateTrendTypeDef trend;
} ticker_data;

typedef struct
{
    string endDate;
    int totalVolume;
    float percentDiff;
} GreenVolumeClusterDataTypeDef;

typedef struct {
    string name;
    vector<ticker_data> data;
    vector<float> derivative_data;
    GreenVolumeClusterDataTypeDef greenCluster;
} ticker;

class StockData
{
public:
    StockData(){}
    static StockData* getInstance(void);
    StockDataDiagCodeTypeDef load_stockData(string database, vector<ticker>& stock_data, int days);
    string display_ticker_data(string name, vector<ticker>& stock_data, int offset);
    string display_ticker_data(ticker m_ticker, int offset);
    StockDataDiagCodeTypeDef load_standard(string file, vector<float>& dataout);


};



#endif