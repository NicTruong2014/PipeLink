#pragma once

#include <locale>
#include <sstream>
#include <iomanip>
#include "Pipe.h"
#include "Plumping.h"
#include "LevelManager.h"
#include "Constant.h"

#define MAX_ROWS 12
#define MAX_SIZE_WIDTH 70

class Utils
{
public:
    static Vec2 GetCenterScreen()
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        return Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    }

    static Size GetScreen()
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        return Size(visibleSize.width, visibleSize.height);
    }

    static std::string FormatIntToString(int number){
        std::stringstream ss;
        ss.imbue(std::locale(""));

        ss << std::fixed << std::setprecision(0) << number;
        std::string result = ss.str();
        std::replace(result.begin(), result.end(), ',', '.');
        return result;
    }

    static bool IsPlumping(TypePipe typePipe)
    {
        return typePipe == TypePipe::PlumpingLeft ||
            typePipe == TypePipe::PlumpingRight ||
            typePipe == TypePipe::PlumpingTop ||
            typePipe == TypePipe::PlumpingBottom;
    }

    static bool IsValidLocation(Vec2 location)
    {
        return location.x >= 0 && location.x <= 6 && location.y >= 0 && location.y <= 6;
    }

    static bool IsPipe(TypePipe typePipe)
    {
        return typePipe != TypePipe::PlumpingLeft &&
            typePipe != TypePipe::PlumpingRight &&
            typePipe != TypePipe::PlumpingTop &&
            typePipe != TypePipe::PlumpingBottom;
    }

    static bool CanNeibour(TypeDirection typeDirection, TypePipe typePipe)
    {
        std::map<TypeDirection, std::list<TypePipe>> myDictionary;

        //Left
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe2);
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe4);
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe5);
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe6);
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe7);
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe8);
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe11);
        myDictionary[TypeDirection::Left].push_back(TypePipe::Pipe12);
        myDictionary[TypeDirection::Left].push_back(TypePipe::PlumpingLeft);

        //Right
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe3);
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe4);
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe6);
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe7);
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe9);
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe10);
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe11);
        myDictionary[TypeDirection::Right].push_back(TypePipe::Pipe12);
        myDictionary[TypeDirection::Right].push_back(TypePipe::PlumpingRight);

        //Top
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe1);
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe2);
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe3);
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe5);
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe6);
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe10);
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe11);
        myDictionary[TypeDirection::Top].push_back(TypePipe::Pipe12);
        myDictionary[TypeDirection::Top].push_back(TypePipe::PlumpingTop);

        //Bottom
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe1);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe4);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe5);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe6);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe8);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe9);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe10);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::Pipe12);
        myDictionary[TypeDirection::Bottom].push_back(TypePipe::PlumpingBottom);

        for (auto direction : myDictionary)
        {
            if (direction.first == typeDirection)
            {
                for (auto pipe : direction.second) 
                {
                    if (pipe == typePipe)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    static bool IsIPadAspectRatio() {
#if WIN32
        return false;
#endif

        int dpi = Device::getDPI();
        auto director = Director::getInstance()->getVisibleSize();
        float xInches = director.width / dpi;
        float yInches = director.height / dpi;
        float diagonalInches = sqrtf(xInches * xInches + yInches * yInches);
        diagonalInches = roundf(diagonalInches * 100.0f) / 100.0f;
        bool isTablet = (diagonalInches >= 6.5f);
        return isTablet;
    }
};