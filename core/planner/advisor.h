#pragma once
// Advisor：D5～D7，幫使用者「改行程」的三個小功能。
//   D5 suggest   一定要去的排不下時，給最多 3 個可以一鍵套用的建議
//   D6 nearby    就近替換：第 i 站可以換成附近哪些景點
//   D7 timeBar   時間條：勾了這些景點大概要幾分鐘
// 做法都是「改一下，再問 Planner 行不行」（D7 只粗估，不問）。
// 它不自己算時間，算時間是 Planner 的事。
//
// 它會用到：DataStore（查景點）、TravelOracle（看近不近）、Recommender（排序）、Planner（試排）。

#include <set>
#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "planner/planner.h"
#include "recommend/recommender.h"
#include "transit/travel_oracle.h"

class Advisor {
public:
    // 建立的時候交給它四樣東西，之後的函式都會用到
    Advisor(const DataStore& data, TravelOracle& travel, const Recommender& rec, Planner& planner);

    // D5：產生建議，最多 3 個。
    // 輸入：req、s 是這次想排的輸入和設定；conflicts 是 mustGoCheck 找到的衝突；
    //       justAdded 是這一輪剛新增的景點
    // 回傳：驗證過、套用後一定排得下的建議
    std::vector<Suggestion> suggest(const TripRequest& req, const Settings& s,
                                    const std::vector<Conflict>& conflicts,
                                    const std::set<int>& justAdded);

    // D6：可以拿來換掉 it.stops[stopIndex] 的景點。
    // 回傳：景點編號，分數高的在前面
    std::vector<int> nearby(const Itinerary& it, int stopIndex,
                            const TripRequest& req, const Settings& s);

    // D7：粗估總共要幾分鐘。
    // 輸入：it 是目前的行程；selected 是使用者剛勾的景點編號
    // 回傳：目前行程的時間 + 每個新勾的景點（停留 + 20 分鐘交通）
    int timeBar(const Itinerary& it, const std::vector<int>& selected, const Settings& s) const;

private:
    const DataStore& data_;
    TravelOracle& travel_;
    const Recommender& rec_;
    Planner& planner_;
};
