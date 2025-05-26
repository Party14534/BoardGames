#include "hashFunction.h"

std::size_t Vector2iHash::operator()(const sf::Vector2i& v) const {
    return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
}
