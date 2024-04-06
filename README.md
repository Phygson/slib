# SLIB

## Requirements:
- node-gyp
> Also, remember to install other necessary modules by running **npm install**

## Building: 
    node-gyp rebuild

## Usage: 
- ### Directly import
```js
var slib = require("./path/to/index.js")
```
- ### Import with npm
```bash
npm install ./path/to/module
```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and then in your js file
```js
var slib = require("slib")
```

# Documentation

## > chordsInScale(tonic, mode)
- **tonic**: string, latin note names with an optional alteration sign, e.g. "Ab" or "C#" or "F".
- **mode**: string, one of the:
  - "Ion" - Ionian (major),
  - "Dor" - Dorian,
  - "Phy" - Phrygian,
  - "Lyd" - Lydian,
  - "Mixolyd" - Mixolydian,
  - "Aeo" - Aeolian (minor),
  - "Loc" - Locrian.
- **Returns**: array, the triad chords that can be built on the provided diatonic scale.

## > notesInScale(tonic, mode)
- **tonic**: string, latin note names with an optional alteration sign, e.g. "Ab" or "C#" or "F".
- **mode**: string, one of the:
  - "Ion" - Ionian (major),
  - "Dor" - Dorian,
  - "Phy" - Phrygian,
  - "Lyd" - Lydian,
  - "Mixolyd" - Mixolydian,
  - "Aeo" - Aeolian (minor),
  - "Loc" - Locrian.
- **Returns**: array, the notes the provided diatonic scale constists of.
