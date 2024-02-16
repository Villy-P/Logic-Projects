# Lisp-Texas-Hold-Em

## Setup

Buckle up.

Download SCBL [here](https://www.sbcl.org/platform-table.html) by going down to the table and select the OS you are using.

Then open up the installer.

Just keep pressing `Next` until you reach the install page.

> Note that installation will not work without admin privileges.

Wait for SCBL to finish installing then navigate to the place it was installed.

> If you just kept pressing `Next` without changing any other setting and are on a Windows computer, it should be found in `C:/Program Files`

The folder name should be `Steel Bank Common Lisp`.

For simplicity, rename it to `SCBL`.

Open up the terminal (For Windows, press `Windows+R` then type `cmd`).

First up, navigate to where this folder (with the `main.fasl`) in the terminal.
You can do this by using `cd`.
For example, if your folder was in `C:/Users/Your name here/Downloads/Lisp-Texas-Hold-Em`, enter in `cd Downloads/Lisp-Texas-Hold-Em`.

Run `C:/Program Files/SCBL/scbl.exe` (Or wherever SCBL was installed).
You should see something like this:

``` txt
This is SBCL 2.3.1, an implementation of ANSI Common Lisp.
More information about SBCL is available at <http://www.sbcl.org/>.

SBCL is free software, provided as is, with absolutely no warranty.
It is mostly in the public domain; some portions are provided under
BSD-style licenses.  See the CREDITS and COPYING files in the
distribution for more information.
*
```

> You can exit SCBL any time by typing in `(quit)` or `(SB-EXT:EXIT)`.

You have to type in three things for the project to run (in order)
Here they are:

* `(require "asdf")`
* `(asdf:load-asd (merge-pathnames "project.asd" (uiop:getcwd)))`
* `(asdf:load-system :project)`

All the files should load in and you should be greeted by

``` txt
Welcome to Texas Hold`em!
What is your name?
```

Enjoy!

You can find the slideshow [here](https://docs.google.com/presentation/d/1WFZvA3ZFB5XT3caBjPvCoLKJQjYBE-53nmBkbIYrIoo/edit#slide=id.p)
