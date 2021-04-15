#pragma once

#include <libfrugi/Settings.h>
#include <dmc/modelcheckers/interface.h>
#include <dmc/model.h>
#include <dmc/dmcapi.h>

class DMCModelBase {
public:
    DMCModelBase(void* handle): _handle(handle), _stateVectorType(nullptr) {
        _dmc_initial_state = reinterpret_cast<decltype(_dmc_initial_state)>(dlsym(_handle, "dmc_initialstate"));
        _dmc_next_states = reinterpret_cast<decltype(_dmc_next_states)>(dlsym(_handle, "dmc_nextstates"));
        assert(_dmc_initial_state);
        assert(_dmc_next_states);
    }

    ~DMCModelBase() {
        assert(0);
    }

//    void setType(lts_type_s* ltsType) {
//        std::cout << "DMCModelBase::setType()" << std::endl;
//        _ltsType = ltsType;
//        _length = ltsType->state_description.size();
//
//        for(size_t i = 0; i < ltsType->edge_label.size(); ++i) {
//            auto& label = ltsType->edge_label[i];
//            std::cout << "  - label: " << label.name << std::endl;
//            if(label.name == "action") {
//                _labelIndex = i;
//            }
//        }
//
//        auto svType = new llmc::statespace::StructType();
//
////        for(size_t i = 0; i < ltsType->edge_label.size(); ++i) {
////            auto& label = ltsType->edge_label[i];
////            svType->addField(label.name, new llmc::statespace::SingleType(label.name));
////        }
//
//        _stateVectorType = svType;
//    }

    size_t getStateLength() const { return _length; }

    void setTransitionGroups(int tgroups) {
        _tgroups = tgroups;
    }

//    void setCB_ReportTransition(TransitionCB cb) {
//        _reportTransition_cb = cb;
//    }

//    virtual int pins_chunk_put(void* ctx_, int type, chunk c) = 0;
//    virtual chunk pins_chunk_get(void* ctx_, int type, int idx) = 0;
//    virtual int pins_chunk_cam(void* ctx_, int type, int idx, int offset, char* data, int len) = 0;
//    virtual uint64_t pins_chunk_put64(void* ctx_, int type, chunk c) = 0;
//    virtual chunk pins_chunk_get64(void* ctx_, int type, uint64_t idx) = 0;
//    virtual uint64_t pins_chunk_cam64(void* ctx_, int type, uint64_t idx, int offset, int* data, int len) = 0;

//    TransitionCB getCB_ReportTransition() {
//        return _reportTransition_cb;
//    }

protected:
//    lts_type_s* _ltsType;
    int _length;
    int _tgroups;
//    next_method_grey_t _pins_getnext;
    dmc_next_states_t _dmc_next_states;
    dmc_initial_state_t _dmc_initial_state;
    void* _handle;
//    TransitionCB _reportTransition_cb;
    std::string _labelName = "action";
    size_t _labelIndex = -1;
    llmc::statespace::Type* _stateVectorType;
};

class DMCModel: public DMCModelBase, public VModel<llmc::storage::StorageInterface> {
public:

    static DMCModel* get(std::string const& filename) {
        auto handle = dlopen(filename.c_str(), RTLD_NOW);
        if(!handle) {
            fprintf(stderr, "Failed to open %s: %s\n", filename.c_str(), dlerror()); fflush(stderr);
            abort();
            return nullptr;
        }
        static int times = 0;
        times++;
        assert(times==1);
        return new DMCModel(handle);
    }

//    using TransitionInfo = typename Model::TransitionInfo;

public:

//    struct VPINSTransitionInfo: public VTransitionInfo {
//        TransitionInfo operator()(typename MODELCHECKER::Context* ctx) const {
//            return getTransitionInfo(ctx, pinsTransitionInfo);
//        }
//
//        VPINSTransitionInfo(const transition_info* pinsTransitionInfo): pinsTransitionInfo(pinsTransitionInfo) {
//        }
//
//        const transition_info* pinsTransitionInfo;
//    };

//    struct PINSTransitionInfo: public TransitionInfoUnExpanded {
//        TransitionInfo operator()(typename MODELCHECKER::Context* ctx) const {
//            return getTransitionInfo(ctx, pinsTransitionInfo);
//        }
//
//        VPINSTransitionInfo(const transition_info* pinsTransitionInfo): pinsTransitionInfo(pinsTransitionInfo) {
//        }
//
//        const transition_info* pinsTransitionInfo;
//    };

