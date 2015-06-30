/*jslint browser: true*/

var io = require('socket.io')

var NetworkDevice = function (gameManager, parameters) {
    'use strict';
    var self = this;

    this.connection = null;
    this.address = null;
    this.port = 0;
    this.gameManager = gameManager;
    console.log(io);
    this.socket = new io.Socket();

    this.initConnection = function (params) {
        var address;
        address = (params === undefined ? 'localhost' : (params.address === 'undefined' ? 'localhost' : params.address));
        self.port = (params === undefined ? 1081 : (params.port === 'undefined' ? 1081 : params.port));
        self.address = 'ws://' + address + ':' + self.port + '/';
        self.socket('http://' + self.address + ':' + self.port);
        window.console.log(self.address);
    };

    this.initConnection(parameters);

    this.socket.on('message', function(connectionEvent) {
        window.console.log('Received from server : [' + connectionEvent.data + ']');
        self.gameManager.treatMessage(connectionEvent.data);
    });


    this.send = function (message) {
        self.connection.send(message);
    };

};