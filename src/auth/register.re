open Config;
let url_dev: string = "http://localhost:8080/";
type state = {
  name: string,
  lastname: string,
  email: string,
  password: string,
  error: string,
};

type action =
  | UpdateNameField(string)
  | UpdateLastNameField(string)
  | UpdateEmailField(string)
  | UpdatePasswordField(string)
  | Register
  | Registered
  | RegisteredFailed(string);

let btnRegisterCss = ReactDOMRe.Style.make(~paddingBottom="20px", ());

let component = ReasonReact.reducerComponent("Register");

let register = state => {
  let payload = Js.Dict.empty();
  Js.Dict.set(payload, "email", Js.Json.string(state.email));
  Js.Dict.set(payload, "password", Js.Json.string(state.password));
  Js.Dict.set(payload, "name", Js.Json.string(state.name));
  Js.Dict.set(payload, "lastname", Js.Json.string(state.lastname));
  Js.Promise.(
    Fetch.fetchWithInit(
      url_back ++ "/signup",
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
         json |> Decoder.decodeProfile |> (user => Some(user) |> resolve)
       )
  );
};

let make = _children => {
  ...component,
  initialState: () => {
    email: "",
    password: "",
    name: "",
    lastname: "",
    error: "",
  },
  reducer: (action, state) =>
    switch (action) {
    | UpdateEmailField(email) => ReasonReact.Update({...state, email})
    | UpdateLastNameField(lastname) =>
      ReasonReact.Update({...state, lastname})
    | UpdateNameField(name) => ReasonReact.Update({...state, name})
    | UpdatePasswordField(password) =>
      ReasonReact.Update({...state, password})
    | Register =>
      ReasonReact.UpdateWithSideEffects(
        state,
        (
          self =>
            Js.Promise.(
              register(state)
              |> then_(result =>
                   switch (result) {
                   | Some(_) => resolve(self.send(Registered))
                   | None =>
                     resolve(
                       self.send(RegisteredFailed("User not registered")),
                     )
                   }
                 )
              |> catch(_err =>
                   Js.Promise.resolve(
                     self.send(RegisteredFailed("User not registered")),
                   )
                 )
              |> ignore
            )
        ),
      )
    | Registered =>
      ReasonReact.SideEffects((_ => ReasonReact.Router.push("login")))
    | RegisteredFailed(err) => ReasonReact.Update({...state, error: err})
    },
  render: self =>
    <div className="card align-middle mx-auto w-50 p-3 text-center">
      <form>
        <div className="card-header">
          (ReasonReact.string("Enregistrement"))
        </div>
        <div className="card-body">
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value=self.state.lastname
              placeholder="Nom"
              onChange=(
                event =>
                  self.send(
                    UpdateLastNameField(
                      ReactEvent.Form.target(event)##value,
                    ),
                  )
              )
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value=self.state.name
              placeholder={js|Prénom|js}
              onChange=(
                event =>
                  self.send(
                    UpdateNameField(ReactEvent.Form.target(event)##value),
                  )
              )
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="text"
              value=self.state.email
              placeholder="Email"
              onChange=(
                event =>
                  self.send(
                    UpdateEmailField(ReactEvent.Form.target(event)##value),
                  )
              )
            />
          </div>
          <div className="input-group mb-3">
            <input
              className="form-control"
              type_="password"
              value=self.state.password
              onChange=(
                event =>
                  self.send(
                    UpdatePasswordField(
                      ReactEvent.Form.target(event)##value,
                    ),
                  )
              )
              placeholder="Mot de passe"
            />
          </div>
        </div>
      </form>
      <div className="justify-content-center" style=btnRegisterCss>
        <button
          className="btn btn-outline-primary"
          onClick=(_ => self.send(Register))>
          (ReasonReact.string("S'enregistrer"))
        </button>
      </div>
      <div className="card-footer text-muted">
        <label> (ReasonReact.string({js|Déjà un compte ?|js})) </label>
        <a href="login"> (ReasonReact.string(" Se connecter")) </a>
      </div>
      <div> (ReasonReact.string(self.state.error)) </div>
    </div>,
};