#pragma once
// D6 Replacer：就近替換。使用者想把第 i 站換掉時，列出附近、放進去也走得完的景點（A 負責，A9）。
// 只列清單，真的換掉是 TripSession 的事。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "planner/timeline_checker.h"
#include "recommend/recommender.h"
#include "transit/travel_oracle.h"

class Replacer {
public:
    // 計劃書沒寫建構函式。「附近」要問車程，「放得下」要問 D1，排序要問分數
    Replacer(const DataStore& data, TimelineChecker& checker, TravelOracle& travel,
             const Recommender& rec);

    // 可以拿來換掉 it.stops[stopIndex] 的景點，分數高的在前面
    std::vector<int> nearby(const Itinerary& it, int stopIndex,
                            const TripRequest& req, const Settings& s);

private:
    const DataStore& data_;
    TimelineChecker& checker_;
    TravelOracle& travel_;
    const Recommender& rec_;
};
