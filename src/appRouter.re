open Mapper;
open NavBar;

type state = {route: page};
type action =
  | ChangePage(page);

let styleRouter =
  ReactDOMRe.Style.make(~backgroundColor="#444444", ~height="100vh", ());

let component = ReasonReact.reducerComponent("AppRouter");
let make = _children => {
  ...component,
  initialState: () => {
    route: ReasonReact.Router.dangerouslyGetInitialUrl() |> Mapper.toPage,
  },
  reducer: (action, _state) =>
    switch (action) {
    | ChangePage(route) => ReasonReact.Update({route: route})
    },
  didMount: self => {
    let watcherId =
      ReasonReact.Router.watchUrl(url =>
        switch (url.path, false) {
        | (["score"], true) => Js.log("")
        | (["score"], false) => Js.log("")
        | (["register"], false) =>
          self.send(ChangePage(Mapper.toPage(url)))
        | (["login"], false) => self.send(ChangePage(Mapper.toPage(url)))
        | _ => self.send(ChangePage(Mapper.toPage(url)))
        }
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  render: self =>
    <div style=styleRouter>
      <NavBar />
      {switch (self.state.route) {
       | Login => <Login />
       | Register => <Register />
       | Score => <Score />
       | CreateTraining => <CreateTraining />
       }}
    </div>,
};