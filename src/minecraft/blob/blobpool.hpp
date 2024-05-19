#ifndef MC_BLOBPOOL_H
#define MC_BLOBPOOL_H

#include "blob.hpp"
#include <cstddef>

class BlobPool{
    protected:
        std::set<std::unique_ptr<Blob>> blobs;
        std::size_t radius;
        Logger* lg;
    public:
        BlobPool(std::size_t radius);    
        void handleBlobs();
        void mergeBlobs();
        void divideBlob();
        
        bool areLinked(std::set<v2<double>> a, std::set<v2<double>> b);

        ~BlobPool();
};

#endif