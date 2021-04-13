const ctree = require('ctree');
process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;

ctree.setAuth("localhost", 8443, "admin", "ADMIN", true);

ctree.createRecord("ctreeSQL", "books", {
	"id": 1,
    "name": "Moby Dick",
    "author": "Herman Melville",
    "country": "United States"
  }
  

, function(err, res){
    if (err) {
        console.log('error:', err);
    } else {
        console.log("record created: ", res);
    }
});





