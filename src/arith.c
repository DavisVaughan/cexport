#include "cexport.h"

SEXP cexport_plus_one(SEXP x) {
  if (!Rf_isInteger(x)) {
    Rf_errorcall(R_NilValue, "`x` must be an integer.");
  }

  if (Rf_length(x) != 1) {
    Rf_errorcall(R_NilValue, "`x` must be be length 1.");
  }

  int out = INTEGER(x)[0] + 1;

  return Rf_ScalarInteger(out);
}
