open Sexplib.Std;

[@deriving sexp]
type term_data = {
  has_cursor: bool,
  shape: TermShape.t,
  family: TermFamily.t,
};

[@deriving sexp]
type t =
  | Indent
  | Padding
  | HoleLabel({len: int})
  | Text({
      length: int,
      caret: option(int),
    })
  | Delim({
      index: DelimIndex.t,
      caret: option(Side.t),
    })
  | Op({caret: option(Side.t)})
  | SpaceOp
  | UserNewline
  | OpenChild({is_inline: bool})
  | ClosedChild({is_inline: bool})
  | DelimGroup
  | EmptyLine
  | LetLine
  | Step(int)
  | Term(term_data);

let mk_Delim = (~caret: option(Side.t)=?, ~index: DelimIndex.t, ()): t =>
  Delim({caret, index});
let mk_Op = (~caret: option(Side.t)=?, ()): t => Op({caret: caret});
let mk_Text = (~caret: option(int)=?, ~length: int, ()): t =>
  Text({caret, length});
let mk_Term =
    (~has_cursor=false, ~shape: TermShape.t, ~family: TermFamily.t, ()): t =>
  Term({has_cursor, shape, family});
let mk_OpenChild = (~is_inline: bool, ()) =>
  OpenChild({is_inline: is_inline});
let mk_ClosedChild = (~is_inline: bool, ()) =>
  ClosedChild({is_inline: is_inline});