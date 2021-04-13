"""
.. dialect:: ctsql
    :name: ctsql
    :dbapi: pyctree
    :connectstring: ctsql://ADMIN:ADMIN@127.0.0.1/ctreeSQL

This file is the actual dialect
"""

import datetime
import re

from sqlalchemy import processors
from sqlalchemy import sql, exc
from sqlalchemy import types as sqltypes, schema as sa_schema
from sqlalchemy import util
from sqlalchemy.engine import default, reflection
from sqlalchemy.sql import compiler, expression

class ctsqlCompiler(compiler.SQLCompiler):
    ansi_bind_rules = True;
    compound_keywords = util.update_copy(
        compiler.SQLCompiler.compound_keywords,
        {
            expression.CompoundSelect.EXCEPT: 'MINUS'
        }
    )

    extract_map = util.update_copy(
        compiler.SQLCompiler.extract_map,
        {
            'month': '%m',
            'day': '%d',
            'year': '%Y',
            'second': '%S',
            'hour': '%H',
            'doy': '%j',
            'minute': '%M',
            'epoch': '%s',
            'dow': '%w',
            'week': '%W',
        })

    def visit_now_func(self, fn, **kw):
        return "CURRENT_TIMESTAMP"

    def visit_localtimestamp_func(self, func, **kw):
        return 'DATETIME(CURRENT_TIMESTAMP, "localtime")'

    def visit_null(self, expr, **kw):
        return 'NULL'

    def visit_char_length_func(self, fn, **kw):
        return "length%s" % self.function_argspec(fn)

    def visit_cast(self, cast, **kwargs):
        if self.dialect.supports_cast:
            return super(ctsqlCompiler, self).visit_cast(cast, **kwargs)
        else:
            return self.process(cast.clause, **kwargs)

    def get_select_precolumns(self, select, **kw):
        """ c-tree SQL puts TOP, it's version of LIMIT here """

        s = ""
        if select._distinct:
            s += "DISTINCT "

        if select._simple_int_limit :
            s += "TOP %d " % select._limit
        if select._offset:
            s += "SKIP %d " % select._offset

        if s:
            return s
        else:
            return compiler.SQLCompiler.get_select_precolumns(
                self, select, **kw)
    def visit_extract(self, extract, **kw):
        try:
            return "CAST(STRFTIME('%s', %s) AS INTEGER)" % (
                self.extract_map[extract.field],
                self.process(extract.expr, **kw)
            )
        except KeyError:
            raise exc.CompileError(
                "%s is not a valid extract argument." % extract.field)

    def limit_clause(self, select, **kw):
        # Limit is after the select keyword
        return ""


class ctsqlDDLCompiler(compiler.DDLCompiler):

    def get_column_specification(self, column, **kwargs):
        coltype = self.dialect.type_compiler.process(
            column.type, type_expression=column)
        colspec = self.preparer.format_column(column) + " " + coltype

        if not column.nullable:
            colspec += " NOT NULL"

        if isinstance(column.default, sa_schema.Sequence):
            if column.default.start == 0:
                start = 0
            else:
                start = column.default.start or 1

            colspec += " AUTO_INCREMENT(%s,%s)" % (start,
                                             column.default.increment or 1)
        elif column is column.table._autoincrement_column:
            colspec += " AUTO_INCREMENT(1,1)"
        else:
            default = self.get_column_default_string(column)
            if default is not None:
                colspec += " DEFAULT " + default
  
        return colspec

    def visit_check_constraint(self, constraint):
        text = ""
        #if constraint.name is not None:
        #    formatted_name = self.preparer.format_constraint(constraint)
        #    if formatted_name is not None:
        #        text += "CONSTRAINT %s " % formatted_name
        #text += "CHECK (%s)" % self.sql_compiler.process(constraint.sqltext,
        #                                                 include_table=False,
        #                                                 literal_binds=True)
        #text += self.define_constraint_deferrability(constraint)
        return None

    #def visit_primary_key_constraint(self, constraint):
    #    # for columns with ctsql_autoincrement=True,
    #    # the PRIMARY KEY constraint can only be inline
    #    # with the column itself.
    #    if len(constraint.columns) == 1:
    #        c = list(constraint)[0]
    #        if (c.primary_key and
    #                c.table.dialect_options['ctsql']['autoincrement'] and
    #                issubclass(c.type._type_affinity, sqltypes.Integer) and
    #                not c.foreign_keys):
    #            return None

    #    return super(ctsqlDDLCompiler, self).visit_primary_key_constraint(
    #        constraint)

    #def visit_foreign_key_constraint(self, constraint):

    #    local_table = constraint.elements[0].parent.table
    #    remote_table = constraint.elements[0].column.table

    #    if local_table.schema != remote_table.schema:
    #        return None
    #    else:
    #        return super(
    #            ctsqlDDLCompiler,
    #            self).visit_foreign_key_constraint(constraint)

    def define_constraint_remote_table(self, constraint, table, preparer):
        """Format the remote table clause of a CREATE CONSTRAINT clause."""

        return preparer.format_table(table, use_schema=False)

    #def visit_create_index(self, create):
    #    index = create.element

    #    text = super(ctsqlDDLCompiler, self).visit_create_index(
    #        create, include_table_schema=False)

    #    whereclause = index.dialect_options["ctsql"]["where"]
    #    if whereclause is not None:
    #        where_compiled = self.sql_compiler.process(
    #            whereclause, include_table=False,
    #            literal_binds=True)
    #        text += " WHERE " + where_compiled

    #    return text


