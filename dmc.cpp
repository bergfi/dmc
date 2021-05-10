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

#include <fstream>
#include <libfrugi/Settings.h>
#include <dmc/model.h>
#include <dmc/statespace/listener.h>
#include <dmc/modelcheckers/interface.h>
#include <dmc/modelcheckers/multicoresimple.h>
#include <dmc/modelcheckers/singlecore.h>
#include <dmc/modelcheckers/multicore_bitbetter.h>
#include <dmc/statespace/listener.h>
#include <dmc/storage/interface.h>
#include <dmc/storage/dtree.h>
#include <dmc/storage/dtree2.h>
#include <dmc/storage/stdmap.h>
#include <dmc/storage/cchm.h>
#include <dmc/storage/treedbs.h>
#include <dmc/storage/treedbsmod.h>

template<typename Storage, template <typename, typename,template<typename,typename> typename> typename ModelChecker>
void goDMCModel(Settings& settings) {
    using MC = ModelChecker<VModel<llmc::storage::StorageInterface>, Storage, llmc::statespace::DotPrinter>;

    std::ofstream f;
    f.open("out.dot", std::fstream::trunc);

    VModel<llmc::storage::StorageInterface>* model = nullptr;
    std::string modelName = settings["model"].asString();
    if(!modelName.empty()) {
        dlerror();
        auto handle = dlopen(modelName.c_str(), RTLD_NOW);
        if(char* err = dlerror()) {
            printf("Error opening model %s: %s\n", modelName.c_str(), err);
            return;
        }

        VModel<llmc::storage::StorageInterface>* (*func)() = (VModel<llmc::storage::StorageInterface>* (*)())dlsym(handle, "getModel");
        if(char* err = dlerror()) {
            printf("Error locating getModel() in model %s: %s\n", modelName.c_str(), err);
            return;
        }
        model = func();
    } else {
        std::cout << "Wrong or no model selected: " << modelName << std::endl;
    }
    if(model) {
        llmc::statespace::DotPrinter<MC, VModel<llmc::storage::StorageInterface>> printer(f);
        MC mc(model, printer);
        mc.getStorage().setSettings(settings);
        mc.setSettings(settings);
        mc.go();
    }
}

template<typename T>
struct HashCompareMurmur {
    static constexpr uint64_t hashForZero = 0x7208f7fa198a2d81ULL;
    static constexpr uint64_t seedForZero = 0xc6a4a7935bd1e995ULL*8ull;

    __attribute__((always_inline))  // he he
    bool equal( const T& j, const T& k ) const {
        return j == k;
    }

    __attribute__((always_inline))
    size_t hash( const T& k ) const {
        return MurmurHash64(&k, sizeof(T), seedForZero);
    }
};

template<template <typename, typename, template<typename,typename> typename> typename ModelChecker>
void goSelectStorage(Settings& settings) {

    if(settings["storage"].asString() == "stdmap") {
        goDMCModel<llmc::storage::StdMap, ModelChecker>(settings);
    } else if(settings["storage"].asString() == "cchm") {
        goDMCModel<llmc::storage::cchm, ModelChecker>(settings);
    } else if(settings["storage"].asString() == "treedbs_stdmap") {
        goDMCModel<llmc::storage::TreeDBSStorage<llmc::storage::StdMap>, ModelChecker>(settings);
    } else if(settings["storage"].asString() == "treedbs_cchm") {
        goDMCModel<llmc::storage::TreeDBSStorage<llmc::storage::cchm>, ModelChecker>(settings);
    } else if(settings["storage"].asString() == "treedbsmod") {
        goDMCModel<llmc::storage::TreeDBSStorageModified, ModelChecker>(settings);
    } else if(settings["storage"].asString() == "dtree") {
        goDMCModel<llmc::storage::DTreeStorage<SeparateRootSingleHashSet<HashSet128<RehasherExit, QuadLinear, HashCompareMurmur>, HashSet<RehasherExit, QuadLinear, HashCompareMurmur>>>, ModelChecker>(settings);
//	} else if(settings["storage"].asString() == "dtree2") {
//		goPINS<llmc::storage::DTree2Storage<HashSet128<RehasherExit, QuadLinear, HashCompareMurmur>,SeparateRootSingleHashSet<HashSet<RehasherExit, QuadLinear, HashCompareMurmur>>>, ModelChecker>(fileName);
    } else {
        std::cout << "Wrong or no storage selected: " << settings["storage"].asString() << std::endl;
    }
}

void go(Settings& settings) {

    if(settings["mc"].asString() == "multicore_simple") {
        goSelectStorage<MultiCoreModelCheckerSimple>(settings);
    } else if(settings["mc"].asString() == "multicore_bitbetter") {
        goSelectStorage<MultiCoreModelChecker>(settings);
    } else if(settings["mc"].asString() == "singlecore_simple") {
        goSelectStorage<SingleCoreModelChecker>(settings);
    } else {
        std::cout << "Wrong or no model checker selected: " << settings["mc"].asString() << std::endl;
    }
}

int main(int argc, char** argv) {

    Settings& settings = Settings::global();
    int c = 0;
    while ((c = getopt(argc, argv, "m:s:t:-:")) != -1) {
//	while ((c = getopt_long(argc, argv, "i:d:s:t:T:p:-:", long_options, &option_index)) != -1) {
        switch(c) {
            case 't':
                if(optarg) {
                    settings["threads"] = std::stoi(optarg);
                }
                break;
            case 'm':
                if(optarg) {
                    settings["mc"] = std::string(optarg);
                }
                break;
            case 's':
                if(optarg) {
                    settings["storage"] = std::string(optarg);
                }
                break;
            case '-':
                settings.insertKeyValue(optarg);
        }
    }

    go(settings);

}
