PHP_ARG_WITH(pdo-ctsql,whether to enable PDO c-tree SQL support,
[  --with-pdo-ctsql          Enable c-tree SQL library])

ctreeACE=no
COBOL=no
if test "$PHP_PDO_CTSQL" != "no"; then

  if test "$PHP_PDO" = "no" && test "$ext_shared" = "no"; then
    AC_MSG_ERROR([PDO is not enabled! Add --enable-pdo to your configure line.])
  fi

  if test -r $PHP_PDO_CTSQL/ctree/include/ctsqlapi.h; then
    CTSQL_DIR=$PHP_PDO_CTSQL
  else
    if test -r $PHP_PDO_CTSQL/include/ctsqlapi.h; then
      CTSQL_DIR=$PHP_PDO_CTSQL
      ctreeACE=yes
    else
      if test -r ../../../ctree/include/ctsqlapi.h; then
        CTSQL_DIR=../../..
      else
        if test -r ../../../include/ctsqlapi.h; then
          CTSQL_DIR=../../..
          ctreeACE=yes
        else
          if test -r ../../ctree.drivers/include/ctsqlapi.h; then
            CTSQL_DIR=../../ctree.drivers
            COBOL=yes
          else
            AC_MSG_ERROR(DSQL directory not found)
          fi
        fi
      fi
    fi
  fi

  if test $COBOL = yes; then
    PHP_ADD_INCLUDE($CTSQL_DIR/include)
    PHP_ADD_INCLUDE(../../ctree.drivers/include)
  else
    if test $ctreeACE = yes; then
      PHP_ADD_INCLUDE($CTSQL_DIR/include)
      case $host_os in
        darwin*)
           dnl on macos we overwrite the host_cpu with the output of uname -m that seems more appropriate
           host_cpu=`uname -m`
          ;;
      esac
    else
      PHP_ADD_INCLUDE($CTSQL_DIR/ctree/include)
    fi
  fi

  AC_DEFINE(DH_OS_UNIX,,Unix platform)
  AC_DEFINE(FAIRCOM_CODE,,All platforms)
  AC_DEFINE(FAIRCOM_MOD,,All platforms)
  case $host_cpu in
    *64)
      echo 64 bit support enaled
      AC_DEFINE(DH_64BIT_MODEL,,64 bit)
      ;;
  esac

  case $host_os in
  linux*)
    PHP_ADD_LIBRARY_WITH_PATH(pthread,,PDO_CTSQL_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(stdc++,,PDO_CTSQL_SHARED_LIBADD)
    ;;
  esac
  
  if test $COBOL = yes; then
    case $host_os in
    linux*)
      case $host_cpu in
      x86_64|amd64|aarch64)
      PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
      PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
      ;;
      i?86)
      PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
      PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
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
        PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
        PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib64,PDO_CTSQL_SHARED_LIBADD)
        ;;
        i?86)
        PHP_ADD_LIBRARY_WITH_PATH(crypto,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
        PHP_ADD_LIBRARY_WITH_PATH(ssl,../../ctree.drivers/lib/License.Lib/openssl/lib,PDO_CTSQL_SHARED_LIBADD)
        ;;
        esac
      esac
      PHP_ADD_LIBRARY_WITH_PATH(ctsqlapi,c.sql.direct/lib/,PDO_CTSQL_SHARED_LIBADD)
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
        PHP_ADD_LIBRARY_WITH_PATH(ctsqlapi,c.sql.direct/lib/,PDO_CTSQL_SHARED_LIBADD)
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
            PHP_ADD_LIBRARY_WITH_PATH(crypto,../../../your/openssl.unix/osx.v10.13.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
            PHP_ADD_LIBRARY_WITH_PATH(ssl,../../../your/openssl.unix/osx.v10.13.64bit/lib64,PDO_CTSQL_SHARED_LIBADD)
            ;;
            esac
          esac
          PHP_ADD_LIBRARY_WITH_PATH(ctsqlapi,$CTSQL_DIR/lib.pql,PDO_CTSQL_SHARED_LIBADD)
    fi
  fi
  
  PHP_SUBST(PDO_CTSQL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pdo_ctsql, pdo_ctsql.c ctsql_driver.c ctsql_statement.c, $ext_shared)

  PHP_ADD_EXTENSION_DEP(pdo_ctsql, pdo)
fi
