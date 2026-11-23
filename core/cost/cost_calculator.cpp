#include "cost/cost_calculator.h"
using namespace std;

bool CostCalculator::loadFares(const string& csvDir) {
    // TODO 讀站到站票價表。
    //
    // 這裡要做的事：
    // 1. 打開票價表的 CSV，每一行是：路線、上車站、下車站、票價。
    // 2. 存進一個 map，鑰匙是（路線, 上車站, 下車站），值是票價。
    //    三個數字當鑰匙可以用 tuple<int, int, int>，
    //    或是把三個數字接成一個字串，例如 "12-3-8"，用 map<string, int>。
    //    這個 map 要放在 class 的 private 裡（.h 要加一行）。
    // 3. 編號記得用 DataStore 那邊換過的 0、1、2……，不要用 TDX 原本的編號。
    return false;
}

int CostCalculator::rideFare(int lineId, int fromStop, int toStop) const {
    // TODO 查票價。
    //
    // 這裡要做的事：
    // 1. lineId 是 -1（走路、YouBike）就直接回傳 0。
    // 2. 用（lineId, fromStop, toStop）去 map 裡找，找到就回傳票價。
    // 3. 找不到先回傳 0。但這通常表示資料有缺，測試的時候要抓出來，不然會默默算錯。
    return 0;
}

void CostCalculator::fillCosts(Itinerary& it, const DataStore& data, const Settings& s) const {
    // TODO 算三個小計，直接寫進 it。
    //
    // 這裡要做的事：
    // 1. fareTotal：把 it.legs 每一個的 fare 加起來。
    // 2. ticketTotal：看 it.stops 每一站，kind 是 ItineraryStop::Spot 的，
    //    加上 data.place(那站的 placeId).ticket。
    // 3. mealTotal：kind 是 ItineraryStop::Meal 的，每一站加 s.lunchCost。
}
