#include <array>
#include <cstdint>
#include "../xstd/vector.hpp"

namespace Backend {
    using Rotation = uint8_t;
    static constexpr Rotation R_UP = 0;
    static constexpr Rotation R_RIGHT = 1;
    static constexpr Rotation R_DOWN = 2;
    static constexpr Rotation R_LEFT = 3;
    
    static constexpr uint8_t FIELD_WIDTH = 10;
    static constexpr uint8_t FIELD_HEIGHT = 20;
    static constexpr uint8_t T_COLLIDER_WID = 4;
    static constexpr uint8_t T_COLLIDER_HEIGHT = 4;
    static constexpr uint8_t T_COLLIDER_LEN = T_COLLIDER_WID * T_COLLIDER_HEIGHT;
    using TetrisCollider = std::array<bool, T_COLLIDER_LEN>;
    using Position2D = TetrisML::Vector2D<>;
    using Velocity2D = TetrisML::Vector2D<>;
    
    /**
     * @brief The body/collision type
     * 
     */
    enum BodyType {
        BLANK, I, Z, S, O, T, L, J, BORDER
    };

    /**
     * @brief Generates the body type from given seed and seed-advance function
     * The reason why we require initial seed is to allow lockless concurrency
     * given that advance is thread-safe
     * 
     * @tparam Seed seed type
     * @tparam NextSeedFunc seed advancement functor
     * @param seed the starting seed
     * @param advance the seed-advance function
     * @return constexpr BodyType the type of the body
     */
    template<typename Seed, typename NextSeedFunc>
    constexpr BodyType body_type_val(Seed seed, NextSeedFunc advance) {
        constexpr auto TYPE_COUNT = 7;
        auto last_3_bits = seed & TYPE_COUNT;
        while(last_3_bits == 0) {
            seed = advance(&seed);
            last_3_bits = seed & TYPE_COUNT;
        }
        return static_cast<BodyType>(last_3_bits);
    }
    
}
