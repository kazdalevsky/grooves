#include "voice.h"
#include <cmath>

namespace groove {

void Voice::Init(float sample_rate)
{
    sr_    = sample_rate;
    phase_ = 0.f;
    env_   = 0.f;
}

void Voice::Trigger(float freq_hz, float amp)
{
    inc_   = freq_hz / sr_;
    env_   = amp;
    phase_ = 0.f;
}

float Voice::Process()
{
    float s = std::sin(6.2831853f * phase_) * env_;
    phase_ += inc_;
    if(phase_ >= 1.f)
        phase_ -= 1.f;
    env_ *= decay_;
    return s;
}

void Voice::Render(float* out, size_t n)
{
    for(size_t i = 0; i < n; i++)
        out[i] = Process();
}

} // namespace groove
