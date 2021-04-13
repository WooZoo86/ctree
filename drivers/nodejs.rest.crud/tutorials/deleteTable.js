const ctree = require('ctree');
process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;

ctree.setAuth("localhost", 8443, "admin", "ADMIN", true);

ctree.deleteTable("ctreeSQL", "books", function(err, res){
    if (err) {
        console.log('error:', err);
    } else {
        console.log("table deleted");
    }
});





