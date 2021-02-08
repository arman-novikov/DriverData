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
        for (const auto& i: online_data)
            onlineData_.push_back(i);

        onOrder_ = on_order_time;
        timestamp_ = ts;
        return;
    }


}
