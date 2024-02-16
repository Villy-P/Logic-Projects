(defun get-left (i)
    (when (eq i 0) (return-from get-left (get-last *computers*)))
    (when (eq i 1) (return-from get-left *main-player*))
    (nth (- i 2) *computers*))

(defun get-left-num (i)
    (when (eq i 0) (return-from get-left-num *computer-num*))
    (when (eq i 1) (return-from get-left-num 0))
    (- i 1))

(defun get-two-left (i)
    (when (eq i 0) (return-from get-two-left (get-second-last *computers*)))
    (when (eq i 1) (return-from get-two-left (get-last *computers*)))
    (when (eq i 2) (return-from get-two-left *main-player*))
    (nth (- i 3) *computers*))

(defun get-current (i)
    (when (eq i 0) (return-from get-current *main-player*))
    (nth (- i 1) *computers*))

(defun main ()
    (setf *random-state* (make-random-state t))
    (setf deck (shuffle deck))
    (princ "Welcome to Texas Hold'em!")(terpri)
    (princ "What is your name? ")
    (finish-output)
    (setq *main-player* (make-instance 'player))
    (setf (player-name *main-player*) (read))
    (setf (player-hand *main-player*) (list))
    (setf (player-chips *main-player*) 2000)
    (setf (player-is-comp *main-player*) nil)
    (setf (player-has-button *main-player*) nil)
    (setf (player-has-folded *main-player*) nil)
    (setf (player-has-checked *main-player*) nil)
    (loop
        (princ "How many people do you want to play against? (limit 2 max 8) ")
        (finish-output)(setf *computer-num* (read))
        (when (and (> *computer-num* 1) (< *computer-num* 9)) (return *computer-num*)))
    (dotimes (i *computer-num*)
        (setq *computers* (append *computers* (list (make-instance 'player))))
        (setf (player-name (nth i *computers*)) (format nil "Computer #~d" i))
        (setf (player-hand (nth i *computers*)) (list))
        (setf (player-chips (nth i *computers*)) 2000)
        (setf (player-is-comp (nth i *computers*)) t)
        (setf (player-has-button (nth i *computers*)) nil)
        (setf (player-has-folded (nth i *computers*)) nil)
        (setf (player-has-checked (nth i *computers*)) nil)
        (give-player-cards (nth i *computers*) 2))

    ; 0 is *main-player* any other is index + 1 of *computer-num*
    (setq *dealer-button-index* (random-from-range 0 *computer-num*))
    (setq *current-player* (get-left (get-left-num (get-left-num *dealer-button-index*))))
    (setq *current-player-index* (get-left-num (get-left-num (get-left-num *dealer-button-index*))))
    
    (terpri)
    (setf (player-has-button (get-current *dealer-button-index*)) t)
    (princ (format nil "~s got the dealer button" (player-name (get-current *dealer-button-index*))))
    (terpri)(princ (format nil 
        "~s put down 5 chips as the Small Blind and ~s put down 10 chips as the Big Blind"
        (player-name (get-left *dealer-button-index*)) (player-name (get-two-left *dealer-button-index*))))
    (setf (player-chips (get-left *dealer-button-index*)) (- (player-chips (get-left *dealer-button-index*)) 5))
    (setf (player-chips (get-two-left *dealer-button-index*)) (- (player-chips (get-two-left *dealer-button-index*)) 10))
    (setf *greatest-better* (get-two-left *dealer-button-index*))
    (terpri)

    (terpri)(princ "The dealer hands you and the computers each two cards.")
    (give-player-cards *main-player* 2)
    (terpri)(princ "You got:")(terpri)
    (print-player-cards *main-player*)

    (loop
        (terpri)(terpri)
        (when (not (player-has-folded *current-player*)) 
        (princ (format nil "It is ~s's turn." (player-name *current-player*)))
        (terpri)(if (eql (player-is-comp *current-player*) t)
            (computer-play *current-player* 0)
            (player-play *main-player* 0))
        (setf *current-player-index* (get-left-num *current-player-index*))
        (setf *current-player* (get-left *current-player-index*))
        (when (eql (player-name *current-player*) (player-name *greatest-better*)) (return *current-player*))))

    (terpri)(terpri)(princ "It is time for the flop.")(terpri)
    (dotimes (i 3)
        (setq *middle-cards* (append *middle-cards* (list (get-last deck))))
        (setf deck (remove-last deck)))

    (setq *current-player* (get-left *dealer-button-index*))
    (setq *current-player-index* (get-left-num *dealer-button-index*))
    (setq *greatest-better* (get-left *dealer-button-index*))
    
    (display-middle-cards)

    (loop
        (terpri)(terpri)
        (when (and (not (player-has-folded *current-player*)) (not (player-has-checked *current-player*)))
        (princ (format nil "It is ~s's turn." (player-name *current-player*)))
        (terpri)(if (eql (player-is-comp *current-player*) t)
            (computer-play *current-player* 1)
            (player-play *main-player* 1))
        (setf *current-player-index* (get-left-num *current-player-index*))
        (setf *current-player* (get-left *current-player-index*))
        (when (eql (player-name *current-player*) (player-name *greatest-better*)) (return *current-player*))))

    (terpri)(terpri)(princ "It is time for the turn.")(terpri)
    (setq *middle-cards* (append *middle-cards* (list (get-last deck))))
    (setf deck (remove-last deck))

    (setq *current-player* (get-left *dealer-button-index*))
    (setq *current-player-index* (get-left-num *dealer-button-index*))
    (setq *greatest-better* (get-left *dealer-button-index*))
    
    (display-middle-cards)

    (loop
        (terpri)(terpri)
        (when (and (not (player-has-folded *current-player*)) (not (player-has-checked *current-player*)))
        (princ (format nil "It is ~s's turn." (player-name *current-player*)))
        (terpri)(if (eql (player-is-comp *current-player*) t)
            (computer-play *current-player* 1)
            (player-play *main-player* 1))
        (setf *current-player-index* (get-left-num *current-player-index*))
        (setf *current-player* (get-left *current-player-index*))
        (when (eql (player-name *current-player*) (player-name *greatest-better*)) (return *current-player*))))

    (terpri)(terpri)(princ "It is time for the river.")(terpri)
    (setq *middle-cards* (append *middle-cards* (list (get-last deck))))
    (setf deck (remove-last deck))
    (display-middle-cards)

    (setq *current-player* (get-left *dealer-button-index*))
    (setq *current-player-index* (get-left-num *dealer-button-index*))
    (setq *greatest-better* (get-left *dealer-button-index*))

    (loop
        (terpri)(terpri)
        (when (and (not (player-has-folded *current-player*)) (not (player-has-checked *current-player*)))
        (princ (format nil "It is ~s's turn." (player-name *current-player*)))
        (terpri)(if (eql (player-is-comp *current-player*) t)
            (computer-play *current-player* 1)
            (player-play *main-player* 1))
        (setf *current-player-index* (get-left-num *current-player-index*))
        (setf *current-player* (get-left *current-player-index*))
        (when (eql (player-name *current-player*) (player-name *greatest-better*)) (return *current-player*))))

    (end-game)

    (finish-output))

(main)