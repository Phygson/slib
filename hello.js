var addon = require('bindings')('slib');

var a = addon.chordsInScale('C','Lyd')
var b = addon.chordsInScale('Fb','Aeo')
var c = addon.notesInScale('A#','Phy')
var d = addon.notesInScale('Db','Loc')

console.log("Chords in C Lydian: " + a)
console.log("Chords in Fb Aeolian: " + b)
console.log("Notes in A# Phygrian: " + c)
console.log("Notes in Db Locrian: " + d)