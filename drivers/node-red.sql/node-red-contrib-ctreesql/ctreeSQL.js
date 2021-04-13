module.exports = function(RED) {
    "use strict";
    var reconnect = RED.settings.ctreeReconnectTime || 30000;
    var ctsql = require('./ctsql');
    function ctreeNode(n) {
        console.dir(n);
		RED.nodes.createNode(this,n);
        this.host = n.host;
        this.port = n.port;
        this.tz = n.tz || "local";
        this.connected = false;
        this.connecting = false;
        this.dbname = n.db;
        var node = this;

        this.connect = function() {
			if (!this.connected && !this.connecting) {
                node.connecting = true;
                ctsql.connect(node.port+"@"+node.host+":"+node.dbname, node.credentials.user, node.credentials.password, {
                    host: node.host,
                    port: node.port,
                    pool: {
                        max: 5,
                        min: 0,
                        idle: 10000
                    },
                });
                node.connection = ctsql;
                node.connected = true;
            }
        }
        /*
        this.on('close', function (done) {
            done();
        });
        */
    }
    RED.nodes.registerType("ctreeSQL_connection", ctreeNode, {
        credentials: {
            user: {type: "text"},
            password: {type: "password"}
        }
    });
    function ctreeNodeIn(n) {
        RED.nodes.createNode(this,n);
        //console.dir(n);
		this.mydb = n.mydb;
        this.querytype = n.querytype;
        this.mydbConfig = RED.nodes.getNode(this.mydb);
        if (this.mydbConfig) {
            this.mydbConfig.connect();
            var node = this;
            node.on("input", function(msg) {
                if (typeof msg.topic === 'string') {
                    //console.dir(node.mydbConfig.connection);
                    var recordset = node.mydbConfig.connection.query(msg.topic);
                    msg.payload = recordset;
                    node.send(msg);
                } else {
                    node.error("msg.topic : the query is not defined as a string");
                }
            });
        }
        else {
            this.error("database not configured");
        }
    }
    RED.nodes.registerType("ctreeSQL", ctreeNodeIn);
}
