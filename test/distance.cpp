#include <set>

#include "../src/minecraft/world/vector.hpp"


double dist(std::set<v2<double>> a, std::set<v2<double>> b){
    //ALG 1
    double avgx1=0, avgx2=0, avgz1=0, avgz2=0;
    std::size_t sizea=a.size(), sizeb=b.size();
    //Get point average position of a
    for(v2<double> tmp : a){
        avgx1 += tmp.x/sizea;
        avgz1 +=tmp.z/sizeb;
    }
    //Get point average position of b
    for(v2<double> tmp : b){
        avgx2 +=tmp.x/sizea;
        avgz2 +=tmp.z/sizeb;
    }
    v2<double> avg1(avgx1,avgz1);
    v2<double> avg2(avgx2,avgz2);
    //Vector connecting two average points and normalize it to calculate dot product.
    v2<double> line=avg2-avg1;
    line = normalize2(line);
    v2<double> tmpmax1, tmpmax2;
    double proj, projmax;
    //Get point of a furthest along line while going towards avg2
    for(v2<double> tmp : a){
        proj = dotProduct(tmp, line);
        if(proj>=projmax){
            tmpmax2 = tmp;
        }
    }
    line = v2<double>(0,0)-line;
    projmax = 0;
    //Get point of b furthest along line while going towards avg1
    for(v2<double> tmp : b){
        proj = dotProduct(tmp, line);
        if(proj>=projmax){
            tmpmax1 = tmp;
        }
    }
    return v2distancefrom(tmpmax2, tmpmax1);
}