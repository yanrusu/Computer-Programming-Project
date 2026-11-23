#pragma once
// D3 GreedySearch：貪婪插入。
// 每一輪試「每個候選 × 每個位置」，挑最划算的插進去，插到塞不下為止。
// 挑了就不回頭，所以不一定是最好的；讓它變更好是 IlsSearch 的事。
//
// 誰會用它：TripSession（透過 PlanSearch）、IlsSearch（搖完之後用它補回去）。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "planner/plan_search.h"
#include "planner/timeline_checker.h"
#include "recommend/recommender.h"

class GreedySearch : public PlanSearch {
public:
    // 建立的時候交給它：DataStore 查景點、D1 問走不走得完、Recommender 問分數
    GreedySearch(const DataStore& data, TimelineChecker& checker, const Recommender& rec);

    // 從 mustGoOrder 開始，一直插景點進去，插到塞不下（參數說明看 plan_search.h）
    Itinerary search(const std::vector<ItineraryStop>& mustGoOrder,
                     const std::vector<int>& candidates) override;

private:
    const DataStore& data_;
    TimelineChecker& checker_;
    const Recommender& rec_;
};
