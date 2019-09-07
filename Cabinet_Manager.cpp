// Copyleft ! 2019, 向昕哲
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <sys/timeb.h>
#include <utility>
#include <vector>
#include <Windows.h>
#include "cabinet"
std::vector<std::shared_ptr<Cabinet> > cabinets;
std::vector<int> canUse;
int main(void)
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    bool again = true, newCabinet = false, quit = false, running = true;
    char choice = 'N';
    int cabinetID = 0, cardID = 0, num = 0, tmp = 1, used = 0;
    std::default_random_engine re;
    std::map<int, int> cabinetMap;
    std::map<int, int>::iterator iterMap;
    std::string d;
    struct timeb timeSeed;
    ftime(&timeSeed);
    re.seed(timeSeed.time * 1000 + timeSeed.millitm);
    std::cout << "Copyleft ! 2019, 向昕哲" << std::endl;
    std::cout << "本柜子管理系统由昕哥制作。该软件遵守 GPL v3.0 协议" << std::endl;
    std::cout << "请输入您要管理的柜子数：";
    std::cin >> num;
    cabinets.resize(num);
    canUse.resize(num);
    std::uniform_int_distribution<unsigned> uni(0, num - 1);
    for (std::vector<std::shared_ptr<Cabinet> >::iterator iter = cabinets.begin(); iter != cabinets.end(); iter++)
    {
        *iter = std::make_shared<Cabinet>();
    }
    for (std::vector<int>::iterator iter = canUse.begin(); iter != canUse.end(); iter++)
    {
        *iter = tmp;
        ++tmp;
    }
    while (running)
    {
        again = true;
        cabinetID = 0;
        cardID = 0;
        d = "";
        std::cout << std::endl << "欢迎使用昕哥牌柜子管理系统！" << std::endl;
        while (again)
        {
            std::cout << "请问您要干什么（N打开新柜子，O打开您的柜子，Q退出）？";
            std::cin >> choice;
            switch (choice)
            {
            case 'N': case 'n':
                again = false;
                newCabinet = true;
                quit = false;
                break;
            case 'O': case 'o':
                again = false;
                newCabinet = false;
                quit = false;
                break;
            case 'Q': case 'q':
                again = false;
                newCabinet = false;
                quit = true;
                break;
            default:
                std::cout << "您输入的不是有效字符，请重新输入" << std::endl;
                again = true;
                break;
            }
        }
        if (quit)
        {
            break;
        }
        else if (newCabinet)
        {
            if (used > num - 1)
            {
                std::cout << "柜子已满，敬请谅解" << std::endl;
            }
            else
            {
                std::cout << "请输入您的卡号：";
                std::cin >> cardID;
                iterMap = cabinetMap.find(cardID);
                if (iterMap != cabinetMap.end())
                {
                    std::cout << "您的卡号已存在，请输入“O”以打开柜子" << std::endl;
                }
                else
                {
                    ftime(&timeSeed);
                    re.seed(timeSeed.time * 1000 + timeSeed.millitm);
                    while (0 == cabinetID)
                    {
                        cabinetID = canUse.at(uni(re));
                    }
                    cabinetMap.insert(std::pair<int, int>(cardID, cabinetID));
                    canUse.at(cabinetID - 1) = 0;
                    std::cout << "您的柜子ID是：" << cabinetID << "号" << std::endl;
                    std::cin.ignore();
                    std::cout << "请输入您要储存的东西（一句话）：";
                    std::getline(std::cin, d);
                    cabinets.at(cabinetID - 1)->store(d);
                    std::cout << "柜子已关闭！" << std::endl;
                    ++used;
                }
            }
        }
        else
        {
            std::cout << "请输入您的卡号：";
            std::cin >> cardID;
            iterMap = cabinetMap.find(cardID);
            if (iterMap == cabinetMap.end())
            {
                std::cout << "您还没有属于此卡的柜子，请输入“N”创建" << std::endl;
            }
            else
            {
                cabinetID = iterMap->second;
                std::cout << "您的柜子ID是" << cabinetID << "号" << std::endl;
                d = cabinets.at(cabinetID - 1)->load();
                std::cout << "您所储存的东西是：" << d << std::endl;
                canUse.at(cabinetID - 1) = cabinetID;
                cabinets.at(cabinetID - 1) = std::make_shared<Cabinet>();
                cabinetMap.erase(iterMap);
                std::cout << "此柜子重归无主" << std::endl;
                --used;
            }
        }
    }
    std::cout << std::endl;
    std::cin.ignore();
    std::cout << "按Enter键退出" << std::endl;
    std::cin.get();
    return 0;
}