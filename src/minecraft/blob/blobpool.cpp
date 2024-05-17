#include "blobpool.hpp"

BlobPool::BlobPool(std::size_t rad) : 
    lg(LoggerHandler::getLogger()){
    this->blobs.insert(std::make_unique<Blob>(rad));
}