# Disturber

`Disturber` is a desktop C++ Qt application for learning a foreign language.

The learning algorithm is inspired by the idea of Anki cards, but contains some adjustments:

* `Disturber` is always open on your computer and periodically pops up in front of you, presenting you with a block of words to translate.
* The block for a new "lesson" is chosen based on the history of your previous responses. The algorithm proposes a mixture of words you failed to translate lately, words you haven't seen in a while, and some new words as well.

The app has native support for German diacritics (e.g. `Ö` and similar) such that a user can enter them even on a non-German keyboard layout. 

## Implementation details

`Disturber` is a QT C++ app, that uses `SQLite3` to store its data in a file. It also supports import and export of language dictionaries in `.csv` format.
