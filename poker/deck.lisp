(defvar suits (make-array `(4)
    :initial-contents `("Clubs" "Diamonds" "Hearts" "Spades")))
(defvar value (make-array `(13)
    :initial-contents `(2 3 4 5 6 7 8 9 10 11 12 13 14)))
(defvar ranks (make-array `(13)
    :initial-contents `("2" "3" "4" "5" "6" "7" "8" "9" "10"
                        "J" "Q" "K" "A")))

(defvar deck `())

(dotimes (i 13)
    (dotimes (j 4)
        (setq deck (append deck (list (make-instance 'card))))
        (setf (card-rank (car (last deck))) (aref ranks i))
        (setf (card-suit (car (last deck))) (aref suits j))
        (setf (card-value (car (last deck))) (aref value j))))

(defun shuffle (sequence)
    (loop for i from (length sequence) downto 2 do 
        (rotatef (elt sequence (random i))
            (elt sequence (1- i))))
    sequence)