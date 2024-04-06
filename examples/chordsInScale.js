var slib = require("./../index.js")
var readlineSync = require('readline-sync');

var tonic = readlineSync.question('Tonic: ');
var mode = readlineSync.question('Mode: ');

console.log("The chords of " + tonic + " " + mode + ": " + slib.chordsInScale(tonic, mode));
