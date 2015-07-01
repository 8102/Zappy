/*global manager*/
var bannerColor = 0, backgroundArray = ["red.png", "blue.png", "green.png", "purple.png", "dark.png"];
/*jslint browser: true*/
var Team = function (parameters) {
    'use strict';
    var self = this;

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
    this.banner = {
        banner: null,
        container: null,
        title: null,
        nbplayers: null,
        content: null
    };

    this.updatePlayerList = function () {
        var i, player;

        self.playerList = [];
        for (i = 0; i < self.players.length; i += 1) {
            if ((player = manager.getPlayerByID(self.players[i])) !== null) {self.playerList.push(player); }
        }
    };

    this.addPlayer = function (number) {
        var i;
        for (i = 0; i < this.players.length; i += 1) {
            if (this.players[i] === number) { return false; }
        }
        this.players.push(number);
        this.nbPlayers += 1;
        self.updatePlayerList();
        self.updateNbPlayersOnBanner();
        return true;
    };

    this.removePlayer = function (number) {
        var i;
        for (i = 0; i < this.players.length; i += 1) {
            if (this.players[i] === number) {
                this.players.splice(i, 1);
                this.nbPlayers -= 1;
                self.updateNbPlayersOnBanner();
                return true;
            }
        }
        return false;
    };

    this.addTeamBanner = function () {
        var teamDisplayer = document.getElementById("GUI-TeamContainer"),
            teamBanner,
            teamBannerContainer,
            teamTitle,
            teamContent;
        if (self.banner.banner !== null) {self.banner.banner.remove(); }

        self.banner.banner = document.createElement("div");
        self.banner.banner.id = "banner-" + self.name;
        self.banner.banner.className = 'teamBanner';
        self.banner.banner.style.backgroundImage = "url('ressources/images/GUIBanners/" + backgroundArray[bannerColor] + "')";
        bannerColor = (bannerColor + 1) % backgroundArray.length;
        teamDisplayer.appendChild(self.banner.banner);

        self.banner.container = document.createElement("div");
        self.banner.container.id = "banner-container-" + self.name;
        self.banner.container.className = "bannerContainer";
        self.banner.banner.appendChild(self.banner.container);

        self.banner.title = document.createElement("div");
        self.banner.title.id = "banner-teamName-" + self.name;
        self.banner.title.className = "teamTitle";
        self.banner.title.innerHTML = self.name;
        self.banner.container.appendChild(self.banner.title);

        self.banner.content = document.createElement("div");
        self.banner.content.id = "banner-content-" + self.name;
        self.banner.content.className = "bannerContent";
        self.banner.container.appendChild(self.banner.content);

        self.updateNbPlayersOnBanner();
    };

    this.getHigherLevel = function () {
        var hl = 1, i, player;

        for (i = 0; i < self.nbPlayers; i += 1) {
            if ((player = manager.getPlayerByID(self.players[i])) !== null) {hl = (player.level > hl ? player.level : hl); }
        }
        return hl;
    };

    this.updateNbPlayersOnBanner = function () {
        self.banner.content.innerHTML = self.nbPlayers + " players alive<br><br>";
        self.banner.content.innerHTML += "level max : " + self.getHigherLevel();
    };


    this.addTeamBanner();
};