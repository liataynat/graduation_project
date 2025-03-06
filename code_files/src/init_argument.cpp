#include "../include/init_argument.h"
#include "../include/init_signal.h"
#include "../include/basis.h"
#include <stdio.h>

// typedef struct {
//     string inst_filename;
//     bool flag_inst;
//     bool flag_auto_select;
//     bool flag_print_smart_format;
//     int seed;
//     bool flag_seed;
//     long long max_step;
//     int cutoff_time;
//     bool flag_time;
//     bool flag_print_sol;
//     bool flag_print_step;
//     bool flag_perform_bms;
//     int BMS_T;
//     int flag_subset_score_calculation;
//     int flag_solution_initialization;
//     bool flag_perform_cc;
//     bool flag_perform_iscc;
//     bool flag_perform_tabu;
//     int tabu_alpha;
//     int flag_reconstruction;
//     int reconstruct_swap_T;
//     bool reconstruct_with_prob;
//     double reconstruct_prob;
//     int flag_subset_removal_scheme;
//     int flag_subset_addition;
//     int flag_perform_alternate_method;
//     int flag_update_item_weight_scheme;
//     int SAPS_T;
//     double SAPS_R;
//     double PAWS_P;
//     int mu;
//     double novel_addition_prob;
//     int flag_subset_selection_scheme;
//     int SAinitN;
//     int SAt;
// } CommandLineArgs;

char inst_filename[256];
bool flag_inst = false;
bool flag_auto_select = false;
bool flag_print_smart_format = false;
int seed = 0;
bool flag_seed = false;
long long max_step = 0;
int cutoff_time = 0;
bool flag_time = false;
bool flag_print_sol = false;
bool flag_print_step = false;
bool flag_perform_bms = false;
int BMS_T = 0;
int flag_subset_score_calculation = 0;
int flag_solution_initialization = 0;
bool flag_perform_cc = false;
bool flag_perform_iscc = false;
bool flag_perform_tabu = false;
int tabu_alpha = 0;
int flag_reconstruction = 0;
int reconstruct_swap_T = 0;
bool reconstruct_with_prob = false;
double reconstruct_prob = 0.0;
int flag_subset_removal_scheme = 0;
int flag_subset_addition = 0;
int flag_perform_alternate_method = 0;
int flag_update_item_weight_scheme = 0;
int SAPS_T = 0;
double SAPS_R = 0.0;
double PAWS_P = 0.0;
int mu = 0;
double novel_addition_prob = 0.0;
int flag_subset_selection_scheme = 0;
int SAinitN = 0;
int SAt = 0;

void init_argument(int argc, char **argv){
    init_signal();

    if(!parse_argument(argc,argv)){
        cout << "argument error" << endl;
        return ;
    };

    best_step = LONG_LONG_MAX;
    rng.seed(seed);

    return ;
}


typedef struct {
    const char* name;
    ArgHandler handler;
    void* field;
    int min;
    int max;
} ParamEntry;

