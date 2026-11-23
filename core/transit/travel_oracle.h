#pragma once
// TravelOracle：排行程的程式「只」透過這個介面問車程。
// 它只規定「要有哪些函式」，自己不做事，真正做事的是 FakeTravel 或 TransitRouter。
// 這樣 D1～D4 不用管背後是假的還是真的交通。
// 之後換成真的交通，只要改 TripSession 裡的一行。
//
// virtual ... = 0 的意思：這裡只寫名字，內容由繼承它的類別寫（教學 04 第 5 節）。

#include "data/types.h"

class TravelOracle {
public:
    // fromPlace 在 departMin 出發，到 toPlace 要多久、多少錢。
    // 搜尋時會被問好幾千次，所以只回傳最少的東西
    virtual TravelInfo travel(int fromPlace, int toPlace, int departMin) = 0;

    // 同一段的完整交通（走路 → 搭 300 路 → 走路……），每一小段在哪上下車、幾點、多少錢。
    // 只有最後排好的行程要給人看時才呼叫
    virtual Leg travelDetail(int fromPlace, int toPlace, int departMin) = 0;

    virtual ~TravelOracle() {}
};
