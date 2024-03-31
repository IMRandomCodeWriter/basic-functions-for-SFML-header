


//SETTINGS
#define ACTIVE 1 // in which case will you really change that?
#define VECTOR2_FUNCTIONS_ACTIVE 1 // defines will functions for sf::Vector3 implemented or not, by default is 1
#define SHAPES_FUNCTIONS_ACTIVE 1 // defines will functions for sf::Vector3 implemented or not, by default is 1
#define VECTOR3_FUNCTIONS_ACTIVE 1 // defines will functions for sf::Vector3 implemented or not, by default is 1
#define QUICK_BF_ACTIVE 0 //defines will quick basic functions implemented or not, by default 0
//SETTINGS



#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#if ACTIVE

// VECTOR2 OPERATORS
template <typename T>
sf::Vector2<T> operator / (const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
{
    return sf::Vector2<T>(v1.x / v2.x, v1.y / v2.y);
}
template <typename T>
sf::Vector2<T> operator * (const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
{
    return sf::Vector2<T>(v1.x * v2.x, v1.y * v2.y);
}
template <typename T>
sf::Vector2<T> operator % (const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
{
    return sf::Vector2<T>(static_cast<int>(v1.x) % static_cast<int>(v2.x), static_cast<int>(v1.y) % static_cast<int>(v2.y));
}
// VECTOR2 OPERATORS

// VECTOR3 OPERATORS
template <typename T>
sf::Vector3<T> operator / (sf::Vector3<T> v1, sf::Vector3<T> v2)
{
    return sf::Vector3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}
template <typename T>
sf::Vector3<T> operator * (sf::Vector3<T> v1, sf::Vector3<T> v2)
{
    return sf::Vector3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
template <typename T>
sf::Vector3<T> operator % (sf::Vector3<T> v1, sf::Vector3<T> v2)
{
    return sf::Vector3<T>(static_cast<int>(v1.x) % static_cast<int>(v2.x), static_cast<int>(v1.y) % static_cast<int>(v2.y), static_cast<int>(v1.z) % static_cast<int>(v2.z));
}
// VECTOR3 OPERATORS

namespace bf
{
#if VECTOR2_FUNCTIONS_ACTIVE
    // VECTORS FUNCTIONS
    template <typename T>
    float distance(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
    {
        return std::sqrt(std::pow(v2.x - v1.x, 2) + std::pow(v2.y - v1.y, 2));
    }

    template <typename T>
    float  magnitude(const sf::Vector2<T>& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    template <typename T>
    sf::Vector2<T>  normalize(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
    {
        return (v1 - v2) / distance(v1, v2);
    }

    template <typename T>
    sf::Vector2<T>  normalize(const sf::Vector2<T>& vector)
    {
        float mag = magnitude(vector);

        if (mag != 0)
        {
            return sf::Vector2<T>(vector.x / mag, vector.y / mag);
        }
        return sf::Vector2<T>(0, 0);
    }

    template <typename T>
    float dot(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template <typename T>
    float angle(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
    {
        if (v1 != sf::Vector2<T>(0, 0) && v2 != sf::Vector2<T>(0, 0))
        {
            return acosf(bf::dot(v1, v2) / (bf::magnitude(v1) * bf::magnitude(v2)));
        }

        return 0.0f;
    }
    // VECTORS FUNCTIONS
#endif



#if SHAPES_FUNCTIONS_ACTIVE
    // SHAPES FUNCTIONS
    sf::Vector2f realCenter(const sf::VertexArray& va)
    {
        sf::Vector2f mp;

        for (int i = 0; i < va.getVertexCount(); i++)
        {
            mp += va[i].position;
        }

        return mp / static_cast<float>(va.getVertexCount());
    }
    sf::Vector2f realCenter(const sf::Shape& shape)
    {
        sf::Vector2f mp;

        for (int i = 0; i < shape.getPointCount(); i++)
        {
            mp += shape.getPoint(i);
        }

        return mp / static_cast<float>(shape.getPointCount());
    }

    void centerOrigin(sf::RectangleShape& rs)
    {
        sf::FloatRect fr = rs.getGlobalBounds();
        rs.setOrigin(fr.width / 2.f, fr.height / 2.f);
    }
    void centerOrigin(sf::CircleShape& cs)
    {
        float cr = cs.getRadius();
        cs.setOrigin(cr / 2.f, cr / 2.f);
    }
    
    bool isCollide(sf::RectangleShape rs1, sf::RectangleShape rs2)
    {
        return rs1.getGlobalBounds().intersects(rs2.getGlobalBounds());
    }
    bool isCollide(sf::RectangleShape rs, sf::CircleShape cs)
    {
        sf::Vector2f distance;

        distance.x = fabs(cs.getPosition().x - rs.getPosition().x);
        distance.y = fabs(cs.getPosition().y - rs.getPosition().y);

        if (distance.x > (rs.getSize().x / 2 + cs.getRadius())) { return false; }
        if (distance.y > (rs.getSize().y / 2 + cs.getRadius())) { return false; }
        if (distance.x <= (rs.getSize().x / 2)) { return true; }
        if (distance.y <= (rs.getSize().y / 2)) { return true; }

        float cDist_sq = pow((distance.x - rs.getSize().x / 2), 2) + pow((distance.y - rs.getSize().y / 2), 2);
        return (cDist_sq <= pow(cs.getRadius(), 2));
    }
    bool isCollide(sf::CircleShape cs1, sf::CircleShape cs2)
    {
        return bf::distance(cs1.getPosition(), cs2.getPosition()) <= cs1.getRadius() + cs2.getRadius();
    }

    bool contains(const sf::Shape& polygon, const sf::Vector2f point) {
        int c = 0;
        int n = polygon.getPointCount();

        for (int i = 0, j = n - 1; i < n; j = i++) {
            if (((polygon.getPoint(i).y > point.y) != (polygon.getPoint(j).y > point.y)) && (point.x < (polygon.getPoint(j).x - polygon.getPoint(i).x) * (point.y - polygon.getPoint(i).y) / (polygon.getPoint(j).y - polygon.getPoint(i).y) + polygon.getPoint(i).x))
            {
                c++;
            }
        }

        return c % 2 == 1;
    }
    bool uni_isCollide(const sf::Shape& s1, const sf::Shape& s2) // universal collide function, works slower, and may not work properly with circles
    {
        for (int i = 0; i < s1.getPointCount(); i++)
        {
            if (bf::contains(s2, s1.getPoint(i)))
            {
                return true;
            }
        }
        return false;
    }
    // SHAPES FUNCTIONS
#endif

#if VECTOR3_FUNCTIONS_ACTIVE
    // 3D VECTOR FUNCTIONS
    template <typename T>
    float distance(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2)
    {
        return std::sqrtf(std::powf(v2.x - v1.x, 2) + std::powf(v2.y - v1.y, 2) + std::powf(v2.z - v1.z, 2));
    }

    template <typename T>
    float magnitude(const sf::Vector3<T>& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    template <typename T>
    sf::Vector3<T> normalize(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2)
    {
        return (v1 - v2) / bf::distance(v1, v2);
    }
    template <typename T>
    sf::Vector3<T> normalize(const sf::Vector3<T>& vector)
    {
        float magnitude = bf::magnitude(vector);

        if (magnitude != 0)
        {
            return sf::Vector3<T>(vector.x / magnitude, vector.y / magnitude, vector.z / magnitude);
        }
        return sf::Vector3<T>(0, 0, 0);
    }

    template <typename T>
    float dot(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template <typename T>
    sf::Vector3<T> cross(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2)
    {
        return sf::Vector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }
    // 3D VECTOR FUNCTIONS
#endif 

}

#if QUICK_BF_ACTIVE
//quick basic functions, at the moment it consists of only 1 function
float bf_quick_distance(const sf::Vector2f& v1, const sf::Vector2f& v2) //use if you dont need precision, in most cases makes no sense, so its disabled by default
{
    return std::powf(v2.x - v1.x, 2) + std::powf(v2.y - v1.y, 2);
}
#endif

#endif