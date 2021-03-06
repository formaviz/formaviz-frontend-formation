open Config;
type state = {
  email: string,
  password: string,
  error: string,
  isUserConnected: bool,
};

type action =
  | UpdateEmailField(string)
  | UpdatePasswordField(string)
  | Login
  | LoggedIn
  | NotLoggedIn(string);

let login = state => {
  let payload = Js.Dict.empty();

  Js.Dict.set(payload, "password", Js.Json.string(state.password));
  Js.Dict.set(payload, "email", Js.Json.string(state.email));
  Js.Promise.(
    Fetch.fetchWithInit(
      url_back ++ "/login",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> UserDecoder.decodeUserLogin
         |> (user => Some(user) |> resolve)
       )
  );
};

let btnLoginCss = ReactDOMRe.Style.make(~paddingBottom="20px", ());

let component = ReasonReact.reducerComponent("login");

let make = _children => {
  ...component,
  initialState: () => {
    email: "",
    password: "",
    error: "",
    isUserConnected: false,
  },
  reducer: (action, state) =>
    switch (action) {
    | UpdateEmailField(email) => ReasonReact.Update({...state, email})
    | UpdatePasswordField(password) =>
      ReasonReact.Update({...state, password})
    | Login =>
      ReasonReact.UpdateWithSideEffects(
        state,
        self =>
          Js.Promise.(
            login(state)
            |> then_(result =>
                 switch (result) {
                 | Some(_) => resolve(self.send(LoggedIn))
                 | None =>
                   resolve(
                     self.send(NotLoggedIn("Error : Bad credentials")),
                   )
                 }
               )
            |> catch(_err =>
                 Js.Promise.resolve(
                   self.send(NotLoggedIn("Error : Bad credentials")),
                 )
               )
            |> ignore
          ),
      )
    | LoggedIn =>
      ReasonReact.SideEffects(_ => ReasonReact.Router.push("liste"))
    | NotLoggedIn(error) => ReasonReact.Update({...state, error})
    },
  render: _self =>
    <div className="card align-middle mx-auto w-50 p-3 text-center">
      <form>
        <div className="card-header"> {ReasonReact.string("Connexion")} </div>
        <div className="card-body">
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value={_self.state.email}
              placeholder="Email"
              onChange={event =>
                _self.send(
                  UpdateEmailField(ReactEvent.Form.target(event)##value),
                )
              }
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="password"
              value={_self.state.password}
              onChange={event =>
                _self.send(
                  UpdatePasswordField(ReactEvent.Form.target(event)##value),
                )
              }
              placeholder="Mot de passe"
            />
          </div>
        </div>
      </form>
      <div className="justify-content-center" style=btnLoginCss>
        <button
          className="btn btn-outline-primary"
          onClick={_ => _self.send(Login)}>
          {ReasonReact.string("Connexion")}
        </button>
      </div>
      <div className="
          card-footer text-muted">
        <label> {ReasonReact.string("Pas encore de compte ?")} </label>
        <a href="register"> {ReasonReact.string("S'inscrire")} </a>
      </div>
      <label> {ReasonReact.string(_self.state.error)} </label>
    </div>,
};
