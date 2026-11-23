#include "transit/transit_router.h"
using namespace std;

// 整個 TransitRouter 的想法（教學 10 第 3 節、教學 06）：
//
// 交通圖長這樣（叫做「路線節點圖」）：
// - 每個站牌是一個點。
// - 每條公車路線在它經過的每個站牌上，各有一個「路線點」。
// - 站牌點 → 路線點：上車，要等車，等多久看時刻表。
// - 路線點 → 下一站的路線點：坐車，時間固定。
// - 路線點 → 站牌點：下車。
// - 站牌和站牌、地點和站牌之間：走路，時間問 StreetRouter。
//
// 找路用改過的 Dijkstra：
// - 課本的 dist[x] 存「最短距離」，這裡存「最早幾點到 x」。
// - 走上車邊的時候，在這個站的發車時刻（排好的 vector<int>）裡，
//   用 lower_bound 找「到站時間之後的第一班車」，dist 就是那班車的時間。
// - 換車要多留 Settings::transferBuffer（3 分鐘）。
// - 到不了的點時間是 INT_MAX，不要拿去加，會溢位。

bool TransitRouter::build(const DataStore& data, const StreetRouter& street,
                          const CostCalculator& cost, const string& csvDir) {
    // 先把三個模組記起來，travel 和 travelDetail 會用到
    data_ = &data;
    street_ = &street;
    cost_ = &cost;

    // TODO 讀公車、YouBike 的 CSV，建出上面說的交通圖。
    //
    // 這裡要做的事：
    // 1. 先用 tests/fixtures/ 手寫的小資料（2 條公車、2 個 YouBike 站）來寫，
    //    建完之後點數、邊數要跟自己手算的一樣。真資料好了再換上。
    // 2. 每個站牌一個點，每條路線在每個站牌一個路線點。
    // 3. 加上車邊、坐車邊、下車邊、走路邊。上車邊要存平日、假日兩套發車時刻。
    // 4. 只有班距、沒有時刻表的公車：從首班車開始，每隔一個班距加一班，加到末班車。
    // 5. 每個地點（景點、起點、終點）也要連到附近的站牌，走路時間問 street.walkMinutes。
    return false;
}

void TransitRouter::setDay(int weekday, bool isHoliday) {
    // TODO 記下今天是平日還是假日，之後上車邊就用那一套發車時刻。
    // 換了日子，算過的車程就不準了，最後要呼叫 clearCache()。
}

void TransitRouter::setOptions(const TripRequest& req, const Settings& s) {
    // TODO 記下 req.allowBus、req.allowBike。
    // 不能搭公車就在 Dijkstra 裡跳過上車邊，不能騎車就跳過 YouBike 的邊，不用重新建圖。
    // 改了之後要呼叫 clearCache()。
}

void TransitRouter::clearCache() {
    // TODO 把記住車程的 map 清空（用 clear()）。
}

TravelInfo TransitRouter::travel(int fromPlace, int toPlace, int departMin) {
    // TODO fromPlace 幾點出發、多久到 toPlace。
    //
    // 這裡要做的事：
    // 1. 出發時間往後對齊到 10 分鐘（Settings::slotMin），例如 9:03 當作 9:10。
    //    這樣 9:01 到 9:10 出發的問題都算同一個，比較常能重複用。
    // 2. 用 map 查「（fromPlace, 對齊後的時間）」算過沒有，算過就直接回傳。
    // 3. 沒算過：從 fromPlace 跑一次看時刻的 Dijkstra。
    //    一次 Dijkstra 會算出到「所有」地點的時間，全部記進 map。
    // 4. 車資：沿著 prev 從終點倒推回去，每一段搭乘問 cost_->rideFare(路線, 上車站, 下車站)。
    // 5. 到不了就 reachable = false。
    TravelInfo info;
    return info;
}

Leg TransitRouter::travelDetail(int fromPlace, int toPlace, int departMin) {
    // TODO 完整的交通，只有最後排好的行程才會呼叫。
    //
    // 這裡要做的事：
    // 1. 用精確的出發時間（不要對齊）跑一次 Dijkstra。
    // 2. 從終點沿著 prev 倒推回起點，就知道經過哪些邊。
    // 3. 連續走同一種方式的邊合成一個 Segment，例如
    //    「走路 → 300 路 → 75 路 → 走路」就是 4 個 Segment。
    // 4. 每個 Segment 填：方式、路線名稱、上下車站、出發到達時間、車資。
    //    path：搭車段從路線形狀切出來，走路段問 street_->path。
    // 5. 倒推出來的順序是反的，記得反過來，再放進 Leg 回傳。
    Leg leg;
    return leg;
}