    DMCModel(void* handle): DMCModelBase(handle) {
    }

    ~DMCModel() {
    }

    size_t getStateLength() const {
        return DMCModelBase::getStateLength();
    }

    virtual size_t getNext(StateID const& s, Context* ctx, size_t tg) {
        return 0;
    }
    size_t getNextAll(StateID const& s, Context* ctx) override {
        auto r = _dmc_next_states(reinterpret_cast<void*>(ctx), s.getData());
        return r;
    }

    void init(Context* ctx) override {
    }

    size_t getInitial(Context* ctx) override {
        auto r = _dmc_initial_state(reinterpret_cast<void*>(ctx));
        return r;
    }

    static llmc::storage::StorageInterface::StateTypeID getTypeID(int type) {
        return type;
    }

//    virtual uint64_t pins_chunk_put64(void* ctx_, int type, chunk c) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//        assert(c.len && "putting chunk with length 0");
//        assert((c.len & 3) == 0 && "putting unaligned chunk");
//        auto r = ctx->mc->newSubState(ctx, (size_t)(c.len / sizeof(llmc::storage::StorageInterface::StateSlot)), (llmc::storage::StorageInterface::StateSlot*)c.data);
//        assert(r.getData() && "0 is not a valid chunk ID");
////        printf("pins_chunk_put64: %zx", r.getData());
////        if(c.data) printArray((char*)c.data, c.len);
////        printf("\n");
//        return r.getData();
//    }

//    virtual chunk pins_chunk_get64(void* ctx_, int type, uint64_t idx) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//        chunk c;
//
//        // TODO: this is deliberately getSubState because we do not care whether or not the chunk already exists
//        auto fsd = ctx->mc->getSubState(ctx, idx);
//        if(!fsd->getLength()) {
//            printf("pins_chunk_get64(%u, %zx): returning chunk with length 0\n", type, idx);
//            abort();
//        }
//        c.len = fsd->getLength() * sizeof(llmc::storage::StorageInterface::StateSlot);
//        c.data = (decltype(c.data))fsd->getData();
//        return c;
//    }

//    virtual void pins_chunk_getpartial64(void* ctx_, int type, uint64_t idx, int offset, int* data, int len) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//        size_t offset_remainder = (offset & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        size_t len_remainder = (len & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        if(offset_remainder == 0 && len_remainder == 0) {
//            ctx->mc->getSubStatePartial(ctx, idx, offset / sizeof(llmc::storage::StorageInterface::StateSlot), (StateSlot*)data, len / sizeof(llmc::storage::StorageInterface::StateSlot));
////            printf("pins_chunk_getpartial64(%u, %zx, %p, %p, %u):", type, idx, offset, data, len);
////            printArray((char*)data, len);
////            printf("\n");
//        } else {
//            pins_chunk_getpartial64_unaligned(ctx_, type, idx, offset, data, len);
////            printf("pins_chunk_getpartial64_unaligned(%u, %zx, %p, %p, %u):", type, idx, offset, data, len);
////            printArray((char*)data, len);
////            printf("\n");
//        }
//    }

//    virtual void pins_chunk_getpartial64_unaligned(void* ctx_, int type, uint64_t idx, int offset, int* data, int len) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//        size_t offset_remainder = (offset & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
////        size_t len_remainder = (len & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        size_t nrSlots = (offset_remainder + len + (sizeof(llmc::storage::StorageInterface::StateSlot) - 1)) / (sizeof(llmc::storage::StorageInterface::StateSlot));
//        StateSlot tempSlots[nrSlots];
//        ctx->mc->getSubStatePartial(ctx, idx, offset / sizeof(llmc::storage::StorageInterface::StateSlot), tempSlots, nrSlots);
//        memcpy(data, ((char*)tempSlots) + offset_remainder, len);
//    }

//    virtual uint64_t pins_chunk_cam64(void* ctx_, int type, uint64_t idx, int offset, int* data, int len) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//
//        size_t offset_remainder = (offset & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        size_t len_remainder = (len & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        if(offset_remainder == 0 && len_remainder == 0) {
////            printf("pins_chunk_cam64(%u, %zx, %u, %p, %u):", type, idx, offset, data, len);
////            if(data) printArray((char*)data, len);
//
////            char buffer[sizeof(llmc::storage::StorageInterface::Delta) + len * sizeof(StateSlot)];
//            size_t deltaOffset = offset / sizeof(llmc::storage::StorageInterface::StateSlot);
//            size_t deltaLength = len / sizeof(llmc::storage::StorageInterface::StateSlot);
//            auto s = ctx->mc->newSubState(ctx, idx, deltaOffset, deltaLength, (llmc::storage::StorageInterface::StateSlot*)data);
////            printf("-> %zx\n", s.getData());
//            return s.getData();
//        } else {
////            printf("pins_chunk_cam64_unaligned(%u, %zx, %u, %p, %u):", type, idx, offset, data, len);
////            if(data) printArray((char*)data, len);
//            auto s = pins_chunk_cam64_unaligned(ctx_, type, idx, offset, data, len);
////            printf("-> %zx\n", s);
//            return s;
//        }
//    }

//    virtual uint64_t pins_chunk_append64(void* ctx_, int type, uint64_t idx, int* data, int len) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//
//        size_t len_remainder = (len & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        if(len_remainder == 0) {
////            printf("pins_chunk_cam64(%u, %zx, %u, %p, %u):", type, idx, offset, data, len);
////            if(data) printArray((char*)data, len);
//
////            char buffer[sizeof(llmc::storage::StorageInterface::Delta) + len * sizeof(StateSlot)];
//            size_t deltaLength = len / sizeof(llmc::storage::StorageInterface::StateSlot);
//            auto s = ctx->mc->appendState(ctx, idx, deltaLength, (llmc::storage::StorageInterface::StateSlot*)data, false);
////            printf("-> %zx\n", s.getData());
//            return s.getData();
//        } else {
//            abort();
//        }
//    }

//    virtual uint64_t dmc_state_cam(void* ctx_, int offset, int* data, int len, transition_info* tinfo) {
//        TransitionInfoUnExpanded t = TransitionInfoUnExpanded::construct(tinfo);
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//
//        size_t offset_remainder = (offset & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        size_t len_remainder = (len & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        if(offset_remainder == 0 && len_remainder == 0) {
////            printf("pins_chunk_cam64(%u, %zx, %u, %p, %u):", type, idx, offset, data, len);
////            if(data) printArray((char*)data, len);
//
////            char buffer[sizeof(llmc::storage::StorageInterface::Delta) + len * sizeof(StateSlot)];
//            size_t deltaOffset = offset / sizeof(llmc::storage::StorageInterface::StateSlot);
//            size_t deltaLength = len / sizeof(llmc::storage::StorageInterface::StateSlot);
//            auto s = ctx->mc->newTransition(ctx, deltaOffset, deltaLength, (llmc::storage::StorageInterface::StateSlot*)data, t);
////            printf("-> %zx\n", s.getData());
//            return s.getData();
//        } else {
//            abort();
//        }
//    }

