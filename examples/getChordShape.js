var slib = require("./../index.js")
var readlineSync = require('readline-sync');

var name = readlineSync.question('Name: ');

console.log(slib.getChordShape(name));
