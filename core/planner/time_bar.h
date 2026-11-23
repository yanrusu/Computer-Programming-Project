#pragma once
// D7 TimeBar：使用者在推薦清單上勾景點時，即時顯示「已選約 7.5 小時／可用 9 小時」（A 負責，A9）。
// 勾一下就要更新，不能跑 D1，所以只粗估，不保證準。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"

class TimeBar {
public:
    // 計劃書沒寫建構函式。要知道每個景點建議待多久
    explicit TimeBar(const DataStore& data);

    // 粗估總共要幾分鐘：目前行程的時間＋新勾選景點的停留＋每個 20 分鐘交通
    int estimate(const Itinerary& it, const std::vector<int>& selected, const Settings& s) const;

private:
    const DataStore& data_;
};
