const ctree = require('ctree');
process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;

ctree.setAuth("localhost", 8443, "admin", "ADMIN", true);

ctree.createTable("ctreeSQL", "books", [
        {
            "name": "id",
            "type": "INTEGER",
            "length": 4
        },
        {
            "name": "name",
            "type": "VARCHAR",
            "length": 128
        },
        {
            "name": "author",
            "type": "VARCHAR",
            "length": 128
        },
        {
            "name": "country",
            "type": "VARCHAR",
            "length": 48
        }
    ]
, function(err, res){
    if (err) {
        console.log('error:', err);
    } else {
        console.log("table created");
    }
});





