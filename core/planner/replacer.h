#pragma once
// D6 Replacer：就近替換。使用者想把第 i 站換掉時，列出附近、放進去也走得完的景點。
// 只列清單，真的換掉是 TripSession 的事。
//
// 誰會用它：TripSession 的 replaceOptions。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "planner/timeline_checker.h"
#include "recommend/recommender.h"
#include "transit/travel_oracle.h"

class Replacer {
public:
    // 建立的時候交給它：DataStore 查景點、D1 試排、TravelOracle 看近不近、Recommender 排序
    Replacer(const DataStore& data, TimelineChecker& checker, TravelOracle& travel,
             const Recommender& rec);

    // 可以拿來換掉 it.stops[stopIndex] 的景點。
    // 回傳：景點編號，分數高的在前面
    std::vector<int> nearby(const Itinerary& it, int stopIndex,
                            const TripRequest& req, const Settings& s);

private:
    const DataStore& data_;
    TimelineChecker& checker_;
    TravelOracle& travel_;
    const Recommender& rec_;
};
