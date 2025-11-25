#lang racket

(provide 
    point 
    segment 
    triangle 
    polygon
    point-json 
    segment-json 
    triangle-json 
    polygon-json
    point-x
    point-y
)

(require json)

(struct point (x y) #:transparent)
(struct segment (p1 p2) #:transparent)
(struct triangle (p1 p2 p3) #:transparent)
(struct polygon (points) #:transparent)

(define (point-json p)
    (hash   'type "point"
            'x (point-x p)
            'y (point-y p)
    )
)

(define (segment-json s)
    (hash   'type "segment"
            'points (list 
                (point-json (segment-p1 s))
                (point-json (segment-p2 s))
                    )
    )
)

(define (triangle-json t)
    (hash   'type "triangle"
            'points (list 
                (point-json (triangle-p1 t))
                (point-json (triangle-p2 t))
                (point-json (triangle-p3 t))
                    )
    )
)

(define (polygon-json poly)
    (hash   'type "polygon"
            'points (map point-json (polygon-points poly))
    )
)
