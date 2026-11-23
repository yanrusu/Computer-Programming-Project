#pragma once
// D3 IlsSearch：在貪婪外面再包一層，讓它有機會回頭（B 負責，B11）。
// 做法是「拿掉連續幾站，再用貪婪補回去，看有沒有比較好」。
// 不用亂數，同樣的輸入每次結果都一樣，測試和 demo 才穩定。
// 補回去的部分直接用 GreedySearch，不要再寫一次。

#include <vector>
#include "data/types.h"
#include "planner/greedy_search.h"
#include "planner/plan_search.h"

class IlsSearch : public PlanSearch {
public:
    // 計劃書沒寫建構函式。重用同一個 GreedySearch
    explicit IlsSearch(GreedySearch& greedy);

    Itinerary search(const std::vector<ItineraryStop>& mustGoOrder,
                     const std::vector<int>& candidates) override;

private:
    GreedySearch& greedy_;
};
