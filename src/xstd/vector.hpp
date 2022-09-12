namespace TetrisML {
    template<typename NumT = double>
    class Vector2D {
    public:
        double x, y;
        bool operator==(const Vector2D<NumT>& rhs) const {
            return this->x == rhs.x && this->y == rhs.y;
        }
    };
    
}