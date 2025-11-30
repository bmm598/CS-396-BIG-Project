#lang racket

(require "geometry.rkt")
(require json)

(define (export-json filename json-data)
  (call-with-output-file filename
    (lambda (out) (write-json json-data out))
    #:exists 'replace)
)

(define (export-segment filename x1 y1 x2 y2)
  (define p1 (point x1 y1))
  (define p2 (point x2 y2))
  (define seg (segment p1 p2))
  (define json-data (segment-json seg))
  (export-json filename json-data)
)

(define (export-polygon filename coords)
  (define numbers (map string->number coords))
  (define points
  (let loop ([i 0] [acc '()])
    (if (>= i (length numbers))
        (reverse acc)
        (loop (+ i 2)
              (cons (point (list-ref numbers i)
                          (list-ref numbers (+ i 1)))
                    acc)))))
  (define poly (polygon points))
  (define json-data (polygon-json poly))
  (export-json filename json-data)
)

(module+ main
  (define args (vector->list (current-command-line-arguments)))
  (define len (length args))
  (cond
    [(< len 5)
     (printf "Usage:\n")
     (printf "  racket export-json.rkt output.json x1 y1 x2 y2   ; segment\n")
     (printf "  racket export-json.rkt output.json x1 y1 x2 y2 x3 y3 ... ; polygon\n")]
    [(= len 5)
     ;; segment
     (define filename (list-ref args 0))
     (define x1 (string->number (list-ref args 1)))
     (define y1 (string->number (list-ref args 2)))
     (define x2 (string->number (list-ref args 3)))
     (define y2 (string->number (list-ref args 4)))
     (export-segment filename x1 y1 x2 y2)
     (printf "Segment JSON written to ~a\n" filename)]
    [(even? (- len 1))
     ;; polygon
     (define filename (car args))
     (define coords (cdr args))
     (export-polygon filename coords)
     (printf "Polygon JSON written to ~a\n" filename)]
    [else
     (printf "Error: Polygon requires an even number of coordinates.\n")]))