#pragma once

struct ChorusParams {
    inline static constexpr float RATE_DEFAULT = 1.0f;
    inline static constexpr float RATE_MIN     = 0.0f;
    inline static constexpr float RATE_MAX     = 5.0f;
    inline static constexpr float RATE_STEP    = 0.01f;

    inline static constexpr float DEPTH_DEFAULT = 0.5f;
    inline static constexpr float DEPTH_MIN     = 0.0f;
    inline static constexpr float DEPTH_MAX     = 1.0f;
    inline static constexpr float DEPTH_STEP    = 0.01f;

    inline static constexpr float CENTRE_DELAY_DEFAULT = 10.0f;
    inline static constexpr float CENTRE_DELAY_MIN     = 1.0f;
    inline static constexpr float CENTRE_DELAY_MAX     = 100.0f;
    inline static constexpr float CENTRE_DELAY_STEP    = 0.1f;

    inline static constexpr float FEEDBACK_DEFAULT = 0.0f;
    inline static constexpr float FEEDBACK_MIN     = -1.0f;
    inline static constexpr float FEEDBACK_MAX     = 1.0f;
    inline static constexpr float FEEDBACK_STEP    = 0.01f;

    inline static constexpr float MIX_DEFAULT = 0.5f;
    inline static constexpr float MIX_MIN     = 0.0f;
    inline static constexpr float MIX_MAX     = 1.0f;
    inline static constexpr float MIX_STEP    = 0.01f;

    inline static constexpr bool STEREO_DEFAULT = true;

    inline static constexpr float STEREO_DIFF_DEFAULT = 0.2f;
    inline static constexpr float STEREO_DIFF_MIN     = 0.0f;
    inline static constexpr float STEREO_DIFF_MAX     = 1.0f;
    inline static constexpr float STEREO_DIFF_STEP    = 0.01f;
};
