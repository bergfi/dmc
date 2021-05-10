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

#include <atomic>
#include <iostream>
#include <ostream>
#include <shared_mutex>
#include <libfrugi/Settings.h>

using namespace libfrugi;

namespace llmc {

namespace statespace {

template<typename ModelChecker, typename Model>
class Listener {
public:

    using StateID = typename ModelChecker::StateID;

    Listener(std::ostream& out) {}

//    void init();
//
//    void finish();
//
//    void writeState(StateID const& stateID);
//
//    template<typename TransitionInfoGetter>
//    void writeTransition(StateID const& from, StateID const& to);
};

template<typename ModelChecker, typename Model>
class VoidPrinter {
public:

    using TransitionInfo = typename Model::TransitionInfo;
    using FullState = typename ModelChecker::FullState;
    using StateID = typename ModelChecker::StateID;

    VoidPrinter() {}

    VoidPrinter(std::ostream& out) {}

    void init() {}

    void finish() {}

    void writeState(Model* model, StateID const& stateID, const FullState* fsd) {}
    void writeEndState(Model* model, StateID const& stateID, const FullState* fsd) {}

    void writeTransition(StateID const& from, StateID const& to, TransitionInfo tInfo) {}

    void setSettings(Settings& settings) {}
};

template<typename ModelChecker, typename Model>
class DotPrinter {
public:
    using Context = typename ModelChecker::Context;
    using mutex_type = std::mutex;
    using updatable_lock = std::unique_lock<mutex_type>;
public:

    using TransitionInfo = typename Model::TransitionInfo;
    using StateID = typename ModelChecker::StateID;
    using FullState = typename ModelChecker::FullState;
    using StateSlot = typename ModelChecker::StateSlot;

    DotPrinter(): out(std::cerr), _writingFullState(false), _writingSubState(false) {

    }
    explicit DotPrinter(std::ostream& out): out(out), _writingFullState(false), _writingSubState(false) {

    }

    void init() {
        updatable_lock lock(mtx);
        out << "digraph somegraph {" << std::endl;
    }

    void finish() {
        updatable_lock lock(mtx);
        out << "}" << std::endl;
    }

    void writeState(Model* model, StateID const& stateID, const FullState* fsd) {
        if(!_writingSubState && fsd && !fsd->isRoot()) {
            return;
        }
        updatable_lock lock(mtx);
        out << "\ts" << stateID.getData();

        out << " [shape=record, label=\"{" << (stateID.getData() & 0xFFFFFFFFFFULL) << " (" << (stateID.getData() >> 40) << ")";
        out << "|{{state|{";
        if(_writingFullState && fsd) writeVector(out, model, fsd->getLength(), fsd->getData());
        out << "}}}";
        out << "}\"]";

        out << ";" << std::endl;
    }

    void writeEndState(Model* model, StateID const& stateID, const FullState* fsd) {}

    void writeTransition(StateID const& from, StateID const& to, TransitionInfo tInfo) {
        updatable_lock lock(mtx);
//        TransitionInfo const& t = tInfo;

        size_t start_pos = 0;
        std::string escape = "\"";
        std::string escaped = "\\\"";
        std::string str = tInfo.label;
        while((start_pos = str.find(escape, start_pos)) != std::string::npos) {
            str.replace(start_pos, escape.length(), escaped);
            start_pos += escaped.length();
        }

        out << "\ts" << from.getData() << " -> s" << to.getData();
        if(str.length() > 0) {
            out << " [label=\"" << str << "\"]";
        } else {
            out << " []";
        }
        out << ";" << std::endl;
    }

    void writeVector(std::ostream& out, Model* model, size_t length, const StateSlot* slots) {
        for(size_t i = 0; i < length; ++i) {
            if(i > 0) {
                out << "|";
            }
            out << "{" << i << "|" << slots[i] << "}";
        }
//        for(int i=0, first=1; i<lts_type_get_state_length(lts_file_get_type(file)); ++i) {
//            if(first) { first = 0; } else { fprintf(file->file, "|"); }
//            const char* name = lts_type_get_state_name(lts_file_get_type(file), i);
//            fprintf(file->file, "{%.3s|%u}", name?name:"??????" , state[i]);
//            //int typeNo = lts_type_get_state_typeno(lts_file_get_type(file), i);
//            //printChunkType(file, lts_type_get_state_name(lts_file_get_type(file), i), typeNo, state[i]);
//        }
    }

    void setSettings(Settings& settings) {
        _writingFullState = settings["listener.writestate"].isOn();
        _writingSubState = settings["listener.writesubstate"].isOn();
    }

    [[nodiscard]] bool isWritingFullState() const {
        return _writingFullState;
    }

    void setWritingFullState(bool writingFullState = true) {
        _writingFullState = writingFullState;
    }

    [[nodiscard]] bool isWritingSubState() const {
        return _writingSubState;
    }

    void setWritingSubState(bool writingSubState = true) {
        _writingSubState = writingSubState;
    }

private:
    std::ostream& out;
    mutex_type mtx;
    bool _writingFullState;
    bool _writingSubState;
};

template<typename ModelChecker, typename Model>
class StatsGatherer {
public:
    using Context = typename ModelChecker::Context;
public:

    using TransitionInfo = typename Model::TransitionInfo;
    using StateID = typename ModelChecker::StateID;
    using StateSlot = typename ModelChecker::StateSlot;
    using FullState = typename ModelChecker::FullState;

    StatsGatherer(): _states(0), _transitions(0) {
    }

    void init() {
    }

    void finish() {
    }

    void writeState(Model* model, StateID const& stateID, const FullState* fsd) {
        ++_states;
    }

    void writeTransition(StateID const& from, StateID const& to, TransitionInfo const& tInfo) {
        ++_transitions;
    }

    void writeVector(std::ostream& out, Model* model, size_t length, const StateSlot* slots) {
    }

    size_t getStates() const {
        return _states;
    }

    size_t getTransitions() const {
        return _transitions;
    }

    void setSettings(Settings& settings) {
    }

private:
    std::atomic<size_t> _states;
    std::atomic<size_t> _transitions;
};

template<typename ModelChecker, typename Model>
class DotPrinterEndOnly {
private:
    DotPrinter<ModelChecker, Model> p;
public:
    using TransitionInfo = typename Model::TransitionInfo;
    using FullState = typename ModelChecker::FullState;
    using StateID = typename ModelChecker::StateID;

    DotPrinterEndOnly() = default;

    explicit DotPrinterEndOnly(std::ostream& out): p(out) {}

    void init() {
        p.init();
    }


    void finish() {
        p.finish();
    }

    void writeState(Model* model, StateID const& stateID, const FullState* fsd) {}
    void writeEndState(Model* model, StateID const& stateID, const FullState* fsd) {
        p.writeState(model, stateID, fsd);
    }

    void writeTransition(StateID const& from, StateID const& to, TransitionInfo tInfo) {}

    void setSettings(Settings& settings) {
        p.setSettings(settings);
        p.setWritingFullState();
    }
};

} // namespace statespace

} // namespace llmc
