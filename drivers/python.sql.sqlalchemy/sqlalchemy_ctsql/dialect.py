"""
.. dialect:: ctsql+pyctsql
    :name: pyctsql
    :dbapi: pyctree
    :connectstring: ctsql://ADMIN:ADMIN@127.0.0.1/ctreeSQL

This file is a necessary plugin to the actual dialect defined in ctsql/base.py
"""

from sqlalchemy import exc, pool
from sqlalchemy import types as sqltypes
from sqlalchemy import util
from sqlalchemy.engine import default, reflection
from sqlalchemy_ctsql.base import ctsqlCompiler, ctsqlDDLCompiler, ctsqlTypeCompiler, ctsqlIdentifierPreparer, ctsqlExecutionContext
from sqlalchemy.types import (BLOB, BOOLEAN, BIGINT, CHAR, DATE, DATETIME, DECIMAL, FLOAT,
                      INTEGER, REAL, NUMERIC, SMALLINT, TEXT,
                      TIMESTAMP, TIME, DATE, DATETIME, VARCHAR, NVARCHAR, NCHAR, VARBINARY)
import os

class ctsqlDialect(default.DefaultDialect):
    name = 'ctsql'
    driver = 'ctsql'
    positional = False
    paramstyle = 'qmark'
    default_paramstyle = 'qmark'
    convert_unicode = False
    encoding = 'utf-8'
    statement_compiler = ctsqlCompiler
    ddl_compiler = ctsqlDDLCompiler
    # server_version_info should be populated at initial connection ot the database
    # default_schema_name should be populated at initial connection ot the database
    execution_ctx_cls = ctsqlExecutionContext
    # execute_sequence_format ???
    preparer = ctsqlIdentifierPreparer
    #ischema_names = ischema_names
    supports_alter = True
    max_identifier_length = 64
    # the driver handles str type which in python 3 means unicode, so in python 3 support unicode!
    if util.py3k:
        supports_unicode_statements = True
        supports_unicode_binds = True
        returns_unicode_strings = True
        description_encoding = None
    else:
        supports_unicode_statements = False
        supports_unicode_binds = False
        returns_unicode_strings = False
 
    #description_encoding = 'use_encoding'

    supports_sane_rowcount = True
    supports_sane_multi_rowcount = False #TODO: check this
    preexecute_autoincrement_sequences = False
    implicit_returning = False

    # dbapi_type_map  ????
    # colspecs use the default for now

    supports_default_values= False
    supports_sequences = False

    sequences_optional = False

    supports_native_enum = False

    supports_native_boolean = False
    supports_native_decimal = True # TODO: check this

    supports_empty_insert = True
    supports_multivalues_insert = False

    # indicates symbol names are
    # UPPERCASEd if they are case insensitive
    # within the database.
    # if this is True, the methods normalize_name()
    # and denormalize_name() must be provided.
    requires_name_normalize = False


# dbapi_exception_translation_map ???
    postfetch_lastrowid = True # paolo debugging. indicates that the automatically generated pk needs to be retrieved

    type_compiler = ctsqlTypeCompiler  # not documented ??
    
    _broken_fk_pragma_quotes = False
    
