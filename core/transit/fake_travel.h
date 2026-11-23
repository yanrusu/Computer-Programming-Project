#pragma once
// FakeTravel：用兩點的直線距離「假裝」車程，測試用。
// 真的交通（TransitRouter）還沒做好之前，排行程和畫面都先用它。
// 不看出發時間、不管公車班次，只求數字大致合理。

#include "data/data_store.h"
#include "transit/travel_oracle.h"

class FakeTravel : public TravelOracle {
public:
    // 建立的時候把 DataStore 交給它，之後才查得到每個地點的座標
    FakeTravel(const DataStore& data);

    // 用直線距離估：1 公里內當作走路，再遠當作搭車
    TravelInfo travel(int fromPlace, int toPlace, int departMin) override;

    // 包成只有一小段的 Leg，地圖上畫成一條直線
    Leg travelDetail(int fromPlace, int toPlace, int departMin) override;

private:
    const DataStore& data_;         // 查座標用
};
