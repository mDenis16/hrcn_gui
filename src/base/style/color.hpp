#pragma once

class c_color
{
private:
    unsigned char _r = 0;
    unsigned char _g = 0;
    unsigned char _b = 0;
    unsigned char _a = 0;

public:
    c_color() = default;
    c_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : _r(r), _g(g), _b(b), _a(a) {}
    ~c_color() = default;

    // Copy constructor
    c_color(const c_color& other)
        : _r(other._r), _g(other._g), _b(other._b), _a(other._a) {}

    // Copy assignment operator
    c_color& operator=(const c_color& other)
    {
        if (this == &other)
            return *this;
        _r = other._r;
        _g = other._g;
        _b = other._b;
        _a = other._a;
        return *this;
    }

    // Move constructor
    c_color(c_color&& other) noexcept
        : _r(other._r), _g(other._g), _b(other._b), _a(other._a)
    {
        other._r = 0;
        other._g = 0;
        other._b = 0;
        other._a = 0;
    }

    // Move assignment operator
    c_color& operator=(c_color&& other) noexcept
    {
        if (this == &other)
            return *this;
        _r = other._r;
        _g = other._g;
        _b = other._b;
        _a = other._a;
        other._r = 0;
        other._g = 0;
        other._b = 0;
        other._a = 0;
        return *this;
    }

    // Getter methods
    inline unsigned char getR() const { return _r; }
    inline unsigned char getG() const { return _g; }
    inline unsigned char getB() const { return _b; }
    inline unsigned char getA() const { return _a; }

    // Setter methods
    inline void setR(unsigned char r) { _r = r; }
    inline void setG(unsigned char g) { _g = g; }
    inline void setB(unsigned char b) { _b = b; }
    inline void setA(unsigned char a) { _a = a; }
};