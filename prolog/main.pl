:- consult('geometry.pl').
:- consult('rules.pl').

run_query_from_file(File) :-
    open(File, read, Stream),
    repeat,
        read(Stream, Query),
        ( Query == end_of_file ->
            close(Stream), !
        ;
            ( call(Query) ->
                format('✓ ~w succeeded~n', [Query])
            ;
                format('✗ ~w failed~n', [Query])
            ),
            fail
        ).

