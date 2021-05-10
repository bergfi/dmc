/*
 * DMC - DMC Model Checker is a modular, multi-core model checker
 * Copyright © 2021 Freark van der Berg
 *
 * This file is part of DMC.
 *
 * DMC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * DMC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DMC.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

template<typename STORAGE>
class VContext;
template<typename STORAGE>
class VModel;

#include <cassert>
#include <string>
#include <dlfcn.h>

#include <dmc/statespace/statetype.h>
#include <dmc/storage/interface.h>
#include <dmc/modelcheckers/interface.h>
#include <dmc/transitioninfo.h>

class Model {
public:

//    size_t getNextAll(typename MODELCHECKERINTERFACE::StateID const& s, typename MODELCHECKERINTERFACE::Context& ctx);
//    typename ModelChecker::StateID getInitial(typename MODELCHECKERINTERFACE::Context& ctx);
//    llmc::statespace::Type* getStateVectorType();

    struct TransitionInfo {
        std::string label;

        TransitionInfo(): label("") {}
        TransitionInfo(const std::string &label) : label(label) {}
    };
};

template<typename STORAGE>
class VContext {
public:
    using StateID = llmc::storage::StorageInterface::StateID;
    using StateSlot = llmc::storage::StorageInterface::StateSlot;

public:
    VModelChecker<STORAGE>* getModelChecker() const {
        return mc;
    };
    StateID getSourceState() const {
        return sourceState;
    }

    VContext(VModelChecker<STORAGE>* mc_, VModel<STORAGE>* model): model(model), mc(mc_), sourceState(0) {}

    template<typename T>
    T* getModel() const {
        return (T*)model;
    }

    VModel<STORAGE>* getModel() const {
        return model;
    }

public:
    VModel<STORAGE>* model;
    VModelChecker<STORAGE>* mc;
    StateID sourceState;
};

template<typename STORAGE, typename MODELCHECKER=VModelChecker<STORAGE>>
class VContextImpl: public VContext<STORAGE> {
public:
    VContextImpl(VModelChecker<STORAGE>* mc_, VModel<STORAGE>* model): VContext<STORAGE>(mc_, model) {}
    MODELCHECKER* getModelChecker() const {
        return static_cast<MODELCHECKER*>(this->mc);
    };
};


template<typename STORAGE>
class VModel: public Model {
public:

    struct TransitionInfo {
        std::string label;

        TransitionInfo(): label("") {}
        TransitionInfo(const std::string &label) : label(label) {}
    };

    using StateID = typename STORAGE::StateID;
    using StateSlot = typename STORAGE::StateSlot;
//    using Context = ContextBase<VModel<MODELCHECKERINTERFACE>>;
    using Context = VContext<STORAGE>;

    virtual void init(Context* ctx) = 0;

    virtual size_t getNext(StateID const& s, Context* ctx, size_t tg) = 0;
    virtual size_t getNextAll(StateID const& s, Context* ctx) = 0;
    virtual size_t getInitial(Context* ctx) = 0;
    virtual llmc::statespace::Type* getStateVectorType() = 0;
    virtual TransitionInfo getTransitionInfo(VContext<llmc::storage::StorageInterface>* ctx, TransitionInfoUnExpanded const& tinfo_) const = 0;
    virtual size_t getStateLength() const = 0;
};