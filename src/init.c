#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP cexport_plus_one(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"cexport_plus_one", (DL_FUNC) &cexport_plus_one, 1},
  {NULL, NULL, 0}
};

void R_init_cexport(DllInfo *dll)
{
  // Register `cexport_plus_one` to be used at the C level from other pkgs
  // We also use R_GetCCallable() and provide a wrapper for users to include
  // in inst/include/cexport.h
  R_RegisterCCallable("cexport", "cexport_plus_one", (DL_FUNC) &cexport_plus_one);

  // Register `cexport_plus_one` to be used from R
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
