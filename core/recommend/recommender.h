#pragma once
// Recommender：替景點打分數、判斷這天去不去得了、列出推薦清單。
// 只看景點本身和使用者的興趣，不管交通，也不排順序。
//
// 誰會用它：TripSession 拿推薦清單當候選；GreedySearch 問分數；Advisor、Replacer 排序時也問分數。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"

class Recommender {
public:
    // 建立的時候把 DataStore 交給它，recommend 才看得到所有景點
    Recommender(const DataStore& data);

    // 一個景點幾分，0～10 分，越高越推薦。
    // 看使用者的興趣跟景點的類別合不合，再加上組員的評分
    double score(const Place& p, const TripRequest& req, const Settings& s) const;

    // 這個景點這一天去不去得了。
    // 公休、或開放時間跟使用者的出發～結束時間重疊太少（不夠待一次），就是 false
    bool canVisit(const Place& p, const TripRequest& req) const;

    // 推薦清單：回傳景點編號，分數高的在前面。
    // 已經在行程裡的（mustGo）、被刪掉的（dontGo）、去不了的都不放
    std::vector<int> recommend(const TripRequest& req, const Settings& s) const;

private:
    const DataStore& data_;         // 查景點用
};
