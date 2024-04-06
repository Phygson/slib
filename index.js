var _slib = require('bindings')('slib');

function isTonic(tonic) {
    if ((['C', 'D', 'E', 'F', 'G', 'A', 'B'].includes(tonic[0]) == false) || tonic.length > 2 || 
        (tonic.length == 2 && ['#', 'b'].includes(tonic[1]) == false)) return false;
}

function isMode(mode) {
    return ["Ion", "Dor", "Phy", "Lyd", "Mixolyd", "Aeo", "Loc"].includes(mode);
}

module.exports.notesInScale = function (tonic, mode) {
    if ((typeof tonic != "string") || (typeof mode != "string")) throw "Wrong parameters' types";

    tonic = tonic.charAt(0).toUpperCase() + tonic.slice(1);
    mode = mode.charAt(0).toUpperCase() + mode.slice(1);
    mode = mode.charAt(0) + mode.slice(1).toLowerCase();

    if (isTonic(tonic) == false) throw "Not a tonic";
    if (isMode(mode) == false) throw "Not a mode";  

    return _slib.notesInScale(tonic, mode).split(" "); 
}

module.exports.chordsInScale = function (tonic, mode) {
    if ((typeof tonic != "string") || (typeof mode != "string")) throw "Wrong parameters' types";

    tonic = tonic.charAt(0).toUpperCase() + tonic.slice(1);
    mode = mode.charAt(0).toUpperCase() + mode.slice(1);
    mode = mode.charAt(0) + mode.slice(1).toLowerCase();

    if (isTonic(tonic) == false) throw "Not a tonic";
    if (isMode(mode) == false) throw "Not a mode";

    return _slib.chordsInScale(tonic, mode).split(" "); 
}