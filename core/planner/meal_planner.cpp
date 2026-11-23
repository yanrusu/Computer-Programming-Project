#include "planner/meal_planner.h"
using namespace std;

vector<ItineraryStop> MealPlanner::mealSlots(const TripRequest& req, const Settings& s) const {
    // TODO 行程 [req.startMin, req.endMin] 跟用餐時段重疊至少 60 分鐘才吃。
    // 兩段時間重疊多少：max(0, min(a2, b2) - max(a1, b1))
    //
    //   9:00～17:00  → 午餐重疊 120 分鐘，要吃；晚餐 0，不吃
    //   9:00～12:00  → 午餐只重疊 30 分鐘，不吃
    //   13:00～20:00 → 午餐 30 不吃；晚餐 120 要吃
    //
    // 上面三個直接拿來當測試。使用者選了「不吃」的話，TripSession 就不會呼叫這個。
    (void)req; (void)s;
    return {};
}
