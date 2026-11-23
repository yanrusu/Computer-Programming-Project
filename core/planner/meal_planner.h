#pragma once
// D2 MealPlanner：決定這趟要吃哪幾餐。
// 只決定「要不要吃午餐、晚餐」，不排餐廳、不管吃什麼，那是使用者自己的事。
// 吃飯站實際幾點開始，是 D1 一站一站算的時候決定的。

#include <vector>
#include "data/types.h"

class MealPlanner {
public:
    // 回傳要吃的那幾餐，每餐是一個 kind == Meal、placeId == -1 的站
    std::vector<ItineraryStop> mealSlots(const TripRequest& req, const Settings& s) const;
};
