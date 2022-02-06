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

using namespace std;

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

typedef struct {
    string name;
    vector<ticker_data> data;
    vector<float> derivative_data;
} ticker;

class StockData
{
public:
    StockData(){}
    static StockData* getInstance(void);
    void load_stockData(string database, vector<ticker>& stock_data, int days);
    string display_ticker_data(string name, vector<ticker>& stock_data, int offset);
    void load_standard(string file, vector<float>& dataout);


};



#endif