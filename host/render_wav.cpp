// Offline render: 4 kicks-ish sine hits at 120 BPM to out.wav (16-bit mono, 48 kHz).
#include <cstdint>
#include <cstdio>
#include <vector>
#include "voice.h"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "out.wav";
    const float sr   = 48000.f;
    const size_t step = (size_t)(sr * 0.5f); // 120 BPM quarter notes
    std::vector<float> buf(step * 4);
    groove::Voice v;
    v.Init(sr);
    for(size_t i = 0; i < buf.size(); i++)
    {
        if(i % step == 0) v.Trigger(i / step % 2 ? 110.f : 55.f, 0.8f);
        buf[i] = v.Process();
    }
    FILE* f = std::fopen(path, "wb");
    if(!f) return 1;
    uint32_t data = (uint32_t)(buf.size() * 2), rate = (uint32_t)sr, byterate = rate * 2, riff = 36 + data, fmt = 16;
    uint16_t pcm = 1, ch = 1, align = 2, bits = 16;
    std::fwrite("RIFF", 1, 4, f); std::fwrite(&riff, 4, 1, f); std::fwrite("WAVEfmt ", 1, 8, f);
    std::fwrite(&fmt, 4, 1, f); std::fwrite(&pcm, 2, 1, f); std::fwrite(&ch, 2, 1, f);
    std::fwrite(&rate, 4, 1, f); std::fwrite(&byterate, 4, 1, f); std::fwrite(&align, 2, 1, f);
    std::fwrite(&bits, 2, 1, f); std::fwrite("data", 1, 4, f); std::fwrite(&data, 4, 1, f);
    for(float s : buf) { int16_t q = (int16_t)(s * 32767.f); std::fwrite(&q, 2, 1, f); }
    std::fclose(f);
    std::printf("wrote %s (%zu samples)\n", path, buf.size());
}
