# Count-Ones
Count the number of binary ones in a file.

For security purposes, a newly mapped file gets initialized with all zeroes. If you have two files that are supposed to be identical, where one might have been aborted in transit, there is a higher likelihood that the file with more ones is in better shape.

(This was written to target Linux and Cygwin.)
