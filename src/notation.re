open DecodeRating;
open Config;
open Rating;

%raw
"import './notation.css'";

type action =
  | Loaded(list(DecodeRating.ratingType))
  | UpdateComment(string)
  | UpdateRate(int)
  | SendRate;

type state = {
  ratingResponse: DecodeRating.ratingType,
  listRating: list(DecodeRating.ratingResponse),
};

let ratingResp = {
  idRating: "",
  comment: "",
  score: 0,
  trainingId: "",
  userOfRating: "",
};

let ratingInit = {rating: ratingResp};

let component = ReasonReact.reducerComponent("notation");

let make = (_children, ~idFormation) => {
  let getRating = self => {
    let payload = Js.Dict.empty();
    Js.Promise.(
      Fetch.fetchWithInit(
        Config.url_back ++ "/rates/" ++ idFormation,
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=
            Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          (),
          ~body=
          Fetch.BodyInit.make("{\"idTraining\":\"637c7f88-581e-4cc6-8864-988213e10d5d\"}"),
        ),
      )
      |> Js.Promise.then_(Fetch.Response.json)
      |> Js.Promise.then_(json =>
           json
           |> DecodeRating.decodeResponse
           |> (result => self.ReasonReact.send(Loaded(result.ratings)))
           |> resolve
         )
    )
    |> ignore;
  };
  {
    ...component,
    initialState: () => {ratingResponse: ratingInit, listRating: []},
    reducer: (action, state) =>
      switch (action) {
      | UpdateRate(score) => ReasonReact.Update({...state, ratingResponse:{rating:{...state.ratingResponse.rating,score}}})
      | UpdateComment(comment) =>
        ReasonReact.Update({...state, ratingResponse:{rating:{...state.ratingResponse.rating, comment}}})
      | SendRate =>
        ReasonReact.Update({
          ...state,
          listRating: [
            {
              idRating: state.ratingResponse.rating.idRating,
              score: state.ratingResponse.rating.score,
              comment: state.ratingResponse.rating.comment,
              trainingId: idFormation,
              userOfRating:"",
            },
            ...state.listRating,
          ],
        })
      },
    didMount: self => getRating(self),
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
                   rating => <RenderRating rating />,
                   _self.state.listRating,
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
                  value={_self.state.ratingResponse.rating.comment}
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
                {ReasonReact.string(
                   string_of_int(_self.state.ratingResponse.rating.score)
                   ++ "/5",
                 )}
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
};