const ctree = require('ctree');
process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;

ctree.setAuth("localhost", 8443, "admin", "ADMIN", true);

ctree.query("ctreeSQL", "books", "c_index", 100, 0, {
        "country": {
            "operator": "=",
            "value": "United States"
        }
    }, function(err, res){
    if (err) {
        console.log('error:', err);
    } else {
        console.log('response', res);
    }
});

