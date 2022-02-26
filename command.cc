#include "command.h"

CommandParams* CommandParams::getInstance()
{
    static CommandParams ins;
    return &ins;
}

void CommandParams::initializeArgs(ArgsInputTypeDef& m_Args)
{
    m_Args.isExport = false;
    m_Args.output_nums = -1;
    m_Args.m_Flag = NUM_OF_FLAGS;

    m_Args.m_GraphMatch.basefilename = "";
    m_Args.m_GraphMatch.fullfill_index = 0;
}

CommandDiagCodeTypeDef CommandParams::argumentsHandle(vector<string> params, ArgsInputTypeDef& m_Args)
{
    initializeArgs(m_Args);
    //arguments input
    for(int i = 1; i < params.size(); i++)
    {
        if(i == params.size() - 1)
        { // shouldnt happen because all the params will be read in couple
            sstr("Missing value for the last flag");
            return COMMAND_NO_LAST_VALUE;
        }
        string optionFlag = params[i];
        
        if(optionFlag == "-a")
        { // algorithm
            string algType = params[++i];
            if(algType == "graph")
            {
                m_Args.m_Flag = GRAPH_MATCH;
                m_Args.m_GraphMatch.fullfill_index++;
            }
            else if(algType == "vlsort")
            {
                m_Args.m_Flag = VOLUME_SORTING;
                m_Args.m_VolumeSorting.fullfill_index++;
            }
            else
            {
                sstr("Invalid option: (", algType, ") for alg flag");
                return COMMAND_INVALID_ALG;
            }
        }
        else if(optionFlag == "-c")
        { // number of output ticker
            char *endptr;
            int nums = strtol(params[++i].c_str(), &endptr, 10);
            if(endptr == params[i])
            {
                sstr("Invalid value for number of output ticker");
                return COMMAND_INVALID_OUTPUT_TICKER;
            }
            else
            {
                if(nums <= 0)
                {
                    sstr("Negative value for number of output ticker");
                    return COMMAND_INVALID_OUTPUT_TICKER;
                }
                m_Args.m_GraphMatch.fullfill_index++;
                m_Args.output_nums = nums;
            }
        }
        else if(optionFlag == "-f")
        { // base file name
            string tempFilename = params[++i];
            if(tempFilename[0] == '-')
            {
                sstr("Empty value for filename flag");
                return COMMAND_NO_FILENAME;
            }
            m_Args.m_GraphMatch.fullfill_index++;
            m_Args.m_GraphMatch.basefilename = tempFilename;
        }
        else if(optionFlag == "-s")
        {
            char *endptr;
            int nums = strtol(params[++i].c_str(), &endptr, 10);
            if(endptr == params[i])
            {
                sstr("Invalid value for spans value");
                return COMMAND_INVALID_SPAN;
            }
            else
            {
                if(nums <= 0)
                {
                    sstr("Negative value for spans value");
                    return COMMAND_INVALID_SPAN;
                }
                m_Args.m_VolumeSorting.fullfill_index++;
                m_Args.m_VolumeSorting.spans = nums;
            }
        }
        else if(optionFlag == "-e")
        {
            m_Args.isExport = true;
            m_Args.m_exportPath = params[++i];
        }
        else
        {
            sstr("Invalid flag: ", optionFlag);
            return COMMAND_INVALID_FLAG;
        }
    }
    return COMMAND_OK;
}