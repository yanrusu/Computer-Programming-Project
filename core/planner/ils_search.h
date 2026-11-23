#pragma once
// D3 IlsSearch：在貪婪外面再包一層，讓它有機會回頭改。
// 做法是「拿掉連續幾站，再用貪婪補回去，看有沒有比較好」。
// 不用亂數，同樣的輸入每次結果都一樣，測試和 demo 才穩定。
// 補回去的部分直接叫 GreedySearch 做，不要再寫一次。
//
// 誰會用它：TripSession（透過 PlanSearch）。

#include <vector>
#include "data/types.h"
#include "planner/greedy_search.h"
#include "planner/plan_search.h"

class IlsSearch : public PlanSearch {
public:
    // 建立的時候把 GreedySearch 交給它，之後一直叫它補景點
    IlsSearch(GreedySearch& greedy);

    // 先貪婪一次，再一直「拿掉幾站、補回去」找更好的（參數說明看 plan_search.h）
    Itinerary search(const std::vector<ItineraryStop>& mustGoOrder,
                     const std::vector<int>& candidates) override;

private:
    GreedySearch& greedy_;
};
