open NavBarCss;

let component = ReasonReact.statelessComponent("navBar");

[@bs.module] external logo: string = "./assets/logo.png";

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
      <div style=logoContainerCSS>
        <img src=logo style=logoCSS alt="logo" />
        {ReasonReact.string("Formaviz")}
      </div>
      <div className="collapse navbar-collapse" id="navbarSupportedContent">
        <ul className="navbar-nav mr-auto">
          <li className="nav-item">
            <a className="btn nav-link" style=btnNav href="login">
              {ReasonReact.string("Login")}
            </a>
          </li>
          <li className="nav-item">
            <a className="btn nav-link" style=btnNav href="register">
              {ReasonReact.string("Register")}
            </a>
          </li>
          <li className="nav-item">
            <a className="btn nav-link" style=btnNav href="createTraining">
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