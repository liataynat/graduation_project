#ifndef INIT_ARGUMENT
#define INIT_ARGUMENT

#include "basis.h" 

extern std::string inst_filename;
extern bool flag_inst ;
extern bool flag_auto_select;
extern bool flag_print_smart_format;
extern int seed;
extern bool flag_seed;
extern bool flag_time;
extern bool flag_print_sol;
extern bool flag_print_step;
extern bool flag_perform_bms;
extern int flag_subset_score_calculation;
extern int flag_solution_initialization;
extern bool flag_perform_cc;
extern bool flag_perform_iscc;
extern bool flag_perform_tabu;
extern int flag_reconstruction;
extern int flag_subset_removal_scheme;
extern int flag_subset_addition;
extern int flag_perform_alternate_method;
extern int flag_update_item_weight_scheme;
extern int flag_subset_selection_scheme;

typedef enum {
    TYPE_INT,
    TYPE_LONG_LONG,
    TYPE_DOUBLE,
    TYPE_BOOL,
    TYPE_STRING
} FieldType;


void init_argument(int, char**);
bool parse_argument(int, char**);
bool handleString(const char* value, FieldType fieldtype, void* field, void* min, void* max);
bool handleBool(const char* value, FieldType fieldtype, void* field, void* min, void* max);
bool handleInt(const char* value, FieldType fieldtype, void* field, void* min, void* max);
bool handleLongLong(const char* value, FieldType fieldtype, void* field, void* min, void* max);
bool handleDouble(const char* value, FieldType fieldtype, void* field, void* min, void* max);

#endif