#pragma once
// D3 PlanSearch：挑景點、排順序的「介面」。
// 它只規定要有 search 這個函式，真正做事的是 GreedySearch（貪婪）和 IlsSearch（ILS）。
// TripSession 只認得 PlanSearch，不用管背後是哪一個，先寫貪婪就能跑。

#include <vector>
#include "data/types.h"

class PlanSearch {
public:
    // 呼叫 search 之前先呼叫這個，把這一輪的輸入和設定交給它
    // （search 要知道幾點結束、步調等等，可是 search 的參數裡沒有）
    void setRequest(const TripRequest& req, const Settings& s) {
        req_ = req;
        settings_ = s;
    }

    // 在一定要去的順序裡補上其他景點，讓分數加總最高，而且整個要走得完。
    // 輸入：mustGoOrder 是 D4 給的順序（起點、一定要去的、吃飯站、終點），
    //       這些不能拿掉，也不能換順序；
    //       candidates 是可以挑的景點編號（推薦清單前 30 名）
    // 回傳：排好的行程（先填 stops 和 totalScore，交通細節和費用之後由 TripSession 補）
    virtual Itinerary search(const std::vector<ItineraryStop>& mustGoOrder,
                             const std::vector<int>& candidates) = 0;

    virtual ~PlanSearch() {}

protected:
    TripRequest req_;               // 這一輪的輸入（setRequest 給的）
    Settings settings_;             // 這一輪的設定（setRequest 給的）
};
