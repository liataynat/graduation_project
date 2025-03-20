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

std::string inst_filename;
bool flag_inst = false;
bool flag_auto_select = false;
bool flag_print_smart_format = false;
int seed = 0;
bool flag_seed = false;
bool flag_time = false;
bool flag_print_sol = false;
bool flag_print_step = false;
bool flag_perform_bms = false;
int flag_subset_score_calculation = 0;
int flag_solution_initialization = 0;
bool flag_perform_cc = false;
bool flag_perform_iscc = false;
bool flag_perform_tabu = false;
int flag_reconstruction = 0;
int flag_subset_removal_scheme = 0;
int flag_subset_addition = 0;
int flag_perform_alternate_method = 0;
int flag_update_item_weight_scheme = 0;
int flag_subset_selection_scheme = 0;

// typedef enum {
//     TYPE_INT,
//     TYPE_LONG_LONG,
//     TYPE_DOUBLE,
//     TYPE_BOOL,
//     TYPE_STRING
// } FieldType;

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

typedef bool (*ArgHandler)(const char* value, FieldType fieldtype, void* field, void* min, void* max);

typedef struct {
    const char* name;
    ArgHandler handler;
    FieldType fieldtype;
    void* field;
    void* min;
    void* max;
} ParamEntry;

double double_min = 0.0;
double double_max = 1.0;
bool parse_argument(int argc,char **argv){
    int i;
    default_algorithm_settings();
    ParamEntry paramTable[] = {
        {"-inst", handleString, TYPE_STRING, &inst_filename, (void*)256, 0},
        {"-auto", handleBool, TYPE_BOOL,&flag_auto_select,0,0},
        {"-formatted_print", handleBool, TYPE_BOOL, &flag_print_smart_format,0,0},
        {"-seed", handleInt, TYPE_INT,&seed, 0, (void*)INT_MAX},
        {"-max_step", handleLongLong, TYPE_LONG_LONG, &max_step, (void*)1, (void*)__LONG_LONG_MAX__},
        {"-cutoff_time", handleInt, TYPE_INT,&cutoff_time, (void*)1, (void*)INT_MAX},
        {"-print_sol", handleBool, TYPE_BOOL,&flag_print_sol ,0,0},
        {"-print_step", handleBool, TYPE_BOOL,&flag_print_step,0,0},
        {"-perform_bms", handleBool, TYPE_BOOL,&flag_perform_bms,0,0},
        {"-bms_t", handleInt, TYPE_INT, &BMS_T, (void*)1, (void*)INT_MAX},
        {"-subset_score_calculation", handleInt, TYPE_INT, &flag_subset_score_calculation, 0, (void*)2},
        {"-solution_initialization_scheme", handleInt, TYPE_INT, &flag_solution_initialization, (void*)1, (void*)4},
        {"-perform_cc", handleBool, TYPE_BOOL,&flag_perform_cc,0,0},
        {"-perform_iscc", handleBool, TYPE_BOOL,&flag_perform_iscc,0,0},
        {"-perform_tabu", handleBool, TYPE_BOOL,&flag_perform_tabu,0,0},
        {"-tabu_alpha", handleInt, TYPE_INT, &tabu_alpha, (void*)1, (void*)INT_MAX},
        {"-reconstruction_scheme", handleInt, TYPE_INT,&flag_reconstruction, (void*)1, (void*)3},
        {"-reconstruct_swap_T", handleInt, TYPE_INT, &reconstruct_swap_T, (void*)2, (void*)INT_MAX},
        {"-reconstruction_with_prob", handleBool, TYPE_BOOL, &reconstruct_with_prob,0,0},
        {"-reconstruction_prob", handleDouble, TYPE_DOUBLE, &reconstruct_prob, &double_min, &double_max},
        {"-subset_removal_scheme", handleInt, TYPE_INT, &flag_subset_removal_scheme, (void*)1, (void*)2},
        {"-subset_addition_scheme", handleInt, TYPE_INT, &flag_subset_addition, (void*)1, (void*)6},
        {"-perform_alternate_method", handleInt, TYPE_INT, &flag_perform_alternate_method, (void*)1, (void*)4},
        {"-update_item_values_scheme", handleInt, TYPE_INT, &flag_update_item_weight_scheme, (void*)1, (void*)4},
        {"-update_item_values_SAPST", handleInt, TYPE_INT, &SAPS_T, (void*)1, (void*)INT_MAX},
        {"-update_item_values_SAPSR", handleDouble, TYPE_DOUBLE, &SAPS_R,  &double_min, &double_max},
        {"-update_item_values_PAWSP", handleDouble, TYPE_DOUBLE, &PAWS_P,  &double_min, &double_max},
        {"-united_calculation_mu", handleInt, TYPE_INT, &mu, (void*)2, (void*)INT_MAX},
        {"-novel_addition_prob", handleDouble, TYPE_DOUBLE, &novel_addition_prob, &double_min, &double_max},
        {"-subset_selection_scheme", handleInt, TYPE_INT, &flag_subset_selection_scheme, (void*)1, (void*)9},
        {"-SAinitN", handleInt, TYPE_INT, &SAinitN, (void*)2, (void*)5},
        {"-SAt", handleInt, TYPE_INT, &SAt, (void*)1, (void*)INT_MAX},
        {NULL,NULL,TYPE_INT,NULL,NULL,NULL}
    };

    for (int i = 1; i < argc; i++) {
        bool found = false;
        for (int j = 0; paramTable[j].name != NULL; j++) {
            if (strcmp(argv[i], paramTable[j].name) == 0) {
                if (i + 1 >= argc) {
                    cout << "argc_num error"  << endl;
                    return false;
                }
                if (!paramTable[j].handler(argv[i + 1], paramTable[j].fieldtype, paramTable[j].field, paramTable[j].min, paramTable[j].max)) {
                    cout << "argv_content error" << endl;
                    return false;
                }
                if(strcmp(paramTable[j].name,"-inst") == 0){
                    flag_inst = true;
                }else if(strcmp(paramTable[j].name,"-seed") == 0){
                    flag_seed = true;
                }else if(strcmp(paramTable[j].name,"-cutoff_time") == 0){
                    flag_time = true;
                }
                i++; 
                found = true;
                break;
            }
        }
        if (!found) {
            // 未知参数
            cout << "unknown argument error" << endl;
            return false;
        }
    }

    //copy
    // cout << flag_auto_select << endl;
    // cout << flag_inst << endl;
    cout << flag_subset_score_calculation << endl;
    cout << init_scores_ptr << endl;

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

bool handleString(const char* value, FieldType fieldtype, void* field, void* min, void* max) {
    std::string* str = (std::string*)field; // 将 void* 转换为 std::string*
    int* size_ptr = (int*)min;             // 将 void* 转换为 int*
    int size = *size_ptr;                  // 获取目标字段的大小
    *str = value; // 使用 std::string 的赋值操作
    // flag_inst = true;
    return true;
}

bool handleBool(const char* value, FieldType fieldtype, void* field, void* min, void* max) {
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

bool handleInt(const char* value, FieldType fieldtype, void* field, void* min, void* max) {
    int* num = (int*)field;
    int* min_val = (int*)min;
    int* max_val = (int*)max;
    if (sscanf(value, "%d", num) != 1 || *num < *min_val || *num > *max_val) return false;
    return true;
}

bool handleLongLong(const char* value, FieldType fieldtype, void* field, void* min, void* max) {
    long long* num = (long long*)field;
    long long* min_val = (long long*)min;
    long long* max_val = (long long*)max;
    if (sscanf(value, "%lld", num) != 1 || *num < *min_val || *num > *max_val) return false;
    return true;
}

bool handleDouble(const char* value, FieldType fieldtype, void* field, void* min, void* max) {
    double* num = (double*)field;
    double* min_val = (double*)min;
    double* max_val = (double*)max;
    if (sscanf(value, "%lf", num) != 1 || *num < *min_val || *num > *max_val) return false;
    return true;
}
