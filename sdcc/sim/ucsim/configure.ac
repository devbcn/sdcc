#!/bin/sh

AC_PREREQ(2.60)
AC_INIT
AC_CONFIG_SRCDIR(.version)
AC_CONFIG_HEADER(ddconfig.h:ddconfig_in.h)

AC_PROG_AWK

AC_MSG_CHECKING(version of the package)
if test -f ${srcdir}/.version; then
  { read VERSION; } < ${srcdir}/.version
  AC_MSG_RESULT($VERSION)
else
  VERSION="0.0.0"
  AC_MSG_RESULT(unknown using 0.0.0)
fi
VERSIONHI=`echo $VERSION|$AWK 'BEGIN {FS="."} {print $1}'`
VERSIONLO=`echo $VERSION|$AWK 'BEGIN {FS="."} {print $2}'`
VERSIONP=`echo $VERSION|$AWK 'BEGIN {FS="."} {print $3}'`
AC_SUBST(VERSION)
AC_SUBST(VERSIONHI)
AC_SUBST(VERSIONLO)
AC_SUBST(VERSIONP)
AC_DEFINE_UNQUOTED(VERSIONSTR, "${VERSION}", [XXX])
AC_DEFINE_UNQUOTED(VERSIONHI, $VERSIONHI, [XXX])
AC_DEFINE_UNQUOTED(VERSIONLO, $VERSIONLO, [XXX])
AC_DEFINE_UNQUOTED(VERSIONP, $VERSIONP, [XXX])
AC_ARG_PROGRAM
# Some options
#==============
# *nix default: "${datadir}/sdcc/doc"
AC_ARG_VAR(docdir, documentation installation directory)
if test "${docdir}" = ""; then
    docdir="\${datadir}"/sdcc/doc
fi
AC_SUBST(docdir)

AC_ARG_ENABLE(ucsim,
[  --enable-ucsim          compile ucsim frontend],
if test $enable_ucsim != "no"; then
    enable_ucsim="yes"
fi,
#default
enable_ucsim="no")
AC_ARG_ENABLE(dlso,
[  --enable-dlso           compile dynamically loadable shared libraries],
if test $enable_dlso != "no"; then
    enable_dlso="yes"
fi,
enable_dlso="no")
AC_ARG_ENABLE(mcs51-port,
[  --disable-mcs51-port    do not compile simulator for mcs51],
if test $enable_mcs51_port != "no"; then
    enable_mcs51_port="yes"
fi,
enable_mcs51_port="yes")
AC_ARG_ENABLE(ds390-port,
[  --disable-ds390-port    do not compile simulator for ds390],
if test $enable_ds390_port != "no"; then
    enable_ds390_port="yes"
fi,
enable_ds390_port="yes")
AC_ARG_ENABLE(avr-port,
[  --enable-avr-port       compile simulator for AVR],
if test $enable_avr_port != "no"; then
    enable_avr_port="yes"
fi,
enable_avr_port="no")
AC_ARG_ENABLE(z80-port,
[  --disable-z80-port      do not compile simulator for z80],
if test $enable_z80_port != "no"; then
    enable_z80_port="yes"
fi,
enable_z80_port="yes")
AC_ARG_ENABLE(z180-port,
[  --disable-z180-port     do not compile simulator for z180],
if test $enable_z180_port != "no"; then
    enable_z180_port="yes"
fi,
enable_z180_port="yes")
AC_ARG_ENABLE(gbz80-port,
[  --disable-gbz80-port    do not compile simulator for gbz80],
if test $enable_gbz80_port != "no"; then
    enable_gbz80_port="yes"
fi,
enable_gbz80_port="yes")
AC_ARG_ENABLE(r2k-port,
[  --disable-r2k-port      do not compile simulator for r2k],
if test $enable_r2k_port != "no"; then
    enable_r2k_port="yes"
fi,
enable_r2k_port="yes")
AC_ARG_ENABLE(r3ka-port,
[  --disable-r3ka-port     do not compile simulator for r3ka],
if test $enable_r3ka_port != "no"; then
    enable_r3ka_port="yes"
fi,
enable_r3ka_port="yes")
AC_ARG_ENABLE(tlcs-port,
[  --disable-tlcs-port    do not compile simulator for TLCS],
if test $enable_tlcs_port != "no"; then
    enable_tlcs_port="yes"
fi,
enable_tlcs_port="yes")
AC_ARG_ENABLE(hc08-port,
[  --disable-hc08-port     do not compile simulator for hc08],
if test $enable_hc08_port != "no"; then
    enable_hc08_port="yes"
fi,
enable_hc08_port="yes")
AC_ARG_ENABLE(s08-port,
[  --disable-s08-port      do not compile simulator for s08],
if test $enable_s08_port != "no"; then
    enable_s08_port="yes"
fi,
enable_s08_port="yes")
AC_ARG_ENABLE(xa-port,
[  --enable-xa-port        compile simulator for xa],
if test $enable_xa_port != "no"; then
    enable_xa_port="yes"
fi,
enable_xa_port="no")
AC_ARG_ENABLE(stm8-port,
[  --disable-stm8-port     do not compile simulator for stm8],
if test $enable_stm8_port != "no"; then
    enable_stm8_port="yes"
fi,
enable_stm8_port="yes")
AC_ARG_ENABLE(st7-port,
[  --enable-st7-port       compile simulator for st7],
if test $enable_st7_port  != "no"; then
    enable_st7_port="yes"
fi,
enable_st7_port="no")
AC_ARG_ENABLE(serio,
[  --enable-serio          compile serio GUI tool (needs curses)],
if test $enable_serio != "no"; then
    enable_serio="yes"
fi,
enable_serio="no")
AC_SUBST(enable_ucsim)
AC_SUBST(enable_dlso)
AC_SUBST(enable_mcs51_port)
AC_SUBST(enable_ds390_port)
AC_SUBST(enable_avr_port)
AC_SUBST(enable_z80_port)
AC_SUBST(enable_z180_port)
AC_SUBST(enable_gbz80_port)
AC_SUBST(enable_r2k_port)
AC_SUBST(enable_r3ka_port)
AC_SUBST(enable_tlcs_port)
AC_SUBST(enable_hc08_port)
AC_SUBST(enable_s08_port)
AC_SUBST(enable_xa_port)
AC_SUBST(enable_stm8_port)
AC_SUBST(enable_st7_port)
AC_SUBST(enable_serio)

