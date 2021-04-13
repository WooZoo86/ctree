if( process.argv.length < 6) {
  console.log("usage: node baseCall.js method type db table index_or_record body")
  console.log("example: node baseCall.js GET record test books 2")
  console.log("example: node baseCall.js DELETE index test books ts_index")
  console.log("use undefined for unused parameters in the middle")
  process.exit();
}

const ctree = require('./index');

ctree.setAuth("localhost", 8443, "admin", "ADMIN", false);

var [method, type, db, table, index_or_record, body] = process.argv.slice(2);

var url = ctree.url+type+"/"+db+"/"+table

if(index_or_record==="undefined")
  index_or_record=undefined
else
  url+="/"+index_or_record

if(body==="undefined")
  body=undefined


ctree.baseCall( method, url, body, function(err, res){
    if (err) {
        console.log('error:', err);
    } else {
        if(res)
            console.log(res);
    }
});

