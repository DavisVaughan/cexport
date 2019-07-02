
<!-- README.md is generated from README.Rmd. Please edit that file -->

# cexport

This README holds an example of:

  - Creating a C function that you can call from R.

  - “Registering” that C callable to be called from *another package’s*
    C code.

  - “Getting” the registered C callable and providing an easy header
    file for other packages to use.

  - Actually calling that function from another package’s C code.

This package implements, registers, and exports the function that will
be called in other packages.

The other package that goes along with this one and actually calls the C
function from it’s own C code is
[cexportuser](https://github.com/DavisVaughan/cexportuser).

You can install this package with:

``` r
devtools::install_github("DavisVaughan/cexport")
```

You can install the companion package that uses this C code (which
should “just work” and also install cexport if needed) with:

``` r
devtools::install_github("DavisVaughan/cexportuser")
```

# Details

Here are the steps to do this yourself:

  - Create your C function (`src/arith.c` - `cexport_plus_one()`)

  - Optionally export it to R with the standard `R_registerRoutines()`
    (`src/init.c`) and `#' @useDynLib cexport, .registration = TRUE`
    (`cexport-package.R`).

  - “Register” the C callable with `R_RegisterCCallable()` so other
    packages can find it with `R_GetCCallable()` (`src/init.c`).

  - At this point, you can either let users call `R_GetCCallable()`
    themselves in their own package, or you can be nice and generate a
    header file that they can just `#include` to get access to your API.

  - Let’s be nice. In `inst/include/cexport_api.h` we create an API
    function with the same signature as our original function, look up
    the C callable once, and call the function.

  - Now install the package.

The next section will be from the perspective of a package that is going
to be calling `cexport_plus_one()` from their own C code. That package
is [cexportuser](https://github.com/DavisVaughan/cexportuser).

  - In the package that is going to be calling `cexport_plus_one()`, add
    `LinkingTo: cexport`.

  - Now also add `Imports: cexport`. This is *required* as you have to
    fully load `cexport` to be able to use its C callables.

  - You must also `@importFrom` *something* from `cexport` so it gets
    loaded. I imported the `plus_one()` function
    (`cexportuser-package.R`).

  - Create your C function that is going to call `cexport_plus_one()`.
    At the top of the file put `#include <cexport_api.h>`. RStudio
    should recognize this for you. You can now call
    `cexport_plus_one()`. (`src/arith.h` - `cexportuser_plus_two()`).

  - Export the C function to R if you want (`src/init.c`, exported as
    `plus_two()` in `arith.R`).

If all goes well you should be able to do something like:

``` r
library(cexportuser)
plus_two(2L)
#> [1] 4
```

# References

A few packages do this:

  - [bdsmatrix](https://github.com/cran/bdsmatrix)
  - [xts](https://github.com/joshuaulrich/xts)

Also R Extensions has some
    advice:

  - <https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Linking-to-native-routines-in-other-packages>

And there is some information in R Packages:

  - [Exporting C Code](https://r-pkgs.org/src.html#c-export)
  - [Importing C Code](https://r-pkgs.org/src.html#c-import)
