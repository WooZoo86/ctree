module.exports = function(RED) {
    "use strict";
    var con = require('./ctree');
    function config(cfg) {
		RED.nodes.createNode(this, cfg);
        this.connected = false;
        this.connecting = false;
        this.host = cfg.host;
        this.port = cfg.port;
        this.ssl = cfg.ssl;
        this.dbname = cfg.db;
        var node = this;

        if( node.credentials.user == undefined || node.credentials.user.length == 0)
            throw ( "user credentials missing" );
        if( node.credentials.password == undefined || node.credentials.password.length == 0)
            throw ( "user password missing" );
        
        this.connect = function() {
			if (!this.connected && !this.connecting) {
                node.connecting = true;
                con.setAuth( node.host, node.port, node.credentials.user, node.credentials.password, node.ssl);
                node.connection = con;
                node.connected = true;
            }
        }
    }
    RED.nodes.registerType("ctree_configuration", config, {
        credentials: {
            user: {type: "text"},
            password: {type: "password"}
        }
    });
    function errorHandler(err, res){
        if (err) {
            console.log('error:', err);
        } else {
            console.log("table created");
        }
    }
    RED.nodes.registerType("ctree", function(cfg) {
        RED.nodes.createNode(this, cfg);
		this.mydb = cfg.mydb;
        this.action = cfg.action;
        this.target = cfg.target;
        this.mydbConfig = RED.nodes.getNode(this.mydb);
        if (this.mydbConfig) {
            this.mydbConfig.connect();
            var node = this;
            node.on("input", function(msg) {
                if (typeof msg.topic !== 'string') {
                    node.error("msg.topic : the query is not defined as a string");
                    return;
                }
                var con = node.mydbConfig.connection;
                var actionMap = {create:"POST", read:"GET", update:"PUT", "delete":"DELETE"};
                var method = actionMap[node.action];
                var msgtopic = msg.topic.split(":");
                var table = msgtopic[0];
                var target = node.target;
                var db = node.mydbConfig.dbname;
                var index_or_record=msgtopic[1];

                if (node.action === 'read' && node.target === 'record') {
                    target='query';
                    method='POST';
                }
                if (node.action === 'create' && node.target === 'table') {
                    if(!msg.payload.fields)
                        msg.payload={fields:msg.payload};
                }
                var url = con.url+target+"/"+db+"/"+table
                if( index_or_record) {
                    url+="/"+index_or_record
                }
                if( msgtopic.length>2 ) {
                    url+="?top="+msgtopic[2]
                }
                if( msgtopic.length>3 ) {
                    url+="&skip="+msgtopic[3]
                }
                con.baseCall( method, url, msg.payload, function(err, res){
                    if (err) {
                        node.error("error: " + err);
                    } else {
                        msg.payload = res;
                        node.send(msg);
                    }
                });
            });
        } else {
            this.error("database not configured");
        }
    });
}
