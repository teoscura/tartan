#include "mcserver.hpp"
#include "blob.hpp"
#include <memory>
#include <thread>

MCServer::MCServer(){
    std::unique_ptr<Blob> mother_region = std::make_unique<Blob>();
    
    //remake this so its a blobworker and decouple handling the world and chunks, and handling the logic.
    std::jthread mother_region_thr(&Blob::eventLoop, mother_region);
    this->blobs.insert(mother_region_thr);
}