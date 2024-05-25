#include "blobpool.hpp"

#include <algorithm>
#include <memory>
#include <numeric>

#include "../../helpers/loggerhandler.hpp"

BlobPool::BlobPool(std::size_t rad) : 
    lg(LoggerHandler::getLogger()),
    radius(rad){
    this->blobs.insert(std::make_unique<Blob>(rad));
}

void BlobPool::mergeBlobs(std::unique_ptr<Blob> b1, std::unique_ptr<Blob> b2){
    auto chunks1 = b1->moveChunks();
    auto chunks2 = b2->moveChunks();
    chunks1.merge(chunks2);
    PlayerList mergedPlayers;
    mergedPlayers.merge(b1->getLocalPlayers());
    mergedPlayers.merge(b2->getLocalPlayers());
    WorldBlob tmpworld(chunks1, this->radius);
    std::unique_ptr<Blob> blob = std::make_unique<Blob>(std::move(tmpworld), mergedPlayers);
    this->blobs.insert(std::move(blob));
}

void BlobPool::divideBlob(std::unique_ptr<Blob> b1){
    //TODO figure out if blob should be divided.
}

bool BlobPool::shouldSplit(std::set<v2<double>> coords){
}

bool BlobPool::areLinked(std::set<v2<double>> a, std::set<v2<double>> b){
    // Calculating the two average points
    auto avg1 = std::accumulate(a.begin(), a.end(), v2<double>(0,0)) / a.size();
    auto avg2 = std::accumulate(b.begin(), b.end(), v2<double>(0,0)) / b.size();
    //Vector connecting two average points and normalize it to calculate dot product.
    v2<double> line=avg2-avg1;
    line = line.normalize();
    // Line starts at avg1 to avg2 first we find the vector thats furthest along that line in a
    auto tmpmax2 = *std::ranges::max_element(a, {}, [&](auto pt){return v2<double>::dotProduct(pt-avg1, line);});
    // flip the line and swap the origin to and find the furthest point for b
    auto tmpmax1 = *std::ranges::max_element(b, {}, [&](auto pt){return v2<double>::dotProduct(pt-avg2, -line);});
    return (tmpmax2-tmpmax1).norm() < 4*this->radius;
}