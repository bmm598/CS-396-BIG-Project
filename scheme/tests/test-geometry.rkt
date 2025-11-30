#lang racket

(require rackunit)
(require (file "../src/geometry.rkt")) ; adjust path if needed

(define (check-and-report expected actual label)
  (check-equal? actual expected)
  (printf "✓ ~a passed\n" label))

;; point tests
(check-and-report 
    (point-x (point 1 2)) 
    1 
    "point-x")

(check-and-report 
    (point-y (point 1 2)) 
    2 
    "point-y")

(check-and-report 
    (point-json (point 3 4)) 
    (hash 'type "point" 'x 3 'y 4) 
    "point-json")

;; segment test
(define seg (segment (point 0 0) (point 3 4)))
(check-and-report 
    (segment-json seg) 
    (hash 'type "segment"
        'points (list (hash 'type "point" 'x 0 'y 0)
            (hash 'type "point" 'x 3 'y 4))) 
    "segment-json")

;; polygon test
(define poly (polygon (list (point 0 0) (point 3 0) (point 3 4) (point 1 5) (point 0 0))))

(check-and-report
    (polygon-json poly)
    (hash 'type "polygon"
        'points (list (hash 'type "point" 'x 0 'y 0)
            (hash 'type "point" 'x 3 'y 0)
            (hash 'type "point" 'x 3 'y 4)
            (hash 'type "point" 'x 1 'y 5)
            (hash 'type "point" 'x 0 'y 0)))
    "polygon-json")
