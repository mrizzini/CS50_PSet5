# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Pneumonoultramicroscopicsilicovolcanoconiosis is the longest word in the English language. It is a synonym for silicosis.

## According to its man page, what does `getrusage` do?

getrusage returns resource usage measurements for who, which can be RUSAGE_SELF, RUSAGE_CHILDREN, or RUSAGE_THREAD

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because we want to be able to save time and memory

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop loops thru the file to check each word in the text. It continues on until c does not reach the end of the file (EOF). It first checks if the character of a word is alphabetical, if it has a \, and it's index is over 0.
If it is, then we append the character to a word variable using the index, and then increment the index. it then checks if the index is greater than LENGTH, which is defined in dictionary.h as 45. So that
is the maximum length of a word that we will be checking. If the word is too long, then we take in the rest of the string and start index at 0 to get ready for the next word.
The next else if statement will take in any words with numbers in them, and then do the same as above and take in the rest of the word and reset index to 0, effecively ignoring words with numbers.
If the final else if statement gets hit, then we know we have reached the end of a word that passes all the checks. We take the last index of the word and put in \0 to signify the end of a string, and update the words counter by 1.
We then pass that word into our check function to check if it matches one of the words in the dictionary, as well as checking the time to complete this task.
We update the time_check with the time it took, and if the word comes back as misspelled, we print out that word.
We add in an error check at the end, and then close out that file.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fgetc reads one character at a time from a stream which will help us keep track of the index of the word. fscanf could cause us to read words in inproperly, because it tries to match the "format", and in such long texts we are using, it is impossible to define that format

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because we don't want those values changing, we are not supposed to change anything about the word or the dictionary in any case, so we don't want those getting changed in any way once a value is in there

