# Geometry Engine

Geometry Engine is a cross-language interpreter and analysis system.

Scheme (Racket) defines points and segments, C++ performs numerical operations, and Prolog validates geometric relations.

## Dependencies

[nlohmann]: https://github.com/nlohmann/json
[racket]: https://docs.racket-lang.org/raqet/installation.html
[prolog]: https://www.swi-prolog.org/download/stable

[nlohmann/json][nlohmann] is needed for JSON parsing.

For Ubuntu:

```bash
sudo apt-get install nlohmann-json3-dev
```

[racket][racket] is needed for generating geometry and creating JSON files.

For Ubuntu:

```bash
sudo apt-get install racket
```

[prolog][prolog] is needed for interpreting rules and creating geometry.

For Ubuntu:

```bash
sudo apt-get install swi-prolog
```

## Usage

Use ```make``` from the makefile to create the client program.

Use ```make run``` to run the program.

Use ```make clean``` to clean program.

## Example Run

After compiling, and using ```make run```:

```bash
./cpp/src/geometry_engine
=== Geometry Engine ===
Please add a point: 
X Value: 0
Y Value: 0
Point (0, 0) added.
Please add another point.
X Value: 1
Y Value: 0
Point (1, 0) added.
Would you like to add another point? y/n y
X Value: 1
Y Value: 1
Point (1, 1) added.
Would you like to add another point? y/n y
X Value: 0
Y Value: 1
Point (0, 1) added.
Would you like to add another point? y/n n

=== Scheme Integration ===

Using Scheme to generate points:
Polygon JSON written to output.json
Point: (0.0, 0.0)
Point: (1.0, 0.0)
Point: (1.0, 1.0)
Point: (0.0, 1.0)

=== Prolog Validation ===

geometry.pl written.
queries.pl written.
Polygon is closed
✓ closed_polygon([p1,p2,p3,p4]) succeeded
✗ duplicate_point_values failed
✓ valid_point_count([p1,p2,p3,p4]) succeeded
✗ segments_intersect([s1,s2,s3,s4]) failed
✗ more_than_two_collinear([p1,p2,p3,p4]) failed
✗ all_collinear([p1,p2,p3,p4]) failed

=== C++ Integration ===

Numerical Operations: 

Computing Distances: 
Distance between Point: (0.0, 0.0) and Point: 1.0, 0.0) is: 1
Distance between Point: (1.0, 0.0) and Point: 1.0, 1.0) is: 1
Distance between Point: (1.0, 1.0) and Point: 0.0, 1.0) is: 1
Distance between Point: (0.0, 1.0) and Point: 0.0, 0.0) is: 1
Total perimeter of geometry: 4

Find Centroid/Midpoint: 
The centroid of the polygon is: (0.5, 0.5)

Translation: 
What would you like to translate by in the x-axis? 2
What would you like to translate by in the y-axis? 3
Translating polygon by 2 on the x-axis
Polygon JSON written to output.json
Point: (2.0, 0.0)
Point: (3.0, 0.0)
Point: (3.0, 1.0)
Point: (2.0, 1.0)
Translating polygon by 3 on the y-axis
Polygon JSON written to output.json
Point: (2.0, 3.0)
Point: (3.0, 3.0)
Point: (3.0, 4.0)
Point: (2.0, 4.0)

Find Centroid/Midpoint: 
The centroid of the polygon is: (2.5, 3.5)

What factor would you like to scale by? 2
Scale about the centroid: 
Scale by a factor of 2: 
Polygon JSON written to output.json
Point: (1.5, 2.5)
Point: (3.5, 2.5)
Point: (3.5, 4.5)
Point: (1.5, 4.5)

Computing Distances: 
Distance between Point: (1.5, 2.5) and Point: 3.5, 2.5) is: 2
Distance between Point: (3.5, 2.5) and Point: 3.5, 4.5) is: 2
Distance between Point: (3.5, 4.5) and Point: 1.5, 4.5) is: 2
Distance between Point: (1.5, 4.5) and Point: 1.5, 2.5) is: 2
Total perimeter of geometry: 8

Find Centroid/Midpoint: 
The centroid of the polygon is: (2.5, 3.5)

=== Prolog Validation ===

geometry.pl written.
queries.pl written.
Polygon is closed
✓ closed_polygon([p1,p2,p3,p4]) succeeded
✗ duplicate_point_values failed
✓ valid_point_count([p1,p2,p3,p4]) succeeded
✗ segments_intersect([s1,s2,s3,s4]) failed
✗ more_than_two_collinear([p1,p2,p3,p4]) failed
✗ all_collinear([p1,p2,p3,p4]) failed

=== End of Geometry Engine ===
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

This project is licensed under the MIT License - see the [LICENSE.md](/LICENSE) file for details.