class ctsqlTypeCompiler(compiler.GenericTypeCompiler):
#    def visit_large_binary(self, type_, **kw):
#        return self.visit_BLOB(type_)

    def visit_DATETIME(self, type_, **kw):
         return "TIMESTAMP"

    def visit_TEXT(self, type_, **kw):
         return "LVARCHAR"

    def visit_BOOLEAN(self, type_, **kw):
         return "BIT"

#    def visit_DATE(self, type_, **kw):
#        if not isinstance(type_, _DateTimeMixin) or \
#                type_.format_is_text_affinity:
#            return super(ctsqlTypeCompiler, self).visit_DATE(type_)
#        else:
#            return "DATE_CHAR"

#    def visit_TIME(self, type_, **kw):
#        if not isinstance(type_, _DateTimeMixin) or \
#                type_.format_is_text_affinity:
#            return super(ctsqlTypeCompiler, self).visit_TIME(type_)
#        else:
#            return "TIME_CHAR"


class ctsqlIdentifierPreparer(compiler.IdentifierPreparer):
    reserved_words = set([
        'a', 'add', 'avg', 'average', 'alter', 'all', 'an', 'array', 'as', 'atta', 'attach', 'autocommit', 
        'begin', 'bottom', 'break', 'buffer', 'call', 'center', 'clear', 'close', 'cluster',
        'compute', 'column', 'col', 'command', 'commit', 'committed', 'connect', 'connection',
        'cost', 'count', 'create', 'current', 'database', 'date', 'declare', 'define', 'default',
        'delete', 'detach', 'desc', 'describe', 'display', 'disconnect', 'drop', 'echo', 'echo',
        'edit', 'else', 'end', 'execute', 'exists', 'exit', 'explain', 'fetch', 'field', 'filter',
        'flush', 'format', 'from', 'function', 'get', 'grant', 'heading', 'help', 'history','host',
        'if_exists', 'if_not_exists', 'id', 'in', 'indexes', 'insert', 'is', 'isolation', 'join', 'left', 'level',
        'link', 'list', 'lock', 'lines', 'linesize', 'max', 'maximum', 'minimum', 'min', 'not', 'num', 'number',
        'of', 'off', 'on', 'open', 'or', 'order', 'page', 'pagesize', 'procedure', 'prepare', 'put',
        'quit', 'read', 'recover', 'rename', 'repeatable', 'report', 'revoke', 'row', 'right',
        'rollback', 'run', 'save', 'pause', 'segment', 'select', 'with', 'schema',
        'serializable', 'set', 'size', 'skip', 'show', 'spool', 'start', 'sum', 'table', 'title',
        'time', 'timestamp', 'timing', 'to', 'top', 'transaction', 'trigger', 'truncate', 'uid', 'uuid', 'unlock',
        'user', 'using', 'update', 'values', 'when', 'where', 'work'
    ])

    def format_index(self, index, use_schema=True, name=None):
        """Prepare a quoted index and schema name."""

        if name is None:
            name = index.name
        result = self.quote(name, index.quote)
        if (not self.omit_schema and
                use_schema and
                getattr(index.table, "schema", None)):
            result = self.quote_schema(
                index.table.schema, index.table.quote_schema) + "." + result
        return result


class ctsqlExecutionContext(default.DefaultExecutionContext):
    @util.memoized_property
    def _preserve_raw_colnames(self):
        return self.execution_options.get("ctsql_raw_colnames", False)

    def _translate_colname(self, colname):
        # TODO: detect ctsql version 3.10.0 or greater;
        # see [ticket:3633]

        # adjust for dotted column names.  ctsql
        # in the case of UNION may store col names as
        # "tablename.colname", or if using an attached database,
        # "database.tablename.colname", in cursor.description
        if callable(colname):
            return colname, None
        if not self._preserve_raw_colnames and "." in colname:
            return colname.split(".")[-1], colname
        else:
            return colname, None

    def get_lastrowid(self):
        """return self.cursor.lastrowid, or equivalent, after an INSERT.

        This may involve calling special cursor functions,
        issuing a new SELECT on the cursor (or a new one),
        or returning a stored value that was
        calculated within post_exec().

        This function will only be called for dialects
        which support "implicit" primary key generation,
        keep preexecute_autoincrement_sequences set to False,
        and when no explicit id value was bound to the
        statement.

        The function is called once, directly after
        post_exec() and before the transaction is committed
        or ResultProxy is generated.   If the post_exec()
        method assigns a value to `self._lastrowid`, the
        value is used in place of calling get_lastrowid().

        Note that this method is *not* equivalent to the
        ``lastrowid`` method on ``ResultProxy``, which is a
        direct proxy to the DBAPI ``lastrowid`` accessor
        in all cases.

        """
        if self.compiled.statement.table._autoincrement_column is None :
            return None
        lastid = str(self.cursor.lastrowid)

        return int(lastid)


