module App = {
  let component = ReasonReact.statelessComponent("Formaviz-Formation");
  let make = _children => {...component, render: _self => <AppRouter />};
};

ReactDOMRe.renderToElementWithId(<App />, "main");