#ifndef _INC_COMMAND
#define _INC_COMMAND

#include <iostream>
#include <string.h>
#include <vector>
#include "commonTypeDef.h"

using namespace std;

typedef enum
{
    COMMAND_OK,
    COMMAND_INVALID_FLAG,
    COMMAND_INVALID_ALG,
    COMMAND_INVALID_OUTPUT_TICKER,
    COMMAND_NO_FILENAME,
    COMMAND_NO_LAST_VALUE,
    NUMS_OF_COMMAND
} CommandDiagCodeTypeDef;

class CommandParams
{
public:
    CommandParams(){}
    virtual ~CommandParams(){}
    static CommandParams* getInstance();
    CommandDiagCodeTypeDef argumentsHandle(vector<string> params, ArgsInputTypeDef& m_Args);

private:
    void initializeArgs(ArgsInputTypeDef& m_Args);
};


#endif