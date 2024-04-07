# SLIB
---
## Requirements:
- node-gyp
> Also, remember to install other necessary modules by running **npm install**
---
## Building: 
    node-gyp rebuild
---
<details>
<summary><h2>Usage:</h2></summary>

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
</details>

---

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
- **Returns**: array of strings, the triad chords that can be built on the provided diatonic scale.

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
- **Returns**: array of 2 arrays of strings, the first array is the notes the diatonic scale consists of, and the second array is the degrees of the notes in relation to the Ionian scale.

## > getRomanScale(tonic, mode)
- **tonic**: string, latin note names with an optional alteration sign, e.g. "Ab" or "C#" or "F".
- **mode**: string, one of the:
  - "Ion" - Ionian (major),
  - "Dor" - Dorian,
  - "Phy" - Phrygian,
  - "Lyd" - Lydian,
  - "Mixolyd" - Mixolydian,
  - "Aeo" - Aeolian (minor),
  - "Loc" - Locrian.
- **Returns**: array of strings, the roman numerals as the are presented in the Fourths-Fifths circle, clockwise (<a href = "https://en.wikipedia.org/wiki/Roman_numerals">Wikipedia</a>).
- **Note:** the diminished chord is represented as minor + prefix "d", e.g. Bdim in C Ionian is "viid".
