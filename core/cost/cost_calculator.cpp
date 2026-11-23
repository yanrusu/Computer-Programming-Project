#include "cost/cost_calculator.h"
using namespace std;

bool CostCalculator::loadFares(const string& csvDir) {
    // TODO 把票價表讀進 map<tuple<int, int, int>, int>：（路線, 上車站, 下車站）→ 幾元。
    // 編號記得用 DataStore 那邊換過的 0、1、2……，不要用 TDX 的原始編號。
    (void)csvDir;
    return false;
}

int CostCalculator::rideFare(int lineId, int fromStop, int toStop) const {
    // TODO 查上面那張表。走路和 YouBike 傳進來的 lineId 是 -1，直接回傳 0。
    // 查不到的話先回傳 0，但最好能讓人發現（例如測試裡抓出來），不然會默默算錯。
    (void)lineId; (void)fromStop; (void)toStop;
    return 0;
}

void CostCalculator::fillCosts(Itinerary& it, const DataStore& data) const {
    // TODO 三個小計：
    // - fareTotal：每個 Leg 的 fare 加起來。
    // - ticketTotal：每個 kind == Spot 的站，加上 data.place(placeId).ticket。
    // - mealTotal：每個 kind == Meal 的站算一餐。一餐多少錢在 Settings::lunchCost（250），
    //   可是這個函式拿不到 Settings，要多傳一個參數還是怎樣，寫的時候在群組講一下。
    (void)it; (void)data;
}
