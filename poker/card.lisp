(defclass card ()
    ((rank :accessor card-rank)
     (suit :accessor card-suit)
     (value :accessor card-value)))