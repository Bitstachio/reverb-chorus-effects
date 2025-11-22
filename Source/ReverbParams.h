#pragma once

struct ReverbParams {
    inline static constexpr bool REVERB_BYPASS_DEFAULT = false;

    inline static constexpr int ROOM_SIZE_DEFAULT = 50;
    inline static constexpr int ROOM_SIZE_MIN     = 0;
    inline static constexpr int ROOM_SIZE_MAX     = 100;
    inline static constexpr int ROOM_SIZE_STEP    = 1;

    inline static constexpr int DAMPING_DEFAULT = 50;
    inline static constexpr int DAMPING_MIN     = 0;
    inline static constexpr int DAMPING_MAX     = 100;
    inline static constexpr int DAMPING_STEP    = 1;

    inline static constexpr int WIDTH_DEFAULT = 100;
    inline static constexpr int WIDTH_MIN     = 0;
    inline static constexpr int WIDTH_MAX     = 100;
    inline static constexpr int WIDTH_STEP    = 1;

    inline static constexpr int WET_DEFAULT = 50;
    inline static constexpr int WET_MIN     = 0;
    inline static constexpr int WET_MAX     = 100;
    inline static constexpr int WET_STEP    = 1;

    inline static constexpr int DRY_DEFAULT = 50;
    inline static constexpr int DRY_MIN     = 0;
    inline static constexpr int DRY_MAX     = 100;
    inline static constexpr int DRY_STEP    = 1;

    inline static constexpr bool FREEZE_MODE_DEFAULT = false;

    inline static constexpr float IR_LENGTH_DEFAULT = 3.0f;
    inline static constexpr float IR_LENGTH_MIN     = 0.0f;
    inline static constexpr float IR_LENGTH_MAX     = 6.0f;
    inline static constexpr float IR_LENGTH_STEP    = 0.01f;
};
