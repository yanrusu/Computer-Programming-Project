#pragma once
// D4 ConflictChecker：在補景點之前，先確定「一定要去的」排不排得下。
// 試過所有順序才下結論，所以說「排不下」的時候一定是真的排不下，還能說出差幾分鐘。
// 它只排一定要去的和吃飯站，不補其他景點（那是 D3），也不想建議（那是 D5）。
//
// 誰會用它：TripSession 每次重新排之前；Advisor 驗證建議行不行。

#include "data/data_store.h"
#include "data/types.h"
#include "planner/meal_planner.h"
#include "planner/timeline_checker.h"

class ConflictChecker {
public:
    // 建立的時候交給它：DataStore 查景點、D1 檢查每種順序、D2 決定要不要放吃飯站
    ConflictChecker(const DataStore& data, TimelineChecker& checker, const MealPlanner& meals);

    // 一定要去的排不排得下。
    // 回傳：MustGoCheck
    //       排得下：ok = true，bestOrder 是最早結束的順序（含起點、吃飯站、終點）
    //       排不下：ok = false，conflicts 說差多少、跟哪些景點有關
    MustGoCheck check(const TripRequest& req, const Settings& s);

private:
    const DataStore& data_;
    TimelineChecker& checker_;
    const MealPlanner& meals_;
};
