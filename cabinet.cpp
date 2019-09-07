#include <Windows.h>
#include "cabinet"
bool Cabinet::isEmpty(void)
{
    if (mData.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}
Cabinet::Cabinet(void)
{
    mData = "";
}
Cabinet::Cabinet(std::string data)
{
    mData = data;
}
Cabinet::~Cabinet(void)
{
    Sleep(NULL);
}
std::string Cabinet::load(void)
{
    return mData;
}
void Cabinet::store(std::string str)
{
    mData = str;
    return;
}