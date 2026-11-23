#include "session/trip_session.h"
using namespace std;

// 誰呼叫誰（教學 10 第 0-2 節）：
//
// 畫面 → TripSession.start / replan
//   ├ Recommender.recommend        推薦清單，前 30 名當候選
//   ├ ConflictChecker.check（D4）  一定要去的排得下嗎？
//   │   ├ MealPlanner.mealSlots（D2） 要放哪幾個吃飯站
//   │   └ TimelineChecker.check（D1） 每種順序走不走得完
//   │       └ TravelOracle.travel     兩站之間要多久
//   ├ 排不下 → Advisor.suggest（D5），這一輪到這裡結束
//   ├ PlanSearch.search（D3）      在那個順序中間補景點
//   │   └ 一直呼叫 TimelineChecker.check（D1）
//   ├ TravelOracle.travelDetail    每一段交通的細節
//   └ CostCalculator.fillCosts     車資、門票、餐費
//
// history_ 是一疊 RoundState，每一輪存一份完整的，
// 所以回到上一輪不用反著做，直接把最上面那份丟掉就好。

// 建構函式：照 .h 裡宣告的順序，把每個模組需要的東西交給它
TripSession::TripSession()
    : fake_(data_),
      travel_(fake_),           // 真的交通做好後，這一行改成 travel_(transit_)
      rec_(data_),
      checker_(data_, travel_),
      greedy_(data_, checker_, rec_),
      ils_(greedy_),
      search_(ils_),
      conflict_(data_, checker_, meals_),
      advisor_(data_, conflict_, rec_),
      replacer_(data_, checker_, travel_, rec_),
      timeBar_(data_) {}

bool TripSession::init(const string& csvDir) {
    // TODO 程式一開始要讀的東西。
    //
    // 這裡要做的事（照順序，哪一步失敗就回傳 false）：
    // 1. data_.loadAll(csvDir)          讀景點
    // 2. street_.load(csvDir)           讀街道
    // 3. cost_.loadFares(csvDir)        讀票價表
    // 4. transit_.build(data_, street_, cost_, csvDir)   建交通圖
    //
    // 真的交通還沒做好之前，2～4 失敗可以先不管，只看 1。
    return data_.loadAll(csvDir);
}

PlanResult TripSession::start(const TripRequest& req, const Settings& s) {
    // TODO 開始第一輪。
    //
    // 這裡要做的事：
    // 1. history_ 清空、justAdded_ 清空（換日期就是重新開始）。
    // 2. transit_.setDay(req.weekday, req.isHoliday)，transit_.setOptions(req, s)。
    // 3. draft_ 的 request、settings 設成 req、s，hasDraft_ = true。
    // 4. 剩下的跟按「執行」一樣，直接 return replan()。
    PlanResult result;
    return result;
}

void TripSession::deletePlaces(const vector<int>& ids) {
    // TODO 刪除（只改草稿）。
    //
    // 對 ids 裡的每個編號 id：
    // 1. 從 draft_.request.mustGo 拿掉（erase）。
    // 2. 放進 draft_.request.dontGo（insert）。被刪的之後不會再被推薦。
    // 3. 從 draft_.request.keptOrder 拿掉：
    //    用 for 迴圈找到它的位置 i，再 keptOrder.erase(keptOrder.begin() + i)。
    // 4. 如果在 justAdded_ 裡，也拿掉。
}

void TripSession::keepOnly(const vector<int>& ids) {
    // TODO 只留這些（只改草稿）。
    //
    // 1. 看目前行程（itinerary()）裡的每個景點站。
    // 2. 不在 ids 裡的，收集起來。
    // 3. 把收集到的交給 deletePlaces。
}

void TripSession::add(const vector<int>& ids) {
    // TODO 新增（只改草稿）。
    //
    // 對 ids 裡的每個編號：
    // 1. 放進 draft_.request.mustGo。
    // 2. 也放進 justAdded_（D5 給建議時要知道哪些是剛加的）。
    //
    // 每一輪新指定的最多 s.maxMustGo（8）個，上一輪留下的不算。
    // 超過的話畫面上就不讓勾，這裡不用再檢查。
}

void TripSession::replace(int stopIndex, int newPlaceId) {
    // TODO 替換第 stopIndex 站（只改草稿）。
    //
    // 1. 舊的那站：跟 deletePlaces 一樣當作刪除。
    // 2. 新的：放進 mustGo 和 justAdded_。
    // 3. 就近替換的話，新的要放在舊的位置：在 keptOrder 裡把舊的編號換成新的。
    //    任選替換就不用，D4 會自己決定放哪裡。
}

void TripSession::restore(int placeId) {
    // TODO 取消刪除（只改草稿）。
    // 從 draft_.request.dontGo 拿掉，它就會重新出現在推薦清單。
}

void TripSession::changeSettings(const TripRequest& req, const Settings& s) {
    // TODO 改設定（只改草稿）。
    //
    // 1. draft_.settings = s。
    // 2. draft_.request 的出發時間、結束時間、興趣、預算、可搭的交通換成 req 的。
    // 3. 日期（weekday、isHoliday）不能改，維持原本的。換日期要重新 start。
    // 4. 可搭的交通改了的話，呼叫 transit_.setOptions(req, s)。
}

