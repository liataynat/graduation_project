#ifndef INIT_ARGUMENT
#define INIT_ARGUMENT

extern char inst_filename[256];
extern bool flag_inst ;
extern bool flag_auto_select;
extern bool flag_print_smart_format;
extern int seed;
extern bool flag_seed;
extern long long max_step;
extern int cutoff_time;
extern bool flag_time;
extern bool flag_print_sol;
extern bool flag_print_step;
extern bool flag_perform_bms;
extern int BMS_T;
extern int flag_subset_score_calculation;
extern int flag_solution_initialization;
extern bool flag_perform_cc;
extern bool flag_perform_iscc;
extern bool flag_perform_tabu;
extern int tabu_alpha;
extern int flag_reconstruction;
extern int reconstruct_swap_T;
extern bool reconstruct_with_prob;
extern double reconstruct_prob;
extern int flag_subset_removal_scheme;
extern int flag_subset_addition;
extern int flag_perform_alternate_method;
extern int flag_update_item_weight_scheme;
extern int SAPS_T;
extern double SAPS_R;
extern double PAWS_P;
extern int mu;
extern double novel_addition_prob;
extern int flag_subset_selection_scheme;
extern int SAinitN;
extern int SAt;


void init_argument(int, char**);
bool parse_argument(int, char**);
bool handleString(const char* value, void* field, size_t size);
bool handleBool(const char* value, void* field);
bool handleInt(const char* value, void* field, int min, int max);
bool handleLongLong(const char* value, void* field, long long min);
bool handleDouble(const char* value, void* field, double min, double max);

#endif