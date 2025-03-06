#ifndef INIT_ARGUMENT
#define INIT_ARGUMENT

extern char inst_filename[256];
extern bool flag_inst = false;
extern bool flag_auto_select = false;
extern bool flag_print_smart_format = false;
extern int seed = 0;
extern bool flag_seed = false;
extern long long max_step = 0;
extern int cutoff_time = 0;
extern bool flag_time = false;
extern bool flag_print_sol = false;
extern bool flag_print_step = false;
extern bool flag_perform_bms = false;
extern int BMS_T = 0;
extern int flag_subset_score_calculation = 0;
extern int flag_solution_initialization = 0;
extern bool flag_perform_cc = false;
extern bool flag_perform_iscc = false;
extern bool flag_perform_tabu = false;
extern int tabu_alpha = 0;
extern int flag_reconstruction = 0;
extern int reconstruct_swap_T = 0;
extern bool reconstruct_with_prob = false;
extern double reconstruct_prob = 0.0;
extern int flag_subset_removal_scheme = 0;
extern int flag_subset_addition = 0;
extern int flag_perform_alternate_method = 0;
extern int flag_update_item_weight_scheme = 0;
extern int SAPS_T = 0;
extern double SAPS_R = 0.0;
extern double PAWS_P = 0.0;
extern int mu = 0;
extern double novel_addition_prob = 0.0;
extern int flag_subset_selection_scheme = 0;
extern int SAinitN = 0;
extern int SAt = 0;


void init_argument(int, char**);
bool parse_argument(int, char**);

#endif