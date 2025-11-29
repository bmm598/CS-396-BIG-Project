#lang racket

(provide 
    point 
    segment 
    polygon
    point-json 
    segment-json 
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

(define (polygon-json poly)
    (hash   'type "polygon"
            'points (map point-json (polygon-points poly))
    )
)
