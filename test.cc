#include <iostream>
#include <string.h>
#include <vector>
#include <utility>
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "commonTypeDef.h"
using namespace std;

vector<pair<float, float>> standard;
vector<pair<float, float>> sample1;
vector<pair<float, float>> sample2;
vector<pair<float, float>> sample3;
vector<pair<float, float>> sample4;
vector<pair<float, float>> sample5;
vector<pair<float, float>> sample6;

vector<float> d_standard;
vector<float> d_sample1;
vector<float> d_sample2;
vector<float> d_sample3;
vector<float> d_sample4;
vector<float> d_sample5;
vector<float> d_sample6;


void load_database(string file, vector<pair<float, float>>& dataout);
void cal_derivative(vector<pair<float, float>>& input, vector<float>& output);
float cal_rms(vector<float>& base, vector<float>& target);

void testing(int args, const char** str)
{
    for(int i = 0; i < args; i++){
        cout << str[i] << endl;
    }
}

int main(int args, char** params)
{
    ArgsInputTypeDef testing1;
    sstr("value:", testing1.m_Flag);
    

    return 0;


}

float cal_rms(vector<float>& base, vector<float>& target)
{
    if(base.size() == target.size()){
        float sum = 0;
        for(int i = 0; i < base.size(); i++){
            sum += pow(base[i] - target[i], 2);
        }
        return sqrt(sum);
    }else{
        cout << "size un-matched" << endl;
        return -1.0;
    }
}

void cal_derivative(vector<pair<float, float>>& input, vector<float>& output)
{
    for(int i = 0; i < input.size() - 1; i++){
        output.push_back( (input[i+1].second - input[i].second) / (input[i+1].first - input[i].first) );
    }
}

void load_database(string file, vector<pair<float, float>>& dataout)
{
    static bool lock = true;
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
        dataout.push_back(point_data);

        start = end + delimiter.length();
        end = s.find(delimiter, start);

        if(lock == false) break;
    }
    lock = true;
    delete(buffer);
    fclose(ptr);
}