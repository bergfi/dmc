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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef __int128 BigStateID;
typedef uint64_t StateID;
typedef uint32_t StateSlot;

typedef uint64_t (* dmc_next_states_big_t)(void* ctx, BigStateID stateID);
typedef uint64_t (* dmc_next_states_t)(void* ctx, StateID stateID);
typedef StateID (* dmc_initial_state_t)(void* ctx);

uint64_t dmc_init(void* ctx);
uint64_t dmc_init_cb(void* ctx);

uint64_t dmc_nextstates(void* ctx, StateID stateID);
StateID dmc_initialstate(void* ctx);

StateID  dmc_insert    (void* ctx, StateSlot* data, uint32_t length, uint32_t isRoot);
StateID  dmc_insertB   (void* ctx, StateSlot* data, uint32_t lengthInBytes, uint32_t isRoot);
StateID  dmc_transition(void* ctx, StateID stateID, StateSlot* data, uint32_t length, uint32_t isRoot);
StateID  dmc_delta     (void* ctx, StateID stateID, uint32_t offset, StateSlot* data, uint32_t length, uint32_t isRoot);
StateID  dmc_deltaB    (void* ctx, StateID stateID, uint32_t offsetInBytes, StateSlot* data, uint32_t lengthInBytes, uint32_t isRoot);
uint64_t dmc_get       (void* ctx, StateID stateID, StateSlot* data, uint32_t isRoot);
uint64_t dmc_getpart   (void* ctx, StateID stateID, uint32_t offset, StateSlot* data, uint32_t length, uint32_t isRoot);
uint64_t dmc_getpartB  (void* ctx, StateID stateID, uint32_t offsetInBytes, StateSlot* data, uint32_t lengthInBytes, uint32_t isRoot);

uint64_t dmc_big_nextstates(void* ctx, BigStateID stateID);
StateID dmc_big_initialstate(void* ctx);

StateID  dmc_big_insert (void* ctx, StateSlot* data, uint32_t length, uint32_t isRoot);
StateID  dmc_big_delta  (void* ctx, BigStateID stateID, uint32_t offset, StateSlot* data, uint32_t length, uint32_t isRoot);
uint64_t dmc_big_get    (void* ctx, BigStateID stateID, StateSlot* data, uint32_t isRoot);
uint64_t dmc_big_getpart(void* ctx, BigStateID stateID, uint32_t offset, StateSlot* data, uint32_t length, uint32_t isRoot);

#ifdef __cplusplus
};
#endif
