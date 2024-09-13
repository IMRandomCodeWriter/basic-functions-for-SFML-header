
//VERSION-0.23



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
    float det(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
    {
        return v1.x * v2.x - v1.y * v2.y;
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

    bool isIntersecting(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2, sf::Vector2f& intersection)
    {
        sf::Vector2f dirP = sf::Vector2f(p2.x - p1.x, p2.y - p1.y);
        sf::Vector2f dirQ = sf::Vector2f(q2.x - q1.x, q2.y - q1.y);

        float denom = dirP.x * dirQ.y - dirP.y * dirQ.x;
        if (denom == 0) {
            return false;
        }

        sf::Vector2f deltaQ = sf::Vector2f(q1.x - p1.x, q1.y - p1.y);
        float t = (deltaQ.x * dirQ.y - deltaQ.y * dirQ.x) / denom;
        float s = (deltaQ.x * dirP.y - deltaQ.y * dirP.x) / denom;

        if (t >= 0 && t <= 1 && s >= 0 && s <= 1) {
            intersection.x = p1.x + t * dirP.x;
            intersection.y = p1.y + t * dirP.y;
            return true;
        }

        return false;
    }
    bool isIntersecting(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2) {
        sf::Vector2f dirP = sf::Vector2f(p2.x - p1.x, p2.y - p1.y);
        sf::Vector2f dirQ = sf::Vector2f(q2.x - q1.x, q2.y - q1.y);

        float denom = dirP.x * dirQ.y - dirP.y * dirQ.x;
        if (denom == 0) {
            return false;
        }

        sf::Vector2f deltaQ = sf::Vector2f(q1.x - p1.x, q1.y - p1.y);
        float t = (deltaQ.x * dirQ.y - deltaQ.y * dirQ.x) / denom;
        float s = (deltaQ.x * dirP.y - deltaQ.y * dirP.x) / denom;

        if (t >= 0 && t <= 1 && s >= 0 && s <= 1) {
            return true;
        }

        return false;
    }
    // VECTORS FUNCTIONS
#endif



#if SHAPES_FUNCTIONS_ACTIVE
    // SHAPES FUNCTIONS
    template <typename T>
    sf::Vector2<T>  realCenter(const sf::VertexArray& va)
    {
        sf::Vector2<T> mp;

        for (int i = 0; i < va.getVertexCount(); i++)
        {
            mp += va[i].position;
        }

        return mp / static_cast<float>(va.getVertexCount());
    }
    template <typename T>
    sf::Vector2<T> realCenter(const sf::Shape& shape)
    {
        sf::Vector2<T> mp;

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

    bool isRayIntersectingShape(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Shape& s, sf::Vector2f& iClose, sf::Vector2f& iFar)
    {
        sf::Vector2f pos = s.getPosition();

        iFar = p1;
        iClose.x = INFINITY;
        iClose.y = INFINITY;

        float fDist = bf::distance(p1, iFar);
        float cDist = bf::distance(p1, iClose);
        bool result = false;

        for (size_t i = 1; i < s.getPointCount(); i++)
        {
            sf::Vector2f intersection;
            bool r = bf::isIntersecting(p1, p2, s.getPoint(i) + pos, s.getPoint(i - 1) + pos, intersection);
            float iDist = bf::distance(p1, intersection);

            if (r)
            {
                result = r;
                float iDist = bf::distance(p1, intersection);
                if (cDist > iDist) { cDist = iDist; iClose = intersection; }
                if (fDist < iDist) { fDist = iDist; iFar = intersection; }
            }
        }

        sf::Vector2f intersection;
        bool r = bf::isIntersecting(p1, p2, s.getPoint(s.getPointCount()) + pos, s.getPoint(0) + pos, intersection);

        if (r)
        {
            result = r;
            float iDist = bf::distance(p1, intersection);
            if (cDist > iDist) { cDist = iDist; iClose = intersection; }
            if (fDist < iDist) { fDist = iDist; iFar = intersection; }
        }

        return r;
    }
    bool isRayIntersectingShape(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Shape& s, sf::Vector2f& intersection)
    {
        sf::Vector2f pos = s.getPosition();
        sf::Vector2f i;
        float dist = INFINITY;
        bool result = false;

        for (size_t k = 1; k < s.getPointCount(); k++)
        {
            if (bf::isIntersecting(p1, p2, s.getPoint(k) + pos, s.getPoint(k - 1) + pos, intersection))
            {
                float iDist = bf::distance(p1, i);
                if (iDist < dist) { dist = iDist; intersection = i; }
                result = true;
            }
        }

        if (bf::isIntersecting(p1, p2, s.getPoint(s.getPointCount()) + pos, s.getPoint(0) + pos, intersection))
        {
            float iDist = bf::distance(p1, i);
            if (iDist < dist) { dist = iDist; intersection = i; }
            result = true;
        }

        return result;
    }
    bool isRayIntersectingShape(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Shape& s)
    {
        sf::Vector2f pos = s.getPosition();

        for (size_t i = 1; i < s.getPointCount(); i++)
        {
            if (bf::isIntersecting(p1, p2, s.getPoint(i) + pos, s.getPoint(i - 1) + pos))
            {
                return true;
            }
        }

        return bf::isIntersecting(p1, p2, s.getPoint(s.getPointCount()), s.getPoint(0));
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
    float det(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2)
    {
        return v1.x * v2.x - v1.y * v2.y - v1.z * v2.z;
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