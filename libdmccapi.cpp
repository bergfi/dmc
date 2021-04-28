#include <dmc/modelcheckers/interface.h>
#include <dmc/dmcapi.h>

extern "C" StateID  dmc_insert(void* ctx_, StateSlot* data, uint32_t length, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    llmc::storage::StorageInterface::StateID r;
//    printf("dmc_insert(%p, %p, %u, %u)\n", ctx_, data, length, isRoot); fflush(stdout);
    if(isRoot) {
        r = ctx->mc->newState(ctx, 0, length, (llmc::storage::StorageInterface::StateSlot*) data).getState();
//        r = ctx->mc->newTransition(ctx, stateID, (llmc::storage::StorageInterface::StateSlot*) data, length, TransitionInfoUnExpanded::None());
    } else {
        r = ctx->mc->newSubState(ctx, length, data);
    }
    assert(r.getData() && "0 is not a valid chunk ID");
    return r.getData();
}

extern "C" StateID  dmc_insertB(void* ctx_, StateSlot* data, uint32_t lengthInBytes, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    llmc::storage::StorageInterface::StateID r;
    //    printf("dmc_insertB(%p, %p, %u, %u)\n", ctx_, data, length, isRoot); fflush(stdout);

    size_t len_remainder = (lengthInBytes & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
    size_t length = lengthInBytes / sizeof(llmc::storage::StorageInterface::StateSlot);

    if(len_remainder == 0) {
        if(isRoot) {
            r = ctx->mc->newState(ctx, 0, length, (llmc::storage::StorageInterface::StateSlot*) data).getState();
        } else {
            r = ctx->mc->newSubState(ctx, length, data);
        }
    } else {
        StateSlot tempSlots[length+1];
        tempSlots[length] = 0;
        memcpy(tempSlots, data, lengthInBytes);
        if(isRoot) {
            r = ctx->mc->newState(ctx, 0, length, tempSlots).getState();
        } else {
            r = ctx->mc->newSubState(ctx, length, tempSlots);
        }
    }
    assert(r.getData() && "0 is not a valid chunk ID");
    return r.getData();
}

extern "C" StateID  dmc_transition(void* ctx_, StateID stateID, StateSlot* data, uint32_t length, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    llmc::storage::StorageInterface::StateID r;
//    printf("dmc_transition(%p, %zu, %p, %u, %u)\n", ctx_, stateID, data, length, isRoot); fflush(stdout);
    if(isRoot) {
        r = ctx->mc->newTransition(ctx, stateID, (llmc::storage::StorageInterface::StateSlot*) data, length, TransitionInfoUnExpanded::None());
    } else {
        r = ctx->mc->newSubState(ctx, length, data);
    }
    assert(r.getData() && "0 is not a valid chunk ID");
    return r.getData();
}

extern "C" StateID  dmc_delta(void* ctx_, StateID stateID, uint32_t offset, StateSlot* data, uint32_t length, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    llmc::storage::StorageInterface::StateID r;
//    printf("dmc_delta(%p, %zx, %u, %p, %u, %u)\n", ctx_, stateID, offset, data, length, isRoot); fflush(stdout);
    if(isRoot) {
        r = ctx->mc->newTransition(ctx, offset, length, (llmc::storage::StorageInterface::StateSlot*) data, TransitionInfoUnExpanded::None());
    } else {
        r = ctx->mc->newSubState(ctx, stateID, offset, length, (llmc::storage::StorageInterface::StateSlot*) data);
    }
    assert(r.getData() && "0 is not a valid chunk ID");
    return r.getData();
}

extern "C" StateID  dmc_deltaB(void* ctx_, StateID stateID, uint32_t offsetInBytes, StateSlot* data, uint32_t lengthInBytes, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    llmc::storage::StorageInterface::StateID r;
//    printf("dmc_deltaB(%p, %zx, %u, %p, %u, %u)\n", ctx_, stateID, offset, data, length, isRoot); fflush(stdout);

    size_t offset_remainder = (offsetInBytes & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
    size_t len_remainder = (lengthInBytes & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));

    size_t offset = offsetInBytes / sizeof(llmc::storage::StorageInterface::StateSlot);

    if(offset_remainder == 0 && len_remainder == 0) {
        size_t length = lengthInBytes / sizeof(llmc::storage::StorageInterface::StateSlot);
        if(isRoot) {
            r = ctx->mc->newTransition( ctx
                                      , offset
                                      , length
                                      , (llmc::storage::StorageInterface::StateSlot*) data
                                      , TransitionInfoUnExpanded::None()
                                      );
        } else {
            r = ctx->mc->newSubState( ctx
                                    , stateID
                                    , offset
                                    , length
                                    , (llmc::storage::StorageInterface::StateSlot*) data
                                    );
        }
    } else {
        size_t nrSlots = (offset_remainder + lengthInBytes + (sizeof(llmc::storage::StorageInterface::StateSlot) - 1)) / (sizeof(llmc::storage::StorageInterface::StateSlot));
        StateSlot tempSlots[nrSlots];
        ctx->mc->getStatePartial(ctx, stateID, offset, tempSlots, nrSlots, isRoot);
        memcpy(((char*)tempSlots) + offset_remainder, data, lengthInBytes);
        if(isRoot) {
            r = ctx->mc->newTransition(ctx, offset, nrSlots, tempSlots, TransitionInfoUnExpanded::None());
        } else {
            r = ctx->mc->newSubState(ctx, stateID, offset, nrSlots, tempSlots);
        }
    }
    assert(r.getData() && "0 is not a valid chunk ID");
    return r.getData();
}

extern "C" uint64_t dmc_get(void* ctx_, StateID stateID, StateSlot* data, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//    printf("dmc_get(%p, %zx, %p, %u)\n", ctx_, stateID, data, isRoot); fflush(stdout);
    return ctx->mc->getState(ctx, stateID, data, isRoot);
}

extern "C" uint64_t dmc_getpart(void* ctx_, StateID stateID, uint32_t offset, StateSlot* data, uint32_t length, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//    printf("dmc_getpart(%p, %zx, %u, %p, %u, %u)\n", ctx_, stateID, offset, data, length, isRoot); fflush(stdout);
    return ctx->mc->getStatePartial(ctx, stateID, offset, data, length, isRoot);
}

extern "C" uint64_t dmc_getpartB(void* ctx_, StateID stateID, uint32_t offsetInBytes, StateSlot* data, uint32_t lengthInBytes, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//    printf("dmc_getpart(%p, %zx, %u, %p, %u, %u)\n", ctx_, stateID, offset, data, length, isRoot); fflush(stdout);
    size_t offset_remainder = (offsetInBytes & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
    size_t len_remainder = (lengthInBytes & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));

    size_t offset = offsetInBytes / sizeof(llmc::storage::StorageInterface::StateSlot);
    if(offset_remainder == 0 && len_remainder == 0) {
        size_t length = lengthInBytes / sizeof(llmc::storage::StorageInterface::StateSlot);
        return ctx->mc->getStatePartial(ctx, stateID, offset, data, length, isRoot);
    } else {
        size_t nrSlots = (offset_remainder + lengthInBytes + (sizeof(llmc::storage::StorageInterface::StateSlot) - 1)) / (sizeof(llmc::storage::StorageInterface::StateSlot));
        StateSlot tempSlots[nrSlots];
        auto r = ctx->mc->getStatePartial(ctx, stateID, offset, tempSlots, nrSlots, isRoot);
        memcpy(data, ((char*)tempSlots) + offset_remainder, lengthInBytes);
        return r;
    }
}