# "ischema_names" indicates string descriptions of types as returned from the database linked to TypeEngine classes.
# The string name should be matched to the most specific type possible within
# sqlalchemy.types, unless there is no matching type within sqlalchemy.types in which
# case it points to a dialect type.
# see also type_migration_guidelines.txt
# personal note: this variable is practially not used by SQLAlchemy afaik.
    ischema_names = {
        'BIGINT': BIGINT,
        'BLOB': BLOB,
        'BIT': BOOLEAN,
        'BOOL': BOOLEAN,
        'BOOLEAN': BOOLEAN,
        'CHARACTER': CHAR,
        'DATE': DATE,
        'DATETIME': DATETIME,
        'DOUBLE': FLOAT,
        'DECIMAL': DECIMAL,
        'FLOAT': FLOAT,
        'INT': INTEGER,
        'INTEGER': INTEGER,
        'NUMERIC': NUMERIC,
        'REAL': REAL,
        'SMALLINT': SMALLINT,
        'TIME': TIME,
        'TIMESTAMP': DATETIME,
        'VARCHAR': VARCHAR,
        'NVARCHAR': NVARCHAR,
        'NCHARACTER': NCHAR,
        'MONEY': DECIMAL,
        'VARBINARY': VARBINARY,
        'LVARCHAR' : TEXT,
    }

    @classmethod
    def dbapi(cls):
        try:
            import pyctree as ctreesql
        except ImportError as e:
            raise e
        return ctreesql
    
    def _supports_schema(self, schema):
        return False

    def __init__(self, isolation_level=None, **kwargs):
        default.DefaultDialect.__init__(self, **kwargs)
        self.isolation_level = isolation_level

        if self.dbapi is not None:
            self.supports_default_values = False
            self.supports_cast = False
            self.supports_multivalues_insert = False
            self._broken_fk_pragma_quotes = True

    _isolation_lookup = {
        'READ COMMITTED': 1 ,
        'REPEATABLE READ' : 2
    }

    def create_xid(self):
        raise NotImplementedError()
    
    def connect(self, *cargs, **cparams):
        return self.dbapi.connect(**cparams)

    def set_isolation_level(self, connection, level):
        try:
            isolation_level = self._isolation_lookup[level.replace('_', ' ')]
        except KeyError:
            raise exc.ArgumentError(
                "Invalid value '%s' for isolation_level. "
                "Valid isolation levels for %s are %s" %
                (level, self.name, ", ".join(self._isolation_lookup))
            )
        connection.set_isolation(isolation_level)

    def get_isolation_level(self, connection):
        isol = connection.get_isolation()
        if isol == 1:
            return "READ COMMITTED"
        elif isol == 2:
            return "REPEATABLE READ"
        else:
            assert False, "Unknown isolation level %s" % isol

    def on_connect(self):
        if self.isolation_level is not None:
            def connect(conn):
                self.set_isolation_level(conn, self.isolation_level)
            return connect
        else:
            return None

    def has_table(self, connection, table_name, schema=None):
        if self._supports_schema(schema) == False:
            schema = None
        if schema is not None:
            query = "?" % (schema,)
        else:
            query = "user()"
        statement = "SELECT tbl from admin.systables where owner=%s and tbl=?" % (query,)
        if schema is not None:
            cursor = connection.execute(statement, (schema, table_name))
        else:
            cursor = connection.execute(statement, (table_name,))
        result = cursor.fetchone()
        cursor.close()
        return bool(result)
        
    def do_savepoint(self, connection, name):
        raise NotImplementedError()

    def do_release_savepoint(self, connection, name):
        raise NotImplementedError()

    @reflection.cache
    def get_pk_constraint(self, connection, table_name, schema=None, **kw):
        if self._supports_schema(schema) == False:
            schema = None
        if schema is not None:
            query = "pk.owner=? and"
        else:
            query = "pk.owner = user() and"
        statement = "select pk.cnstrname, colname, colposition from admin.sys_keycol_usage kcol, admin.sys_tbl_constrs pk where pk.cnstrname=kcol.cnstrname and pk.owner=kcol.owner and pk.tblname = kcol.tblname and cnstrtype='P' and %s pk.tblname=? order by colposition" % (query,)
        if schema is not None:
            cursor = connection.execute(statement,(schema,table_name))
        else:
            cursor = connection.execute(statement,(table_name,))
        result = cursor.fetchall()
        cols = [r[1] for r in result]
        if len(result) > 0:
            name = result[0][0] 
        else:
            name = None 
        cursor.close()
        return {'constrained_columns': cols, 'name': name}

    @reflection.cache
    def get_foreign_keys(self, connection, table_name, schema=None, **kw):
        if self._supports_schema(schema) == False:
            schema = None
        if schema is not None:
            query = "tc.owner=? and"
        else:
            query = "tc.owner = user() and"
        statement = "select tc.cnstrname, kcol.colname, refowner, reftblname, refcnstrname, rcol.colname from admin.sys_keycol_usage kcol, admin.sys_tbl_constrs tc, admin.sys_ref_constrs rt, admin.sys_keycol_usage rcol where tc.cnstrname = kcol.cnstrname and tc.owner = kcol.owner and tc.tblname = kcol.tblname and rt.tblname = tc.tblname and rt.owner = tc.owner and rt.cnstrname = tc.cnstrname and rcol.tblname = rt.reftblname and rcol.owner = rt.refowner and rcol.cnstrname = rt.refcnstrname and rcol.colposition = kcol.colposition and cnstrtype='F' and %s tc.tblname=? order by tc.cnstrname, kcol.colposition" % (query,)
        if schema is not None:
            cursor = connection.execute(statement,(schema,table_name,))
        else:
            cursor = connection.execute(statement,(table_name,))

        result = cursor.fetchall()

        fkeys = []
        constraint_name = None
        constrained_columns = []
        referred_columns = []
        referred_table = None
        referred_schema = None
        for r in result:
            if r[0] != constraint_name:
                if (constraint_name != None):
                    fkey_d = {
                        'name': constraint_name,
                        'constrained_columns': constrained_columns,
                        'referred_schema': referred_schema,
                        'referred_table': referred_table,
                        'referred_columns': referred_columns,
                    }
                    fkeys.append(fkey_d)
                constraint_name = r[0]
                referred_table = r[3]
                if self._supports_schema(schema):
                    referred_schema = r[2]
                constrained_columns = []
                referred_columns = []
            constrained_columns.append(r[1])
            referred_columns.append(r[5])
        if (constraint_name != None):
            fkey_d = {
                'name': constraint_name,
                'constrained_columns': constrained_columns,
                'referred_schema': referred_schema,
                'referred_table': referred_table,
                'referred_columns': referred_columns,
            }
            fkeys.append(fkey_d)
        cursor.close()
        return (fkeys)

    @reflection.cache
    def get_indexes(self, connection, table_name, schema=None, **kw):
        if self._supports_schema(schema) == False:
            schema = None
        if schema is not None:
            query = "?"
        else:
            query = "user()"
        statement = "select sysi.idxname, sysi.idxtype, sysi.colname from admin.sysindexes sysi left outer join admin.sys_tbl_constrs sysc on sysi.tblowner = sysc.owner and sysi.tbl = sysc.tblname and sysi.idxname = sysc.idxname where sysc.cnstrtype is NULL and sysi.tblowner=%s and sysi.tbl=? order by sysi.id, sysi.idxseq" % (query,)
        if schema is not None:
            cursor = connection.execute(statement,(schema,table_name))
        else:
            cursor = connection.execute(statement,(table_name,))
        result = cursor.fetchall()
        indexes = []
        index_name = None
        index_unique = False
        index_cols = []
        for r in result:
            if r[0] != index_name:
                if (index_name != None):
                    index_d = {
                        'name': index_name,
                        'column_names': index_cols, 
                        'unique':index_unique
                    }
                    indexes.append(index_d)
                index_name = r[0]
                index_cols = []
                index_unique = (r[1] == 'U')
            index_cols.append(r[2])
        if (index_name != None):
            index_d = {
                'name': index_name,
                'column_names': index_cols, 
                'unique':index_unique
            }
            indexes.append(index_d)
        cursor.close()
        return (indexes)

    @reflection.cache
    def get_table_names(self, connection, schema=None, **kw):
        if self._supports_schema(schema) == False:
            schema = None
        if schema is not None:
            query = "?"
        else:
            query = "user()"
        statement = "SELECT tbl from admin.systables where tbltype='T' and owner = %s" % (query,)
        if schema is not None:
            cursor = connection.execute(statement,(schema,))
        else:
            cursor = connection.execute(statement)
        names = []
        for row in cursor:
            names.append(row[0])
        cursor.close()
        return (names)

    @reflection.cache
    def get_view_names(self, connection, schema=None, **kw):
        if self._supports_schema(schema) == False:
            schema = None
        if schema is not None:
            query = "?"
        else:
            query = "user()"
        statement = "SELECT tbl from admin.systables where tbltype='V' and owner = %s" % (query,)
        if schema is not None:
            cursor = connection.execute(statement,(schema,))
        else:
            cursor = connection.execute(statement)
        names = []
        for row in cursor:
            names.append(row[0])
        cursor.close()
        return (names)

    @reflection.cache
    def get_columns(self, connection, table_name, schema=None, **kw):
        if self._supports_schema(schema) == False:
            schema = None
        if schema is not None:
            query = "?"
        else:
            query = "user()"
        statement = "select colid from admin.sysidentity where owner = %s and tbl = ?" % (query,)
        if schema is not None:
             colid = connection.execute(statement, (table_name,schema)).fetchone()
        else:
             colid = connection.execute(statement, (table_name,)).fetchone()
        if colid != None:
            colid = colid[0] 
        statement = "SELECT id, col, coltype, width, scale, nullflag, dflt_value, cnstrtype from admin.syscolumns as cols left outer join admin.sys_keycol_usage as keycol on cols.owner = keycol.owner and cols.tbl = keycol.tblname and cols.col = keycol.colname left outer join admin.sys_tbl_constrs as const on cols.owner = const.owner and cols.tbl = const.tblname and keycol.cnstrname = const.cnstrname where cols.owner=%s and cols.tbl=? order by id" % (query,)
        if schema is not None:
             cursor = connection.execute(statement,(table_name,schema))
        else:
             cursor = connection.execute(statement,(table_name,))

        columns = []
        for row in cursor:
            coltype = self.resolve_type(row[2].upper(),row[3],row[4])
            columns.append({
                'name': row[1],
                'type': coltype,
                'nullable': row[5] == 'Y',
                'default': row[6],
                'autoincrement': colid != None and colid < 0 and (-1-colid == row[0]),
                'primary_key': 'P' == row[7],
            })
        cursor.close()
        return columns

    def resolve_type(self, coltype, width, scale):
        if coltype in ('VARCHAR', 'NVARCHAR', 'CHARACTER', 'NCHARACTER'):
            return self.ischema_names.get(coltype)(width)
        if coltype in self.ischema_names:
            return self.ischema_names[coltype]
        else:
            #if len(self.ischema_names) > 0: # it is only 0 for one unit test.
            raise exc.SAWarning('Did not recognize type: %s' % (coltype) )
            #return sqltypes.NullType

    def create_connect_args(self, url):
        if url.query:
            raise exc.ArgumentError(
                "Invalid ctsql URL: %s\nQuery parameters not supported" % (url,))

        opts = url.translate_connect_args()
        username = opts.pop("username", [] )
        if (username):
            opts['user'] = username

        return ([], opts)

    def is_disconnect(self, e, connection, cursor):
        return isinstance(e, self.dbapi.ProgrammingError) and \
            "invalid/closed Connect instance" in str(e)	