    void printArray(char* data, size_t len) {
        char* dataEnd = data + len;
        while(data < dataEnd) {
            printf(" %x", *data);
            data++;
        }
    }

//    virtual uint64_t pins_chunk_cam64_unaligned(void* ctx_, int type, uint64_t idx, int offset, int* data, int len) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//
//        size_t offset_remainder = (offset & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
////        size_t len_remainder = (len & (sizeof(llmc::storage::StorageInterface::StateSlot) - 1));
//        size_t nrSlots = (offset_remainder + len + (sizeof(llmc::storage::StorageInterface::StateSlot) - 1)) / (sizeof(llmc::storage::StorageInterface::StateSlot));
//        StateSlot tempSlots[nrSlots];
//        ctx->mc->getSubStatePartial(ctx, idx, offset / sizeof(llmc::storage::StorageInterface::StateSlot), tempSlots, nrSlots);
//        memcpy(((char*)tempSlots) + offset_remainder, data, len);
////        auto d = ctx->mc->newDelta(offset / sizeof(llmc::storage::StorageInterface::StateSlot), tempSlots, nrSlots);
//        auto s = ctx->mc->newSubState(ctx, idx, offset / sizeof(llmc::storage::StorageInterface::StateSlot), nrSlots, tempSlots);
////        ctx->mc->deleteDelta(d);
//        return s.getData();
//    }

//    virtual int pins_chunk_put(void* ctx_, int type, chunk c) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//        assert(c.len && "putting chunk with length 0");
//        auto r = ctx->mc->newSubState(ctx, (size_t)(c.len / sizeof(llmc::storage::StorageInterface::StateSlot)), (llmc::storage::StorageInterface::StateSlot*)c.data);
////        printf("pins_chunk_put %u:", c.len);
////        char* ch = c.data;
////        char* end = c.data + c.len;
////        while(ch < end) {
////            printf(" %02x", *ch);
////            ch++;
////        }
////        printf("\n");
//        assert(r.getData() && "0 is not a valid chunk ID");
//        return r.getData();
//    }

//    virtual chunk pins_chunk_get(void* ctx_, int type, int idx) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//        chunk c;
//        auto fsd = ctx->mc->getSubState(ctx, idx);
//        if(!fsd->getLength()) {
//            printf("pins_chunk_get %u %u returns a 0-length vector", type, idx);
//            abort();
//        }
//        c.len = fsd->getLength() * sizeof(llmc::storage::StorageInterface::StateSlot);
//        c.data = (decltype(c.data))fsd->getData();
////        printf("pins_chunk_get %u:", c.len);
////        char* ch = c.data;
////        char* end = c.data + c.len;
////        while(ch < end) {
////            printf(" %02x", *ch);
////            ch++;
////        }
////        printf("\n");
//        return c;
//    }

//    virtual int pins_chunk_cam(void* ctx_, int type, int idx, int offset, char* data, int len) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
////        auto d = ctx->mc->newDelta(offset, (llmc::storage::StorageInterface::StateSlot*)data, len / sizeof(llmc::storage::StorageInterface::StateSlot*));
//        auto s = ctx->mc->newSubState(ctx, idx, offset, len / sizeof(llmc::storage::StorageInterface::StateSlot*), (llmc::storage::StorageInterface::StateSlot*)data);
////        ctx->mc->deleteDelta(d);
//        return s.getData();
//    }

//    static void reportTransitionCB(void* ctx_, transition_info* tinfo, int* state, int* changes) {
//        auto ctx = reinterpret_cast<VContext<llmc::storage::StorageInterface>*>(ctx_);
//        TransitionInfoUnExpanded t = TransitionInfoUnExpanded::construct(tinfo);
//        ctx->mc->newTransition( ctx
//                , ((DMCModel*)ctx->model)->getStateLength()
//                , (llmc::storage::StorageInterface::StateSlot*)state
//                , t
//        );
//    }

