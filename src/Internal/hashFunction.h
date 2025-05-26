#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <functional>

struct Vector2iHash {
    std::size_t operator()(const sf::Vector2i& v) const;
};

#endif
