#pragma once
// CostCalculator：算錢（C 負責，C10）。
// 車資查「站到站票價表」，那張表是離線工具事先從 TDX 換算好的，這裡只負責查表和加總。
// 不算轉乘優惠、不算外地人電子票證優惠，YouBike 算 0 元。

#include <string>
#include "data/data_store.h"
#include "data/types.h"

class CostCalculator {
public:
    // 讀站到站票價表
    bool loadFares(const std::string& csvDir);

    // 一段搭乘多少錢：用（路線, 上車站, 下車站）查表。YouBike 是 0
    int rideFare(int lineId, int fromStop, int toStop) const;

    // 把行程的車資、門票、餐費小計算好，寫進 it
    void fillCosts(Itinerary& it, const DataStore& data) const;
};
