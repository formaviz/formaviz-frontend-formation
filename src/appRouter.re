open Mapper;

type state = {route: page};
type action =
  | ChangePage(page);

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
        switch (url.hash, MyAppStatus.isUserLoggedIn) {
        | "score" => self.send(ChangePage(Mapper.toPage("score")))
        | ("register", false) =>
          self.send(ChangePage(Mapper.toPage("register")))
        | ("login", false) => self.send(ChangePage(Mapper.toPage("login")))
        | _ => self.send(ChangePage(Mapper.toPage("login")))
        }
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  render: self =>
    <div>
      {switch (self.state.route) {
       | Login => <Login />
       | Register => <Register />
       | Score => <Score />
       }}
    </div>,
};