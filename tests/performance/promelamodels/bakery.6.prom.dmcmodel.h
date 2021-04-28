/** Generated DMC model - bakery.6.prom
 * State size:  20 elements (80 bytes)
 * Transitions: 32
 */

#define EXPECT_FALSE(e) __builtin_expect(e, 0)

#define EXPECT_TRUE(e) __builtin_expect(e, 1)
#ifdef DNDEBUG
#define model_assert(e,...)    ((void)0);
#else
#define model_assert(e,...) \
    if (EXPECT_FALSE(!(e))) {\
        char buf[4096];\
        if (#__VA_ARGS__[0])\
            snprintf(buf, 4096, ": " __VA_ARGS__);\
        else\
            buf[0] = '\0';\
        printf("assertion \"%s\" failed%s", #e, buf);\
        exit(-1);\
    }
#endif
#include <dmc/model.h>
#include <dmc/modelcheckers/interface.h>
#include "../StateIdentifier.h"
using StateSlot = llmc::storage::StorageInterface::StateSlot;
using ModelStateIdentifier = StateIdentifier<StateSlot>;
typedef uint64_t MemOffset;

class DMCModelbakery___prom: public VModel<llmc::storage::StorageInterface>
{
public:
	typedef union sj_uint1 {
		int pad;
		unsigned int var:1;
	} sj_uint1;
	
	typedef union sj_int8 {
		int pad;
		char var;
	} sj_int8;
	
	typedef union sj_int16 {
		int pad;
		short var;
	} sj_int16;
	
	typedef union sj_int32 {
		int pad;
		int var;
	} sj_int32;
	
	typedef union sj_uint8 {
		int pad;
		unsigned char var;
	} sj_uint8;
	
	typedef union sj_uint16 {
		int pad;
		unsigned short var;
	} sj_uint16;
	
	typedef union sj_uint32 {
		int pad;
		unsigned int var;
	} sj_uint32;
	
	static sj_uint1 __spins_scratch_sj_uint1; // TODO: unsure if needed
	static sj_int32 __spins_scratch_sj_int32; // TODO: unsure if needed
	static sj_int8 __spins_scratch_sj_int8; // TODO: unsure if needed
	static sj_uint16 __spins_scratch_sj_uint16; // TODO: unsure if needed
	static sj_uint8 __spins_scratch_sj_uint8; // TODO: unsure if needed
	static sj_uint32 __spins_scratch_sj_uint32; // TODO: unsure if needed
	static sj_int16 __spins_scratch_sj_int16; // TODO: unsure if needed
	
	typedef struct sj_struct_P_0_0_t {
		sj_int16 _pc;
		sj_uint8 j;
		sj_uint8 max;
	} sj_struct_P_0_0_t;
	
	typedef struct sj_struct_P_1_0_t {
		sj_int16 _pc;
		sj_uint8 j;
		sj_uint8 max;
	} sj_struct_P_1_0_t;
	
	typedef struct sj_struct_globals_t {
		sj_uint8 choosing[4];
		sj_uint8 number[4];
	} sj_struct_globals_t;
	
	typedef struct sj_struct_P_2_0_t {
		sj_int16 _pc;
		sj_uint8 j;
		sj_uint8 max;
	} sj_struct_P_2_0_t;
	
	typedef struct sj_struct_P_3_0_t {
		sj_int16 _pc;
		sj_uint8 j;
		sj_uint8 max;
	} sj_struct_P_3_0_t;
	
	typedef struct sj_struct_state_t {
		sj_struct_P_0_0_t P_0_0;
		sj_struct_P_1_0_t P_1_0;
		sj_struct_globals_t globals;
		sj_struct_P_2_0_t P_2_0;
		sj_struct_P_3_0_t P_3_0;
	} sj_struct_state_t;
	
	typedef sj_struct_state_t state_t;


    size_t getInitial(Context* ctx) override {
sj_struct_state_t initial;memset(&initial, 0, sizeof(sj_struct_state_t));
			initial.P_0_0._pc.var                           = 0; // -1
			initial.P_0_0.j.var                             = 0; // 0
			initial.P_0_0.max.var                           = 0; // 1
			initial.P_1_0._pc.var                           = 0; // 2
			initial.P_1_0.j.var                             = 0; // 3
			initial.P_1_0.max.var                           = 0; // 4
			initial.globals.choosing[0].var                 = 0; // 5
			initial.globals.choosing[1].var                 = 0; // 6
			initial.globals.choosing[2].var                 = 0; // 7
			initial.globals.choosing[3].var                 = 0; // 8
			initial.globals.number[0].var                   = 0; // 9
			initial.globals.number[1].var                   = 0; // 10
			initial.globals.number[2].var                   = 0; // 11
			initial.globals.number[3].var                   = 0; // 12
			initial.P_2_0._pc.var                           = 0; // 13
			initial.P_2_0.j.var                             = 0; // 14
			initial.P_2_0.max.var                           = 0; // 15
			initial.P_3_0._pc.var                           = 0; // 16
			initial.P_3_0.j.var                             = 0; // 17
			initial.P_3_0.max.var                           = 0; // 18
		
		model_assert(20*4 == sizeof(sj_struct_state_t),
			"state_t SIZE MISMATCH!: state: %zu != %i", 
		sizeof(sj_struct_state_t), 20*4);
		ModelStateIdentifier init;
		init.init(ctx, &initial, sizeof(sj_struct_state_t) / 4, true);
		printf("Uploading initial state %zx (length: %zu)\n", init.data, init.getLength());
		return 1;
		}
		
		int spins_get_successor_sid0(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid1(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid2(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid3(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid(Context* model, state_t *in, void *arg, state_t *out, int atomic, int *cpy_src) {
			switch (atomic) {
			case 0: return spins_get_successor_sid0(model, in, arg, out, cpy_src); break;
			case 1: return spins_get_successor_sid1(model, in, arg, out, cpy_src); break;
			case 2: return spins_get_successor_sid2(model, in, arg, out, cpy_src); break;
			case 3: return spins_get_successor_sid3(model, in, arg, out, cpy_src); break;
			default: printf("Wrong structural ID"); exit(-1);
			}
		}

		size_t getNextAll(StateID const& sourceStateID, Context* ctx) {
			int states_emitted = 0;
			state_t source;
			auto& mc = *ctx->getModelChecker();
			mc.getStatePartial(ctx, sourceStateID, 0, (StateSlot*)&source, sizeof(source)/4, true);
			state_t* in = &source;

			// P_0_0(0-->1)	[choosing[0] = 1] -1
			if ((in->P_0_0._pc.var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 0, in);
			}
			// P_0_0(1-->1)	[((j < 4) && (number[j] > max))] -1
			if ((in->P_0_0._pc.var == 1) &&
				((in->P_0_0.j.var < 4) && (in->globals.number[in->P_0_0.j.var].var > in->P_0_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 1, in);
			}
			// P_0_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
			if ((in->P_0_0._pc.var == 1) &&
				((in->P_0_0.j.var < 4) && (in->globals.number[in->P_0_0.j.var].var <= in->P_0_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 2, in);
			}
			// P_0_0(1-->2)	[((j == 4) && (max < 5))] -1
			if ((in->P_0_0._pc.var == 1) &&
				((in->P_0_0.j.var == 4) && (in->P_0_0.max.var < 5))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 3, in);
			}
			// P_0_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
			if ((in->P_0_0._pc.var == 2) &&
				((in->P_0_0.j.var < 4) && (in->globals.choosing[in->P_0_0.j.var].var == 0))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 4, in);
			}
			// P_0_0(4-->2)	[(((number[j] == 0) || (number[j] < number[0])) || ((number[j] == number[0]) && (0 <= j)))] -1
			if ((in->P_0_0._pc.var == 4) &&
				(((in->globals.number[in->P_0_0.j.var].var == 0) || (in->globals.number[in->P_0_0.j.var].var < in->globals.number[0].var)) || ((in->globals.number[in->P_0_0.j.var].var == in->globals.number[0].var) && (0 <= in->P_0_0.j.var)))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 5, in);
			}
			// P_0_0(2-->3)	[(P_0_0.j == 4)] -1
			if ((in->P_0_0._pc.var == 2) &&
				(in->P_0_0.j.var == 4)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 6, in);
			}
			// P_0_0(3-->0)	[number[0] = 0] -1
			if ((in->P_0_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 7, in);
			}
			// P_1_0(0-->1)	[choosing[1] = 1] -1
			if ((in->P_1_0._pc.var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 8, in);
			}
			// P_1_0(1-->1)	[((j < 4) && (number[j] > max))] -1
			if ((in->P_1_0._pc.var == 1) &&
				((in->P_1_0.j.var < 4) && (in->globals.number[in->P_1_0.j.var].var > in->P_1_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 9, in);
			}
			// P_1_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
			if ((in->P_1_0._pc.var == 1) &&
				((in->P_1_0.j.var < 4) && (in->globals.number[in->P_1_0.j.var].var <= in->P_1_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 10, in);
			}
			// P_1_0(1-->2)	[((j == 4) && (max < 5))] -1
			if ((in->P_1_0._pc.var == 1) &&
				((in->P_1_0.j.var == 4) && (in->P_1_0.max.var < 5))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 11, in);
			}
			// P_1_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
			if ((in->P_1_0._pc.var == 2) &&
				((in->P_1_0.j.var < 4) && (in->globals.choosing[in->P_1_0.j.var].var == 0))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 12, in);
			}
			// P_1_0(4-->2)	[(((number[j] == 0) || (number[j] < number[1])) || ((number[j] == number[1]) && (1 <= j)))] -1
			if ((in->P_1_0._pc.var == 4) &&
				(((in->globals.number[in->P_1_0.j.var].var == 0) || (in->globals.number[in->P_1_0.j.var].var < in->globals.number[1].var)) || ((in->globals.number[in->P_1_0.j.var].var == in->globals.number[1].var) && (1 <= in->P_1_0.j.var)))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 13, in);
			}
			// P_1_0(2-->3)	[(P_1_0.j == 4)] -1
			if ((in->P_1_0._pc.var == 2) &&
				(in->P_1_0.j.var == 4)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 14, in);
			}
			// P_1_0(3-->0)	[number[1] = 0] -1
			if ((in->P_1_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 15, in);
			}
			// P_2_0(0-->1)	[choosing[2] = 1] -1
			if ((in->P_2_0._pc.var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 16, in);
			}
			// P_2_0(1-->1)	[((j < 4) && (number[j] > max))] -1
			if ((in->P_2_0._pc.var == 1) &&
				((in->P_2_0.j.var < 4) && (in->globals.number[in->P_2_0.j.var].var > in->P_2_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 17, in);
			}
			// P_2_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
			if ((in->P_2_0._pc.var == 1) &&
				((in->P_2_0.j.var < 4) && (in->globals.number[in->P_2_0.j.var].var <= in->P_2_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 18, in);
			}
			// P_2_0(1-->2)	[((j == 4) && (max < 5))] -1
			if ((in->P_2_0._pc.var == 1) &&
				((in->P_2_0.j.var == 4) && (in->P_2_0.max.var < 5))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 19, in);
			}
			// P_2_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
			if ((in->P_2_0._pc.var == 2) &&
				((in->P_2_0.j.var < 4) && (in->globals.choosing[in->P_2_0.j.var].var == 0))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 20, in);
			}
			// P_2_0(4-->2)	[(((number[j] == 0) || (number[j] < number[2])) || ((number[j] == number[2]) && (2 <= j)))] -1
			if ((in->P_2_0._pc.var == 4) &&
				(((in->globals.number[in->P_2_0.j.var].var == 0) || (in->globals.number[in->P_2_0.j.var].var < in->globals.number[2].var)) || ((in->globals.number[in->P_2_0.j.var].var == in->globals.number[2].var) && (2 <= in->P_2_0.j.var)))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 21, in);
			}
			// P_2_0(2-->3)	[(P_2_0.j == 4)] -1
			if ((in->P_2_0._pc.var == 2) &&
				(in->P_2_0.j.var == 4)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 22, in);
			}
			// P_2_0(3-->0)	[number[2] = 0] -1
			if ((in->P_2_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 23, in);
			}
			// P_3_0(0-->1)	[choosing[3] = 1] -1
			if ((in->P_3_0._pc.var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 24, in);
			}
			// P_3_0(1-->1)	[((j < 4) && (number[j] > max))] -1
			if ((in->P_3_0._pc.var == 1) &&
				((in->P_3_0.j.var < 4) && (in->globals.number[in->P_3_0.j.var].var > in->P_3_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 25, in);
			}
			// P_3_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
			if ((in->P_3_0._pc.var == 1) &&
				((in->P_3_0.j.var < 4) && (in->globals.number[in->P_3_0.j.var].var <= in->P_3_0.max.var))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 26, in);
			}
			// P_3_0(1-->2)	[((j == 4) && (max < 5))] -1
			if ((in->P_3_0._pc.var == 1) &&
				((in->P_3_0.j.var == 4) && (in->P_3_0.max.var < 5))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 27, in);
			}
			// P_3_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
			if ((in->P_3_0._pc.var == 2) &&
				((in->P_3_0.j.var < 4) && (in->globals.choosing[in->P_3_0.j.var].var == 0))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 28, in);
			}
			// P_3_0(4-->2)	[(((number[j] == 0) || (number[j] < number[3])) || ((number[j] == number[3]) && (3 <= j)))] -1
			if ((in->P_3_0._pc.var == 4) &&
				(((in->globals.number[in->P_3_0.j.var].var == 0) || (in->globals.number[in->P_3_0.j.var].var < in->globals.number[3].var)) || ((in->globals.number[in->P_3_0.j.var].var == in->globals.number[3].var) && (3 <= in->P_3_0.j.var)))) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 29, in);
			}
			// P_3_0(2-->3)	[(P_3_0.j == 4)] -1
			if ((in->P_3_0._pc.var == 2) &&
				(in->P_3_0.j.var == 4)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 30, in);
			}
			// P_3_0(3-->0)	[number[3] = 0] -1
			if ((in->P_3_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 31, in);
			}
			return states_emitted;
		}

		int spins_get_actions (Context* ctx, StateID sourceStateID, int t, state_t *in) {
			auto& mc = *ctx->getModelChecker();
			int states_emitted = 0;
			sj_struct_state_t local_state;
			sj_struct_state_t* out = &local_state;
			int cpy[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, };

			switch(t) {
			case 0: {
				// P_0_0(0-->1)	[choosing[0] = 1] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 1;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				out->globals.choosing[0].var = 1;
				cpy[((int *)&out->globals.choosing[0].pad - (int *)out)] = 0;
				out->P_0_0.j.var = 0;
				cpy[((int *)&out->P_0_0.j.pad - (int *)out)] = 0;
				out->P_0_0.max.var = 0;
				cpy[((int *)&out->P_0_0.max.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 1: {
				// P_0_0(1-->1)	[((j < 4) && (number[j] > max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 1;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				out->P_0_0.max.var = out->globals.number[out->P_0_0.j.var].var;
				cpy[((int *)&out->P_0_0.max.pad - (int *)out)] = 0;
				out->P_0_0.j.var = (out->P_0_0.j.var + 1);
				cpy[((int *)&out->P_0_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 2: {
				// P_0_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 1;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				out->P_0_0.j.var = (out->P_0_0.j.var + 1);
				cpy[((int *)&out->P_0_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 3: {
				// P_0_0(1-->2)	[((j == 4) && (max < 5))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 2;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				out->globals.number[0].var = (out->P_0_0.max.var + 1);
				cpy[((int *)&out->globals.number[0].pad - (int *)out)] = 0;
				out->P_0_0.j.var = 0;
				cpy[((int *)&out->P_0_0.j.pad - (int *)out)] = 0;
				out->globals.choosing[0].var = 0;
				cpy[((int *)&out->globals.choosing[0].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 4: {
				// P_0_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 4;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 5: {
				// P_0_0(4-->2)	[(((number[j] == 0) || (number[j] < number[0])) || ((number[j] == number[0]) && (0 <= j)))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 2;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				out->P_0_0.j.var = (out->P_0_0.j.var + 1);
				cpy[((int *)&out->P_0_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 6: {
				// P_0_0(2-->3)	[(P_0_0.j == 4)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 3;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 7: {
				// P_0_0(3-->0)	[number[0] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_0_0._pc.var = 0;
				cpy[((int *)&out->P_0_0._pc.pad - (int *)out)] = 0;
				out->globals.number[0].var = 0;
				cpy[((int *)&out->globals.number[0].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 8: {
				// P_1_0(0-->1)	[choosing[1] = 1] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 1;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				out->globals.choosing[1].var = 1;
				cpy[((int *)&out->globals.choosing[1].pad - (int *)out)] = 0;
				out->P_1_0.j.var = 0;
				cpy[((int *)&out->P_1_0.j.pad - (int *)out)] = 0;
				out->P_1_0.max.var = 0;
				cpy[((int *)&out->P_1_0.max.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 9: {
				// P_1_0(1-->1)	[((j < 4) && (number[j] > max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 1;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				out->P_1_0.max.var = out->globals.number[out->P_1_0.j.var].var;
				cpy[((int *)&out->P_1_0.max.pad - (int *)out)] = 0;
				out->P_1_0.j.var = (out->P_1_0.j.var + 1);
				cpy[((int *)&out->P_1_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 10: {
				// P_1_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 1;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				out->P_1_0.j.var = (out->P_1_0.j.var + 1);
				cpy[((int *)&out->P_1_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 11: {
				// P_1_0(1-->2)	[((j == 4) && (max < 5))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 2;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				out->globals.number[1].var = (out->P_1_0.max.var + 1);
				cpy[((int *)&out->globals.number[1].pad - (int *)out)] = 0;
				out->P_1_0.j.var = 0;
				cpy[((int *)&out->P_1_0.j.pad - (int *)out)] = 0;
				out->globals.choosing[1].var = 0;
				cpy[((int *)&out->globals.choosing[1].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 12: {
				// P_1_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 4;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 13: {
				// P_1_0(4-->2)	[(((number[j] == 0) || (number[j] < number[1])) || ((number[j] == number[1]) && (1 <= j)))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 2;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				out->P_1_0.j.var = (out->P_1_0.j.var + 1);
				cpy[((int *)&out->P_1_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 14: {
				// P_1_0(2-->3)	[(P_1_0.j == 4)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 3;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 15: {
				// P_1_0(3-->0)	[number[1] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_1_0._pc.var = 0;
				cpy[((int *)&out->P_1_0._pc.pad - (int *)out)] = 0;
				out->globals.number[1].var = 0;
				cpy[((int *)&out->globals.number[1].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 16: {
				// P_2_0(0-->1)	[choosing[2] = 1] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 1;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				out->globals.choosing[2].var = 1;
				cpy[((int *)&out->globals.choosing[2].pad - (int *)out)] = 0;
				out->P_2_0.j.var = 0;
				cpy[((int *)&out->P_2_0.j.pad - (int *)out)] = 0;
				out->P_2_0.max.var = 0;
				cpy[((int *)&out->P_2_0.max.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 17: {
				// P_2_0(1-->1)	[((j < 4) && (number[j] > max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 1;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				out->P_2_0.max.var = out->globals.number[out->P_2_0.j.var].var;
				cpy[((int *)&out->P_2_0.max.pad - (int *)out)] = 0;
				out->P_2_0.j.var = (out->P_2_0.j.var + 1);
				cpy[((int *)&out->P_2_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 18: {
				// P_2_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 1;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				out->P_2_0.j.var = (out->P_2_0.j.var + 1);
				cpy[((int *)&out->P_2_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 19: {
				// P_2_0(1-->2)	[((j == 4) && (max < 5))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 2;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				out->globals.number[2].var = (out->P_2_0.max.var + 1);
				cpy[((int *)&out->globals.number[2].pad - (int *)out)] = 0;
				out->P_2_0.j.var = 0;
				cpy[((int *)&out->P_2_0.j.pad - (int *)out)] = 0;
				out->globals.choosing[2].var = 0;
				cpy[((int *)&out->globals.choosing[2].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 20: {
				// P_2_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 4;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 21: {
				// P_2_0(4-->2)	[(((number[j] == 0) || (number[j] < number[2])) || ((number[j] == number[2]) && (2 <= j)))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 2;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				out->P_2_0.j.var = (out->P_2_0.j.var + 1);
				cpy[((int *)&out->P_2_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 22: {
				// P_2_0(2-->3)	[(P_2_0.j == 4)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 3;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 23: {
				// P_2_0(3-->0)	[number[2] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_2_0._pc.var = 0;
				cpy[((int *)&out->P_2_0._pc.pad - (int *)out)] = 0;
				out->globals.number[2].var = 0;
				cpy[((int *)&out->globals.number[2].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 24: {
				// P_3_0(0-->1)	[choosing[3] = 1] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 1;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				out->globals.choosing[3].var = 1;
				cpy[((int *)&out->globals.choosing[3].pad - (int *)out)] = 0;
				out->P_3_0.j.var = 0;
				cpy[((int *)&out->P_3_0.j.pad - (int *)out)] = 0;
				out->P_3_0.max.var = 0;
				cpy[((int *)&out->P_3_0.max.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 25: {
				// P_3_0(1-->1)	[((j < 4) && (number[j] > max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 1;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				out->P_3_0.max.var = out->globals.number[out->P_3_0.j.var].var;
				cpy[((int *)&out->P_3_0.max.pad - (int *)out)] = 0;
				out->P_3_0.j.var = (out->P_3_0.j.var + 1);
				cpy[((int *)&out->P_3_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 26: {
				// P_3_0(1-->1)	[((j < 4) && (number[j] <= max))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 1;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				out->P_3_0.j.var = (out->P_3_0.j.var + 1);
				cpy[((int *)&out->P_3_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 27: {
				// P_3_0(1-->2)	[((j == 4) && (max < 5))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 2;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				out->globals.number[3].var = (out->P_3_0.max.var + 1);
				cpy[((int *)&out->globals.number[3].pad - (int *)out)] = 0;
				out->P_3_0.j.var = 0;
				cpy[((int *)&out->P_3_0.j.pad - (int *)out)] = 0;
				out->globals.choosing[3].var = 0;
				cpy[((int *)&out->globals.choosing[3].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 28: {
				// P_3_0(2-->4)	[((j < 4) && (choosing[j] == 0))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 4;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 29: {
				// P_3_0(4-->2)	[(((number[j] == 0) || (number[j] < number[3])) || ((number[j] == number[3]) && (3 <= j)))] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 2;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				out->P_3_0.j.var = (out->P_3_0.j.var + 1);
				cpy[((int *)&out->P_3_0.j.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 30: {
				// P_3_0(2-->3)	[(P_3_0.j == 4)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 3;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 31: {
				// P_3_0(3-->0)	[number[3] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->P_3_0._pc.var = 0;
				cpy[((int *)&out->P_3_0._pc.pad - (int *)out)] = 0;
				out->globals.number[3].var = 0;
				cpy[((int *)&out->globals.number[3].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			}
			return 0;
		}

		size_t getNext(StateID const& s, Context* ctx, size_t tg) override {
			abort();
		}
		llmc::statespace::Type* getStateVectorType() override {
			return nullptr;
		}
		void init(Context* ctx) override {
		}
		TransitionInfo getTransitionInfo(VContext<llmc::storage::StorageInterface>* ctx, TransitionInfoUnExpanded const& tinfo_) const override {
			ModelStateIdentifier labelID = tinfo_.get<ModelStateIdentifier>();
			StateSlot str[labelID.getLength()];
			labelID.pull(ctx, str);
			return TransitionInfo(std::string((char*)str, labelID.getLength()*4));
		}
		size_t getStateLength() const override {
			return 0;
		}
	};
