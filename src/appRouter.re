open Mapper;

type state = {route: page};

type action =
  | ChangePage(page);

let component = ReasonReact.reducerComponent("AppRouter");

let make = _children => {
  ...component,
  initialState: () => {
    route: ReasonReact.Router.dangerouslyGetInitialUrl() |> Mapper.toPage
  },
  reducer: (action, _state) =>
    switch action {
    | ChangePage(route) => ReasonReact.Update({route: route})
    },
  didMount: self => {
    let watcherId =
      ReasonReact.Router.watchUrl(browserUrl => {
        /* pattern matching sur type produit */
        let (path, _hash, _search) = (
          browserUrl.path,
          browserUrl.hash,
          browserUrl.search
        );
        let fallbackUrl: ReasonReact.Router.url = {
          path: ["register"],
          hash: "",
          search: ""
        };
        /* TODO: implement loggin system */
        let isUserLoggedIn = true;
        switch (path, isUserLoggedIn) {
        | (["login"], false) =>
          self.send(ChangePage(Mapper.toPage(browserUrl)))
        | (_, true) => self.send(ChangePage(Mapper.toPage(browserUrl)))
        | (_, false) => self.send(ChangePage(Mapper.toPage(fallbackUrl)))
        };
      });
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  render: self =>
    <div>
      (
        switch self.state.route {
        | Login => <Login />
        | Register => <Register />
        | Score => <Score />
        }
      )
    </div>
};