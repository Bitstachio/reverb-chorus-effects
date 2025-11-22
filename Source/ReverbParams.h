#pragma once

struct ReverbParams {
    inline static constexpr float ROOM_SIZE_DEFAULT = 0.5f;
    inline static constexpr float ROOM_SIZE_MIN     = 0.0f;
    inline static constexpr float ROOM_SIZE_MAX     = 1.0f;
    inline static constexpr float ROOM_SIZE_STEP    = 0.01f;

    inline static constexpr float DAMPING_DEFAULT = 0.5f;
    inline static constexpr float DAMPING_MIN     = 0.0f;
    inline static constexpr float DAMPING_MAX     = 1.0f;
    inline static constexpr float DAMPING_STEP    = 0.01f;

    inline static constexpr float WIDTH_DEFAULT = 1.0f;
    inline static constexpr float WIDTH_MIN     = 0.0f;
    inline static constexpr float WIDTH_MAX     = 1.0f;
    inline static constexpr float WIDTH_STEP    = 0.01f;

    inline static constexpr float WET_DEFAULT = 0.5f;
    inline static constexpr float WET_MIN     = 0.0f;
    inline static constexpr float WET_MAX     = 1.0f;
    inline static constexpr float WET_STEP    = 0.01f;

    inline static constexpr float DRY_DEFAULT = 0.5f;
    inline static constexpr float DRY_MIN     = 0.0f;
    inline static constexpr float DRY_MAX     = 1.0f;
    inline static constexpr float DRY_STEP    = 0.01f;

    inline static constexpr bool FREEZE_MODE_DEFAULT = false;

    inline static constexpr float IR_LENGTH_DEFAULT = 3.0f;
    inline static constexpr float IR_LENGTH_MIN     = 0.0f;
    inline static constexpr float IR_LENGTH_MAX     = 6.0f;
    inline static constexpr float IR_LENGTH_STEP    = 0.01f;
};