AC_ARG_ENABLE(statistic,
[  --enable-statistic      compile statistical features (slower simulation)],
if test $enable_statistic != "no"; then
   enable_statistic="yes"
fi,
enable_statistic="no")
AC_DEFINE_UNQUOTED(STATISTIC, $enable_statistic, [XXX])


# Required programs
#-------------------
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_INSTALL
AC_PROG_RANLIB
dnl AC_LANG_CPLUSPLUS

AC_CHECK_PROG(STRIP, strip, strip, :)

AC_LIBTOOL_DLOPEN
dnl AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

AC_PROG_LEX
if test ${LEX} = "flex"; then
        AC_DEFINE(HAVE_FLEX, 1, [XXX])
fi
AC_PROG_YACC


AC_LANG_CPLUSPLUS

# Checking for header files.
# ===========================================================================

if test -d /stuff/include; then
  CPPFLAGS="$CPPFLAGS -I/stuff/include"
fi

AC_HEADER_STDC
AC_CHECK_HEADERS(endian.h sys/endian.h machine/endian.h sys/isa_defs.h)
AC_CHECK_HEADERS(getopt.h)
AC_CHECK_HEADERS(unistd.h)
AC_CHECK_HEADERS(termios.h)

AC_CHECK_HEADER(curses.h,
  AC_DEFINE(HAVE_CURSES_H, 1, [XXX])
  curses_h_ok=yes,
  curses_h_ok=no
)

ucsim_cv_socket="unknown"
AC_CHECK_HEADER(sys/socket.h,
  AC_DEFINE(HAVE_SYS_SOCKET_H, 1, [XXX])
  AC_DEFINE(SOCKET_AVAIL, 1, [XXX])
  AC_DEFINE_UNQUOTED(UCSOCKET_T, int, [XXX])
  ucsim_cv_socket="<sys/socket.h>"
)

WINSOCK_AVAIL=0
if test $ucsim_cv_socket = unknown; then
  AC_CHECK_HEADER(winsock2.h,
    AC_DEFINE(HAVE_WINSOCK2_H, 1, [XXX])
    AC_DEFINE(SOCKET_AVAIL, 1, [XXX])
    AC_DEFINE_UNQUOTED(UCSOCKET_T, SOCKET, [XXX])
    ucsim_cv_socket="<winsock2.h>"
    WINSOCK_AVAIL=1
  )
