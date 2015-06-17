module.exports = function (port) {
	/*
	** Require scope
	*/
	var http = require('http');

	/*
	** variable scope
	*/
	var server = http.createServer(function(req, res) {
		console.log('HTTP server created !');
	});

	server.listen(port);

	module.exports.Server = server;
}