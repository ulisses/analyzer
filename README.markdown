USE
===

	analyzer -i <dir> [-x<file.xml> | -p<file.pdf> | -t<file.tex>]

where dir is the directory you want to extract metrics from. And [-x,-p,-t] is the output type of file you want.

DEPENDENCIES
============

This section concerns the installation (manually) of the essential Haskell packages and assumes that the user has already installed Cabal in his system.

First install language-c-0.3.2.1, but do not install the version on hackage. Install mine.
Goto language-c-0.3.2.1 and run this commands:

```java
runhaskell Setup.hs configure --enable-library-profiling
runhaskell Setup.hs build
sudo runhaskell Setup.hs install
```

After this install the following packages with cabal:

For the following packages,

* MissingH
* graphviz
* hxt
* HaTeX
* text
* strict
* language-c-comments
* monad-parallel
* monad-loops

do **sudo cabal install** _name-of-package_


After that hit

	make

and then

	sudo make install
	
in this folder, after that you will have a new command: analyzer

Running multicore
=================

Make sure you have installed all the Haskell packages.

If you have multiple cores on your machine (n cores), you should use:

	analyzer [OPTIONS] +RTS -N<nrOfCores>

