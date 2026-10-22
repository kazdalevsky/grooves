#pragma once
#include <cstddef>

namespace groove {

// Simple sine voice with exponential decay. No allocation, safe for audio callback.
class Voice
{
  public:
    void Init(float sample_rate);
    void Trigger(float freq_hz, float amp);
    float Process();
    void  Render(float* out, size_t n);

  private:
    float sr_    = 48000.f;
    float phase_ = 0.f;
    float inc_   = 0.f;
    float env_   = 0.f;
    float decay_ = 0.9995f;
};

} // namespace groove