bool parse_argument(int argc,char **argv){
    int i;
    // CommandLineArgs args = {0};
    // ParamEntry paramTable[] = {
    //     {"-inst", handleString, &args.inst_filename, 0, sizeof(args.inst_filename)},
    //     {"-auto", handleBool, &args.flag_auto_select, 0, 0},
    //     {"-formatted_print", handleBool, &args.flag_print_smart_format, 0, 0},
    //     {"-seed", handleInt, &args.seed, 0, INT_MAX},
    //     {"-max_step", handleLongLong, &args.max_step, 1, LLONG_MAX},
    //     {"-cutoff_time", handleInt, &args.cutoff_time, 1, INT_MAX},
    //     {"-print_sol", handleBool, &args.flag_print_sol, 0, 0},
    //     {"-print_step", handleBool, &args.flag_print_step, 0, 0},
    //     {"-perform_bms", handleBool, &args.flag_perform_bms, 0, 0},
    //     {"-bms_t", handleInt, &args.BMS_T, 1, INT_MAX},
    //     {"-subset_score_calculation", handleInt, &args.flag_subset_score_calculation, 0, 2},
    //     {"-solution_initialization_scheme", handleInt, &args.flag_solution_initialization, 1, 4},
    //     {"-perform_cc", handleBool, &args.flag_perform_cc, 0, 0},
    //     {"-perform_iscc", handleBool, &args.flag_perform_iscc, 0, 0},
    //     {"-perform_tabu", handleBool, &args.flag_perform_tabu, 0, 0},
    //     {"-tabu_alpha", handleInt, &args.tabu_alpha, 1, INT_MAX},
    //     {"-reconstruction_scheme", handleInt, &args.flag_reconstruction, 1, 3},
    //     {"-reconstruct_swap_T", handleInt, &args.reconstruct_swap_T, 2, INT_MAX},
    //     {"-reconstruction_with_prob", handleBool, &args.reconstruct_with_prob, 0, 0},
    //     {"-reconstruction_prob", handleDouble, &args.reconstruct_prob, 0.0, 1.0},
    //     {"-subset_removal_scheme", handleInt, &args.flag_subset_removal_scheme, 1, 2},
    //     {"-subset_addition_scheme", handleInt, &args.flag_subset_addition, 1, 6},
    //     {"-perform_alternate_method", handleInt, &args.flag_perform_alternate_method, 1, 4},
    //     {"-update_item_values_scheme", handleInt, &args.flag_update_item_weight_scheme, 1, 4},
    //     {"-update_item_values_SAPST", handleInt, &args.SAPS_T, 1, INT_MAX},
    //     {"-update_item_values_SAPSR", handleDouble, &args.SAPS_R, 0.0, 1.0},
    //     {"-update_item_values_PAWSP", handleDouble, &args.PAWS_P, 0.0, 1.0},
    //     {"-united_calculation_mu", handleInt, &args.mu, 2, INT_MAX},
    //     {"-novel_addition_prob", handleDouble, &args.novel_addition_prob, 0.0, 1.0},
    //     {"-subset_selection_scheme", handleInt, &args.flag_subset_selection_scheme, 1, 9},
    //     {"-SAinitN", handleInt, &args.SAinitN, 2, 5},
    //     {"-SAt", handleInt, &args.SAt, 1, INT_MAX},
    //     {NULL, NULL, NULL, 0, 0} // 结束标志
    // };
    // for (int i = 1; i < argc; i++) {
    //     bool found = false;
    //     for (int j = 0; paramTable[j].name != NULL; j++) {
    //         if (strcmp(argv[i], paramTable[j].name) == 0) {
    //             if (++i >= argc) return false; // 参数缺失
    //             if (!paramTable[j].handler(argv[i], &args, paramTable[j].field, paramTable[j].min, paramTable[j].max)) {
    //                 return false; // 参数解析失败
    //             }
    //             found = true;
    //             break;
    //         }
    //     }
    //     if (!found) {
    //         fprintf(stderr, "Unknown argument: %s\n", argv[i]);
    //         return false; // 未知参数
    //     }
    // }
    ParamEntry paramTable[] = {
        {"-inst", handleString, inst_filename, sizeof(inst_filename)},
        {"-auto", handleBool, &flag_auto_select},
        {"-formatted_print", handleBool, &flag_print_smart_format},
        {"-seed", handleInt, &seed, 0, INT_MAX},
        {"-max_step", handleLongLong, &max_step, 1},
        {"-cutoff_time", handleInt, &cutoff_time, 1, INT_MAX},
        {"-print_sol", handleBool, &flag_print_sol},
        {"-print_step", handleBool, &flag_print_step},
        {"-perform_bms", handleBool, &flag_perform_bms},
        {"-bms_t", handleInt, &BMS_T, 1, INT_MAX},
        {"-subset_score_calculation", handleInt, &flag_subset_score_calculation, 0, 2},
        {"-solution_initialization_scheme", handleInt, &flag_solution_initialization, 1, 4},
        {"-perform_cc", handleBool, &flag_perform_cc},
        {"-perform_iscc", handleBool, &flag_perform_iscc},
        {"-perform_tabu", handleBool, &flag_perform_tabu},
        {"-tabu_alpha", handleInt, &tabu_alpha, 1, INT_MAX},
        {"-reconstruction_scheme", handleInt, &flag_reconstruction, 1, 3},
        {"-reconstruct_swap_T", handleInt, &reconstruct_swap_T, 2, INT_MAX},
        {"-reconstruction_with_prob", handleBool, &reconstruct_with_prob},
        {"-reconstruction_prob", handleDouble, &reconstruct_prob, 0.0, 1.0},
        {"-subset_removal_scheme", handleInt, &flag_subset_removal_scheme, 1, 2},
        {"-subset_addition_scheme", handleInt, &flag_subset_addition, 1, 6},
        {"-perform_alternate_method", handleInt, &flag_perform_alternate_method, 1, 4},
        {"-update_item_values_scheme", handleInt, &flag_update_item_weight_scheme, 1, 4},
        {"-update_item_values_SAPST", handleInt, &SAPS_T, 1, INT_MAX},
        {"-update_item_values_SAPSR", handleDouble, &SAPS_R, 0.0, 1.0},
        {"-update_item_values_PAWSP", handleDouble, &PAWS_P, 0.0, 1.0},
        {"-united_calculation_mu", handleInt, &mu, 2, INT_MAX},
        {"-novel_addition_prob", handleDouble, &novel_addition_prob, 0.0, 1.0},
        {"-subset_selection_scheme", handleInt, &flag_subset_selection_scheme, 1, 9},
        {"-SAinitN", handleInt, &SAinitN, 2, 5},
        {"-SAt", handleInt, &SAt, 1, INT_MAX},
        {NULL, NULL, NULL, 0, 0}
    };


    //copy

    if(flag_auto_select) {
        if(!flag_inst) return false;
        ifstream infile(inst_filename);
        if (!infile.is_open()) {
            cout << "infile error" << endl;
            exit(1);
        }
        infile >> item_num >> set_num;

        if(item_num > 2500 && item_num < 5000 && set_num > 920000 && set_num < 1100000) // rail
            Rail_settings();

        if((item_num > 500 && item_num < 520 && set_num > 200 && set_num < 220) || 
            (item_num > 1000 && item_num < 1100 && set_num > 300 && set_num < 350) || 
            (item_num > 2000 && item_num < 2050 && set_num > 450 && set_num < 500) ||
            (item_num > 4000 && item_num < 4100 && set_num > 700 && set_num < 800))
            CLR_settings();

        if((item_num > 200 && item_num < 250 && set_num > 150 && set_num < 200) ||
            (item_num > 650 && item_num < 700 && set_num > 400 && set_num < 450) ||
            (item_num > 1700 && item_num < 1800 && set_num > 1000 && set_num < 1100) ||
            (item_num > 4600 && item_num < 4700 && set_num > 2300 && set_num < 2400))
            CYC_settings();

        if((item_num > 3000 && item_num < 3100 && set_num > 100 && set_num < 150) ||
            (item_num > 9800 && item_num < 9900 && set_num > 200 && set_num < 250) ||
            (item_num > 27200 && item_num < 27300 && set_num > 400 && set_num < 450) ||
            (item_num > 88400 && item_num < 88500 && set_num > 700 && set_num < 750))
            STS_settings();

        if(item_num > 100 && item_num < 150 && set_num > 150 && set_num < 200)
            ST_Small_settings();

        if((item_num > 450 && item_num < 500 && set_num > 2500 && set_num < 2600) ||
            (item_num > 450 && item_num < 500 && set_num > 2300 && set_num < 2400) ||
            (item_num > 600 && item_num < 650 && set_num > 3450 && set_num < 3500) ||
            (item_num > 2800 && item_num < 2850 && set_num > 13400 && set_num < 13500))
            ST_Medium_settings();

        if((item_num > 19100 && item_num < 19200 && set_num > 62500 && set_num < 62600) ||
            (item_num > 74000 && item_num < 75000 && set_num > 166000 && set_num < 167000))
            ST_Large_settings();

        if(item_num > 500 && item_num < 600 && set_num > 45000 && set_num < 65000) // rail507-582
            Rail_Small_LLVM_settings();

        if(item_num > 500 && item_num < 550 && set_num > 150 && set_num < 200) // BDBJ
            BDBJ_settings();

        if(item_num > 2800 && item_num < 2900 && set_num > 4500 && set_num < 4600)  // SQL
            SQL_settings();
        
        if(item_num > 450 && item_num < 500 && set_num > 2500 && set_num < 2600)  // BDBC
            BDBC_settings();
        
        if(item_num > 300 && item_num < 310 && set_num > 1100 && set_num < 1200)  // x264
            x264_settings();
        
        if(item_num > 150 && item_num < 200 && set_num > 1000 && set_num < 1050)  // LLVM
            Rail_Small_LLVM_settings();
        
        if(item_num > 11000 && item_num < 28500 && set_num > 5000 && set_num < 12000)  // scpcyc10-11
            CYC_Large_settings();
    }

    // cout << "reading params complete\n";

    switch(flag_subset_score_calculation) {
        case 1:
            compute_score_ptr = compute_score_basic;
            init_scores_ptr = init_scores_basic;
            delete_scores_ptr = delete_scores_basic;
            break;
        case 2:
            compute_score_ptr = compute_score_united;
            init_scores_ptr = init_scores_united;
            delete_scores_ptr = delete_scores_united;
            break;
    }

    switch(flag_solution_initialization) {
        case 1:
            init_sol_heuristic_ptr = init_solu_best_score;
            break;
        case 2:
            init_sol_heuristic_ptr = init_solu_best_score_no_bms;
            break;
        case 3:
            init_sol_heuristic_ptr = init_solu_item_based;
            break;
        case 4:
            init_sol_heuristic_ptr = init_solu_item_based_no_bms;
            break;
    }

    switch(flag_reconstruction) {
        case 1:
            reconstruct_solu_ptr = reconstruct_remove_one_randomly;
            reconstruct_swapT_init = reconstruct_swapT_init_none;
            reconstruct_swapT_delete = reconstruct_swapT_delete_none;
            break;
        case 2:
            reconstruct_solu_ptr = reconstruct_remove_one_best;
            reconstruct_swapT_init = reconstruct_swapT_init_none;
            reconstruct_swapT_delete = reconstruct_swapT_delete_none;
            break;
        case 3:
            reconstruct_solu_ptr = reconstruct_swap_t;
            reconstruct_swapT_init = reconstruct_swapT_init_do;
            reconstruct_swapT_delete = reconstruct_swapT_delete_do;
            break;
    }

    switch(flag_subset_removal_scheme) {
        case 1:
            get_rmN_ptr = remove_one;
            break;
        case 2:
            get_rmN_ptr = adaptive_removal;
            break;
    }

    switch(flag_subset_addition) {
        case 1:
            get_select_set_ptr = greedy_addition;
            break;
        case 2:
            get_select_set_ptr = novel_addition;
            break;
        case 3:
            get_select_set_ptr = local_greedy_addition;
            break;
        case 4:
            get_select_set_ptr = local_novel_addition_no_bms;
            break;
        case 5:
            get_select_set_ptr = prob_dis_addition;
            break;
        case 6:
            get_select_set_ptr = local_novel_addition;
            break;
    }

    switch(flag_update_item_weight_scheme) {
        case 1:
            update_variables_item_weighting_ptr = update_variables_SAPS;
            break;
        case 2:
            update_variables_item_weighting_ptr = update_variables_PAWS;
            break;
        case 3:
            update_variables_item_weighting_ptr = update_variables_NuSC;
            break;
        case 4:
            update_variables_item_weighting_ptr = update_variables_no_item_weighting;
            break;
    }

    switch(flag_subset_selection_scheme) {
        case 1:
            break_ties_ptr = break_ties_random;
            break;
        case 2:
            break_ties_ptr = break_ties_weight;
            break;
        case 3:
            break_ties_ptr = break_ties_age;
            break;
        case 4:
            break_ties_ptr = break_ties_subscore_random;
            break;
        case 5:
            break_ties_ptr = break_ties_subscore_weight;
            break;
        case 6:
            break_ties_ptr = break_ties_subscore_age;
            break;
        case 7:
            break_ties_ptr = break_ties_score;
            break;
        case 8:
            break_ties_ptr = break_ties_score_subscore;
            break;
        case 9:
            break_ties_ptr = break_ties_score_subscore_age;
            break;
    }

    // cout << "parsing arguments complete\n";

    if(flag_subset_score_calculation == 1) 
        if(flag_subset_selection_scheme > 3)
            return false;
    if(flag_perform_alternate_method == 4 && flag_subset_removal_scheme == 2) return false;
    return flag_inst;



}//好多啊