fi
AC_SUBST(WINSOCK_AVAIL)

if test $ucsim_cv_socket != unknown; then
  AC_EGREP_HEADER(socklen_t,
    $ucsim_cv_socket,
    AC_DEFINE_UNQUOTED(SOCKLEN_T, socklen_t, [XXX]),
    AC_DEFINE_UNQUOTED(SOCKLEN_T, uint, [XXX]))
fi
AC_DEFINE_UNQUOTED(HEADER_SOCKET, ${ucsim_cv_socket}, [XXX])

AC_CHECK_HEADER(dlfcn.h)
AC_HEADER_DIRENT

# This must be after CXXCPP

AC_CACHE_CHECK(which header file defines FD_ macros, ucsim_cv_fd,
[ucsim_cv_fd="unknown"
AC_EGREP_CPP(yes, [
#include <winsock2.h>
#ifdef FD_ZERO
yes
#endif], ucsim_cv_fd="<winsock2.h>")
AC_EGREP_CPP(yes, [
#include <sys/time.h>
#ifdef FD_ZERO
yes
#endif], ucsim_cv_fd="<sys/time.h>")
AC_EGREP_CPP(yes, [
#include <sys/types.h>
#ifdef FD_ZERO
yes
#endif], ucsim_cv_fd="<sys/types.h>")
AC_EGREP_CPP(yes, [
#include <sys/select.h>
#ifdef FD_ZERO
yes
#endif], ucsim_cv_fd="<sys/select.h>")])

ucsim_cv_header_ok=0
if echo $ucsim_cv_fd|grep time >/dev/null 2>&1; then
AC_DEFINE(FD_NEED_TIME_H, 1, [XXX])
ucsim_cv_header_ok=1
else
AC_DEFINE(FD_NEED_TIME_H, 0, [XXX])
fi
if echo $ucsim_cv_fd|grep types >/dev/null 2>&1; then
AC_DEFINE(FD_NEED_TYPES_H, 1, [XXX])
ucsim_cv_header_ok=1
else
AC_DEFINE(FD_NEED_TYPES_H, 0, [XXX])
fi
if echo $ucsim_cv_fd|grep select >/dev/null 2>&1; then
AC_DEFINE(FD_NEED_SELECT_H, 1, [XXX])
ucsim_cv_header_ok=1
else
AC_DEFINE(FD_NEED_SELECT_H, 0, [XXX])
fi
if echo $ucsim_cv_fd|grep winsock2 >/dev/null 2>&1; then
AC_DEFINE(FD_NEED_WINSOCK2_H, 1, [XXX])
ucsim_cv_header_ok=1
else
AC_DEFINE(FD_NEED_WINSOCK2_H, 0, [XXX])
fi

AC_DEFINE_UNQUOTED(FD_HEADER_OK, ${ucsim_cv_header_ok}, [XXX])
AC_DEFINE_UNQUOTED(HEADER_FD, ${ucsim_cv_fd}, [XXX])


# Checking for functions/libs
# ===========================================================================
if echo $ucsim_cv_socket|grep winsock2 >/dev/null 2>&1; then
  LIBS="-lws2_32 $LIBS"
else
  AC_CHECK_LIB(socket,socket)
  AC_CHECK_LIB(nsl,xdr_short)
  AC_CHECK_LIB(rt,nanosleep)
fi

AC_CHECK_LIB(dl,dlopen,
dl_ok="yes"
DL="-ldl",
dl_ok="no"
DL="")
AC_SUBST(dl_ok)
AC_SUBST(DL)

#AC_CHECK_LIB(panel,panel_above,
#panel_ok="yes"
#curses_ok="yes"
#CURSES_LIBS="-lpanel -lcurses"
#,
#panel_ok="no"
#AC_CHECK_LIB(curses,nl,
#curses_ok="yes"
#CURSES_LIBS="-lcurses"
#,
#curses_ok="no")
#,
#-lcurses)
CURSES_LIBS=""
if test $curses_h_ok != yes; then
  panel_ok="no"
  curses_ok="no"
else
  AC_CHECK_LIB(panel,panel_above,
    panel_ok="yes"
    curses_ok="no"
    CURSES_LIBS="-lpanel",
    panel_ok="no"
    curses_ok="no"
  )

  if test $curses_ok != yes; then
    AC_CHECK_LIB(curses,nl,
      curses_ok="yes"
      CURSES_LIBS="${CURSES_LIBS} -lcurses",
      curses_ok="no")
  fi

  if test $curses_ok != yes; then
    AC_CHECK_LIB(ncurses,nl,
      curses_ok="yes"
      CURSES_LIBS="${CURSES_LIBS} -lncurses",
      curses_ok="no")
  fi
fi

AC_SUBST(panel_ok)
AC_SUBST(curses_ok)
AC_SUBST(CURSES_LIBS)

AC_FUNC_VPRINTF
AC_CHECK_FUNCS(vsnprintf)
AC_CHECK_FUNCS(_vsnprintf)
AC_CHECK_FUNCS(vasprintf)
AC_CHECK_FUNCS(strlen strcpy strcat strstr strcmp strerror strtok strdup)
AC_CHECK_FUNCS(strchr memcpy)
dnl AC_CHECK_FUNCS(getline)
dnl AC_CHECK_FUNCS(getdelim)
AC_CHECK_FUNCS(fgets)
AC_CHECK_FUNCS(yylex)

AC_CACHE_CHECK(whether scanf knows %a, ucsim_cv_scanf_a,
[echo "a b" >conftest.data
AC_TRY_RUN([
#include <stdio.h>
void main(void)
{
  FILE *f;
  char *a;
  int  i;
  if ((f= fopen("conftest.data", "r")) == NULL)
    exit(1);
  i= fscanf(f, " %a[a-z] ", &a);
  fclose(f);
  if (i == 0)
    exit(2);
  if (i == 1)
    exit(0);
  exit(3);
}],
ucsim_cv_scanf_a="yes",
ucsim_cv_scanf_a="no",
ucsim_cv_scanf_a="unknown")
])
if test "$ucsim_cv_scanf_a" = "yes"; then
  AC_DEFINE(SCANF_A, 1, [XXX])
fi

AC_CACHE_CHECK(whether getcwd is GNUish, ucsim_cv_getcwd,
[AC_TRY_RUN([
#include <unistd.h>
void main(void)
{
  if ((getcwd(NULL, 0)) == NULL)
    exit(1);
  exit(0);
}],
ucsim_cv_getcwd="yes",
ucsim_cv_getcwd="no",
ucsim_cv_getcwd="unknown")
])
if test "$ucsim_cv_getcwd" = "yes"; then
  AC_DEFINE(GNU_GETCWD, 1, [XXX])
fi

AC_DEFUN([ucsim_ACCEPT_LENGTH_T],
 [AC_CACHE_CHECK([for type of length pointer parameter of accept],
   ucsim_cv_accept_length_type,
   [ac_save_CPPFLAGS="$CPPFLAGS"
    ucsim_cv_accept_length_type=no
    for ac_val in int size_t socklen_t; do
      CPPFLAGS="$ac_save_CPPFLAGS -DACCEPT_SOCKLEN_T=$ac_val"
      AC_TRY_COMPILE([#include <sys/types.h>
#include ${ucsim_cv_socket}],
        [struct sockaddr a; $ac_val len; accept (0, &a, &len);],
        [ucsim_cv_accept_length_type=$ac_val; break])
    done
    CPPFLAGS="$ac_save_CPPFLAGS"])
  if test "$ucsim_cv_accept_length_type" != no; then
    AC_DEFINE_UNQUOTED(ACCEPT_SOCKLEN_T, $ucsim_cv_accept_length_type,
      [Define to be the type of length parameter of accept (without the \*').])
  fi
 ]
)
#'

ucsim_ACCEPT_LENGTH_T

# Macro definitions
###################

# Check whether the compiler for the current language is SunPRO.

AC_DEFUN([sdcc_IS_SUNPRO],
[AC_CACHE_CHECK([whether we are using the SunPRO _AC_LANG compiler],
  [sdcc_cv_[]_AC_LANG_ABBREV[]_compiler_sunpro],
  [_AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [[#if !defined __SUNPRO_C && !defined __SUNPRO_CC
       choke me
#endif
]])],
    [sdcc_cv_[]_AC_LANG_ABBREV[]_compiler_sunpro=yes],
    [sdcc_cv_[]_AC_LANG_ABBREV[]_compiler_sunpro=no])
])])

# sdcc_IS_VALID_OPTION macro checks if the current compiler, selected by 
# AC_LANG, supports option specified as the 1st parameter. The test fails if
# the compiler returns an error or in case something is writeen to stderr.
# For example: sdcc_VALID_OPT(-fPIC)

AC_DEFUN([sdcc_IS_VALID_OPTION],
[arg1=`echo $1 | sed -e"s/^-*//" -e"s/-/_/"`
ac_test_[]_AC_LANG_PREFIX[]FLAGS=${[]_AC_LANG_PREFIX[]FLAGS+set}
sdcc_save_[]_AC_LANG_PREFIX[]FLAGS=$[]_AC_LANG_PREFIX[]FLAGS
AC_CACHE_CHECK(whether _AC_LANG accepts $1, sdcc_cv_[]_AC_LANG_ABBREV[]_$arg1,
  [sdcc_save_[]_AC_LANG_ABBREV[]_werror_flag=$ac_[]_AC_LANG_ABBREV[]_werror_flag
   ac_[]_AC_LANG_ABBREV[]_werror_flag=yes
   
   []_AC_LANG_PREFIX[]FLAGS="$1"
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM()],
     [eval sdcc_cv_[]_AC_LANG_ABBREV[]_$arg1=yes],
     [eval sdcc_cv_[]_AC_LANG_ABBREV[]_$arg1=no])
   ac_[]_AC_LANG_ABBREV[]_werror_flag=$sdcc_save_[]_AC_LANG_ABBREV[]_werror_flag])
   []_AC_LANG_PREFIX[]FLAGS=$sdcc_save_[]_AC_LANG_PREFIX[]FLAGS
])

# Checking characteristics of compilers and other programs
# --------------------------------------------------------

# Cross compiling overrides
# FIXME
if test "$CC" = "i586-mingw32msvc-gcc"; then
  ac_cv_c_bigendian=no
  ac_cv_sizeof_char=1
  ac_cv_sizeof_short=2
  ac_cv_sizeof_int=4
  ac_cv_sizeof_long=4
  ac_cv_sizeof_long_long=4
fi

# Checking whether byte ordering is bigendian
# --------------------------------------------------------
AC_C_BIGENDIAN

PICOPT=""
SHAREDLIB="no"

if test "$ac_cv_cxx_compiler_gnu" = "yes"; then
  AC_CACHE_CHECK(whether preprocessor accepts -MM or -M,ucsim_cv_MM,
  echo "#include <stdio.h>" >_test_.c
  echo "" >>_test_.c
  $CXXCPP -v -MM _test_.c 1>&5 2>&5
  if test "$?" = "0"; then
    ucsim_cv_MM="-MM"
  else
    ucsim_cv_MM="-M"
  fi
  rm -f _test_.*)

  # This is the first time when CFLAGS are set/modified!!

  sdcc_IS_VALID_OPTION(-ggdb)
  sdcc_IS_VALID_OPTION(-gstabs)
  if test "$ucsim_cv_cxx_gstabs" = "yes"; then
    gopt="-gstabs+ -g3"
  elif test "$ucsim_cv_cxx_ggdb" = "yes"; then
    gopt="-ggdb -g3"
  else
    gopt="-g"
  fi
  if test "$CXXFLAGS"x = x ;then
    CXXFLAGS="$gopt"
  else
    CXXFLAGS="$CXXFLAGS $gopt"
  fi

  sdcc_IS_VALID_OPTION(-pipe)
  if test "$ucsim_cv_cxx_pipe" = "yes"; then
    CXXFLAGS="$CXXFLAGS -pipe"
  fi

  MAKEDEP="$CXX $ucsim_cv_MM"
  WALL_FLAG="-Wall"
else
  sdcc_IS_SUNPRO
  if test "$sdcc_cv_cxx_compiler_sunpro" = "yes"; then
    CXXFLAGS="-xO2 $CXXFLAGS"
    MAKEDEP="$CXX -xM1"
    WALL_FLAG=
  fi
fi

# pic_flag is defined by AC_PROG_LIBTOOL
PICOPT=$pic_flag

if test "$PICOPT"x != "x"; then
    SHAREDLIB="yes"
fi
AC_SUBST(MAKEDEP)
AC_SUBST(WALL_FLAG)
AC_SUBST(SHAREDLIB)
AC_SUBST(PICOPT)

dlso_ok="no"
if test $SHAREDLIB = "yes" -a $dl_ok = "yes" -a $enable_dlso = "yes"; then
    dlso_ok="yes"
fi
AC_SUBST(dlso_ok)

# Checks for typedefs, structures, and compiler characteristics.
# ===========================================================================

AC_TYPE_SIGNAL
if test "$cross_compiling" = "no"; then
AC_CHECK_SIZEOF(char)
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
else
    if $CXX -v 2>&1|grep "mingw" >/dev/null 2>&1; then
        ac_cv_sizeof_char=1
        ac_cv_sizeof_short=2
        ac_cv_sizeof_int=4
        ac_cv_sizeof_long=4
        ac_cv_sizeof_long_long=4
    else
        : # FIXME
    fi
#echo
fi

type_name()
{
    if expr "$ac_cv_sizeof_char" '>=' "$1" >/dev/null; then
        echo "char"
        exit
    fi
    if expr "$ac_cv_sizeof_short" '>=' "$1" >/dev/null; then
        echo "short"
        exit
    fi
    if expr "$ac_cv_sizeof_int" '>=' "$1" >/dev/null; then
        echo "int"
        exit
    fi
    if expr "$ac_cv_sizeof_long" '>=' "$1" >/dev/null; then
        echo "long"
        exit
    fi
    if expr "$ac_cv_sizeof_long_long" '>=' "$1" >/dev/null; then
        echo "long long"
        exit
    fi
    echo "long long"
}

AC_MSG_CHECKING(type name for byte)
TYPE_BYTE=`type_name 1`
AC_MSG_RESULT($TYPE_BYTE)
AC_MSG_CHECKING(type name for word)
TYPE_WORD=`type_name 2`
AC_MSG_RESULT($TYPE_WORD)
AC_MSG_CHECKING(type name for dword)
TYPE_DWORD=`type_name 4`
AC_MSG_RESULT($TYPE_DWORD)
AC_DEFINE_UNQUOTED(TYPE_BYTE, [$TYPE_BYTE], [XXX])
AC_DEFINE_UNQUOTED(TYPE_WORD, [$TYPE_WORD], [XXX])
AC_DEFINE_UNQUOTED(TYPE_DWORD, [$TYPE_DWORD], [XXX])
AC_DEFINE_UNQUOTED(TYPE_UBYTE, [unsigned $TYPE_BYTE], [XXX])
AC_DEFINE_UNQUOTED(TYPE_UWORD, [unsigned $TYPE_WORD], [XXX])
AC_DEFINE_UNQUOTED(TYPE_UDWORD, [unsigned $TYPE_DWORD], [XXX])

AH_TOP([#ifndef DDCONFIG_HEADER
#define DDCONFIG_HEADER])
AH_BOTTOM([/* ucsim custom defines */
#define DD_TRUE     1
#define DD_FALSE    0
#define NIL         0
#endif /* DDCONFIG_HEADER */])

if echo $TYPE_DWORD|grep short >/dev/null; then
    A="h"
elif echo $TYPE_DWORD|grep long >/dev/null; then
    A="l"
else
    A=""
fi

if echo $TYPE_WORD|grep short >/dev/null; then M="h"
elif echo $TYPE_WORD|grep long >/dev/null; then M="l"
else M=""
fi

AC_DEFINE_UNQUOTED(_A_, "${A}", [XXX])
AC_DEFINE_UNQUOTED(_M_, "${M}", [XXX])

# Generating output files
# ===========================================================================

AC_OUTPUT(Makefile
main.mk:main_in.mk
packages.mk:packages_in.mk
sim.src/Makefile
cmd.src/Makefile
s51.src/Makefile
avr.src/Makefile
z80.src/Makefile
tlcs.src/Makefile
hc08.src/Makefile
xa.src/Makefile
stm8.src/Makefile
st7.src/Makefile
gui.src/Makefile
gui.src/serio.src/Makefile
doc/Makefile
)

#gui.src/portmon.src/Makefile


# End of configure.ac
