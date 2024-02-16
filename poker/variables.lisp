(declaim (sb-ext:muffle-conditions sb-ext:compiler-note))

(defvar *main-player* nil)

(defvar *computer-num* 0)
(defvar *computers* (list))
(defvar *middle-cards* (list))

(defvar *dealer-button-index* nil)
(defvar *current-player* nil)
(defvar *current-player-index* nil)
(defvar *greatest-better* nil)

(defvar *current-bet* 10)
(defvar *pot-amount* 15)

(defvar *last-player-called* nil)

(defun display-middle-cards ()
    (dotimes (i (length *middle-cards*))
        (princ (format nil "A ~s of ~s" 
            (card-rank (nth i *middle-cards*)) 
            (card-suit (nth i *middle-cards*))))(terpri)))