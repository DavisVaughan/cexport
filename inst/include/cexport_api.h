#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

// (SEXP (*)(SEXP))
//  ^     ^  ^
//  |     |  |- Takes a SEXP
//  |     |- Object is a function pointer
//  |- Returns a SEXP

// We make the pointer static so it is only looked up once

SEXP cexport_plus_one(SEXP x) {
  static SEXP (*f)() = NULL;

  if (f == NULL) {
    f = (SEXP (*)(SEXP)) R_GetCCallable("cexport", "cexport_plus_one");
  }

  return f(x);
}
