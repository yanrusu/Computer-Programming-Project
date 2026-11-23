#include "street/street_router.h"
using namespace std;

// 整個 StreetRouter 的做法在教學 10 第 2 節，大致是：
// 1. 路口是點、路段是邊，權重是公尺。
// 2. 起點終點通常不在路口上，先找最近的路口。路口有幾萬個，
//    用 500 公尺的格子分好，只比同一格和旁邊 8 格就好。
// 3. 從起點的路口跑課本的 Dijkstra。
// 4. 公尺換分鐘：走路每分鐘 75 公尺，騎車每分鐘 250 公尺再加借還車時間。
// 5. 同樣的起終點會被問很多次，算過就記起來。

bool StreetRouter::load(const string& csvDir) {
    // TODO(B9) 讀路口和路段的 CSV 建圖，然後讀步行時間快取（data/cache/，不進 Git）。
    (void)csvDir;
    return false;
}

int StreetRouter::walkMinutes(double lat1, double lon1, double lat2, double lon2) const {
    // TODO(B9) 找兩邊最近的路口 → Dijkstra 算公尺 → 除以 75 再無條件進位。
    (void)lat1; (void)lon1; (void)lat2; (void)lon2;
    return 0;
}

int StreetRouter::bikeMinutes(double lat1, double lon1, double lat2, double lon2) const {
    // TODO(B9) 跟走路一樣，只是除以 250，再加上借車、還車的時間（多少分鐘先放進 Settings）。
    (void)lat1; (void)lon1; (void)lat2; (void)lon2;
    return 0;
}

vector<pair<double, double>> StreetRouter::path(double lat1, double lon1,
                                                double lat2, double lon2) const {
    // TODO(B9) Dijkstra 跑完後用 prev 從終點倒推回起點，把每個路口的座標串起來（記得反轉）。
    (void)lat1; (void)lon1; (void)lat2; (void)lon2;
    return {};
}
