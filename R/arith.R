#' Add one
#'
#' @param x A single integer.
#'
#' @export
plus_one <- function(x) {
  .Call(cexport_plus_one, x)
}
