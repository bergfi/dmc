/** Generated DMC model - phils.5.prom
 * State size:  24 elements (96 bytes)
 * Transitions: 48
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

class DMCModelphils___prom: public VModel<llmc::storage::StorageInterface>
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
	
	typedef struct sj_struct_phil_0_0_t {
		sj_int16 _pc;
	} sj_struct_phil_0_0_t;
	
	typedef struct sj_struct_phil_1_0_t {
		sj_int16 _pc;
	} sj_struct_phil_1_0_t;
	
	typedef struct sj_struct_phil_2_0_t {
		sj_int16 _pc;
	} sj_struct_phil_2_0_t;
	
	typedef struct sj_struct_phil_3_0_t {
		sj_int16 _pc;
	} sj_struct_phil_3_0_t;
	
	typedef struct sj_struct_phil_4_0_t {
		sj_int16 _pc;
	} sj_struct_phil_4_0_t;
	
	typedef struct sj_struct_phil_5_0_t {
		sj_int16 _pc;
	} sj_struct_phil_5_0_t;
	
	typedef struct sj_struct_globals_t {
		sj_uint8 fork[12];
	} sj_struct_globals_t;
	
	typedef struct sj_struct_phil_6_0_t {
		sj_int16 _pc;
	} sj_struct_phil_6_0_t;
	
	typedef struct sj_struct_phil_7_0_t {
		sj_int16 _pc;
	} sj_struct_phil_7_0_t;
	
	typedef struct sj_struct_phil_8_0_t {
		sj_int16 _pc;
	} sj_struct_phil_8_0_t;
	
	typedef struct sj_struct_phil_9_0_t {
		sj_int16 _pc;
	} sj_struct_phil_9_0_t;
	
	typedef struct sj_struct_phil_10_0_t {
		sj_int16 _pc;
	} sj_struct_phil_10_0_t;
	
	typedef struct sj_struct_phil_11_0_t {
		sj_int16 _pc;
	} sj_struct_phil_11_0_t;
	
	typedef struct sj_struct_state_t {
		sj_struct_phil_0_0_t phil_0_0;
		sj_struct_phil_1_0_t phil_1_0;
		sj_struct_phil_2_0_t phil_2_0;
		sj_struct_phil_3_0_t phil_3_0;
		sj_struct_phil_4_0_t phil_4_0;
		sj_struct_phil_5_0_t phil_5_0;
		sj_struct_globals_t globals;
		sj_struct_phil_6_0_t phil_6_0;
		sj_struct_phil_7_0_t phil_7_0;
		sj_struct_phil_8_0_t phil_8_0;
		sj_struct_phil_9_0_t phil_9_0;
		sj_struct_phil_10_0_t phil_10_0;
		sj_struct_phil_11_0_t phil_11_0;
	} sj_struct_state_t;
	
	typedef sj_struct_state_t state_t;


    size_t getInitial(Context* ctx) override {
sj_struct_state_t initial;memset(&initial, 0, sizeof(sj_struct_state_t));
			initial.phil_0_0._pc.var                        = 0; // -1
			initial.phil_1_0._pc.var                        = 0; // 0
			initial.phil_2_0._pc.var                        = 0; // 1
			initial.phil_3_0._pc.var                        = 0; // 2
			initial.phil_4_0._pc.var                        = 0; // 3
			initial.phil_5_0._pc.var                        = 0; // 4
			initial.globals.fork[0].var                     = 0; // 5
			initial.globals.fork[1].var                     = 0; // 6
			initial.globals.fork[2].var                     = 0; // 7
			initial.globals.fork[3].var                     = 0; // 8
			initial.globals.fork[4].var                     = 0; // 9
			initial.globals.fork[5].var                     = 0; // 10
			initial.globals.fork[6].var                     = 0; // 11
			initial.globals.fork[7].var                     = 0; // 12
			initial.globals.fork[8].var                     = 0; // 13
			initial.globals.fork[9].var                     = 0; // 14
			initial.globals.fork[10].var                    = 0; // 15
			initial.globals.fork[11].var                    = 0; // 16
			initial.phil_6_0._pc.var                        = 0; // 17
			initial.phil_7_0._pc.var                        = 0; // 18
			initial.phil_8_0._pc.var                        = 0; // 19
			initial.phil_9_0._pc.var                        = 0; // 20
			initial.phil_10_0._pc.var                       = 0; // 21
			initial.phil_11_0._pc.var                       = 0; // 22
		
		model_assert(24*4 == sizeof(sj_struct_state_t),
			"state_t SIZE MISMATCH!: state: %zu != %i", 
		sizeof(sj_struct_state_t), 24*4);
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

		int spins_get_successor_sid4(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid5(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid6(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid7(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid8(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid9(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid10(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid11(Context* model, state_t *in, void *arg, state_t *out, int *cpy_src) {
			int states_emitted = 0;

			return states_emitted;
		}

		int spins_get_successor_sid(Context* model, state_t *in, void *arg, state_t *out, int atomic, int *cpy_src) {
			switch (atomic) {
			case 0: return spins_get_successor_sid0(model, in, arg, out, cpy_src); break;
			case 1: return spins_get_successor_sid1(model, in, arg, out, cpy_src); break;
			case 2: return spins_get_successor_sid2(model, in, arg, out, cpy_src); break;
			case 3: return spins_get_successor_sid3(model, in, arg, out, cpy_src); break;
			case 4: return spins_get_successor_sid4(model, in, arg, out, cpy_src); break;
			case 5: return spins_get_successor_sid5(model, in, arg, out, cpy_src); break;
			case 6: return spins_get_successor_sid6(model, in, arg, out, cpy_src); break;
			case 7: return spins_get_successor_sid7(model, in, arg, out, cpy_src); break;
			case 8: return spins_get_successor_sid8(model, in, arg, out, cpy_src); break;
			case 9: return spins_get_successor_sid9(model, in, arg, out, cpy_src); break;
			case 10: return spins_get_successor_sid10(model, in, arg, out, cpy_src); break;
			case 11: return spins_get_successor_sid11(model, in, arg, out, cpy_src); break;
			default: printf("Wrong structural ID"); exit(-1);
			}
		}

		size_t getNextAll(StateID const& sourceStateID, Context* ctx) {
			int states_emitted = 0;
			state_t source;
			auto& mc = *ctx->getModelChecker();
			mc.getStatePartial(ctx, sourceStateID, 0, (StateSlot*)&source, sizeof(source)/4, true);
			state_t* in = &source;

			// phil_0_0(0-->1)	[(fork[0] == 0)] -1
			if ((in->phil_0_0._pc.var == 0) &&
				(in->globals.fork[0].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 0, in);
			}
			// phil_0_0(1-->2)	[(fork[1] == 0)] -1
			if ((in->phil_0_0._pc.var == 1) &&
				(in->globals.fork[1].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 1, in);
			}
			// phil_0_0(2-->3)	[fork[0] = 0] -1
			if ((in->phil_0_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 2, in);
			}
			// phil_0_0(3-->0)	[fork[1] = 0] -1
			if ((in->phil_0_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 3, in);
			}
			// phil_1_0(0-->1)	[(fork[1] == 0)] -1
			if ((in->phil_1_0._pc.var == 0) &&
				(in->globals.fork[1].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 4, in);
			}
			// phil_1_0(1-->2)	[(fork[2] == 0)] -1
			if ((in->phil_1_0._pc.var == 1) &&
				(in->globals.fork[2].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 5, in);
			}
			// phil_1_0(2-->3)	[fork[1] = 0] -1
			if ((in->phil_1_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 6, in);
			}
			// phil_1_0(3-->0)	[fork[2] = 0] -1
			if ((in->phil_1_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 7, in);
			}
			// phil_2_0(0-->1)	[(fork[2] == 0)] -1
			if ((in->phil_2_0._pc.var == 0) &&
				(in->globals.fork[2].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 8, in);
			}
			// phil_2_0(1-->2)	[(fork[3] == 0)] -1
			if ((in->phil_2_0._pc.var == 1) &&
				(in->globals.fork[3].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 9, in);
			}
			// phil_2_0(2-->3)	[fork[2] = 0] -1
			if ((in->phil_2_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 10, in);
			}
			// phil_2_0(3-->0)	[fork[3] = 0] -1
			if ((in->phil_2_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 11, in);
			}
			// phil_3_0(0-->1)	[(fork[3] == 0)] -1
			if ((in->phil_3_0._pc.var == 0) &&
				(in->globals.fork[3].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 12, in);
			}
			// phil_3_0(1-->2)	[(fork[4] == 0)] -1
			if ((in->phil_3_0._pc.var == 1) &&
				(in->globals.fork[4].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 13, in);
			}
			// phil_3_0(2-->3)	[fork[3] = 0] -1
			if ((in->phil_3_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 14, in);
			}
			// phil_3_0(3-->0)	[fork[4] = 0] -1
			if ((in->phil_3_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 15, in);
			}
			// phil_4_0(0-->1)	[(fork[4] == 0)] -1
			if ((in->phil_4_0._pc.var == 0) &&
				(in->globals.fork[4].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 16, in);
			}
			// phil_4_0(1-->2)	[(fork[5] == 0)] -1
			if ((in->phil_4_0._pc.var == 1) &&
				(in->globals.fork[5].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 17, in);
			}
			// phil_4_0(2-->3)	[fork[4] = 0] -1
			if ((in->phil_4_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 18, in);
			}
			// phil_4_0(3-->0)	[fork[5] = 0] -1
			if ((in->phil_4_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 19, in);
			}
			// phil_5_0(0-->1)	[(fork[5] == 0)] -1
			if ((in->phil_5_0._pc.var == 0) &&
				(in->globals.fork[5].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 20, in);
			}
			// phil_5_0(1-->2)	[(fork[6] == 0)] -1
			if ((in->phil_5_0._pc.var == 1) &&
				(in->globals.fork[6].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 21, in);
			}
			// phil_5_0(2-->3)	[fork[5] = 0] -1
			if ((in->phil_5_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 22, in);
			}
			// phil_5_0(3-->0)	[fork[6] = 0] -1
			if ((in->phil_5_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 23, in);
			}
			// phil_6_0(0-->1)	[(fork[6] == 0)] -1
			if ((in->phil_6_0._pc.var == 0) &&
				(in->globals.fork[6].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 24, in);
			}
			// phil_6_0(1-->2)	[(fork[7] == 0)] -1
			if ((in->phil_6_0._pc.var == 1) &&
				(in->globals.fork[7].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 25, in);
			}
			// phil_6_0(2-->3)	[fork[6] = 0] -1
			if ((in->phil_6_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 26, in);
			}
			// phil_6_0(3-->0)	[fork[7] = 0] -1
			if ((in->phil_6_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 27, in);
			}
			// phil_7_0(0-->1)	[(fork[7] == 0)] -1
			if ((in->phil_7_0._pc.var == 0) &&
				(in->globals.fork[7].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 28, in);
			}
			// phil_7_0(1-->2)	[(fork[8] == 0)] -1
			if ((in->phil_7_0._pc.var == 1) &&
				(in->globals.fork[8].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 29, in);
			}
			// phil_7_0(2-->3)	[fork[7] = 0] -1
			if ((in->phil_7_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 30, in);
			}
			// phil_7_0(3-->0)	[fork[8] = 0] -1
			if ((in->phil_7_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 31, in);
			}
			// phil_8_0(0-->1)	[(fork[8] == 0)] -1
			if ((in->phil_8_0._pc.var == 0) &&
				(in->globals.fork[8].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 32, in);
			}
			// phil_8_0(1-->2)	[(fork[9] == 0)] -1
			if ((in->phil_8_0._pc.var == 1) &&
				(in->globals.fork[9].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 33, in);
			}
			// phil_8_0(2-->3)	[fork[8] = 0] -1
			if ((in->phil_8_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 34, in);
			}
			// phil_8_0(3-->0)	[fork[9] = 0] -1
			if ((in->phil_8_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 35, in);
			}
			// phil_9_0(0-->1)	[(fork[9] == 0)] -1
			if ((in->phil_9_0._pc.var == 0) &&
				(in->globals.fork[9].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 36, in);
			}
			// phil_9_0(1-->2)	[(fork[10] == 0)] -1
			if ((in->phil_9_0._pc.var == 1) &&
				(in->globals.fork[10].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 37, in);
			}
			// phil_9_0(2-->3)	[fork[9] = 0] -1
			if ((in->phil_9_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 38, in);
			}
			// phil_9_0(3-->0)	[fork[10] = 0] -1
			if ((in->phil_9_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 39, in);
			}
			// phil_10_0(0-->1)	[(fork[10] == 0)] -1
			if ((in->phil_10_0._pc.var == 0) &&
				(in->globals.fork[10].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 40, in);
			}
			// phil_10_0(1-->2)	[(fork[11] == 0)] -1
			if ((in->phil_10_0._pc.var == 1) &&
				(in->globals.fork[11].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 41, in);
			}
			// phil_10_0(2-->3)	[fork[10] = 0] -1
			if ((in->phil_10_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 42, in);
			}
			// phil_10_0(3-->0)	[fork[11] = 0] -1
			if ((in->phil_10_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 43, in);
			}
			// phil_11_0(0-->1)	[(fork[11] == 0)] -1
			if ((in->phil_11_0._pc.var == 0) &&
				(in->globals.fork[11].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 44, in);
			}
			// phil_11_0(1-->2)	[(fork[0] == 0)] -1
			if ((in->phil_11_0._pc.var == 1) &&
				(in->globals.fork[0].var == 0)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 45, in);
			}
			// phil_11_0(2-->3)	[fork[11] = 0] -1
			if ((in->phil_11_0._pc.var == 2)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 46, in);
			}
			// phil_11_0(3-->0)	[fork[0] = 0] -1
			if ((in->phil_11_0._pc.var == 3)) {
				states_emitted += spins_get_actions (ctx, sourceStateID, 47, in);
			}
			return states_emitted;
		}

		int spins_get_actions (Context* ctx, StateID sourceStateID, int t, state_t *in) {
			auto& mc = *ctx->getModelChecker();
			int states_emitted = 0;
			sj_struct_state_t local_state;
			sj_struct_state_t* out = &local_state;
			int cpy[24] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, };

			switch(t) {
			case 0: {
				// phil_0_0(0-->1)	[(fork[0] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_0_0._pc.var = 1;
				cpy[((int *)&out->phil_0_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[0].var = 1;
				cpy[((int *)&out->globals.fork[0].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 1: {
				// phil_0_0(1-->2)	[(fork[1] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_0_0._pc.var = 2;
				cpy[((int *)&out->phil_0_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[1].var = 1;
				cpy[((int *)&out->globals.fork[1].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 2: {
				// phil_0_0(2-->3)	[fork[0] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_0_0._pc.var = 3;
				cpy[((int *)&out->phil_0_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[0].var = 0;
				cpy[((int *)&out->globals.fork[0].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 3: {
				// phil_0_0(3-->0)	[fork[1] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_0_0._pc.var = 0;
				cpy[((int *)&out->phil_0_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[1].var = 0;
				cpy[((int *)&out->globals.fork[1].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 4: {
				// phil_1_0(0-->1)	[(fork[1] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_1_0._pc.var = 1;
				cpy[((int *)&out->phil_1_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[1].var = 1;
				cpy[((int *)&out->globals.fork[1].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 5: {
				// phil_1_0(1-->2)	[(fork[2] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_1_0._pc.var = 2;
				cpy[((int *)&out->phil_1_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[2].var = 1;
				cpy[((int *)&out->globals.fork[2].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 6: {
				// phil_1_0(2-->3)	[fork[1] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_1_0._pc.var = 3;
				cpy[((int *)&out->phil_1_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[1].var = 0;
				cpy[((int *)&out->globals.fork[1].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 7: {
				// phil_1_0(3-->0)	[fork[2] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_1_0._pc.var = 0;
				cpy[((int *)&out->phil_1_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[2].var = 0;
				cpy[((int *)&out->globals.fork[2].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 8: {
				// phil_2_0(0-->1)	[(fork[2] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_2_0._pc.var = 1;
				cpy[((int *)&out->phil_2_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[2].var = 1;
				cpy[((int *)&out->globals.fork[2].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 9: {
				// phil_2_0(1-->2)	[(fork[3] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_2_0._pc.var = 2;
				cpy[((int *)&out->phil_2_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[3].var = 1;
				cpy[((int *)&out->globals.fork[3].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 10: {
				// phil_2_0(2-->3)	[fork[2] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_2_0._pc.var = 3;
				cpy[((int *)&out->phil_2_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[2].var = 0;
				cpy[((int *)&out->globals.fork[2].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 11: {
				// phil_2_0(3-->0)	[fork[3] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_2_0._pc.var = 0;
				cpy[((int *)&out->phil_2_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[3].var = 0;
				cpy[((int *)&out->globals.fork[3].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 12: {
				// phil_3_0(0-->1)	[(fork[3] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_3_0._pc.var = 1;
				cpy[((int *)&out->phil_3_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[3].var = 1;
				cpy[((int *)&out->globals.fork[3].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 13: {
				// phil_3_0(1-->2)	[(fork[4] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_3_0._pc.var = 2;
				cpy[((int *)&out->phil_3_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[4].var = 1;
				cpy[((int *)&out->globals.fork[4].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 14: {
				// phil_3_0(2-->3)	[fork[3] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_3_0._pc.var = 3;
				cpy[((int *)&out->phil_3_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[3].var = 0;
				cpy[((int *)&out->globals.fork[3].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 15: {
				// phil_3_0(3-->0)	[fork[4] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_3_0._pc.var = 0;
				cpy[((int *)&out->phil_3_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[4].var = 0;
				cpy[((int *)&out->globals.fork[4].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 16: {
				// phil_4_0(0-->1)	[(fork[4] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_4_0._pc.var = 1;
				cpy[((int *)&out->phil_4_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[4].var = 1;
				cpy[((int *)&out->globals.fork[4].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 17: {
				// phil_4_0(1-->2)	[(fork[5] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_4_0._pc.var = 2;
				cpy[((int *)&out->phil_4_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[5].var = 1;
				cpy[((int *)&out->globals.fork[5].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 18: {
				// phil_4_0(2-->3)	[fork[4] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_4_0._pc.var = 3;
				cpy[((int *)&out->phil_4_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[4].var = 0;
				cpy[((int *)&out->globals.fork[4].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 19: {
				// phil_4_0(3-->0)	[fork[5] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_4_0._pc.var = 0;
				cpy[((int *)&out->phil_4_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[5].var = 0;
				cpy[((int *)&out->globals.fork[5].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 20: {
				// phil_5_0(0-->1)	[(fork[5] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_5_0._pc.var = 1;
				cpy[((int *)&out->phil_5_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[5].var = 1;
				cpy[((int *)&out->globals.fork[5].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 21: {
				// phil_5_0(1-->2)	[(fork[6] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_5_0._pc.var = 2;
				cpy[((int *)&out->phil_5_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[6].var = 1;
				cpy[((int *)&out->globals.fork[6].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 22: {
				// phil_5_0(2-->3)	[fork[5] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_5_0._pc.var = 3;
				cpy[((int *)&out->phil_5_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[5].var = 0;
				cpy[((int *)&out->globals.fork[5].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 23: {
				// phil_5_0(3-->0)	[fork[6] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_5_0._pc.var = 0;
				cpy[((int *)&out->phil_5_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[6].var = 0;
				cpy[((int *)&out->globals.fork[6].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 24: {
				// phil_6_0(0-->1)	[(fork[6] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_6_0._pc.var = 1;
				cpy[((int *)&out->phil_6_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[6].var = 1;
				cpy[((int *)&out->globals.fork[6].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 25: {
				// phil_6_0(1-->2)	[(fork[7] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_6_0._pc.var = 2;
				cpy[((int *)&out->phil_6_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[7].var = 1;
				cpy[((int *)&out->globals.fork[7].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 26: {
				// phil_6_0(2-->3)	[fork[6] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_6_0._pc.var = 3;
				cpy[((int *)&out->phil_6_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[6].var = 0;
				cpy[((int *)&out->globals.fork[6].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 27: {
				// phil_6_0(3-->0)	[fork[7] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_6_0._pc.var = 0;
				cpy[((int *)&out->phil_6_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[7].var = 0;
				cpy[((int *)&out->globals.fork[7].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 28: {
				// phil_7_0(0-->1)	[(fork[7] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_7_0._pc.var = 1;
				cpy[((int *)&out->phil_7_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[7].var = 1;
				cpy[((int *)&out->globals.fork[7].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 29: {
				// phil_7_0(1-->2)	[(fork[8] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_7_0._pc.var = 2;
				cpy[((int *)&out->phil_7_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[8].var = 1;
				cpy[((int *)&out->globals.fork[8].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 30: {
				// phil_7_0(2-->3)	[fork[7] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_7_0._pc.var = 3;
				cpy[((int *)&out->phil_7_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[7].var = 0;
				cpy[((int *)&out->globals.fork[7].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 31: {
				// phil_7_0(3-->0)	[fork[8] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_7_0._pc.var = 0;
				cpy[((int *)&out->phil_7_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[8].var = 0;
				cpy[((int *)&out->globals.fork[8].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 32: {
				// phil_8_0(0-->1)	[(fork[8] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_8_0._pc.var = 1;
				cpy[((int *)&out->phil_8_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[8].var = 1;
				cpy[((int *)&out->globals.fork[8].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 33: {
				// phil_8_0(1-->2)	[(fork[9] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_8_0._pc.var = 2;
				cpy[((int *)&out->phil_8_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[9].var = 1;
				cpy[((int *)&out->globals.fork[9].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 34: {
				// phil_8_0(2-->3)	[fork[8] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_8_0._pc.var = 3;
				cpy[((int *)&out->phil_8_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[8].var = 0;
				cpy[((int *)&out->globals.fork[8].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 35: {
				// phil_8_0(3-->0)	[fork[9] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_8_0._pc.var = 0;
				cpy[((int *)&out->phil_8_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[9].var = 0;
				cpy[((int *)&out->globals.fork[9].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 36: {
				// phil_9_0(0-->1)	[(fork[9] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_9_0._pc.var = 1;
				cpy[((int *)&out->phil_9_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[9].var = 1;
				cpy[((int *)&out->globals.fork[9].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 37: {
				// phil_9_0(1-->2)	[(fork[10] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_9_0._pc.var = 2;
				cpy[((int *)&out->phil_9_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[10].var = 1;
				cpy[((int *)&out->globals.fork[10].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 38: {
				// phil_9_0(2-->3)	[fork[9] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_9_0._pc.var = 3;
				cpy[((int *)&out->phil_9_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[9].var = 0;
				cpy[((int *)&out->globals.fork[9].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 39: {
				// phil_9_0(3-->0)	[fork[10] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_9_0._pc.var = 0;
				cpy[((int *)&out->phil_9_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[10].var = 0;
				cpy[((int *)&out->globals.fork[10].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 40: {
				// phil_10_0(0-->1)	[(fork[10] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_10_0._pc.var = 1;
				cpy[((int *)&out->phil_10_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[10].var = 1;
				cpy[((int *)&out->globals.fork[10].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 41: {
				// phil_10_0(1-->2)	[(fork[11] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_10_0._pc.var = 2;
				cpy[((int *)&out->phil_10_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[11].var = 1;
				cpy[((int *)&out->globals.fork[11].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 42: {
				// phil_10_0(2-->3)	[fork[10] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_10_0._pc.var = 3;
				cpy[((int *)&out->phil_10_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[10].var = 0;
				cpy[((int *)&out->globals.fork[10].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 43: {
				// phil_10_0(3-->0)	[fork[11] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_10_0._pc.var = 0;
				cpy[((int *)&out->phil_10_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[11].var = 0;
				cpy[((int *)&out->globals.fork[11].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 44: {
				// phil_11_0(0-->1)	[(fork[11] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_11_0._pc.var = 1;
				cpy[((int *)&out->phil_11_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[11].var = 1;
				cpy[((int *)&out->globals.fork[11].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 45: {
				// phil_11_0(1-->2)	[(fork[0] == 0)] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_11_0._pc.var = 2;
				cpy[((int *)&out->phil_11_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[0].var = 1;
				cpy[((int *)&out->globals.fork[0].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 46: {
				// phil_11_0(2-->3)	[fork[11] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_11_0._pc.var = 3;
				cpy[((int *)&out->phil_11_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[11].var = 0;
				cpy[((int *)&out->globals.fork[11].pad - (int *)out)] = 0;
				mc.newTransition(ctx, sizeof(sj_struct_state_t) / 4, (StateSlot*)out, TransitionInfoUnExpanded::None());
				++states_emitted;
				return states_emitted;
			}
			case 47: {
				// phil_11_0(3-->0)	[fork[0] = 0] -1
				memcpy(out, in, sizeof(sj_struct_state_t));
				out->phil_11_0._pc.var = 0;
				cpy[((int *)&out->phil_11_0._pc.pad - (int *)out)] = 0;
				out->globals.fork[0].var = 0;
				cpy[((int *)&out->globals.fork[0].pad - (int *)out)] = 0;
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
