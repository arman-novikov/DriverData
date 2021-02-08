#include "DriverData.hpp"

DriverData::DriverData():
    onlineData_(online_data_t(ONLINE_WINDOW_SIZE)),
    onOrder_{0}
{

}

void DriverData::Update(const online_data_t& online_data,
            size_t on_order_time,
            const timestamp_t& ts)
{
    if (onlineData_.empty()) {
        onlineData_.insert(onlineData_.end(),
                           online_data.begin(), online_data.end());
        onOrder_ = on_order_time;
        timestamp_ = ts;
        return;
    }

    timestamp_t time_diff = ts - timestamp_;
    if (time_diff < 0)
        throw std::runtime_error("timestamp is outdated");

    if (time_diff == 0) {
        return; // no new data
    }

    size_t interim_diff = time_diff / INTERIM_MULTIPLIER;

    // todo: extract into a method patch_missing_data()
    // or throw an exception?
    if (online_data.size() < interim_diff) {
        // means some data is missing
        // gonna patch it with default values: OFFLINE
        size_t patch_count = interim_diff - online_data.size();
        while(patch_count--) {
            onlineData_.push_back(OFFLINE);
        }
    }

    // append data
    auto start = online_data.end() - interim_diff;
    for (auto it = start; it != online_data.end(); ++it){
        onlineData_.push_back(*it);
    }

    timestamp_ = ts;
    onOrder_ = on_order_time;
}
