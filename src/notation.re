[%%raw "import './notation.css'"];

type action =
  | UpdateComment(string)
  | UpdateRate(int)
  | SendRate;

type state = {
    comment:string,
    rate:int
}
let component = ReasonReact.reducerComponent("notation");

let make = (_children) => {
  ...component,
  initialState: () => {
     comment: "",
     rate: 0,
  },
  reducer: (action, state) =>
    switch (action) {
      |UpdateRate(rate) => ReasonReact.Update({...state,rate})
      |UpdateComment(comment) => ReasonReact.Update({...state,comment})
      |SendRate => ReasonReact.NoUpdate
    },
  render: _self =>
    <div className="card align-middle mx-auto w-50 p-3 text-center">
        <div className="card-header">  
            <label>{ReasonReact.string("Notation")}  </label>
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
                <a id="1" onClick={event => _self.send(UpdateRate(1))} title="Give 5 stars">{ReasonReact.string(".")}
                </a>
                <a id="2" onClick={event => _self.send(UpdateRate(2))} title="Give 4 stars">{ReasonReact.string(".")}
                </a>
                <a id="3" onClick={event => _self.send(UpdateRate(3))} title="Give 3 stars">{ReasonReact.string(".")}
                </a>
                <a id="4" onClick={event => _self.send(UpdateRate(4))} title="Give 2 stars">{ReasonReact.string(".")}
                </a>
                <a id="5" onClick={event => _self.send(UpdateRate(5))} title="Give 1 star">{ReasonReact.string(".")}
                </a>
                <label> {ReasonReact.string(string_of_int(_self.state.rate)++"/5")}</label>
            </div>
            <button
                className="btn btn-outline-primary"
                onClick={_ => _self.send({SendRate})}>
                {ReasonReact.string("Ajout d'un commentaire")}
            </button>
        </div>
  </div>,
};