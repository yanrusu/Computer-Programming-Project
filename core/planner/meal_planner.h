#pragma once
// D2 MealPlanner：決定這趟要吃哪幾餐。
// 只決定「要不要吃午餐、晚餐」，不排餐廳、不管吃什麼，那是使用者自己的事。
// 吃飯站實際幾點開始，是 D1 一站一站算的時候決定的。
//
// 誰會用它：D4 ConflictChecker 排一定要去的順序時，把吃飯站一起放進去。

#include <vector>
#include "data/types.h"

class MealPlanner {
public:
    // 這趟要吃哪幾餐。
    // 回傳：0～2 個吃飯站（kind 是 Meal、placeId 是 -1，晚餐的 isDinner 是 true），
    //       午餐在前、晚餐在後
    std::vector<ItineraryStop> mealSlots(const TripRequest& req, const Settings& s) const;
};
