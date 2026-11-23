#pragma once
// D7 TimeBar：使用者在推薦清單上勾景點時，即時顯示「已選約 7.5 小時／可用 9 小時」。
// 勾一下就要更新，不能跑 D1（太慢），所以只粗估，不保證準。
//
// 誰會用它：TripSession 的 timeBarMinutes。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"

class TimeBar {
public:
    // 建立的時候把 DataStore 交給它，才查得到每個景點要待多久
    TimeBar(const DataStore& data);

    // 粗估總共要幾分鐘。
    // 輸入：it 是目前的行程；selected 是使用者剛勾的景點編號
    // 回傳：目前行程的時間 + 每個新勾的景點（停留 + 20 分鐘交通）
    int estimate(const Itinerary& it, const std::vector<int>& selected, const Settings& s) const;

private:
    const DataStore& data_;
};
