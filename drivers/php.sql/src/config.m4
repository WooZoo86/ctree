PHP_ARG_WITH(ctsql,whether to enable c-tree SQL support,
[  --with-ctsql[=ctreeESQL dir]          Enable c-tree SQL library])

ctreeACE=no
COBOL=no
if test "$PHP_CTSQL" != "no"; then
  if test -r $PHP_CTSQL/ctree/include/sql_lib.h; then
    CTESQL_DIR=$PHP_CTSQL
  else
    if test -r $PHP_CTSQL/include/sdk/sql.embedded/sql_lib.h; then
      CTESQL_DIR=$PHP_CTSQL
      ctreeACE=yes
    else
      if test -r ../../../ctree/include/sql_lib.h; then
        CTESQL_DIR=../../..
      else
        if test -r ../../../include/sdk/sql.embedded/sql_lib.h; then
          CTESQL_DIR=../../..
          ctreeACE=yes
        else
          if test -r sql.embedded/include/sql_lib.h; then
            CTESQL_DIR=sql.embedded
            COBOL=yes
          else
            if test -r ../../ctree.drivers/include/unix/sql_lib.h; then
              CTESQL_DIR=../../ctree.drivers
              COBOL=yes
            else
              AC_MSG_ERROR(ESQL directory not found)
            fi
          fi
        fi
      fi
    fi
  fi

  if test $COBOL = yes; then
    PHP_ADD_INCLUDE($CTESQL_DIR/include)
    PHP_ADD_INCLUDE($CTESQL_DIR/include/unix)
  else
    if test $ctreeACE = yes; then
      PHP_ADD_INCLUDE($CTESQL_DIR/include)
      PHP_ADD_INCLUDE($CTESQL_DIR/include/sdk/sql.embedded)
      case $host_os in
        darwin*)
           dnl on macos we overwrite the host_cpu with the output of uname -m that seems more appropriate
           host_cpu=`uname -m`
          ;;
      esac
    else
      PHP_ADD_INCLUDE($CTESQL_DIR/ctree/include)
      case $host_os in
        linux*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/linux)
          ;;
        aix*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/aix)
          ;;
        solaris*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/solaris)
          ;;
        hp*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/hp)
          ;;
        darwin*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/macos)
          host_cpu=`uname -m`
          ;;
        qnxrtp*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/qnxrtp)
          ;;
        sco*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/sco)
          ;;
        freebsd7*)
          PHP_ADD_INCLUDE($CTESQL_DIR/ctree/sql/src/public/os/freebsd7)
          ;;
        esac
    fi
  fi

  AC_DEFINE(DH_OS_UNIX,,Unix platform)
  case $host_cpu in
    *64)
      echo 64 bit support enaled
      AC_DEFINE(DH_64BIT_MODEL,,64 bit)
      ;;
  esac

  PHP_REQUIRE_CXX

  case $host_os in
    linux*)
      PHP_ADD_LIBRARY_WITH_PATH(stdc++,,CTSQL_SHARED_LIBADD)
      PHP_ADD_LIBRARY_WITH_PATH(pthread,,CTSQL_SHARED_LIBADD)
	  ;;
    freebsd*)
      AC_DEFINE(DH_OS_UNIX_FREEBSD8,,free bsd)
      PHP_ADD_LIBRARY_WITH_PATH(stdc++,,CTSQL_SHARED_LIBADD)
          ;;
    darwin*)
      AC_DEFINE(DH_OS_UNIX_MACOS,,macos)
          ;;
  esac
  
  if test $COBOL = yes; then
    case $host_os in
    linux*)
      case $host_cpu in
      x86_64|amd64|aarch64)
       PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib64,CTSQL_SHARED_LIBADD)
       PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib64,CTSQL_SHARED_LIBADD)
       ;;
      i?86)
       PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib,CTSQL_SHARED_LIBADD)
       PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib,CTSQL_SHARED_LIBADD)
       ;;
      armv7l)
       PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
       PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
       ;;
      esac
      ;;
    darwin*)
    case $host_cpu in
    x86_64)
     PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib64,CTSQL_SHARED_LIBADD)
     PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib64,CTSQL_SHARED_LIBADD)
     ;;
    i?86)
     PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib,CTSQL_SHARED_LIBADD)
     PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib,CTSQL_SHARED_LIBADD)
     ;;
    esac
      ;;
    esac
    PHP_ADD_LIBRARY_WITH_PATH(ctesql, $CTESQL_DIR/lib,CTSQL_SHARED_LIBADD)
  else
    if test $ctreeACE = yes; then
    case $host_os in
        linux*)
        case $host_cpu in
        x86_64|amd64|aarch64)
        PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
        PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
        ;;
        i?86)
        PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
        PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
        ;;
        armv7l)
        PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
        PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
        ;;
        esac
          ;;
        darwin*)
          case $host_cpu in
          x86_64)
          PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
          ;;
          i?86)
          PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
          ;;
          esac
        esac
      PHP_ADD_LIBRARY_WITH_PATH(ctesql, $CTESQL_DIR/lib/sql.embedded,CTSQL_SHARED_LIBADD)
    else
      case $host_os in
          linux*)
          case $host_cpu in
          x86_64|amd64)
          PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../your/openssl.unix/linux.x64.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../your/openssl.unix/linux.x64.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
          ;;
          aarch64)
          PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../your/openssl.unix/linux.v2.6.arm_generic.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../your/openssl.unix/linux.v2.6.arm_generic.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
          ;;
          i?86)
          PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../your/openssl.unix/linux.v2.6.x86.32bit/lib,PDO_CTSQL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../your/openssl.unix/linux.v2.6.x86.32bit/lib,PDO_CTSQL_SHARED_LIBADD)
          ;;
          armv7l)
          PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../your/openssl.unix/linux.v2.6.arm_generic.32bit/lib,PDO_CTSQL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../your/openssl.unix/linux.v2.6.arm_generic.32bit/lib,PDO_CTSQL_SHARED_LIBADD)
          ;;
          esac
            ;;
          darwin*)
            case $host_cpu in
            x86_64)
            PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../your/openssl.unix/osx.v10.13.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
            PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../your/openssl.unix/osx.v10.13.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
            ;;
            i?86)
            PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
            PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
            ;;
            esac
          esac
      PHP_ADD_LIBRARY_WITH_PATH(ctesql, $CTESQL_DIR/lib.pql,CTSQL_SHARED_LIBADD)
    fi
  fi

  PHP_SUBST(CTSQL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(ctsql, ctsql.c, $ext_shared)
fi
