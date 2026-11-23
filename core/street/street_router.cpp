#include "street/street_router.h"
using namespace std;

// 整個 StreetRouter 的想法（教學 10 第 2 節）：
// - 把街道想成一張圖：每個路口是一個點，每段路是一條邊，邊的長度是公尺。
// - 起點、終點通常不剛好在路口上，所以先找「離它最近的路口」。
// - 從起點的路口跑課本的 Dijkstra，就知道到每個路口最短幾公尺。
// - 公尺換成分鐘：走路每分鐘 75 公尺，騎車每分鐘 250 公尺。

bool StreetRouter::load(const string& csvDir) {
    // TODO 讀街道 CSV，建圖。
    //
    // 這裡要做的事：
    // 1. 讀路口的 CSV：每個路口有編號和座標，存進 vector。
    // 2. 讀路段的 CSV：每段路有兩端的路口和長度（公尺），
    //    存成鄰接串列 vector<vector<pair<int, int>>>，兩個方向都要加（路可以雙向走）。
    // 3. 找最近的路口時，路口有幾萬個，一個一個比太慢。
    //    可以先把地圖切成 500 公尺的格子，每個路口放進它所在的格子，
    //    找的時候只比同一格和旁邊 8 格。（先一個一個比也可以，慢了再改）
    // 4. 步行時間快取（data/cache/）有的話就讀進來，沒有就之後算完再存。
    return false;
}

int StreetRouter::walkMinutes(double lat1, double lon1, double lat2, double lon2) const {
    // TODO 沿街道走路要幾分鐘。
    //
    // 這裡要做的事：
    // 1. 找離起點最近的路口 a、離終點最近的路口 b。
    // 2. 從 a 跑 Dijkstra（用 priority_queue），得到 a 到 b 最短幾公尺。
    // 3. 公尺 ÷ 75 就是分鐘，用 ceil 無條件進位。
    // 4. 同樣的起點終點會被問很多次，算過的可以用 map 記起來，下次直接回傳。
    return 0;
}

int StreetRouter::bikeMinutes(double lat1, double lon1, double lat2, double lon2) const {
    // TODO 沿街道騎 YouBike 要幾分鐘。
    //
    // 跟 walkMinutes 一樣找最短的公尺數，只是：
    // 1. 公尺 ÷ 250 才是騎車的分鐘。
    // 2. 再加上借車、還車的時間（幾分鐘先問組員，放進 Settings，不要寫死）。
    return 0;
}

vector<pair<double, double>> StreetRouter::path(double lat1, double lon1,
                                                double lat2, double lon2) const {
    // TODO 沿街道的路線座標。
    //
    // 這裡要做的事：
    // 1. 跟 walkMinutes 一樣跑 Dijkstra，但多記一個 prev 陣列：
    //    prev[x] = 走到 x 之前的那個路口。
    // 2. 從終點的路口開始，一直往 prev 走回起點，把每個路口的座標 push_back 進去。
    // 3. 這樣得到的是「終點到起點」，最後用 reverse 反過來。
    vector<pair<double, double>> points;
    return points;
}
