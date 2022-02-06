#include "stockData.h"

using namespace std;

StockData* StockData::getInstance(void)
{
    static StockData stockDataInstance;
    return &stockDataInstance;
}

void StockData::load_stockData(string database, vector<ticker>& stock_data, int days)
{
    // ACB,20211217,33.15,33.3,33.05,33.2,2403500
    int _skip = 0;
    ifstream file(database.c_str());
    string line;
    string date_lock;
    while (getline(file, line) && days != 0)
    {
        if(_skip == 1){ //each ticker data
            ticker_data element_data;
            int element_id = 0;
            stringstream ss(line);
            string element;
            for(int i = 0; getline(ss, element, ','); i++){
                switch (i) {
                    case 0: {//ticker name
                        auto itr = find_if(stock_data.begin(), stock_data.end(), [&element](const ticker& obj) {return (obj.name == element);});
                        if(itr == stock_data.end()){ //push new ticker
                            ticker temper_ticker;
                            temper_ticker.name = element;
                            stock_data.push_back(temper_ticker);
                            element_id = stock_data.size() - 1;
                        }else{//ticker already existed
                            element_id = itr - stock_data.begin();
                        }
                    }
                        break;
                    case 1: //ticker date
                        if(date_lock != element) {
                            days--;
                        }
                        element_data.date = element;
                        date_lock = element;
                        break;
                    case 2: //ticker open price
                        element_data.open = stof(element);
                        break;
                    case 3: //ticker high price
                        element_data.high = stof(element);
                        break;
                    case 4: //ticker low price
                        element_data.low = stof(element);
                        break;
                    case 5: //ticker close price
                        element_data.close = stof(element);
                        break;
                    case 6: //ticker volume price
                        element_data.volume = stoi(element);
                        break;
                    default:
                    break;
                }
            }
            if(days != 0){
                element_data.trend = (element_data.close >= element_data.open)?PRICE_INCREASE:PRICE_DECREASE;
                stock_data[element_id].data.push_back(element_data);
            }
        }else{
            _skip = 1;
        }
    }
    file.close();
}

string StockData::display_ticker_data(string name, vector<ticker>& stock_data, int offset)
{
    auto itr = find_if(stock_data.begin(), stock_data.end(), [&name](const ticker& obj) {return obj.name == name;});
    if(itr != stock_data.end()){
        stringstream ss;
        ticker temper = stock_data[itr-stock_data.begin()];
        ticker_data temp = temper.data[temper.data.size() - 1 - offset];
        ss << "open: " << temp.open << ", close: " << temp.close << ", volume: " << temp.volume;
        return ss.str();
    }
    return "";
}

void StockData::load_standard(string file, vector<float>& dataout)
{
    vector<pair<float, float>> raw_data;
    bool lock = true;
    FILE* ptr;
    ptr = fopen(file.c_str(), "rb");
    char* buffer = new char[4096];
    bzero(buffer, 4096);
    int fsize = fread(buffer, 1, 4096, ptr);
	string s = string(buffer).substr(2, fsize -4);
    string delimiter = "), (";

    int start = 0;
    int end = s.find(delimiter);
    while(true){
        if(end == string::npos) lock = false;
        string temp = s.substr(start, end-start);
        int sep = temp.find(", ");
        pair<float, float> point_data;
        point_data.first = stof(temp.substr(0, sep));
        point_data.second = stof(temp.substr(sep+2, temp.length() - sep + 2));
        raw_data.push_back(point_data);

        start = end + delimiter.length();
        end = s.find(delimiter, start);

        if(lock == false) break;
    }
    delete(buffer);
    fclose(ptr);
    for(int i = 0; i < raw_data.size() - 1; i++){
        dataout.push_back( (raw_data[i+1].second - raw_data[i].second) / (raw_data[i+1].first - raw_data[i].first) );
    }
}