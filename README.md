# DMC Model Checker

DMC Model Checker is a modular multi-threaded model checker with a model-agnostic model interface, the DMC API. Models can implement this API such that DMC can model check them. The modules that DMC consists of are:
- a search core
- a state storage component
- a state printer

Currently, DMC employs two simple breadth-first search cores, without sophisticated work-stealing. One search core is single-core, which is used as reference; the other is multi-core, used for performance.

The state storage component stores states. For this, a number of options are available:
- [dtree](https://github.com/bergfi/dtree), concurrent compression tree of DMC [1]
- [treedbs](https://github.com/utwente-fmt/ltsmin/blob/master/src/mc-lib/treedbs-ll.c), concurrent compression tree of [LTSmin](https://ltsmin.utwente.nl) [2]  
- [cchm](https://github.com/bergfi/hashmap), a concurrent chaining hash map [3]
- [stdmap](https://www.cplusplus.com/reference/unordered_map/unordered_map/), `std::unordered_map`

The state printer is one of:
- *VoidPrinter* that does not print anything, for performance
- *DotPrinter* that prints the state space to a .dot file

# Dependencies

DMC depends on:
- [dtree](https://github.com/bergfi/dtree), a state compression dtree [1]
- [libfrugi](https://github.com/bergfi/libfrugi), a general-purpose library

Dependencies are downloaded during configuration unless specified otherwise.

# Build

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j 4
```
To use the dependencies of DMC at specific location, use 

```
cmake .. -DFETCHCONTENT_SOURCE_DIR_DTREE=/path/to/dtree -DFETCHCONTENT_SOURCE_DIR_LIBFRUGI=/path/to/libfrugi
```

# Usage

Primary usage of DMC is embedding into a larger project. The command line usage needs to be looked at. Some common options are:
- `-m SEARCHCORE`, where `SEARCHCORE` can be any of `singlecore_simple` or `multicore_bitbetter`
- `-s STATESTORAGE`, where `STATESTORAGE` can be any of `dtree`, `treedbsmod`, `treedbs_cchm`, `cchm` or `stdmap`
- `--threads N`, where `N` is the number of model-checking threads to use
- the positional argument is a filename of a shared object implementing the DMC API.

The tests in `/tests/unit`:
- `storage_test` tests the state storage components by directly interfacing with them, without DMC in between
- `model_test` invokes combinations of search cores and state storages on a number of models

Furthermore, `/tests/performance` contains a number of performance tests which can be invoked as if invoking `dmc`, but without positional argument.

References:
- [1] van der Berg, F. I. (2021) Recursive Variable-Length State Compression for Multi-Core Software Model Checking. 2021 NASA Formal Methods. Preprint.
- [2] Laarman, A., van de Pol, J. C., & Weber, M. (2011). Parallel Recursive State Compression for Free. ArXiv. http://arxiv.org/abs/1104.3119
- [3] van der Berg, F. I., & van de Pol, J. (2019). Concurrent chaining hash maps for software model checking. In C. Barrett, & J. Yang (Eds.), 2019 Formal Methods in Computer Aided Design (FMCAD) (pp. 46-54). [8894279] (Proceedings of the Conference on Formal Methods in Computer-Aided Design (FMCAD); Vol. 2019). IEEE. https://doi.org/10.23919/FMCAD.2019.8894279

# License

DMC - DMC Model Checker is a modular, multi-core model checker
Copyright © 2021 Freark van der Berg

DMC is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

DMC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DMC; see COPYING.  If not, see <https://www.gnu.org/licenses/>.