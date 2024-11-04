(defun remove-last (sequence)
    (reverse (cdr (reverse sequence))))

(defun get-last (sequence)
    (car (last sequence)))

(defun get-second-last (sequence)
    (nth (- (length sequence) 2) sequence))

(defun concat-lists (seq1 seq2)
    (if (null seq1)
        seq2
        (cons (car seq1) (concat-lists (cdr seq1) seq2))))

(defun selection-sort (full-hand)
    (let ((new-list (copy-list full-hand)))
        (dotimes (i (- (length full-hand) 1))
            (let ((min-index i))
                (loop for j from (+ i 1) to (- (length full-hand) 1) by 1 do
                    (when (< (card-value (nth j new-list)) (card-value (nth min-index new-list)))
                        (setf min-index j)))
        (let ((temp (nth min-index new-list)))
            (setf (nth min-index new-list) (nth i new-list))
            (setf (nth i new-list) temp))))
    (return-from selection-sort new-list)))

(defun is-in-order (hand)
    (loop for i from 1 to (length hand) by 1 do
        (when (not (eql (card-value (nth i hand)) (+ (card-value (nth (- i 1) hand)) 1)))
            (return-from is-in-order nil)))
    (return-from is-in-order t))

(defun all-in-suit (hand)
    (let ((s (card-suit (nth 0 hand))))
        (dotimes (i 7)
            (when (not (eql s (card-suit (nth i hand))))
                (return-from all-in-suit nil))))
    (return-from all-in-suit t))

; http://www.lee-mac.com/sublist.html

(defun sublist ( lst idx len )
    (cond
        ((null lst) nil)
        ((< 0  idx) (sublist (cdr lst) (1- idx) len))
        ((null len) lst)
        ((< 0  len) (cons (car lst) (sublist (cdr lst) idx (1- len)))))
)

(defun num-of-n-in-list (n seq)
    (let ((count 0))
        (dotimes (i (length seq))
            (when (eql (card-value (nth i seq)) n)
                (setf count (+ count 1))))
    (return-from num-of-n-in-list count)))