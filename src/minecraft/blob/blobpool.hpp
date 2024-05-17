#ifndef MC_BLOBPOOL_H
#define MC_BLOBPOOL_H

#include "blob.hpp"

class BlobPool{
    protected:
        std::set<std::unique_ptr<Blob>> blobs;
        Logger* lg;
    public:
        BlobPool(std::size_t radius);
        void handleBlobs();
        void mergeBlobs();
        void divideBlob();
        ~BlobPool();
};

#endif