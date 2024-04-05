# SLIB

## Requirements:
- node-gyp
> Also, remember to install other necessary modules by running **npm install**

## Building: 
    node-gyp rebuild

## Running (temporary): 
    node hello.js

# Documentation

## > chordsInScale(tonic, mode)
- **tonic**: string, latin note names with an optional alteration sign.
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
- **tonic**: string, latin note names with an optional alteration sign.
- **mode**: string, one of the:
  - "Ion" - Ionian (major),
  - "Dor" - Dorian,
  - "Phy" - Phrygian,
  - "Lyd" - Lydian,
  - "Mixolyd" - Mixolydian,
  - "Aeo" - Aeolian (minor),
  - "Loc" - Locrian.
- **Returns**: array, the notes the provided diatonic scale constists of.
