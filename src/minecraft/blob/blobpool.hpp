#ifndef MC_BLOBPOOL_H
#define MC_BLOBPOOL_H


#include <cstddef>
#include <memory>

#include "../../helpers/logger.hpp"
#include "blob.hpp"

class BlobPool{
    protected:
        std::set<std::unique_ptr<Blob>> blobs;
        std::size_t radius;
        Logger* lg;
    public:
        BlobPool(std::size_t radius);    
        void handleBlobs();
        void mergeBlobs(std::unique_ptr<Blob> b1, std::unique_ptr<Blob> b2);
        void divideBlob(std::unique_ptr<Blob> b1);
        
        bool shouldSplit(std::set<v2<double>> coords);
        bool areLinked(std::set<v2<double>> a, std::set<v2<double>> b);

        ~BlobPool();
};

#endif