#include <dmc/modelcheckers/interface.h>
#include <dmc/dmcapi.h>

extern "C" StateID  dmc_insert(void* ctx_, StateSlot* data, uint32_t length, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    llmc::storage::StorageInterface::StateID r;
    printf("dmc_insert(%p, %p, %u, %u)\n", ctx_, data, length, isRoot); fflush(stdout);
    if(isRoot) {
        r = ctx->mc->newState(ctx, 0, length, (llmc::storage::StorageInterface::StateSlot*) data).getState();
//        r = ctx->mc->newTransition(ctx, stateID, (llmc::storage::StorageInterface::StateSlot*) data, length, TransitionInfoUnExpanded::None());
    } else {
        r = ctx->mc->newSubState(ctx, length, data);
    }
    assert(r.getData() && "0 is not a valid chunk ID");
    return r.getData();
}

extern "C" StateID  dmc_transition(void* ctx_, StateID stateID, StateSlot* data, uint32_t length, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    llmc::storage::StorageInterface::StateID r;
    printf("dmc_transition(%p, %zu, %p, %u, %u)\n", ctx_, stateID, data, length, isRoot); fflush(stdout);
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
    printf("dmc_delta(%p, %zx, %u, %p, %u, %u)\n", ctx_, stateID, offset, data, length, isRoot); fflush(stdout);
    if(isRoot) {
        r = ctx->mc->newTransition(ctx, offset, length, (llmc::storage::StorageInterface::StateSlot*) data, TransitionInfoUnExpanded::None());
    } else {
        r = ctx->mc->newSubState(ctx, stateID, offset, length, (llmc::storage::StorageInterface::StateSlot*) data);
    }
    assert(r.getData() && "0 is not a valid chunk ID");
    return r.getData();
}

extern "C" uint64_t dmc_get(void* ctx_, StateID stateID, StateSlot* data, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    printf("dmc_get(%p, %zx, %p, %u)\n", ctx_, stateID, data, isRoot); fflush(stdout);
    return ctx->mc->getState(ctx, stateID, data, isRoot);
}

extern "C" uint64_t dmc_getpart(void* ctx_, StateID stateID, uint32_t offset, StateSlot* data, uint32_t length, uint32_t isRoot) {
    auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
    printf("dmc_getpart(%p, %zx, %u, %p, %u, %u)\n", ctx_, stateID, offset, data, length, isRoot); fflush(stdout);
    return ctx->mc->getStatePartial(ctx, stateID, offset, data, length, isRoot);
}