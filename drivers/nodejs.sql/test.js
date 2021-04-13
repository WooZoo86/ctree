const ctsql = require('./ctsql');

ctsql.connect("6597@localhost:ctreeSQL", "admin", "ADMIN");

var result = ctsql.query("select * FROM admin.syscolumns");
console.log(result.columnNames);
console.log(result.rows[0]);
console.log(result.rows[1]);
ctsql.end();
