#pragma once
// Recommender：替景點打分數、判斷這天去不去得了、列出推薦清單。
// 只看景點本身和使用者的興趣，不管交通，也不排順序。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"

class Recommender {
public:
    // 計劃書沒寫建構函式。recommend 要掃所有景點，所以跟 DataStore 拿
    explicit Recommender(const DataStore& data);

    // 景點分數 0～10
    double score(const Place& p, const TripRequest& req, const Settings& s) const;

    // 這一天去不去得了：公休，或開放時間跟出發～結束時間重疊不到一次停留，就是 false
    bool canVisit(const Place& p, const TripRequest& req) const;

    // 推薦清單，分數高的在前面。行程裡已經有的、被刪掉的不放
    std::vector<int> recommend(const TripRequest& req, const Settings& s) const;

private:
    const DataStore& data_;
};
