#include "planner/time_bar.h"
using namespace std;

TimeBar::TimeBar(const DataStore& data) : data_(data) {}

int TimeBar::estimate(const Itinerary& it, const vector<int>& selected, const Settings& s) const {
    // TODO(A9)
    //   目前行程的時間 = 最後一站的離開（或到達終點）- 第一站的出發；行程是空的就是 0
    //   每個新勾選的景點加：停留 × s.paceFactor + s.timeBarTravelMin（20）
    // 沒有預算條，只估時間。
    (void)it; (void)selected; (void)s;
    return 0;
}
