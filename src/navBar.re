open NavBarCss;

[@bs.module] external logo : string = "./assets/logo.png";

type action =
  | GoToLogin
  | GoToRegiser
  | GoToCreate;

let component = ReasonReact.statelessComponent("navbar");

let make = _children => {
  ...component /*initialState: () => {},x
    reducer: (action, _) =>
      switch (action) {
      | GoToLogin =>
        ReasonReact.SideEffects(_ => ReasonReact.Router.push("login"))
      | GoToRegiser =>
        ReasonReact.SideEffects(_ => ReasonReact.Router.push("register"))
      | GoToCreate =>
        ReasonReact.SideEffects(_ => ReasonReact.Router.push("create"))
      },*/,
  render: _self =>
    <nav className="card navbar navbar-expand-lg" style=navBarCss>
      <div style=logoContainerCSS>
        <img src=logo style=logoCSS alt="logo" />
        <div style=titleCSS> (ReasonReact.string("Formaviz")) </div>
      </div>
      <div className="collapse navbar-collapse" id="navbarSupportedContent">
        <ul className="navbar-nav mr-auto">
          <li className="nav-item">
            <a className="btn nav-link" style=btnNav href="login">
              (ReasonReact.string("Se connecter "))
            </a>
          </li>
          <li className="nav-item">
            <a className="btn nav-link" style=btnNav href="register">
              (ReasonReact.string("S'enregister "))
            </a>
          </li>
          <li className="nav-item">
            <a className="btn nav-link" style=btnNav href="createTraining">
              (ReasonReact.string("Creation de formation"))
            </a>
          </li>
          <li className="nav-item">
            <a className="btn nav-link" style=btnNav href="liste">
              (ReasonReact.string("Consultation de formation"))
            </a>
          </li>
        </ul>
      </div>
    </nav>,
};