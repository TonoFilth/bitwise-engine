#include "bitwise/core/log.h"
#include "bitwise/core/console.h"

int main(int argc, char** argv)
{
    bw::console::write_cformat("Max Channels: %lu\n", bw::log::kMaxChannels);
    bw::console::write_cformat("Max User Channels: %lu\n", bw::log::kMaxUserChannels);

    bw::log::channel_name(bw::LogChannel::eUSER, "My Channel");

    for (uint8_t i = 0; i < bw::log::kMaxChannels; ++i)
    {
        bw::console::write_cformat("%s | %s\n", bw::log::channel_name(i), bw::log::channel_enabled((uint8_t) i) ? "Enabled" : "Disabled");
    }

    BW_LOG_INFO(bw::LogChannel::eSYSTEM, "Hello");
    BW_LOG("Hello");

    return 0;
}