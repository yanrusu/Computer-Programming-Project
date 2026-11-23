#include "session/trip_session.h"
using namespace std;

// 整個流程在教學 10 第 0-2 節和第 14 節。
// history_ 是一疊 RoundState，每一輪存一份完整的（快照），
// 所以回到上一輪不用反著做，直接把最上面那份丟掉就好。

TripSession::TripSession()
    : fake_(data_),
      rec_(data_),
      checker_(data_, fake_),
      greedy_(data_, checker_, rec_),
      ils_(greedy_),
      conflict_(data_, checker_, meals_),
      advisor_(data_, conflict_, rec_),
      replacer_(data_, checker_, fake_, rec_),
      timeBar_(data_) {}

bool TripSession::init(const string& csvDir) {
    // TODO(A5) 依序：data_.loadAll → street_.load → transit_.build → cost_.loadFares。
    // 哪一步失敗就回傳 false，讓畫面告訴使用者是哪裡讀不到。
    // 真的交通還沒好之前，street_ 和 transit_ 失敗可以先不管。
    return data_.loadAll(csvDir);
}

PlanResult TripSession::start(const TripRequest& req, const Settings& s) {
    // TODO(A5) 第一輪：
    // 1. history_ 清空（換日期就是重新開始）。
    // 2. 跟 replan 一樣的步驟排出行程（D4 → 排不下就 D5 → 排得下就 D3 → 交通細節 → 費用）。
    // 3. 排得下就 push_back 成第一輪。
    (void)req; (void)s;
    return {};
}

void TripSession::deletePlaces(const vector<int>& ids) {
    // TODO(A5) 草稿裡：從 mustGo 拿掉、放進 dontGo。被刪的景點之後不會再被推薦。
    (void)ids;
}

void TripSession::keepOnly(const vector<int>& ids) {
    // TODO(A5) 草稿裡：行程中不在 ids 裡的景點全部當作刪除。
    (void)ids;
}

void TripSession::add(const vector<int>& ids) {
    // TODO(A5) 草稿裡：加進 mustGo。每一輪新指定的最多 s.maxMustGo（8）個，
    // 上一輪留下的不算在裡面。超過的話畫面上就不讓勾。
    (void)ids;
}

void TripSession::replace(int stopIndex, int newPlaceId) {
    // TODO(A5) 草稿裡：舊的那站當作刪除，新的加進 mustGo。
    // 就近替換的話，新的放在舊的位置（keptOrder 裡換掉）；任選替換就讓 D4 重排順序。
    (void)stopIndex; (void)newPlaceId;
}

void TripSession::restore(int placeId) {
    // TODO(A5) 草稿裡：從 dontGo 拿掉，它就會重新出現在推薦清單。
    (void)placeId;
}

void TripSession::changeSettings(const TripRequest& req, const Settings& s) {
    // TODO(A7) 草稿裡換成新的時間和設定。日期（weekday、isHoliday）不能改，
    // 傳進來不一樣的話就照舊，換日期要重新 start。
    (void)req; (void)s;
}

PlanResult TripSession::replan() {
    // TODO(A5) 按「執行」：
    // 1. 草稿的 mustGo／dontGo 丟給 conflict_.check（D4）。
    // 2. 排不下：advisor_.suggest（D5），回傳衝突和建議。草稿留著，使用者可以返回修改。
    // 3. 排得下：candidates = rec_.recommend 的前 s.candidateCount 名，
    //    ils_.setRequest(...) 之後 ils_.search(D4 的順序, candidates)。
    // 4. 每一段交通問 travelDetail（現在是 fake_），再 cost_.fillCosts 算錢。
    // 5. 這一輪行程裡的景點全部加進 mustGo，順序記進 keptOrder（下一輪 D4 要用）。
    // 6. push_back 成新的一輪，草稿清掉。
    return {};
}

void TripSession::discardDraft() {
    // TODO(A5) 按「取消」：草稿丟掉，hasDraft_ = false。
}

PlanResult TripSession::trim(const vector<int>& removeIds) {
    // TODO(A5) 微調的「套用」：
    // - 從目前的行程拿掉那幾站，剩下的順序丟給 checker_.check（D1）重算時間。
    // - 不補新景點、不跑 D4：少一站只會讓後面提早到，一定走得完。
    // - 全部刪光也照樣存成新的一輪，畫面提示「行程裡沒有景點」。
    // - push_back 成新的一輪。
    (void)removeIds;
    return {};
}

PlanResult TripSession::applySuggestion(const Suggestion& sug) {
    // TODO(A8) 照 sug.action 改草稿（拿掉景點、延後結束、改緊湊步調、忽略預算或用餐），
    // 然後跟 replan 一樣排一次。
    (void)sug;
    return {};
}

void TripSession::backToEdit() {
    // TODO(A8) 衝突畫面按「返回修改」：什麼都不用動，草稿本來就還在，回到重排模式就好。
}

bool TripSession::undo() {
    // TODO(A5) 只剩第一輪（或還沒開始）就回傳 false；不然 pop_back，草稿也一起丟掉。
    return false;
}

const Itinerary& TripSession::itinerary() const {
    if (history_.empty()) return empty_;
    return history_.back().itinerary;
}

vector<int> TripSession::recommendations() const {
    // TODO(A5) 用目前這一輪（重排模式中就用草稿）的 request 和 settings 問 rec_.recommend。
    return {};
}

vector<int> TripSession::deletedPlaces() const {
    // TODO(A5) 目前這一輪（或草稿）的 dontGo 轉成 vector 回傳。
    return {};
}

vector<int> TripSession::replaceOptions(int stopIndex) const {
    // TODO(A9) 問 replacer_.nearby(目前的行程, stopIndex, request, settings)。
    (void)stopIndex;
    return {};
}

int TripSession::timeBarMinutes(const vector<int>& selected) const {
    // TODO(A9) 問 timeBar_.estimate(目前的行程, selected, settings)。
    (void)selected;
    return 0;
}

void TripSession::exportWeb(const string& folder) const {
    // TODO(A6) web_.writePlaces(data_, folder) 和 web_.writeTrip(itinerary(), data_, folder)。
    (void)folder;
}
