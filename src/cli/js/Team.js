/*jslint browser: true*/
var Team = function (parameters) {
    'use strict';

    if (parameters === undefined) {
        this.name = "Anonymous";
        this.color = 0xffffffff;
        this.nbPlayers = 0;
        this.players = [];
        this.playerList = [];
        this.eggs = [];
    } else {    this.name = parameters.name === undefined ? "Anonymous" : parameters.name;
                this.color = parameters.color === undefined ? 0xffffffff : parameters.color;
                this.nbPlayers = parameters.nbPlayers === undefined ? 0 : parameters.nbPlayers;
                this.players = parameters.players === undefined ? [] : parameters.players;
                this.eggs = parameters.eggs === undefined ? [] : parameters.eggs;
        }



    this.addPlayer = function (number) {
        var i;
        for (i = 0; i < this.players.length; i += 1) {
            if (this.players[i] === number) { return false; }
        }
        this.players.push(number);
        this.nbPlayers += 1;
        return true;
    };



    this.removePlayer = function (number) {
        var i;
        for (i = 0; i < this.players.length; i += 1) {
            if (this.players[i] === number) {
                this.players.splice(i, 1);
                this.nbPlayers -= 1;
                return true;
            }
        }
        return false;
    };

};