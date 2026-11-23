#pragma once
// D4 ConflictChecker：在補景點之前，先確定「一定要去的」排不排得下（B 負責，B10）。
// 用窮舉＋剪枝，所以說「排不下」的時候一定是真的排不下，還能說出差幾分鐘。
// 它只看一定要去的和吃飯站，不補其他景點（那是 D3），也不想建議（那是 D5）。

#include "data/data_store.h"
#include "data/types.h"
#include "planner/meal_planner.h"
#include "planner/timeline_checker.h"

class ConflictChecker {
public:
    // 計劃書沒寫建構函式。每種順序都要丟給 D1，吃飯站跟 D2 要
    ConflictChecker(const DataStore& data, TimelineChecker& checker, const MealPlanner& meals);

    // 一定要去的排不排得下。排得下就回傳最早結束的順序，排不下就回傳衝突
    MustGoCheck check(const TripRequest& req, const Settings& s);

private:
    const DataStore& data_;
    TimelineChecker& checker_;
    const MealPlanner& meals_;
};
