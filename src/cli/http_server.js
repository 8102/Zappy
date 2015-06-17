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

function httpInit (port) {
	server.listen(port);
}
