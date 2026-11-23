#pragma once
// D3 GreedySearch：貪婪插入。
// 每一輪試「每個候選 × 每個位置」，挑最划算的插進去，插到塞不下為止。
// 挑了就不回頭，所以可能不是最好的；讓它變好是 IlsSearch 的事。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "planner/plan_search.h"
#include "planner/timeline_checker.h"
#include "recommend/recommender.h"

class GreedySearch : public PlanSearch {
public:
    // 計劃書沒寫建構函式。要問 D1 走不走得完，要問 Recommender 每個景點幾分
    GreedySearch(const DataStore& data, TimelineChecker& checker, const Recommender& rec);

    Itinerary search(const std::vector<ItineraryStop>& mustGoOrder,
                     const std::vector<int>& candidates) override;

private:
    const DataStore& data_;
    TimelineChecker& checker_;
    const Recommender& rec_;
};
