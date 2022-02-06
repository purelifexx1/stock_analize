#ifndef _INC_COMMON_TYPEDEF
#define _INC_COMMON_TYPEDEF

#include <iostream>
#include <string.h>
#include <vector>
#include <utility>
#include <math.h>
#include <sstream>

#define sstr(fmt, ...) LOG::logs(fmt, ##__VA_ARGS__)

using namespace std;

typedef enum
{
    GRAPH_MATCH,
    VOLUME_SORTING,
    NUM_OF_FLAGS
} ArgsFlagTypeDef;

typedef struct
{
    string basefilename;
    int fullfill_index; //3
} GraphMatchTypeDef;

typedef struct
{
    int spans;
    int fullfill_index; // 3
} VolumeSortingTypeDef;


typedef struct
{
    ArgsFlagTypeDef m_Flag;
    GraphMatchTypeDef m_GraphMatch;
    VolumeSortingTypeDef m_VolumeSorting;
    int output_nums;
} ArgsInputTypeDef;

namespace LOG
{

template<typename... Args>
void logs(Args... args)
{
    (cout << ... << args) << endl;
}
}


#endif