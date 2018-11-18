#include "Surface.h"

Surface::Surface(sf::Color &c, Material m): _colour(c), _material(m)
{
}

Surface::Surface(sf::Color & c) : Surface(c, Material(50, 0.0))
{
}
