open NavBarCss;

type state = {yolo: string};

type action =
  | GoToLogin
  | GoToRegister
  | GoToCreate;

let component = ReasonReact.reducerComponent("navBar");

let make = _children => {
  ...component,
  initialState: () => {yolo: "test"},
  reducer: (action, state) =>
    switch (action) {
    | GoToLogin =>
      ReasonReact.SideEffects(_ => ReasonReact.Router.push("login"))
    | GoToRegister =>
      ReasonReact.SideEffects(_ => ReasonReact.Router.push("register"))
    | GoToCreate =>
      ReasonReact.SideEffects(_ => ReasonReact.Router.push("register"))
    | _ => ReasonReact.NoUpdate
    },
  render: self =>
    <nav className="card navbar" style=navBarCss>
      <a className="navbar-brand"> {ReasonReact.string("Formaviz")} </a>
      <button className="navbar-toggler" style=btnCSS href="login">
        {ReasonReact.string("Login")}
        <span className="navbar-toggler-icon" />
      </button>
      <button className="navbar-toggler" style=btnCSS href="register">
        {ReasonReact.string("Register")}
        <span className="navbar-toggler-icon" />
      </button>
      <button className="navbar-toggler" style=btnCSS href="createTraining">
        {ReasonReact.string("create")}
        <span className="navbar-toggler-icon" />
      </button>
    </nav>,
};