    TransitionInfo getTransitionInfo(VContext<llmc::storage::StorageInterface>* ctx, TransitionInfoUnExpanded const& tinfo_) const override {
//        auto tinfo = tinfo_.get<transition_info*>();
//        if(tinfo && tinfo->labels) {
//            // TODO: There's some shortcuts here: labels are currently still in the PINS format, meaning 32bit.
//            // So as a shortcut, we assume the label chunkID to be in the first 2 32bit slots
//            // TODO: We also assume labels are substates, but that seems a correct assumption
//            size_t labelIndex = 0;//ctx->getModel<DMCModel>()->_labelIndex;
//            if(labelIndex < ctx->getModel<DMCModel>()->_ltsType->edge_label.size()) {
//                uint64_t idx = *(uint64_t*)tinfo->labels;
//                if(idx) {
//                    auto fsd = ctx->mc->getSubState(ctx, idx);
//                    if(fsd) {
//                        return TransitionInfo(std::string(fsd->getCharData(), fsd->getLengthInBytes()));
//                    }
//                }
//            }
//        }
        return TransitionInfo();
    }

    llmc::statespace::Type* getStateVectorType() override {
        return _stateVectorType;
    }

protected:
    typename llmc::storage::StorageInterface::StateID _initID;
};

//template<typename MODELCHECKER>
//class DMCModelCheckerWrapper {
//public:
//
//    DMCModelCheckerWrapper(MODELCHECKER* m): _m(m) {
//
//    }
//
//    int pins_chunk_put(int type, chunk c) {
//        return 0;
//    }
//    chunk pins_chunk_get(int type, int idx) {
//        return {0};
//    }
//    int pins_chunk_cam(int type, int idx, int offset, char* data, int len) {
//        return 0;
//    }
//
//    void reportTransition(void* tinfo, void* state, size_t length, void* changes) {
//        //_m->newTransition(
//    }
//
//    static void reportTransitionCB(void* s, transition_info* tinfo, int* state, int* changes) {
////        DMCModelCheckerWrapper* ss = reinterpret_cast<DMCModelCheckerWrapper*>(ctx);
////        ss->reportTransition(tinfo, state, model->getLength(), changes);
//    }
//
//protected:
//    MODELCHECKER* _m;
//};
