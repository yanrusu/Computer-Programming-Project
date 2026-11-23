#pragma once
// D5 Advisor：一定要去的排不下時，給使用者最多 3 個可以一鍵套用的建議。
// 每個建議都要先套用看看、用 D4 確認真的排得下，才能拿出來給人看。
// 衝突本身是 D4 找的，這裡只負責想辦法。

#include <set>
#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "planner/conflict_checker.h"
#include "recommend/recommender.h"

class Advisor {
public:
    // 計劃書沒寫建構函式。驗證建議要用 D4，「分數低的先拿掉」要用 Recommender
    Advisor(const DataStore& data, ConflictChecker& conflict, const Recommender& rec);

    // 產生建議，最多 3 個。justAdded 是這一輪剛新增的景點
    std::vector<Suggestion> suggest(const TripRequest& req, const Settings& s,
                                    const std::vector<Conflict>& conflicts,
                                    const std::set<int>& justAdded);

private:
    const DataStore& data_;
    ConflictChecker& conflict_;
    const Recommender& rec_;
};
