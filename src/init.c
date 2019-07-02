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
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
