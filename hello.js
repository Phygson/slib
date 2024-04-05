var addon = require('bindings')('slib');

var a = addon.chordsInScale('F','Lyd').split(" ")
var b = addon.chordsInScale('Fb','Aeo').split(" ")
var c = addon.notesInScale('C#','Lyd').split(" ")
var d = addon.notesInScale('Fb','Aeo').split(" ")

console.log(a)
console.log(b)
console.log(c)
console.log(d)