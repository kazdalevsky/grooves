#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <cmath>
#include <vector>
#include "daisysp.h"
#include "voice.h"

TEST_CASE("voice is silent until triggered")
{
    groove::Voice v;
    v.Init(48000.f);
    CHECK(v.Process() == doctest::Approx(0.f));
}

TEST_CASE("voice decays and stays bounded")
{
    groove::Voice v;
    v.Init(48000.f);
    v.Trigger(110.f, 0.8f);
    std::vector<float> buf(48000);
    v.Render(buf.data(), buf.size());
    float peak_start = 0.f, peak_end = 0.f;
    for(size_t i = 0; i < 480; i++) peak_start = std::fmax(peak_start, std::fabs(buf[i]));
    for(size_t i = buf.size() - 480; i < buf.size(); i++) peak_end = std::fmax(peak_end, std::fabs(buf[i]));
    CHECK(peak_start <= 0.8f);
    CHECK(peak_end < peak_start);
}

TEST_CASE("DaisySP oscillator links and runs on host")
{
    daisysp::Oscillator osc;
    osc.Init(48000.f);
    osc.SetFreq(440.f);
    float peak = 0.f;
    for(int i = 0; i < 480; i++) peak = std::fmax(peak, std::fabs(osc.Process()));
    CHECK(peak > 0.4f);
}
