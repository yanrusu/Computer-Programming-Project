#pragma once
// D3 PlanSearch：挑景點、排順序的介面（B 負責）。
// 貪婪（GreedySearch）和 ILS（IlsSearch）都長這樣，TripSession 不用管背後是哪一個。
// 先寫貪婪就能跑，ILS 之後包在外面。

#include <vector>
#include "data/types.h"

class PlanSearch {
public:
    // 計劃書沒有這個。search 要知道這一輪的輸入和設定（幾點結束、步調……），
    // 但計劃書的 search 參數裡沒有，所以先在呼叫 search 之前用這個交給它。
    // 寫的時候覺得改成 search 多帶兩個參數比較順的話，在群組講一聲再改。
    void setRequest(const TripRequest& req, const Settings& s) {
        req_ = req;
        settings_ = s;
    }

    // mustGoOrder 是 D4 給的順序（一定要去的＋吃飯站，含起點終點），裡面的不能拿掉、不能換順序。
    // 從 candidates 裡挑景點插進去，讓分數加總最高，而且整個要走得完
    virtual Itinerary search(const std::vector<ItineraryStop>& mustGoOrder,
                             const std::vector<int>& candidates) = 0;

    virtual ~PlanSearch() = default;

protected:
    TripRequest req_;
    Settings settings_;
};
