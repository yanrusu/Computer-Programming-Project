#include "recommend/recommender.h"
using namespace std;

// 把傳進來的 DataStore 記在 data_，之後的函式要用
Recommender::Recommender(const DataStore& data) : data_(data) {}

double Recommender::score(const Place& p, const TripRequest& req, const Settings& s) const {
    // TODO 算一個景點幾分。（公式還在研究，之後可能換成更簡單的）
    //
    // 公式：分數 = (s.eta × 興趣符合度 + (1 - s.eta) × 評分 ÷ 5) × 10
    //
    // 興趣符合度（0～1）怎麼算：
    // 1. 分子：i 從 0 到 6，把 req.interest[i] × (p.category[i] 是 true 就是 1，不然 0) 加起來。
    // 2. 使用者那邊的長度 = sqrt(每一類強度的平方加起來)。
    // 3. 景點那邊的長度 = sqrt(景點有幾類)。
    // 4. 符合度 = 分子 ÷ (兩個長度相乘)。任何一個長度是 0 就當符合度 0，不要除以 0。
    //
    // 使用者完全沒填興趣（7 格都是 0）的話，只看評分：分數 = 評分 ÷ 5 × 10。
    //
    // 對答案用的例子（教學 08 第 1 節）：
    // 使用者「歷史 3、美食 2」，第二市場（歷史＋美食，評分 4）是 9.26 分。
    return 0;
}

bool Recommender::canVisit(const Place& p, const TripRequest& req) const {
    // TODO 這一天去不去得了。
    //
    // 這裡要做的事：
    // 1. 開門 = p.openMin[req.weekday]，關門 = p.closeMin[req.weekday]。
    // 2. 開門是 -1 表示公休，回傳 false。
    // 3. 算開放時間和使用者時間重疊多久：
    //    重疊 = min(關門, req.endMin) - max(開門, req.startMin)
    // 4. 重疊 < p.stayMin（不夠待一次）就回傳 false，不然回傳 true。
    //
    // 畫面上灰色不能選的景點，就是這裡回傳 false 的。
    return false;
}

vector<int> Recommender::recommend(const TripRequest& req, const Settings& s) const {
    // TODO 推薦清單。
    //
    // 這裡要做的事：
    // 1. 用 for 迴圈看每個景點（編號 i 從 0 到 data_.places().size() - 1），以下的跳過不要：
    //    - canVisit 是 false 的
    //    - 在 req.mustGo 裡的（已經在行程裡了），用 req.mustGo.count(i) > 0 判斷
    //    - 在 req.dontGo 裡的（被刪掉的）
    //    - 起點、終點本身
    // 2. 剩下的照分數由高到低排；同分的話評分高的在前面。
    //    排序可以用 sort 加一個自己寫的比較函式（教學 10 第 6 節有範例）。
    // 3. 回傳排好的編號。
    //
    // 這裡回傳全部。TripSession 只拿前 s.candidateCount（30）個給排行程用。
    vector<int> answer;
    return answer;
}
