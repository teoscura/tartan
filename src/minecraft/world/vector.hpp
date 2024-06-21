//simple protos for vector functions needed in block calculations.
#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <cmath>

template<typename T>
struct v2{
    T x;
    T z;

    v2(T x, T z);
    v2();
    v2<T> operator+(v2<T> v2);
    v2<T> operator-();
    v2<T> operator-(v2<T> v2);
    v2<T> operator*(double n);
    v2<T> operator/(double n);
    v2<T> normalize();
    T norm();
    static T dotProduct(const v2<T> v1, const v2<T> v2);
};

template<typename T>
struct v3{
    T x;
    T y;
    T z;

    v3(T x,T y,T z);
    v3();
    v3<T> operator+(v3<T> v2);
    v3<T> operator-();
    v3<T> operator-(v3<T> v2);
    v3<T> operator*(double n);
    v3<T> operator/(double n);
    v3<T> normalize();
    T norm();
    static T dotProduct(const v3<T> v1, const v3<T> v2);
};

static const v2<int32_t> zero2();
static const v2<int32_t> one2();
static const v2<int32_t> left2();
static const v2<int32_t> right2();
static const v2<int32_t> forwards2();
static const v2<int32_t> backwards2();
static const v3<int32_t> zero3(); //create zero vector
static const v3<int32_t> one3(); //create vector lenght sqrt3, each component 1
static const v3<int32_t> up(); //1y
static const v3<int32_t> down(); //-1y
static const v3<int32_t> left3(); //WEST -1x
static const v3<int32_t> right3(); //EAST 1x
static const v3<int32_t> forwards3(); //SOUTH 1z
static const v3<int32_t> backwards3();

template<typename T>
v2<T>::v2(T x, T z){
   this->x = x;
   this->z = z; 
}

template<typename T>
v2<T>::v2(){
    this->x = 0;
    this->z = 0;
}

template<typename T>
v2<T> v2<T>::operator+(v2<T> v2){
    return v2(this->x+v2.x,this->z+v2.z);
}

template<typename T>
v2<T> v2<T>::operator-(){
    return v2(-this->x, -this->z);
}
template<typename T>
v2<T> v2<T>::operator-(v2<T> v2){
    return v2(this->x-v2.x, this->z-v2.z);
}

template<typename T>
v2<T> v2<T>::operator*(double n){
    return v2(this->x*n,this->z*n);
}

template<typename T>
v2<T> v2<T>::operator/(double n){
    return v2(this->x/n,this->z/n);
}

template<typename T>
v2<T> minv2(v2<T> v1, v2<T> v2){
    return v2(min(v1.x,v2.x), min(v1.z,v2.z));
}

template<typename T>
v2<T>  maxv2(const v2<T>& v1, const v2<T>& v2){
    return v2(max(v1.x,v2.x), max(v1.z,v2.z));
}

template<typename T>
double v2distancefrom(const v2<T>& v1, const v2<T>& v2){
    return sqrt(pow(v2.x-v1.x, 2.0)+pow(v2.z-v1.z, 2.0));
}

template<typename T>
T v2<T>::norm(){
    return sqrt(pow(this->x, 2.0)+pow(this->z, 2.0));
}

template<typename T>
v2<T> v2<T>::normalize(){
    auto l = this->norm();
    return v2(this->x/l, this->z/l);
}

template<typename T>
int isEqual2(const v2<T>& v1, const v2<T>& v2){
    if(v1.x==v2.x&&v1.z==v2.z){
        return 1;
    }
    return 0;
}

template<typename T>
v2<T> floorv2(const v2<T>& v){
    return v2(floor(v.x),
                floor(v.z));
}

template<typename T>
T v2<T>::dotProduct(const v2<T> v1,const v2<T> v2){
    return (v1.x*v2.x + v1.z*v2.z);
}

template<typename T>
v2<T> conv3d_2d(const v3<T>& v){
    return v2<T>(v.x,v.z);
}

template<typename T>
v3<T>::v3(T x, T y, T z){
    this->x = x;
    this->y = y;
    this->z = z;
}

template<typename T>
v3<T>::v3(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template<typename T>
v3<T> v3<T>::operator+(v3<T> v3){
    return v3(this->x+v3.x,this->y+v3.y,this->z+v3.z);
}

template<typename T>
v3<T> v3<T>::operator-(){
    return v3(-this->x, -this->y, -this->z);
}
template<typename T>
v3<T> v3<T>::operator-(v3<T> v3){
    return v3(this->x-v3.x, this->y-v3.y, this->z-v3.z);
}

template<typename T>
v3<T> v3<T>::operator*(double n){
    return v3(this->x*n,this->y*n,this->z*n);
}

template<typename T>
v3<T> v3<T>::operator/(double n){
    return v3(this->x/n, this->y/n, this->z/n);
}

template<typename T>
v3<T> minv3(const v3<T>& v1, const v3<T>& v2){
    v3<T> vector;
    vector.x = min(v1.x,v2.x);
    vector.y = min(v1.y,v2.y);
    vector.z = min(v1.z,v2.z);
    return vector;
}

template<typename T>
v3<T> maxv3(const v3<T>& v1, const v3<T>& v2){
    v3<T> vector;
    vector.x = max(v1.x,v2.x);
    vector.y = max(v1.y,v2.y);
    vector.z = max(v1.z,v2.z);
    return vector;
}

template<typename T>
v3<T> conv2d_3d(const v2<T>& v){
    return createv3(v.x, 0, v.z);
}

template<typename T>
double v3distancefrom(const v3<T>& v1, const v3<T>& point){
    return sqrt(pow(v1.x-point.x, 2.0)+
                pow(v1.y-point.y, 2.0)+
                pow(v1.z-point.z, 2.0));
}

template<typename T>
int isEqual3(const v3<T>& v1, const v3<T>& v2){
    if(v1.x==v2.x&&v1.y==v2.y&&v1.z==v2.z){
        return 1;
    }
    return 0;
}

template<typename T>
v3<T> floorv3(const v3<T>& v){
    return createv3(floor(v.x),
                    floor(v.y),
                    floor(v.z));
}

template<typename T>
T v3<T>::norm(){
    return sqrt(pow(this->x, 2.0)+pow(this->y, 2.0)+pow(this->z, 2.0));
}

template<typename T>
v3<T> v3<T>::normalize(){
    auto l = this->norm();
    return v3(this->x/l, this->y/l, this->z/l);
}

template<typename T>
T v3<T>::dotProduct(const v3<T> v1,const v3<T> v2){
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

#endif