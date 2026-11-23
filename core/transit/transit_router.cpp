#include "transit/transit_router.h"
using namespace std;

// 做法在教學 10 第 3 節和教學 06，這裡只記重點：
// - 路線節點圖：每條路線在每個站牌上各有一個點。站牌點 → 路線點是「上車邊」，
//   等車時間加在這裡；路線點 → 下一站的路線點是「坐車邊」；路線點 → 站牌點是「下車」。
// - Dijkstra 的 dist 不是存距離，是存「幾點到」。走上車邊時，
//   用 lower_bound 在這個站的發車時刻裡找「到站時間之後的下一班」。
// - 只有班距沒有時刻表的公車，用首班車＋班距產生時刻，之後跟一般的一樣處理。
// - 換車多留 Settings::transferBuffer（3 分鐘）。
// - 到不了的點時間是 INT_MAX，不要拿去加，會溢位。
// - 一次 Dijkstra 會算出一個地點到「所有」地點，全部記起來。
//   記的時候出發時間往後對齊到 10 分鐘（Settings::slotMin），這樣比較容易重複用到。

bool TransitRouter::build(const DataStore& data, const StreetRouter& street, const string& csvDir) {
    // TODO(B7) 先用 tests/fixtures/ 手寫的小資料（2 條公車、2 個 YouBike 站）建圖，
    // 點數、邊數要跟手算的一樣。C 的真資料 12/6 前換上。
    // 站牌之間、地點到站牌的步行邊，時間問 street.walkMinutes。
    (void)data; (void)street; (void)csvDir;
    return false;
}

void TransitRouter::setDay(int weekday, bool isHoliday) {
    // TODO(B7) 每條上車邊都存平日、假日兩套時刻，這裡決定之後用哪一套。換了要 clearCache。
    (void)weekday; (void)isHoliday;
}

void TransitRouter::setOptions(const TripRequest& req, const Settings& s) {
    // TODO(B8) 記下 allowBus、allowBike。不能搭的就在 Dijkstra 裡跳過那種邊，不用重新建圖。
    // 改了就 clearCache。
    (void)req; (void)s;
}

void TransitRouter::clearCache() {
    // TODO(B8) 把記住的車程清空
}

TravelInfo TransitRouter::travel(int fromPlace, int toPlace, int departMin) {
    // TODO(B8) 1. 出發時間往後對齊到 10 分鐘。
    //          2. 這個（出發地點, 時段）算過了就直接查表回傳。
    //          3. 沒算過就跑一次看時刻的 Dijkstra，把到所有地點的答案都記起來。
    // 車資：沿著 prevEdge 倒推，每一段搭乘問 CostCalculator::rideFare。
    // （TransitRouter 怎麼拿到 CostCalculator，計劃書的 build 沒有寫，到時候再一起定。）
    (void)fromPlace; (void)toPlace; (void)departMin;
    return {};
}

Leg TransitRouter::travelDetail(int fromPlace, int toPlace, int departMin) {
    // TODO(B9) 用精確的出發時間（不對齊）跑一次，從終點用 prev 倒推出
    // 「走路 → 300 路 → 75 路 → 走路」，每一小段是一個 Segment。
    // 搭車段的 path 從 TDX 路線形狀切出來，走路段的 path 問 StreetRouter::path。
    (void)fromPlace; (void)toPlace; (void)departMin;
    return {};
}
