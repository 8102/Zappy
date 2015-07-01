/*global THREE*/
var cubeGeom = new THREE.BoxGeometry(1, 1, 1);

var SHAPE = {PLANE: 0, SPHERE: 1, BOX: 2, CYLINDER: 3, CIRCLE: 4, SHAPE: 5, DODECAHEDRON: 6, ICOSAHEDRON: 7, TETRAHEDRON: 8, OCTAHEDRON: 9, TORUS: 10, TORUSKNOT: 11};
var LIGHT_SHAPE = {PLANE: 12, SPHERE: 13, BOX: 14, CYLINDER: 15, CIRCLE: 16, SHAPE: 17, DODECAHEDRON: 18, ICOSAHEDRON: 19, TETRAHEDRON: 20, OCTAHEDRON: 21, TORUS: 22, TORUSKNOT: 23};
var MATERIAL = { BASIC: 0, LAMBERT: 1, DEPTH: 2, FACE: 3, PHONG: 4};
var PREFAB_MATERIAL = { GROUND: 0, GROUND_SIDE: 1, SKYBOX_UP: 2, SKYBOX_DOWN: 3, SKYBOX_LEFT: 4, SKYBOX_RIGHT: 5, SKYBOX_FRONT: 6, SKYBOX_BACK: 7, LINEMATE: 8, DERAUMERE: 9, SIBUR: 10, MENDIANE: 11, PHIRAS: 12, THYSTAME: 13, EGG: 14, FOOD: 15};
var i;

