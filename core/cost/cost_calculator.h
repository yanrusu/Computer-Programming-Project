#pragma once
// CostCalculator：算錢。
// 車資查「站到站票價表」，那張表是離線工具事先從 TDX 換算好的，這裡只負責查表和加總。
// 不算轉乘優惠、不算外地人電子票證優惠，YouBike 算 0 元。
//
// 誰會用它：TransitRouter 算每段車資時問 rideFare；行程排好後 TripSession 呼叫 fillCosts。

#include <string>
#include "data/data_store.h"
#include "data/types.h"

class CostCalculator {
public:
    // 讀站到站票價表。回傳：讀成功是 true
    bool loadFares(const std::string& csvDir);

    // 一段搭乘多少錢。
    // 輸入：路線編號、上車站、下車站
    // 回傳：幾元。走路、YouBike（lineId 是 -1）是 0
    int rideFare(int lineId, int fromStop, int toStop) const;

    // 把行程的車資、門票、餐費小計算好，寫進 it 的 fareTotal、ticketTotal、mealTotal。
    // 一餐多少錢用 s.lunchCost（預設 250 元）
    void fillCosts(Itinerary& it, const DataStore& data, const Settings& s) const;
};
