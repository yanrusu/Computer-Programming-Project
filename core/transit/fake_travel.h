#pragma once
// FakeTravel：用兩點的直線距離「假裝」車程。
// 真的交通（TransitRouter）12 月才會好，在那之前排行程和介面都先用它測。
// 不看出發時間、不管公車班次，也不畫路線，只求數字大致合理。

#include "data/data_store.h"
#include "transit/travel_oracle.h"

class FakeTravel : public TravelOracle {   // 測試用
public:
    // 計劃書沒寫建構函式。它要知道每個地點的座標，所以跟 DataStore 拿
    explicit FakeTravel(const DataStore& data);

    TravelInfo travel(int fromPlace, int toPlace, int departMin) override;
    Leg travelDetail(int fromPlace, int toPlace, int departMin) override;

private:
    const DataStore& data_;
};
