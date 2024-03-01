set(cross_prefix aarch64-linux-gnu-)

set(CMAKE_C_COMPILER ${cross_prefix}gcc)
set(CMAKE_CXX_COMPILER ${cross_prefix}g++)
set(CMAKE_ASM_COMPILER ${cross_prefix}gcc)
set(CMAKE_AR ${cross_prefix}ar)
set(CMAKE_RANLIB ${cross_prefix}ranlib)
set(CMAKE_LINKER ${cross_prefix}ld)
set(CMAKE_STRIP ${cross_prefix}strip)
