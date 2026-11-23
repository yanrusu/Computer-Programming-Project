#include "planner/replacer.h"
using namespace std;

Replacer::Replacer(const DataStore& data, TimelineChecker& checker, TravelOracle& travel,
                   const Recommender& rec)
    : data_(data), checker_(checker), travel_(travel), rec_(rec) {}

vector<int> Replacer::nearby(const Itinerary& it, int stopIndex,
                             const TripRequest& req, const Settings& s) {
    // TODO
    // 1. 找候選：從第 stopIndex 站過去交通 s.nearbyMin（15）分鐘內的景點，
    //    不在行程裡、也不在 req.dontGo 裡的。
    // 2. 每個候選放到第 stopIndex 站的位置，整個順序丟給 checker_.check，走得完的留下。
    // 3. 留下的照分數由高到低排。
    // 起點、終點、吃飯站不能被替換，傳進來的話直接回傳空的。
    (void)it; (void)stopIndex; (void)req; (void)s;
    return {};
}
