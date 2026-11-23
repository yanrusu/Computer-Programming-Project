#pragma once
// DataStore：把 data/csv/ 裡的 CSV 讀進來，之後大家都跟它拿地點資料。
// 只負責讀檔和存放，不做任何計算，也不 cout（讀檔出錯就回傳 false）。
//
// 誰會用它：幾乎所有模組。程式一開始由 TripSession 呼叫 loadAll 讀一次。

#include <string>
#include <vector>
#include "data/types.h"

class DataStore {
public:
    // 讀所有 CSV。
    // 輸入：CSV 放在哪個資料夾，例如 "data/csv"
    // 回傳：全部讀成功是 true；有檔案打不開、或某一行格式不對，就是 false
    bool loadAll(const std::string& csvDir);

    // 拿到所有地點。地點的編號就是它在這個 vector 裡的位置
    const std::vector<Place>& places() const;

    // 用編號拿一個地點，例如 place(3) 就是第 3 個地點
    const Place& place(int id) const;

    // 用名字找地點。
    // 輸入：使用者打的字，例如 "州廳"
    // 回傳：名字裡有這幾個字的地點編號，例如台中州廳的編號
    std::vector<int> searchByName(const std::string& keyword) const;

    // 給測試用的：測試不讀 CSV，直接把手寫的地點放進來。
    // 會順便把每個地點的 id 設成它在陣列裡的位置
    void setPlaces(const std::vector<Place>& places);

private:
    std::vector<Place> places_;     // 所有地點
};
