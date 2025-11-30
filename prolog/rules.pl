closed_polygon(Points) :-
    consecutive_segments(Points),
    first_last_segment(Points),
    writeln('Polygon is closed').

consecutive_segments([A,B|Rest]) :-
    segment(_,A,B),
    consecutive_segments([B|Rest]).
consecutive_segments([_]).

first_last_segment(Points) :-
    last(Points, Last),
    Points = [First|_],
    segment(_,Last,First).


duplicate_point_values :-
    point(P1,X,Y),
    point(P2,X,Y),
    P1 \= P2,
    format('Duplicate coordinates found: ~w and ~w both at (~w,~w), invalid shape.~n', [P1,P2,X,Y]).

valid_point_count(Points) :-
    length(Points, N),
    N >= 3.

orientation(point(_,X1,Y1), point(_,X2,Y2), point(_,X3,Y3), Val) :-
    Val is (Y2 - Y1) * (X3 - X2) - (X2 - X1) * (Y3 - Y2).

segments_intersect(Segments) :-
    member(S1, Segments),
    member(S2, Segments),
    S1 @< S2,             
    segments_intersect_pair(S1,S2),
    writeln("There are overlapping segments, invalid shape.").


segments_intersect_pair(S1,S2) :-
    segment(S1,A,B),
    segment(S2,C,D),
    point(A,X1,Y1), point(B,X2,Y2),
    point(C,X3,Y3), point(D,X4,Y4),
    orientation(point(A,X1,Y1), point(B,X2,Y2), point(C,X3,Y3), O1),
    orientation(point(A,X1,Y1), point(B,X2,Y2), point(D,X4,Y4), O2),
    orientation(point(C,X3,Y3), point(D,X4,Y4), point(A,X1,Y1), O3),
    orientation(point(C,X3,Y3), point(D,X4,Y4), point(B,X2,Y2), O4),
    O1 * O2 < 0,
    O3 * O4 < 0.

collinear(point(_,X1,Y1), point(_,X2,Y2), point(_,X3,Y3)) :-
    Area is X1*(Y2-Y3) + X2*(Y3-Y1) + X3*(Y1-Y2),
    Area =:= 0.

collinear_group(Points, Group) :-
    findall([P1,P2,P3],
        (member(P1,Points),
         member(P2,Points),
         member(P3,Points),
         P1 @< P2, P2 @< P3,
         point(P1,X1,Y1),
         point(P2,X2,Y2),
         point(P3,X3,Y3),
         collinear(point(P1,X1,Y1), point(P2,X2,Y2), point(P3,X3,Y3))),
        Groups),
    Groups \= [],
    Group = Groups.

more_than_two_collinear(Points) :-
    collinear_group(Points, Groups),
    member(G, Groups),
    length(G, N),
    N >= 3,
    format('Collinear points found: ~w~n', [G]).

all_collinear([_,_]).
all_collinear([A,B,C|Rest]) :-
    point(A,X1,Y1), point(B,X2,Y2), point(C,X3,Y3),
    Area is X1*(Y2 - Y3) + X2*(Y3 - Y1) + X3*(Y1 - Y2),
    Area =:= 0,
    all_collinear([B,C|Rest]).