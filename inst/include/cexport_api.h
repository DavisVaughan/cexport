#ifndef cexport_api_h
#define cexport_api_h

#include <Rinternals.h> // For SEXP usage
#include <R_ext/Rdynload.h> // For R_GetCCallable

// Function pointer signature:
// (SEXP (*)(SEXP))
//  ^     ^  ^
//  |     |  |- Takes a SEXP
//  |     |- Object is a function pointer
//  |- Returns a SEXP

static R_INLINE SEXP cexport_plus_one(SEXP x) {
  // Initialize a static function pointer that persists between fn calls
  static SEXP (*fn)(SEXP) = NULL;

  // Only look it up once
  if (fn == NULL) {
    fn = (SEXP (*)(SEXP)) R_GetCCallable("cexport", "cexport_plus_one");
  }

  // Call the function
  return fn(x);
}

#endif // cexport_api_h
