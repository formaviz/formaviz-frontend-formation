open Comment;

%raw
"import './notation.css'";

type action =
  | UpdateComment(string)
  | UpdateRate(int)
  | SendRate;

type state = {
  comment: string,
  rate: int,
  listComment: list(Comment.comment),
};

let component = ReasonReact.reducerComponent("notation");

let newComment = state => {
  {idComment: 0, rate: state.rate, content: state.comment};
};

let make = _children => {
  ...component,
  initialState: () => {comment: "", rate: 0, listComment: []},
  reducer: (action, state) =>
    switch (action) {
    | UpdateRate(rate) => ReasonReact.Update({...state, rate})
    | UpdateComment(comment) => ReasonReact.Update({...state, comment})
    | SendRate =>
      ReasonReact.Update({
        ...state,
        listComment: [
          {idComment: 0, rate: state.rate, content: state.comment},
          ...state.listComment,
        ],
      })
    },
  render: _self =>
    <div>
      <div className="card align-middle p-3 text-center">
        <div className="card-header">
          <label> {ReasonReact.string("Avis :")} </label>
        </div>
        <div className="card-body">
          {ReasonReact.array(
             Array.of_list(
               List.map(
                 comment => <RenderComment comment />,
                 _self.state.listComment,
               ),
             ),
           )}
        </div>
      </div>
      <div className="card align-middle p-3 text-center">
        <div className="card-header">
          <label> {ReasonReact.string("Donner votre avis :")} </label>
        </div>
        <div className="card-body">
          <form>
            <div className="input-group mb-3">
              <span className="input-group-text" id="">
                {ReasonReact.string("Commentaire :")}
              </span>
              <input
                className="form-control"
                type_="text"
                value={_self.state.comment}
                onChange={event =>
                  _self.send(
                    UpdateComment(ReactEvent.Form.target(event)##value),
                  )
                }
              />
            </div>
          </form>
          <div className="rating">
            <a
              id="1"
              onClick={_ => _self.send(UpdateRate(1))}
              title="Give 5 stars">
              {ReasonReact.string(".")}
            </a>
            <a
              id="2"
              onClick={_ => _self.send(UpdateRate(2))}
              title="Give 4 stars">
              {ReasonReact.string(".")}
            </a>
            <a
              id="3"
              onClick={_ => _self.send(UpdateRate(3))}
              title="Give 3 stars">
              {ReasonReact.string(".")}
            </a>
            <a
              id="4"
              onClick={_ => _self.send(UpdateRate(4))}
              title="Give 2 stars">
              {ReasonReact.string(".")}
            </a>
            <a
              id="5"
              onClick={_ => _self.send(UpdateRate(5))}
              title="Give 1 star">
              {ReasonReact.string(".")}
            </a>
            <label>
              {ReasonReact.string(string_of_int(_self.state.rate) ++ "/5")}
            </label>
          </div>
          <button
            className="btn btn-outline-primary"
            onClick={_ => _self.send({SendRate})}>
            {ReasonReact.string("Ajout d'un commentaire")}
          </button>
        </div>
      </div>
    </div>,
};