var GeometryFactory = function () {
    'use strict';
    var self = this;

    this.shapes = [];
    this.preparedShapes = [];
    this.materials = [];
    this.prefabMaterials = [];
    this.textures = [];
    this.texturesFileName = [
        "checkerboard.jpg", "grass.jpg", "grass.png", "ground.jpg", "water.jpg", "glow.png", "skyboxTextures/dawnMountain/xneg.png", "skyboxTextures/dawnMountain/xpos.png",
        "skyboxTextures/dawnMountain/yneg.png", "skyboxTextures/dawnMountain/ypos.png", "skyboxTextures/dawnMountain/zneg.png", "skyboxTextures/dawnMountain/zpos.png",                                         "skyboxTextures/stormySky/xneg.png", "skyboxTextures/stormySky/xpos.png", "skyboxTextures/stormySky/yneg.png", "skyboxTextures/stormySky/ypos.png",                                                     "skyboxTextures/stormySky/zneg.png", "skyboxTextures/stormySky/zpos.png", "skyboxTextures/oneDayInHell/xneg.png", "skyboxTextures/oneDayInHell/xpos.png",                                               "skyboxTextures/oneDayInHell/yneg.png", "skyboxTextures/oneDayInHell/ypos.png", "skyboxTextures/oneDayInHell/zneg.png", "skyboxTextures/oneDayInHell/zpos.png", "minecraft_surface.png",
        "minecraft_side.png", "skyboxTextures/darkSea/xneg.png", "skyboxTextures/darkSea/xpos.png", "chocolate.png",
        "skyboxTextures/darkSea/yneg.png", "skyboxTextures/darkSea/ypos.png", "skyboxTextures/darkSea/zneg.png", "skyboxTextures/darkSea/zpos.png"
    ];

    for (i = 0; i < this.texturesFileName.length; i += 1) {
        this.textures[this.texturesFileName[i]] = new THREE.ImageUtils.loadTexture('ressources/images/textures/' + this.texturesFileName[i]);
    }

    this.shapes[SHAPE.SPHERE] = THREE.SphereGeometry;
    this.shapes[SHAPE.BOX] = THREE.BoxGeometry;
    this.shapes[SHAPE.PLANE] = THREE.PlaneBufferGeometry;
    this.shapes[SHAPE.CYLINDER] = THREE.CylinderGeometry;
    this.shapes[SHAPE.CIRCLE] = THREE.CircleGeometry;
    this.shapes[SHAPE.SHAPE] = THREE.ShapeGeometry;
    this.shapes[SHAPE.DODECAHEDRON] = THREE.DodecahedronGeometry;
    this.shapes[SHAPE.ICOSAHEDRON] = THREE.IcosahedronGeometry;
    this.shapes[SHAPE.TETRAHEDRON] = THREE.TetrahedronGeometry;
    this.shapes[SHAPE.OCTAHEDRON] = THREE.OctahedronGeometry;
    this.shapes[SHAPE.TORUS] = THREE.TorusGeometry;
    this.shapes[SHAPE.TORUSKNOT] = THREE.TorusKnotGeometry;

    this.preparedShapes[LIGHT_SHAPE.BOX] = new THREE.BoxGeometry(1, 1, 1);
    this.preparedShapes[LIGHT_SHAPE.PLANE] = new THREE.PlaneBufferGeometry(1, 1, 1, 1);
    this.preparedShapes[LIGHT_SHAPE.SPHERE] = new THREE.SphereGeometry(1, 32, 16);
    this.preparedShapes[LIGHT_SHAPE.CYLINDER] = new THREE.CylinderGeometry(1, 1, 1, 32, 16);
    this.preparedShapes[LIGHT_SHAPE.CIRCLE] = new THREE.CircleGeometry(1, 0.1, 1, 1);
    this.preparedShapes[LIGHT_SHAPE.TETRAHEDRON] = new THREE.TetrahedronGeometry(1, 2);
    this.preparedShapes[LIGHT_SHAPE.ICOSAHEDRON] = new THREE.IcosahedronGeometry(1, 2);
    this.preparedShapes[LIGHT_SHAPE.OCTAHEDRON] = new THREE.OctahedronGeometry(1, 1);
    this.preparedShapes[LIGHT_SHAPE.DODECAHEDRON] = new THREE.DodecahedronGeometry(1, 2);
    this.preparedShapes[LIGHT_SHAPE.TORUS] = new THREE.BoxGeometry(1, 0.2, 64, 10);
    this.preparedShapes[LIGHT_SHAPE.TORUSKNOT] = new THREE.BoxGeometry(1, 0.2, 64, 10, 2, 3);


    this.materials[MATERIAL.BASIC] = THREE.MeshBasicMaterial;
    this.materials[MATERIAL.LAMBERT] = THREE.MeshLambertMaterial;
    this.materials[MATERIAL.DEPTH] = THREE.MeshDepthMaterial;
    this.materials[MATERIAL.FACE] = THREE.MeshFaceMaterial;
    this.materials[MATERIAL.PHONG] = THREE.MeshPhongMaterial;

/*
    this.textures['minecraft_side.png'].wrapS = THREE.RepeatWrapping;
    this.textures['minecraft_side.png'].wrapT = THREE.RepeatWrapping;
    this.textures['minecraft_side.png'].repeat.set(10, 1);
*/
    this.groundMaterialArray = [];
    this.mat1 = new this.materials[MATERIAL.BASIC]({side: THREE.FrontSide, map: this.textures['minecraft_surface.png']});
    this.mat2 = new this.materials[MATERIAL.BASIC]({side: THREE.FrontSide, map: this.textures['minecraft_side.png']});
    for (i = 0; i < 6; i += 1) {
        this.groundMaterialArray.push(i === 2 || i === 3 ? this.mat1 : this.mat2);
    }
    this.prefabMaterials[PREFAB_MATERIAL.GROUND] = new this.materials[MATERIAL.BASIC]({transparent: false, opacity: 0.4, side: THREE.DoubleSide, map: this.textures['grass.png']});
    this.prefabMaterials[PREFAB_MATERIAL.FOOD] = new this.materials[MATERIAL.BASIC]({side: THREE.FrontSide, map: this.textures['chocolate.png']});
    this.prefabMaterials[PREFAB_MATERIAL.LINEMATE] = new this.materials[MATERIAL.PHONG]({side: THREE.FrontSide, color: 'lime'});
    this.prefabMaterials[PREFAB_MATERIAL.DERAUMERE] = new this.materials[MATERIAL.PHONG]({side: THREE.FrontSide, color: 'red'});
    this.prefabMaterials[PREFAB_MATERIAL.SIBUR] = new this.materials[MATERIAL.PHONG]({side: THREE.FrontSide, color: 'blue'});
    this.prefabMaterials[PREFAB_MATERIAL.MENDIANE] = new this.materials[MATERIAL.PHONG]({side: THREE.FrontSide, color: 'cyan'});
    this.prefabMaterials[PREFAB_MATERIAL.PHIRAS] = new this.materials[MATERIAL.PHONG]({side: THREE.FrontSide, color: 'yellow'});
    this.prefabMaterials[PREFAB_MATERIAL.THYSTAME] = new this.materials[MATERIAL.PHONG]({side: THREE.FrontSide, color: 'mistyrose'});
    this.prefabMaterials[PREFAB_MATERIAL.EGG] = new this.materials[MATERIAL.PHONG]({side: THREE.FrontSide, color: 'white'});


    this.createEgg = function (color) {
        var egg = new THREE.Mesh(this.preparedShapes[LIGHT_SHAPE.SPHERE], new this.materials[MATERIAL.PHONG]({color: color, side: THREE.FrontSide}));
        egg.scale.set(0.1, 0.16, 0.1);
        return egg;
    };

};