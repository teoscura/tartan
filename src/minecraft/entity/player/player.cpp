#include "player.hpp"

Player::operator v2<double>(){
    return conv3d_2d(this->getXYZ());
}