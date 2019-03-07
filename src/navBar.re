open NavBarCss;

type state = {yolo: string};

type action =
  | GoToLogin
  | GoToRegister
  | GoToCreate;

let component = ReasonReact.statelessComponent("navBar");

let make = _children => {
  ...component,
  /*initialState: () => {yolo: ""},
    reducer: (action, _) =>
      switch (action) {
      | GoToLogin =>
        ReasonReact.SideEffects(_ => ReasonReact.Router.push("login"))
      | GoToRegister =>
        ReasonReact.SideEffects(_ => ReasonReact.Router.push("register"))
      | GoToCreate =>
        ReasonReact.SideEffects(_ => ReasonReact.Router.push("register"))
      | _ => ReasonReact.NoUpdate
      },*/
  render: self =>
    <nav className="card navbar navbar-expand-lg" style=navBarCss>
      <a className="navbar-brand"> {ReasonReact.string("Formaviz")} </a>
      <div className="collapse navbar-collapse" id="navbarSupportedContent">
        <ul className="navbar-nav mr-auto">
          <li className="nav-item">
            <a className="nav-link" href="login">
              {ReasonReact.string("Login")}
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="register">
              {ReasonReact.string("Register")}
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="createTraining">
              {ReasonReact.string("create")}
            </a>
          </li>
        </ul>
      </div>
    </nav>,
  /*<button className="navbar-toggler" style=btnCSS href="login">
      {ReasonReact.string("Login")}
      <span className="navbar-toggler-icon" />
    </button>
    <button className="navbar-toggler" style=btnCSS href="register">
      {ReasonReact.string("Register")}
      <span className="navbar-toggler-icon" />
    </button>
    <button
      className="navbar-toggler" style=btnCSS href="createTraining">
      {ReasonReact.string("create")}
      <span className="navbar-toggler-icon" />
    </button>*/
};