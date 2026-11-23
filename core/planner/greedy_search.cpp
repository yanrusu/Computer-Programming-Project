#include "planner/greedy_search.h"
using namespace std;

// 把傳進來的三個模組記起來，search 要用
GreedySearch::GreedySearch(const DataStore& data, TimelineChecker& checker, const Recommender& rec)
    : data_(data), checker_(checker), rec_(rec) {}

Itinerary GreedySearch::search(const vector<ItineraryStop>& mustGoOrder,
                               const vector<int>& candidates) {
    // TODO 貪婪插入（教學 10 第 10 節）。
    //
    // 準備：
    //   route = mustGoOrder（目前的順序）
    //   先 check 一次 route，記下目前的結束時間 nowEnd。
    //
    // 重複做下面的事，直到這一輪什麼都插不進去：
    //   bestRatio = -1（目前找到最好的比例），記下最好的是哪個候選、插在哪個位置
    //   對每個還沒在 route 裡的候選 c：
    //     對每個可以插的位置 pos（從 1 到 route.size() - 1，也就是起點後面到最後一站前面）：
    //       1. 複製一份 route，在 pos 插入候選 c（kind = Spot、placeId = c）。
    //       2. r = checker_.check(新的順序, req_, settings_)
    //       3. r.ok 是 false 就跳過。
    //       4. 多花的時間 = r.endMin - nowEnd，小於 1 就當 1（不能除以 0）。
    //       5. 分數 = rec_.score(data_.place(c), req_, settings_)
    //       6. 比例 = 分數 × 分數 ÷ 多花的時間。比 bestRatio 大就記下來。
    //   都試完了：
    //     bestRatio 還是 -1 → 插不進去了，結束。
    //     不然把最好的那個真的插進 route，更新 nowEnd，再重複一輪。
    //
    // 最後：
    //   用最後一次 check 的 timed 當作行程的 stops，
    //   totalScore = 所有景點的分數加起來，回傳。
    //
    // 對答案：教學 10 第 10 節的例子，每一輪插進去的景點要一樣，最後總分 26.5。
    Itinerary it;
    return it;
}
