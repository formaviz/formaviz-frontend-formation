type comment = {
  idComment: int,
  rate: int,
  content: string,
};

module RenderComment = {
  let component = ReasonReact.statelessComponent("renderComment");
  let make = (~comment, _) => {
    ...component,
    render: _ =>
      <div className="item">
        <div>
          {ReasonReact.string("Note : ")}
          {ReasonReact.string(string_of_int(comment.rate))}
        </div>
        <div>
          {ReasonReact.string("Commentaire : ")}
          {ReasonReact.string(comment.content)}
        </div>
      </div>,
  };
};
