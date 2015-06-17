/*
** Require scope
*/
var net = require('net');

/*
** variable scope
*/
var client = new net.Socket();
console.log(process.argv[2]);

function tcpInit (addr, port) {
	client.connect(port, addr, function() {
		console.log('Connected');
	});
}