PlanResult TripSession::replan() {
    // TODO 按「執行」：照草稿重新排（教學 08 第 3 節有範例）。
    //
    // 這裡要做的事：
    // 1. mc = conflict_.check(draft_.request, draft_.settings)       ← D4
    // 2. mc.ok 是 false（排不下）：
    //    result.ok = false，result.conflicts = mc.conflicts，
    //    result.suggestions = advisor_.suggest(草稿的 request, settings, mc.conflicts, justAdded_)
    //    直接回傳。草稿留著，使用者可以「返回修改」或套用建議。
    // 3. 排得下：
    //    candidates = rec_.recommend(...) 的前 settings.candidateCount 個
    //    search_.setRequest(草稿的 request, settings)
    //    it = search_.search(mc.bestOrder, candidates)                ← D3
    // 4. 每兩站之間的交通：i 從 0 到 it.stops.size() - 2，
    //    it.legs.push_back(travel_.travelDetail(第 i 站的地點, 第 i+1 站的地點, 第 i 站的離開時間))
    //    吃飯站的 placeId 是 -1：它的地點當作跟前一站一樣，前後兩段放一個 0 分鐘的空 Leg。
    // 5. cost_.fillCosts(it, data_, 草稿的 settings) 算錢。
    // 6. 這一輪行程裡的景點全部變成一定要去，下一輪才會留下：
    //    keptOrder 清空，照行程順序把每個景點站的 placeId 放進 mustGo 和 keptOrder。
    // 7. draft_.itinerary = it，history_.push_back(draft_)，justAdded_ 清空，hasDraft_ = false。
    // 8. 回傳 ok = true 和 it。
    PlanResult result;
    return result;
}

void TripSession::discardDraft() {
    // TODO 按「取消」：草稿丟掉。
    // draft_ = history_.back()（回到現在這一輪），justAdded_ 清空，hasDraft_ = false。
}

PlanResult TripSession::trim(const vector<int>& removeIds) {
    // TODO 微調的「套用」（教學 08 第 3 節有範例）。
    //
    // 1. next = history_.back()（從現在這一輪改）。
    // 2. 從 next.itinerary.stops 拿掉 removeIds 裡的景點，剩下的放進新的順序 order。
    // 3. 被拿掉的也要從 next.request 的 mustGo、keptOrder 拿掉，放進 dontGo。
    // 4. r = checker_.check(order, next.request, next.settings)，用 r.timed 當新的 stops。
    //    少一站只會讓後面提早到，所以一定走得完，不用跑 D4。
    // 5. 跟 replan 的第 4、5 步一樣補交通細節和費用。
    // 6. 全部刪光也照樣存，畫面會提示「行程裡沒有景點」。
    // 7. history_.push_back(next)，draft_ = next，回傳。
    PlanResult result;
    return result;
}

PlanResult TripSession::applySuggestion(const Suggestion& sug) {
    // TODO 套用一個建議，然後再排一次。
    //
    // 照 sug.action 改草稿：
    //   DropNew、RemoveExisting → 把 sug.places 交給 deletePlaces
    //   ExtendEnd               → draft_.request.endMin = sug.newEndMin
    //   FastPace                → draft_.settings.paceFactor = 0.75
    //   IgnoreBudget            → draft_.settings.ignoreBudget = true
    //   IgnoreMeal              → draft_.settings.ignoreMeal = true
    // 改完 return replan()。
    PlanResult result;
    return result;
}

void TripSession::backToEdit() {
    // TODO 排不下時按「返回修改」。
    // 草稿本來就還在，只要讓 hasDraft_ = true，回到重排模式就好。
}

bool TripSession::undo() {
    // TODO 回到上一輪。
    //
    // 1. history_.size() <= 1（只剩第一輪或還沒開始）就回傳 false。
    // 2. history_.pop_back()。
    // 3. draft_ = history_.back()，justAdded_ 清空，hasDraft_ = false。
    // 4. 回傳 true。
    return false;
}

const Itinerary& TripSession::itinerary() const {
    // 還沒開始排就回傳空的行程，不然回傳最上面那一輪的
    if (history_.empty()) {
        return empty_;
    }
    return history_.back().itinerary;
}

vector<int> TripSession::recommendations() const {
    // TODO 推薦清單。
    // 用草稿的 request 和 settings 呼叫 rec_.recommend，直接回傳。
    // （不在重排模式時，草稿就是現在這一輪，所以一樣用草稿）
    vector<int> answer;
    return answer;
}

vector<int> TripSession::deletedPlaces() const {
    // TODO 已刪除的景點。
    // 把 draft_.request.dontGo 裡的編號一個一個 push_back 進 vector，回傳。
    vector<int> answer;
    return answer;
}

vector<int> TripSession::replaceOptions(int stopIndex) {
    // TODO 就近替換的選項。
    // 呼叫 replacer_.nearby(itinerary(), stopIndex, 草稿的 request, 草稿的 settings)，直接回傳。
    vector<int> answer;
    return answer;
}

int TripSession::timeBarMinutes(const vector<int>& selected) const {
    // TODO 時間條。
    // 呼叫 timeBar_.estimate(itinerary(), selected, 草稿的 settings)，直接回傳。
    return 0;
}

void TripSession::exportWeb(const string& folder) const {
    // TODO 寫出網頁的資料檔。
    // web_.writePlaces(data_, folder)，再 web_.writeTrip(itinerary(), data_, folder)。
}
