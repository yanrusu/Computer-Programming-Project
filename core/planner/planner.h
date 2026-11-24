#pragma once
// Planner：排行程的 D1～D4 全部在這裡。
//   D1 check        給一個順序，算出每站幾點、走不走得完
//   D2 mealSlots    這趟要吃哪幾餐
//   D3 greedy、ils  挑景點、排順序
//   D4 mustGoCheck  一定要去的排不排得下
// 這幾個函式互相呼叫就是一般的成員函式呼叫，例如 greedy 裡面直接寫 check(...)。
// 它不管畫面、不記每一輪的狀態（那是 TripSession 的事），也不給建議（那是 Advisor 的事）。
//
// 它會用到：DataStore（查景點）、TravelOracle（問車程）、Recommender（問分數）。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "recommend/recommender.h"
#include "transit/travel_oracle.h"

class Planner {
public:
    // 建立的時候交給它三樣東西，之後的函式都會用到
    Planner(const DataStore& data, TravelOracle& travel, const Recommender& rec);

    // D1：檢查一個順序走不走得完。
    // 輸入：order 是照順序排好的每一站（第一站是起點；有終點的話最後一站是終點；
    //       吃飯也是一站，kind 是 Meal）；req 是使用者的輸入；s 是設定
    // 回傳：ok 走不走得完、reason 走不完的原因、
    //       timed 每站算好的到達／開始／離開時間、endMin 幾點結束、cost 總共花多少
    CheckResult check(const std::vector<ItineraryStop>& order,
                      const TripRequest& req, const Settings& s);

    // D2：這趟要吃哪幾餐。
    // 回傳：0～2 個吃飯站（kind 是 Meal、placeId 是 -1，晚餐的 isDinner 是 true），午餐在前
    std::vector<ItineraryStop> mealSlots(const TripRequest& req, const Settings& s) const;

    // D3：貪婪插入。在一定要去的順序裡一直插景點，插到塞不下。
    // 輸入：mustGoOrder 是 mustGoCheck 給的順序（起點、一定要去的、吃飯站、終點），
    //       這些不能拿掉、不能換順序；candidates 是可以挑的景點編號（推薦前 30 名）
    // 回傳：排好的行程（填 stops 和 totalScore，交通細節和費用之後由 TripSession 補）
    Itinerary greedy(const std::vector<ItineraryStop>& mustGoOrder,
                     const std::vector<int>& candidates,
                     const TripRequest& req, const Settings& s);

    // D3：ILS。先貪婪一次，再一直「拿掉幾站、用 greedy 補回去」找更好的。
    // 輸入、回傳跟 greedy 一樣
    Itinerary ils(const std::vector<ItineraryStop>& mustGoOrder,
                  const std::vector<int>& candidates,
                  const TripRequest& req, const Settings& s);

    // D4：一定要去的排不排得下。
    // 回傳：排得下：ok = true，bestOrder 是最早結束的順序（含起點、吃飯站、終點）
    //       排不下：ok = false，conflicts 說差多少、跟哪些景點有關
    MustGoCheck mustGoCheck(const TripRequest& req, const Settings& s);

private:
    const DataStore& data_;         // 查景點資料
    TravelOracle& travel_;          // 問車程
    const Recommender& rec_;        // 問景點幾分
};
