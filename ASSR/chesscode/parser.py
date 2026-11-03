from tree_sitter import Language, Parser, Query, QueryCursor
import tree_sitter_pgn as ts_pgn

PGN_LANGUAGE = Language(ts_pgn.language())

PARSER = Parser(PGN_LANGUAGE)

# Query for game boundaries and main-line moves.
# Ignore all headers, comments, variations, and result codes.
QUERY = Query(
    PGN_LANGUAGE,
    """
    (series_of_games
      game: (game) @game)

    (game
      (movetext
        san_move: (san_move) @san_move))
    """,
)


def emit_output(main_line: list[bytes | None]) -> None:
    if not main_line:
        return
    # eg: d4 d5 c4 c6 Nc3 Nf6 Nf3 e6 e3 Nbd7 Bd3 dc4
    print(' '.join(x.decode().strip() for x in main_line if x is not None))


def main() -> None:
    with open('chess.pgn', 'rb') as file:
        tree = PARSER.parse(file.read())

    query_cursor = QueryCursor(QUERY)
    matches = query_cursor.matches(tree.root_node)

    main_line: list[bytes | None] = []
    for item in matches:
        if item[1].get('game'):
            emit_output(main_line)
            main_line = []
            continue
        if nodes := item[1].get('san_move'):
            main_line.append(nodes[0].text)
            continue

    emit_output(main_line)


if __name__ == '__main__':
    main()
