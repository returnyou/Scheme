#include <string.h>
#include "bool.h"
#include "list.h"
#include "env.h"

scm_object scm_true[1];
scm_object scm_false[1];
scm_object scm_void[1];

static scm_object* boolean_p_prim(int, scm_object *[]);
static scm_object* not_p_prim(int, scm_object *[]);
static scm_object* eq_p_prim(int, scm_object *[]);
static scm_object* equal_p_prim(int, scm_object *[]);

static int equal(scm_object *, scm_object *);

void scm_init_bool(scm_env *env)
{
    // initialize types
    scm_true->type = scm_true_type;
    scm_false->type = scm_false_type;
    scm_void->type = scm_void_type;

    scm_add_prim(env, "boolean?", boolean_p_prim, 1, 1);
    scm_add_prim(env, "not", not_p_prim, 1, 1);
    scm_add_prim(env, "eq?", eq_p_prim, 2, 2);
    scm_add_prim(env, "equal?", equal_p_prim, 2, 2);
}

static int equal(scm_object *x, scm_object *y)
{
    if (!SAME_OBJ(x, y))
        return 0;
    if (!SCM_SAME_TYPE(SCM_TYPE(x), SCM_TYPE(y))) // types: true, false, null...
        return 0;
    
    switch (SCM_TYPE(x)) {
        case scm_integer_type:
            return SCM_INT_VAL(x) == SCM_INT_VAL(y);
        case scm_float_type:
            return SCM_FLOAT_VAL(x) == SCM_FLOAT_VAL(y);
        case scm_char_type:
            return SCM_CHAR_VAL(x) == SCM_CHAR_VAL(y);
        case scm_string_type:
            return strcmp(SCM_CHAR_STR_VAL(x), SCM_CHAR_STR_VAL(y)) == 0;
        case scm_symbol_type:
            return strcmp(SCM_SYMBOL_STR_VAL(x), SCM_SYMBOL_STR_VAL(y)) == 0;
        case scm_pair_type:
            // TODO: equal of pair
            return 0;
    }
    return 0;
}

static scm_object* boolean_p_prim(int argc, scm_object *argv[])
{
    return SCM_BOOL(SCM_BOOLP(argv[0]));
}

static scm_object* not_p_prim(int argc, scm_object *argv[])
{
    return SCM_FALSEP(argv[0]) ? scm_true : scm_false;
}

static scm_object* eq_p_prim(int argc, scm_object *argv[])
{
    return SCM_BOOL(equal(argv[0], argv[1]));
}

static scm_object* equal_p_prim(int argc, scm_object *argv[])
{
    return SCM_BOOL(equal(argv[0], argv[1]));
}