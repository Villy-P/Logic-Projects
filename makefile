run-poker:
	sbcl.exe --eval '(require "asdf")' --eval '(asdf:load-asd (merge-pathnames "poker/project.asd" (uiop:getcwd)))' --eval '(asdf:load-system :project)'