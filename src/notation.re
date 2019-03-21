open DecodeRating;
open Config;
open Rating;

%raw
"import './notation.css'";

let containerBtn =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flexDirection="column",
    ~width="100%",
    (),
  );

type action =
  | Loaded(list(DecodeRating.ratingResponse))
  | UpdateComment(string)
  | UpdateRate(int)
  | ErrorSend(string)
  | Success
  | SendRate;

type state = {
  ratingResponse: DecodeRating.ratingResponse,
  listRating: list(DecodeRating.ratingResponse),
  error: string,
};

let component = ReasonReact.reducerComponent("notation");

let make = (_children, ~idFormation) => {
  let ratingResp = {
    idRating: "",
    comment: "",
    score: 0,
    idTraining: idFormation,
  };
  let getRating = self => {
    let payload = Js.Dict.empty();
    Js.Promise.(
      Fetch.fetchWithInit(
        Config.url_back ++ "/rates?idTraining=" ++ idFormation,
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=
            Fetch.HeadersInit.make({
              "Content-Type": "application/json",
              "Authorization": "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6IlFVVXlSa1JCUWpJMU5rTTJRVEZFTWpaQ05qSkNNa1k0UmpCRVFUVXlRVEUwUlVGRlJVRTFOZyJ9.eyJpc3MiOiJodHRwczovL2Zvcm1hdml6ei5ldS5hdXRoMC5jb20vIiwic3ViIjoiYXV0aDB8MTBkOWZkNmYtZjJiNi00YjJiLTkxMjItZjhjYzBhYTc4NTA4IiwiYXVkIjpbImh0dHBzOi8vZm9ybWF2aXp6L2FwaS92MiIsImh0dHBzOi8vZm9ybWF2aXp6LmV1LmF1dGgwLmNvbS91c2VyaW5mbyJdLCJpYXQiOjE1NTMxMzUzNjIsImV4cCI6MTU1MzIyMTc2MiwiYXpwIjoiNENoMXl3aUptWjQyc3lBSWR6ald5UHdSa3hobHFPczIiLCJzY29wZSI6Im9wZW5pZCBwcm9maWxlIGVtYWlsIGFkZHJlc3MgcGhvbmUiLCJndHkiOiJwYXNzd29yZCIsInBlcm1pc3Npb25zIjpbXX0.a6yISblTHOeyY1TNVpP1rX8piugJ9QKMYhN9OFCtYxrZcNkr0PU3FynvSD3kkIl89hedkamTen-AgP7DVwoJuRqxtY4w9BGUTfgQlpOd1zMCEhdv8dLc-LWkPeaYPCDa2vjFAxrCEt666lYkKA_OSsDtu_MyRH_uIh0AHn3qZi3KWxlJbsKGtYUzuu2JQ43KRxQtbnUZJQ9em7PFwgfiE_s3tsvHC1p_FFSv2ocMjxviiLEs_tzCToZs2bH2V4IfEayP8AvCJAvo6L21X1lA8LzJqM-wvw_TkUDEXEdQ_99x1ouZIN1OT5L0q92HtxTbBoHxx1UvCJJjM5wBN06J9w",
            }),
          (),
        ),
      )
      |> Js.Promise.then_(Fetch.Response.json)
      |> Js.Promise.then_(json =>
           json
           |> DecodeRating.decodeResponse
           |> (result => self.ReasonReact.send(Loaded(result.ratings)))
           |> Js.log
           |> resolve
         )
    )
    |> ignore;
  };
  let sendRating = state => {
    Js.Promise.(
      Fetch.fetchWithInit(
        url_back ++ "/rates",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              Js.Json.stringify(
                DecodeRating.encodeRating(state.ratingResponse),
              ),
            ),
          ~headers=
            Fetch.HeadersInit.make({
              "Content-Type": "application/json",
              "Authorization": "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6IlFVVXlSa1JCUWpJMU5rTTJRVEZFTWpaQ05qSkNNa1k0UmpCRVFUVXlRVEUwUlVGRlJVRTFOZyJ9.eyJpc3MiOiJodHRwczovL2Zvcm1hdml6ei5ldS5hdXRoMC5jb20vIiwic3ViIjoiYXV0aDB8ODQyOGZlMGMtODEzMi00NDM0LWE2ZWItNzI1N2E4OWRmZDBmIiwiYXVkIjpbImh0dHBzOi8vZm9ybWF2aXp6L2FwaS92MiIsImh0dHBzOi8vZm9ybWF2aXp6LmV1LmF1dGgwLmNvbS91c2VyaW5mbyJdLCJpYXQiOjE1NTMxODk3NTgsImV4cCI6MTU1MzI3NjE1OCwiYXpwIjoiNENoMXl3aUptWjQyc3lBSWR6ald5UHdSa3hobHFPczIiLCJzY29wZSI6Im9wZW5pZCBwcm9maWxlIGVtYWlsIGFkZHJlc3MgcGhvbmUiLCJndHkiOiJwYXNzd29yZCIsInBlcm1pc3Npb25zIjpbXX0.BhRFfUxV1ZUY0ZYpJXoHfBJat3eqDqLtPzaNauusdb1Li8e-vgxF0YsuuYX4gEMt6eDuWdQuSPaYlvygDe_1AMY0RooDAgzuqZO0YQ4IVxDEVHcoyHRd6QFoWooMher8Ce0jxV_bh1oP4kcCKtbY2CpKwF10FPEm3IRKYg9SeJ-XEtNWSo4M1rG3cZVmks9atASLa50pzzdMOzI0mTiJ-cwfzphmKJVWLFwmSuodJyw5KCyirQc_w_nS7r8SfdRiSqZKq3j0peHjmp6pmn_76CiVvkUl-m2kvOWJjy-1CK7X_NcbY0a_ATsDPtxrapb73BcJ7jFlwROIMif_QVqf9Q",
            }),
          (),
        ),
      )
      |> then_(Fetch.Response.json)
      |> then_(json =>
           json
           |> DecodeRating.decodeResponse
           |> (resp => Some(resp) |> resolve)
         )
    );
  };
  {
    ...component,
    initialState: () => {
      ratingResponse: ratingResp,
      listRating: [],
      error: "",
    },
    reducer: (action, state) =>
      switch (action) {
      | UpdateRate(score) =>
        ReasonReact.Update({
          ...state,
          ratingResponse: {
            ...state.ratingResponse,
            score,
          },
        })
      | UpdateComment(comment) =>
        ReasonReact.Update({
          ...state,
          ratingResponse: {
            ...state.ratingResponse,
            comment,
          },
        })
      | SendRate =>
        ReasonReact.UpdateWithSideEffects(
          state,
          self =>
            Js.Promise.(
              sendRating(state)
              |> then_(result =>
                   switch (result) {
                   | Some(result) => resolve(self.send(Success))
                   | None =>
                     Js.Promise.resolve(self.send(ErrorSend("Erreur")))
                   }
                 )
              |> catch(_err =>
                   Js.Promise.resolve(
                     self.send(
                       ErrorSend({js|Vous avez déjà commenté.|js}),
                     ),
                   )
                 )
              |> ignore
            ),
        )
      | Loaded(listRating) => ReasonReact.Update({...state, listRating})
      | Success =>
        ReasonReact.Update({
          ...state,
          listRating: [
            {
              idRating: state.ratingResponse.idRating,
              score: state.ratingResponse.score,
              comment: state.ratingResponse.comment,
              idTraining: idFormation,
            },
            ...state.listRating,
          ],
        })
      | ErrorSend(error) => ReasonReact.Update({...state, error})
      | _ => ReasonReact.NoUpdate
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
                  value={_self.state.ratingResponse.comment}
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
                   string_of_int(_self.state.ratingResponse.score) ++ "/5",
                 )}
              </label>
            </div>
            <div style=containerBtn>
              <button
                className="btn btn-outline-primary"
                onClick={_ => _self.send({SendRate})}>
                {ReasonReact.string("Ajout d'un commentaire")}
              </button>
              <label> {ReasonReact.string(_self.state.error)} </label>
            </div>
          </div>
        </div>
      </div>,
  };
};
