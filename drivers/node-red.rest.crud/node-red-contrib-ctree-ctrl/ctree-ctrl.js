module.exports = function(RED) {
    const { spawn } = require('child_process');
    function CtreeControlNode(config) {
        RED.nodes.createNode(this,config);
        this.path = config.path;
        var node = this;
        node.on('input', function(msg) {
            node.log(node.path);
            var cwd = node.path.substring(0, node.path.lastIndexOf("/"));
            if (node.path.includes("\\"))
                cwd = node.path.substring(0, node.path.lastIndexOf("\\"));
            node.log(cwd);
            const child = spawn(node.path, [], {cwd: cwd});
            child.stdout.on('data', (chunk) => {
                msg.payload = chunk;
                node.send(msg);
            });
            //child.stderr.pipe(dest);

            child.on('close', (code) => {
                msg.payload = code;
                node.send(msg);
            });

        });
    }
    RED.nodes.registerType("ctree-control", CtreeControlNode);
}