typedef bool (*ArgHandler)(const char* value, void* field, ...);

// bool handleString(const char* value, CommandLineArgs* args, char* field, size_t size) {
//     if (strlen(value) >= size) return false; // 检查长度是否超出
//     strncpy(field, value, size - 1);
//     field[size - 1] = '\0'; // 确保字符串结束符
//     return true;
// }

// bool handleBool(const char* value, CommandLineArgs* args, bool* field) {
//     if (strcmp(value, "0") == 0) {
//         *field = false;
//     } else if (strcmp(value, "1") == 0) {
//         *field = true;
//     } else {
//         return false;
//     }
//     return true;
// }

// bool handleInt(const char* value, CommandLineArgs* args, int* field, int min, int max) {
//     if (sscanf(value, "%d", field) != 1 || *field < min || *field > max) return false;
//     return true;
// }

// bool handleLongLong(const char* value, CommandLineArgs* args, long long* field, long long min) {
//     if (sscanf(value, "%lld", field) != 1 || *field < min) return false;
//     return true;
// }

// bool handleDouble(const char* value, CommandLineArgs* args, double* field, double min, double max) {
//     if (sscanf(value, "%lf", field) != 1 || *field < min || *field > max) return false;
//     return true;
// }

bool handleString(const char* value, void* field, size_t size) {
    char* str = (char*)field;
    if (strlen(value) >= size) return false;
    strncpy(str, value, size - 1);
    str[size - 1] = '\0';
    return true;
}

bool handleBool(const char* value, void* field) {
    bool* b = (bool*)field;
    if (strcmp(value, "0") == 0) {
        *b = false;
    } else if (strcmp(value, "1") == 0) {
        *b = true;
    } else {
        return false;
    }
    return true;
}

bool handleInt(const char* value, void* field, int min, int max) {
    int* num = (int*)field;
    if (sscanf(value, "%d", num) != 1 || *num < min || *num > max) return false;
    return true;
}

bool handleLongLong(const char* value, void* field, long long min) {
    long long* num = (long long*)field;
    if (sscanf(value, "%lld", num) != 1 || *num < min) return false;
    return true;
}

bool handleDouble(const char* value, void* field, double min, double max) {
    double* num = (double*)field;
    if (sscanf(value, "%lf", num) != 1 || *num < min || *num > max) return false;
    return true;
}
