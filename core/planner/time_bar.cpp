#include "planner/time_bar.h"
using namespace std;

// 把 DataStore 記起來，estimate 要用
TimeBar::TimeBar(const DataStore& data) : data_(data) {}

int TimeBar::estimate(const Itinerary& it, const vector<int>& selected, const Settings& s) const {
    // TODO 粗估時間。
    //
    // 這裡要做的事：
    // 1. 目前行程的時間：
    //    行程是空的（it.stops.size() == 0）就是 0；
    //    不然是「最後一站的離開時間 - 第一站的離開時間」。
    //    （最後一站是終點的話，用它的到達時間）
    // 2. 每個 selected 裡的景點，加上：
    //    data_.place(那個編號).stayMin × s.paceFactor + s.timeBarTravelMin（20）
    // 3. 回傳加起來的分鐘數。
    //
    // 只估時間，沒有預算條。
    return 0;
}
