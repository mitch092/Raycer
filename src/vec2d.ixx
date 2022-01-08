export module vec2d;

template <class T>
export class Vec2d {
   public:
    Vec2d(T x, T y) : _x(x), _y(y) {}
    T get_x() const {
        return _x;
    }
    T get_y() const {
        return _y;
    }

   private:
    T _x;
    T _y;
};