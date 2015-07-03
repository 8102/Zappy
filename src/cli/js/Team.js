/*global manager*/
var bannerColor = 0, backgroundArray = ["red.png", "blue.png", "green.png", "purple.png", "dark.png", "orange.png", "grey.png", "limegreen.png", "turquoise.png"],
    shaftArray = ["red.png", "blue.png", "green.png", "purple.png", "dark.png", "orange.png", "grey.png", "limegreen.png", "turquoise.png"];
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
        bannerContainer: null,
        banner: null,
        shaft: null,
        container: null,
        title: null,
        nbplayers: null,
        content: null
    };

    this.nbDead = 0;

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

        self.banner.bannerContainer = document.createElement("div");
        self.banner.bannerContainer.id = "banner-container-" + self.name;
        self.banner.bannerContainer.className = "teamBannerContainer";
        teamDisplayer.appendChild(self.banner.bannerContainer);

        self.banner.shaft = document.createElement("div");
        self.banner.shaft.id = "banner-shaft-" + self.name;
        self.banner.shaft.className = "bannerShaft";
        self.banner.shaft.style.backgroundImage = "url('ressources/images/GUIBanners/shaft-" + shaftArray[bannerColor] + "')";
        self.banner.bannerContainer.appendChild(self.banner.shaft);

        self.banner.banner = document.createElement("div");
        self.banner.banner.id = "banner-" + self.name;
        self.banner.banner.className = 'teamBanner';
        self.banner.banner.style.backgroundImage = "url('ressources/images/GUIBanners/" + backgroundArray[bannerColor] + "')";
        self.banner.bannerContainer.appendChild(self.banner.banner);
        bannerColor = (bannerColor + 1) % backgroundArray.length;



        self.banner.container = document.createElement("div");
        self.banner.container.id = "banner-content-container-" + self.name;
        self.banner.container.className = "bannerContentContainer";

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
        var i, nbEggsReady = 0;

        self.banner.content.innerHTML = self.nbPlayers + " Players Alive<br><br>";
        self.banner.content.innerHTML += "Higher Level : " + self.getHigherLevel() + "<br><br>";
        self.banner.content.innerHTML += "Deads : " + self.nbDead + "<br><br>";
        for (i = 0; i < self.eggs.length; i += 1) {
            if (self.eggs[i].isReady === true) {nbEggsReady += 1; }
        }
        self.banner.content.innerHTML += "Eggs : " + self.eggs.length + (nbEggsReady > 0 ? "<br> - (" + nbEggsReady + " ready) - " : "");
    };


    this.addTeamBanner();
};