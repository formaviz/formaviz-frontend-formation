open DecodeRating;

module RenderRating = {
  let component = ReasonReact.statelessComponent("renderRating");
  let make = (~rating, _) => {
    ...component,
    render: _ =>
      <div className="item">
        <div>
          {ReasonReact.string("Note : ")}
          {ReasonReact.string(string_of_int(rating.score))}
        </div>
        <div>
          {ReasonReact.string("Commentaire : ")}
          {ReasonReact.string(rating.comment)}
        </div>
      </div>,
  };
};
