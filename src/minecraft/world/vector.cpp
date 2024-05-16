#include "vector.hpp"

static const v2<int32_t> zero2(){
    return v2(0,0);
}

static const v2<int32_t> one2(){
    return v2(1,
                    1);
}

static const v2<int32_t> forwards2(){
    return v2(0,
                    1);
}

static const v2<int32_t> backwards2(){
    return v2( 0,
                    -1);
}

static const v2<int32_t> right2(){
    return v2(1,
                    0);
}

static const v2<int32_t> left2(){
    return v2(-1,
                     0);
}

static const v3<int32_t> zero3(){
    return v3(0, 0, 0);
}

static const v3<int32_t> one3(){
    return v3(1, 1, 1);
}

static const v3<int32_t> up(){ // 1y
    return v3(0, 1, 0);
}

static const v3<int32_t> down(){
    return v3(0, -1, 0);
}

static const v3<int32_t> left3(){ //WEST 
    return v3(-1, 0, 0);
}

static const v3<int32_t> right3(){  //EAST 1x
    return v3(1, 0, 0);
}

static const v3<int32_t> forwards3(){ //SOUTH 1z
    return v3(0, 0, 1);
}

static const v3<int32_t> backwards3(){ //NORTH 
    return v3(0, 0, -1);
}