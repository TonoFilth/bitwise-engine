#include <bitwise/core.h>

int main(int argc, char** argv)
{
    bw::initialize();

    for (int i = 0; i < bw::log::kMaxChannels; ++i)
    {
        bw::console::write_format("Channel %d | %s\n", i, bw::log::channel_enabled((uint8_t) i) ? "Enabled" : "Disabled");
    }

    BW_LOG_INFO(bw::LogChannel::eSYSTEM, "Hello");
    BW_LOG("Hello");

    bw::shutdown();

    return 0;
}