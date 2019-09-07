// Copyleft ! 2019, 向昕哲
// This file is a part of Cabinet Manager.
// Cabinet Manager is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Cabinet Manager is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with Cabinet Manager.If not, see < https://www.gnu.org/licenses/>.
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