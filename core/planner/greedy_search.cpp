#include "planner/greedy_search.h"
using namespace std;

GreedySearch::GreedySearch(const DataStore& data, TimelineChecker& checker, const Recommender& rec)
    : data_(data), checker_(checker), rec_(rec) {}

Itinerary GreedySearch::search(const vector<ItineraryStop>& mustGoOrder,
                               const vector<int>& candidates) {
    // TODO 從 mustGoOrder 開始（教學 10 第 10 節）：
    //
    // 重複做，直到什麼都塞不進去：
    //   對每個還沒排進去的候選、每個可以插的位置（起點後面到終點前面都試）：
    //     插進去 → 丟給 checker_.check(順序, req_, settings_)
    //     走得完的話，算「分數² ÷ 多花的時間」
    //       分數問 rec_.score(data_.place(id), req_, settings_)
    //       多花的時間 = 插進去之後的結束時間 - 插之前的結束時間，至少算 1，免得除以 0
    //   挑比例最大的那一個、那一個位置，真的插進去。
    //
    // 一定要去的和吃飯站已經在 mustGoOrder 裡了，只能在它們中間插東西，不能動它們。
    // 回傳的 Itinerary 先填 stops（用最後一次 check 的 timed）和 totalScore，
    // legs 和費用之後由 TripSession 補。
    //
    // 測試：用教學 10 第 10 節的例子，每一輪插的景點都要一樣，最後總分 26.5。
    (void)mustGoOrder; (void)candidates;
    return {};
}
