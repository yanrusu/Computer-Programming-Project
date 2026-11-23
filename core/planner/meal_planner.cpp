#include "planner/meal_planner.h"
using namespace std;

vector<ItineraryStop> MealPlanner::mealSlots(const TripRequest& req, const Settings& s) const {
    // TODO 決定要吃哪幾餐。
    //
    // 規則：行程時間跟用餐時段「重疊至少 60 分鐘」才吃。
    // 兩段時間 [a1, a2] 和 [b1, b2] 重疊幾分鐘：
    //     重疊 = min(a2, b2) - max(a1, b1)，算出來小於 0 就當 0
    //
    // 這裡要做的事：
    // 1. 使用者選了不吃飯（s.ignoreMeal 是 true）就直接回傳空的。
    // 2. 算 [req.startMin, req.endMin] 跟午餐 [s.lunchFrom, s.lunchTo] 重疊多久。
    //    >= 60 的話，做一個 ItineraryStop：kind = ItineraryStop::Meal、placeId = -1、
    //    isDinner = false，push_back 進去。
    // 3. 晚餐 [s.dinnerFrom, s.dinnerTo] 一樣，isDinner = true。
    //
    // 拿來寫測試的三個例子：
    //   9:00～17:00  → 午餐重疊 120 分鐘，要吃；晚餐 0，不吃
    //   9:00～12:00  → 午餐只重疊 30 分鐘，不吃
    //   13:00～20:00 → 午餐 30，不吃；晚餐 120，要吃
    vector<ItineraryStop> meals;
    return meals;
}
