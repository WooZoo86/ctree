var request = require('request');

var ctree = function () {};

ctree.prototype.debug = false;

ctree.prototype.setAuth = function (server, port, user, pass, ssl) {
  if(this.debug)
    console.log('auth!');
  this.server = server;
  this.port = port;
  this.user = user;
  this.pass = pass;
  this.ssl = ssl;
  this.url = (ssl?"https":"http")+"://" + server + ":" + port + "/ctree/api/v1/"
};

ctree.prototype.createTable = function (db, table, fields, callback) {
    this.baseCall( "POST", this.url+"table/"+db+"/"+table, {fields:fields}, callback);
};

ctree.prototype.readTable = function (db, table, callback) {
    this.baseCall( "GET", this.url+"table/"+db+"/"+table, undefined, callback);
};

ctree.prototype.deleteTable = function (db, table, callback) {
    this.baseCall( "DELETE", this.url+"table/"+db+"/"+table, undefined, callback);
};

ctree.prototype.createIndex = function (db, table, index, unique, fields, callback) {
    this.baseCall( "POST", this.url+"index/"+db+"/"+table+"/"+index, {fields:fields,unique:unique}, callback);
};

ctree.prototype.readIndex = function (db, table, index, callback) {
    this.baseCall( "GET", this.url+"table/"+db+"/"+table, undefined, callback);
};

ctree.prototype.deleteIndex = function (db, table, index, callback) {
    this.baseCall( "DELETE", this.url+"table/"+db+"/"+table+"/"+index, undefined, callback);
};

ctree.prototype.createRecord = function (db, table, record, callback) {
    this.baseCall( "POST", this.url+"record/"+db+"/"+table, record, callback);
};

ctree.prototype.readRecord = function (db, table, index, callback) {
    this.baseCall( "GET", this.url+"table/"+db+"/"+table, undefined, callback);
};

ctree.prototype.deleteRecord = function (db, table, index, callback) {
    this.baseCall( "DELETE", this.url+"table/"+db+"/"+table+"/"+index, undefined, callback);
};

ctree.prototype.query = function (db, table, index, top, skip, fields, callback) {
    this.baseCall( "POST", this.url+"query/"+db+"/"+table+"/"+index+"?top="+top+"&skip="+skip, {find:fields}, callback);
};

ctree.prototype.baseCall = function (method, url, body, callback) {
    if(this.debug) {
        console.log('url: ' + url);
        if(body)
            console.log('body: ', body);
    }
    request(url, {
      method: method,
      insecure: true,
      rejectUnauthorized: false,
      auth: {
        user: this.user,
        pass: this.pass
      },
      json: true,
      body: body
    }, function(error, response, body){
        if (!error && response.statusCode == 200) {
            callback(false, body);
        } else {
            callback(error || response.statusCode, body);
        }
    });
};

module.exports = new ctree();

    
