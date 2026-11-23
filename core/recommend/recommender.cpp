#include "recommend/recommender.h"
using namespace std;

Recommender::Recommender(const DataStore& data) : data_(data) {}

double Recommender::score(const Place& p, const TripRequest& req, const Settings& s) const {
    // TODO(A2) 目前的公式（還在研究，可能會換成更簡單的）：
    //   分數 = (s.eta × 興趣符合度 + (1 - s.eta) × 評分 ÷ 5) × 10
    // 興趣符合度用 cosine similarity：使用者的 7 類強度（0～3）當一個向量，
    // 景點的 7 類（有是 1、沒有是 0）當另一個向量，算夾角的 cos。
    // 使用者完全沒填興趣（7 格都是 0）的話，只看評分：評分 ÷ 5 × 10。
    // 例子在教學 08 第 1 節：「歷史 3、美食 2」的人，第二市場 9.26 分。
    (void)p; (void)req; (void)s;
    return 0;
}

bool Recommender::canVisit(const Place& p, const TripRequest& req) const {
    // TODO(A2) 看 p.openMin[req.weekday]：
    // - 是 -1 就是公休，不行。
    // - 開放時間跟 [req.startMin, req.endMin] 的重疊不到 p.stayMin，也不行。
    // 畫面上不能選的景點（灰色）就是這裡回傳 false 的。
    (void)p; (void)req;
    return false;
}

vector<int> Recommender::recommend(const TripRequest& req, const Settings& s) const {
    // TODO(A2)
    // 1. 拿掉 canVisit 不行的、在 req.mustGo 裡的（已經在行程裡了）、在 req.dontGo 裡的。
    //    起點、終點也不要推薦。
    // 2. 照分數由高到低排，同分的看評分。
    // 前 s.candidateCount（30）名會拿去給 D3 當候選，這裡回傳全部就好，誰要用誰自己切。
    (void)req; (void)s;
    return {};
}
