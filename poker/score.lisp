(defmethod end-game ()
    (terpri)(princ "The game has ended")(terpri)
    (let ((greatest *main-player*) (isTie nil) (score (get-score *main-player*)))
        (dotimes (i (length *computers*))
            (when (> (get-score (nth i *computers*)) score)
                (setq greatest (nth i *computers*))
                (setq isTie nil)
                (setq score (get-score (nth i *computers*)))))
    (princ (format nil "~s has won!" (player-name greatest)))))

(defmethod get-score ((object player))
    (let ((score 0) (sorted-full-hand (selection-sort (concat-lists (player-hand object) *middle-cards*))))
        (when (is-royal-flush sorted-full-hand)                               (setq score (+ score 10)))
        (when (and (isflush sorted-full-hand) (is-straight sorted-full-hand)) (setq score (+ score 9)))
        (when (is-four-of-a-kind sorted-full-hand)                            (setq score (+ score 8)))
        (when (is-full-house sorted-full-hand)                                (setq score (+ score 7)))
        (when (isflush sorted-full-hand)                                      (setq score (+ score 6)))
        (when (is-straight sorted-full-hand)                                  (setq score (+ score 5)))
        (when (is-three-of-a-kind sorted-full-hand)                           (setq score (+ score 4)))
        (when (eql (get-pairs sorted-full-hand) 2)                            (setq score (+ score 3)))
        (when (eql (get-pairs sorted-full-hand) 1)                            (setq score (+ score 2)))
    (return-from get-score score)))

(defmethod isflush (sorted-full-hand)
    (loop for i from 0 to 2 by 1 do
        (when (all-in-suit (sublist sorted-full-hand i 5))
            (return-from isflush t)))
    (return-from isflush nil))

(defmethod is-royal-flush (sorted-full-hand)
    (when (not (isflush sorted-full-hand)) (return-from is-royal-flush nil))
    (let ((last-list (sublist sorted-full-hand 2 nil)))
        (when (and (is-in-order last-list) (eql 14 (card-value (get-last last-list))))
            (return-from is-royal-flush t)))
    (return-from is-royal-flush nil))

(defmethod is-four-of-a-kind (sorted-full-hand)
    (loop for i from 2 to 15 by 1 do
        (when (eql (num-of-n-in-list i sorted-full-hand) 4)
            (return-from is-four-of-a-kind t)))
    (return-from is-four-of-a-kind nil))

(defmethod is-full-house (sorted-full-hand)
    (when (and (eql (num-of-n-in-list 11 sorted-full-hand) 3) (eql (num-of-n-in-list 13 sorted-full-hand) 2))
        (return-from is-full-house t))
    (return-from is-full-house nil))

(defmethod is-straight (sorted-full-hand)
    (loop for i from 0 to 2 by 1 do
        (when (is-in-order (sublist sorted-full-hand i 5))
            (return-from is-straight t)))
    (return-from is-straight nil))

(defmethod is-three-of-a-kind (sorted-full-hand)
    (loop for i from 2 to 15 by 1 do
        (when (eql (num-of-n-in-list i sorted-full-hand) 3)
            (return-from is-three-of-a-kind t)))
    (return-from is-three-of-a-kind nil))

(defmethod get-pairs (sorted-full-hand)
    (let ((c 0))
        (loop for i from 2 to 15 by 1 do
            (when (> (num-of-n-in-list i sorted-full-hand) 1)
                (setf c (+ c 1))))
    (return-from get-pairs c)))