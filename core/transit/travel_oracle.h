#pragma once
// TravelOracle：排行程的程式「只」透過這個介面問車程。
// 背後是 FakeTravel（直線距離，先拿來測）還是 TransitRouter（真的公車），
// D1～D4 都不用知道。之後換成真的交通，只要改 TripSession 裡建哪一個那一行。

#include "data/types.h"

class TravelOracle {
public:
    // fromPlace 在 departMin 出發，到 toPlace 要多久、多少錢。
    // 搜尋時會被問好幾千次，所以只回傳最少的東西，要快
    virtual TravelInfo travel(int fromPlace, int toPlace, int departMin) = 0;

    // 同一段的完整交通（走路 → 搭 300 路 → 走路……）。
    // 只有最後排好的行程要給人看時才呼叫，慢一點沒關係
    virtual Leg travelDetail(int fromPlace, int toPlace, int departMin) = 0;

    virtual ~TravelOracle() = default;
};
