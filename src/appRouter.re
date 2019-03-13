open Mapper;
open NavBar;
open SessionUser;

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
      ReasonReact.Router.watchUrl(url => {
        let (path, _hash, _search) = (url.path, url.hash, url.search);
        let fallback: ReasonReact.Router.url = {
          path: ["register"],
          hash: "",
          search: "",
        };
        switch (path, isConnected) {
        | (["login"], false) => self.send(ChangePage(Mapper.toPage(url)))
        | (_, true) => self.send(ChangePage(Mapper.toPage(url)))
        | (_, false) => self.send(ChangePage(Mapper.toPage(fallback)))
        };
      });
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  render: self =>
    <div>
      {switch (self.state.route) {
       | Login => <Login />
       | Register => <Register />
       | Score => <Score />
       | CreateTraining => <CreateTraining />
       | ConsultationFormation(idFormation) =>
         <ConsultationFormation idFormation />
       | ListeFormation => <ListeFormation />
       }}
    </div>,
};