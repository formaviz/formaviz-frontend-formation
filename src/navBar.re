open NavBarCss;

let component = ReasonReact.statelessComponent("navBar");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = _children => {
  ...component,
  render: _self =>
    <nav className="card navbar" style=navBarCss>
      <a className="navbar-brand"> {ReasonReact.string("Formaviz")} </a>
      <button className="navbar-toggler" style=btnCSS>
        {ReasonReact.string("test")}
        <span className="navbar-toggler-icon" />
      </button>
      <button className="navbar-toggler" style=btnCSS>
        {ReasonReact.string("test")}
        <span className="navbar-toggler-icon" />
      </button>
      <button className="navbar-toggler" style=btnCSS>
        {ReasonReact.string("test")}
        <span className="navbar-toggler-icon" />
      </button>
    </nav>,
};